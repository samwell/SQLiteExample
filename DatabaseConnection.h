#include <iostream>
#include <string>
#include <map>
#include <list>
#include "sqlite3.h"
#include "DatabaseConnectionException.h"

using namespace std;

class DatabaseConnection {
private:
   static const char * filename;
   sqlite3 * db;
   sqlite3_stmt * statement;
   bool isPrepared;
   list<string> columns;
   int step;
   int columnNum(char * colName);
public:
   DatabaseConnection();
   ~DatabaseConnection();
   void open();
   void close();
   void reset();
   void finalize();
   void execute(char * query);
   bool next();
   list<string> getColumns();
   string getColumn(char * colName);
   int columnCount();
   list<multimap<string, string> > fetchAll();
};
