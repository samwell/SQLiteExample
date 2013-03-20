#include <iostream>
#include "DatabaseConnection.h"

using namespace std;

int main() {
   DatabaseConnection db;
   try {
      list<multimap<string, string> > results = db.execute(const_cast<char *>("SELECT * FROM test;"));
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