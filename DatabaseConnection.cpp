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

list<multimap<string, string> > DatabaseConnection::execute(char * query) {
   list<multimap<string, string> > results;

   int result = sqlite3_prepare_v2(db, query, -1, &statement, 0);

   if(result == SQLITE_OK) {
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
   } else {
      throw DatabaseConnectionException(result);
   }

   return results;
}