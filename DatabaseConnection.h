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
public:
   DatabaseConnection();
   ~DatabaseConnection();
   void open();
   void close();
   list<multimap<string, string> > execute(char * query);
};
