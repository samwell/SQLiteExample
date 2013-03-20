#include <iostream>
#include <string>
#include "DatabaseConnection.h"

using namespace std;

int main() {
	DatabaseConnection db;
	try {
		db.execute(const_cast<char *>("SELECT * FROM test2;"));

		// Example: Listing all columns from executed query
		cout << "Lists all columns from table" << endl;

		list<string> columns = db.getColumns();
		for(list<string>::iterator i = columns.begin(); i != columns.end(); i++)
			cout << (*i) << endl;

		// Example: Extracting specific data types into acceptable data types
		cout << endl << "Extract specific data types" << endl;

		int intTest = db.getInt(const_cast<char *>("intTest"));
		double doubleTest = db.getDouble(const_cast<char *>("doubleTest"));
		int numericTest = db.getInt(const_cast<char *>("numericTest"));
		string blobTest = db.getText(const_cast<char *>("blobTest"));
		string textTest = db.getText(const_cast<char *>("textTest"));

		cout << "INT: " << intTest << endl;
		cout << "DOUBLE: " << doubleTest << endl;
		cout << "NUMERIC: " << numericTest << endl;
		cout << "BLOB: " << blobTest << endl;
		cout << "TEXT: " << textTest << endl;

		// Resets the pointer back to the beginning
		db.reset();

		// Example: Extract any type of data types
		cout << endl << "Extract any type of data types" << endl;
		cout << "NUMERICTEST: " << db.getColumn(const_cast<char *>("numericTest")) << " TEXTTEST: " << db.getColumn(const_cast<char *>("textTest")) << endl;

		// Got new set of data. Why? Because I can.
		db.finalize();
		db.execute(const_cast<char *>("SELECT * FROM test;"));

		// Example: Extract all data obtained from executing the query
		cout << endl << "Extract all data from query and store in a list of multimaps" << endl;
		list<multimap<string, string> > results = db.fetchAll();
		list<multimap<string, string> >::iterator rows = results.begin();

		while(rows != results.end()) {
			multimap<string, string>::iterator row = (*rows).begin();
			while(row != (*rows).end()) {
				cout << (*row).first << " " << (*row).second << " ";
				row++;
			}

			cout << endl;

			rows++;
		}
	} catch (DatabaseConnectionException e) {
		cout << e.getMessage();
	}

	// Deletes pointer to query
	db.finalize();

	// Deletes pointer to database connection
	db.close();

	return 0;
}
