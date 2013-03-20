#include "DatabaseConnection.h"

const char * DatabaseConnection::filename = "database.db";

DatabaseConnection::DatabaseConnection() {
	open();
	step = -1;
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
	step = -1;
	sqlite3_reset(statement);
}

void DatabaseConnection::finalize() {
	step = -1;
	sqlite3_finalize(statement);
}

void DatabaseConnection::execute(char * query) {
	int prepare = sqlite3_prepare_v2(db, query, -1, &statement, 0);

	if(prepare != SQLITE_OK)
		throw DatabaseConnectionException(prepare, __LINE__);

	isPrepared = true;

	for(int i = 0; i < columnCount(); i++) {
		columns.push_back(string(sqlite3_column_name(statement, i)));
	}

	next();
}

bool DatabaseConnection::next() {
	if(!isPrepared)
		throw DatabaseConnectionException(DatabaseConnectionException::IS_NOT_PREPARED, __LINE__);

	step = sqlite3_step(statement);

	if(step != SQLITE_ROW)
		return false;

	return true;
}

int DatabaseConnection::columnNum(char * colName) {
	if(!isPrepared)
		throw DatabaseConnectionException(DatabaseConnectionException::IS_NOT_PREPARED, __LINE__);

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
		throw DatabaseConnectionException(DatabaseConnectionException::IS_NOT_PREPARED, __LINE__);

	if(step != SQLITE_ROW) {
		if(!next())
			throw DatabaseConnectionException(DatabaseConnectionException::NO_ROW, __LINE__);
	}

	int index = columnNum(colName);

	if(index == -1)
		throw DatabaseConnectionException(DatabaseConnectionException::COLUMN_NOT_FOUND, __LINE__);

	return (char*)sqlite3_column_text(statement, index);
}

int DatabaseConnection::getInt(char * colName) {
	if(!isPrepared)
		throw DatabaseConnectionException(DatabaseConnectionException::IS_NOT_PREPARED, __LINE__);

	if(step != SQLITE_ROW) {
		if(!next())
			throw DatabaseConnectionException(DatabaseConnectionException::NO_ROW, __LINE__);
	}

	int index = columnNum(colName);

	if(index == -1)
		throw DatabaseConnectionException(DatabaseConnectionException::COLUMN_NOT_FOUND, __LINE__);

	if(sqlite3_column_type(statement, index) != SQLITE_INTEGER)
		throw DatabaseConnectionException(DatabaseConnectionException::COLUMN_NOT_INT, __LINE__);

	return sqlite3_column_int(statement, index);
}

double DatabaseConnection::getDouble(char * colName) {
	if(!isPrepared)
		throw DatabaseConnectionException(DatabaseConnectionException::IS_NOT_PREPARED, __LINE__);

	if(step != SQLITE_ROW) {
		if(!next())
			throw DatabaseConnectionException(DatabaseConnectionException::NO_ROW, __LINE__);
	}

	int index = columnNum(colName);

	if(index == -1)
		throw DatabaseConnectionException(DatabaseConnectionException::COLUMN_NOT_FOUND, __LINE__);

	if(sqlite3_column_type(statement, index) != SQLITE_FLOAT)
		throw DatabaseConnectionException(DatabaseConnectionException::COLUMN_NOT_FLOAT, __LINE__);

	return sqlite3_column_double(statement, index);
}

string DatabaseConnection::getText(char * colName) {
	if(!isPrepared)
		throw DatabaseConnectionException(DatabaseConnectionException::IS_NOT_PREPARED, __LINE__);

	if(step != SQLITE_ROW) {
		if(!next())
			throw DatabaseConnectionException(DatabaseConnectionException::NO_ROW, __LINE__);
	}

	int index = columnNum(colName);

	if(index == -1)
		throw DatabaseConnectionException(DatabaseConnectionException::COLUMN_NOT_FOUND, __LINE__);

	if(sqlite3_column_type(statement, index) != SQLITE_TEXT)
		throw DatabaseConnectionException(DatabaseConnectionException::COLUMN_NOT_TEXT, __LINE__);

	return (char*)sqlite3_column_text(statement, index);
}

int DatabaseConnection::columnCount() {
	if(!isPrepared)
		throw DatabaseConnectionException(DatabaseConnectionException::IS_NOT_PREPARED, __LINE__);

	return sqlite3_column_count(statement);
}

list<multimap<string, string> > DatabaseConnection::fetchAll() {
	if(!isPrepared)
		throw DatabaseConnectionException(DatabaseConnectionException::IS_NOT_PREPARED, __LINE__);

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