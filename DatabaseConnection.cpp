#include "DatabaseConnection.h"

const char * DatabaseConnection::filename = "database.db";

DatabaseConnection::DatabaseConnection() {
	open();
}

DatabaseConnection::~DatabaseConnection() {
	close();
}

void DatabaseConnection::open() {
	sqlite3_open(filename, &db);
}

void DatabaseConnection::close() {
	sqlite3_close(db);
}

void DatabaseConnection::reset() {
	sqlite3_reset(statement);
}

void DatabaseConnection::finalize() {
	sqlite3_finalize(statement);
}

void DatabaseConnection::execute(char * query) {
	int prepare = sqlite3_prepare_v2(db, query, -1, &statement, 0);

	if(prepare != SQLITE_OK)
		throw DatabaseConnectionException(prepare);

	isPrepared = true;

	for(int i = 0; i < columnCount(); i++) {
		columns.push_back(string(sqlite3_column_name(statement, i)));
	}

	next();
}

bool DatabaseConnection::next() {
	if(!isPrepared)
		throw DatabaseConnectionException(DatabaseConnectionException::IS_NOT_PREPARED);

	step = sqlite3_step(statement);

	if(step != SQLITE_ROW)
		return false;

	return true;
}

int DatabaseConnection::columnNum(char * colName) {
	if(!isPrepared)
		throw DatabaseConnectionException(DatabaseConnectionException::IS_NOT_PREPARED);

	for(int i = 0; i < columnCount(); i++) {
		string dbCol = string(sqlite3_column_name(statement, i));
		string inCol = string(colName);
		if(dbCol == inCol)
			return i;
	}

	return -1;
}

list<string> DatabaseConnection::getColumns() {
	return columns;
}

string DatabaseConnection::getColumn(char * colName) {
	if(!isPrepared)
		throw DatabaseConnectionException(DatabaseConnectionException::IS_NOT_PREPARED);

	int index = columnNum(colName);

	if(index == -1)
		throw DatabaseConnectionException(DatabaseConnectionException::COLUMN_NOT_FOUND);

	return string((char*)sqlite3_column_text(statement, index));
}

int DatabaseConnection::columnCount() {
	if(!isPrepared)
		throw DatabaseConnectionException(DatabaseConnectionException::IS_NOT_PREPARED);

	return sqlite3_column_count(statement);
}

list<multimap<string, string> > DatabaseConnection::fetchAll() {
	if(!isPrepared)
		throw DatabaseConnectionException(DatabaseConnectionException::IS_NOT_PREPARED);

	list<multimap<string, string> > results;
	reset();

	int cols = sqlite3_column_count(statement);
	int step = sqlite3_step(statement);
	while(step == SQLITE_ROW) {
		multimap<string, string> row;
		for(int col = 0; col < cols; col++) {
			string colName = string(sqlite3_column_name(statement, col));
			string rowValue = string((char*)sqlite3_column_text(statement, col));
			row.insert(pair<string, string>(colName, rowValue));
		}

		results.push_back(row);

		step = sqlite3_step(statement);
	}

	return results;
}