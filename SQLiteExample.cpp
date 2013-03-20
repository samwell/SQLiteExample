#include <iostream>
#include <string>
#include "DatabaseConnection.h"

using namespace std;

int main() {
	DatabaseConnection db;
	try {
		db.execute(const_cast<char *>("SELECT * FROM test;"));

		list<string> columns = db.getColumns();
		for(list<string>::iterator i = columns.begin(); i != columns.end(); i++)
			cout << (*i) << endl;

		cout << "ID: " << db.getColumn(const_cast<char *>("id")) << " NAME: " << db.getColumn(const_cast<char *>("name")) << endl;

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

	db.close();

	return 0;
}
