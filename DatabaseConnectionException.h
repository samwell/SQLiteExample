#include <iostream>
#include "sqlite3.h"

using namespace std;

class DatabaseConnectionException {
private:
   int status;
public:
   DatabaseConnectionException(int inStatus) { 
      status = inStatus; 
   }
   const char * getMessage() const {
      const char * message;
      switch(status) {
         case SQLITE_ERROR:
            message = "Error Code: 1, Message: SQL error or missing database";
            break;
         case SQLITE_INTERNAL:
            message = "Error Code: 2, Message: Internal logic error in SQLite";
            break;
         case SQLITE_PERM:
            message = "Error Code: 3, Message: Access permission denied";
            break;
         case SQLITE_ABORT:
            message = "Error Code: 4, Message: Callback routine requested an abort";
            break;
         case SQLITE_BUSY:
            message = "Error Code: 5, Message: The database file is locked";
            break;
         case SQLITE_LOCKED:
            message = "Error Code: 6, Message: A table in the database is locked";
            break;
         case SQLITE_NOMEM:
            message = "Error Code: 7, Message: A malloc() failed";
            break;
         case SQLITE_READONLY:
            message = "Error Code: 8, Message: Attempt to write a readonly database";
            break;
         case SQLITE_INTERRUPT:
            message = "Error Code: 9, Message: Operation terminated by sqlite3_interrupt()";
            break;
         case SQLITE_IOERR:
            message = "Error Code: 10, Message: Some kind of disk I/O error occurred";
            break;
         case SQLITE_CORRUPT:
            message = "Error Code: 11, Message: The database disk image is malformed";
            break;
         case SQLITE_NOTFOUND:
            message = "Error Code: 12, Message: Unknown opcode in sqlite3_file_control()";
            break;
         case SQLITE_FULL:
            message = "Error Code: 13, Message: Insertion failed because database is full";
            break;
         case SQLITE_CANTOPEN:
            message = "Error Code: 14, Message: Unable to open the database file";
            break;
         case SQLITE_PROTOCOL:
            message = "Error Code: 15, Message: Database lock protocol error";
            break;
         case SQLITE_EMPTY:
            message = "Error Code: 16, Message: Database is empty";
            break;
         case SQLITE_SCHEMA:
            message = "Error Code: 17, Message: The database schema changed";
            break;
         case SQLITE_TOOBIG:
            message = "Error Code: 18, Message: String or BLOB exceeds size limit";
            break;
         case SQLITE_CONSTRAINT:
            message = "Error Code: 19, Message: Abort due to constraint violation";
            break;
         case SQLITE_MISMATCH:
            message = "Error Code: 20, Message: Data type mismatch";
            break;
         case SQLITE_MISUSE:
            message = "Error Code: 21, Message: Library used incorrectly";
            break;
         case SQLITE_NOLFS:
            message = "Error Code: 22, Message: Uses OS features not supported on host";
            break;
         case SQLITE_AUTH:
            message = "Error Code: 23, Message: Authorization denied";
            break;
         case SQLITE_FORMAT:
            message = "Error Code: 24, Message: Auxiliary database format error";
            break;
         case SQLITE_RANGE:
            message = "Error Code: 25, Message: 2nd parameter to sqlite3_bind out of range";
            break;
         case SQLITE_NOTADB:
            message = "Error Code: 26, Message: File opened that is not a database file";
            break;
         case SQLITE_ROW:
            message = "Error Code: 100, Message: sqlite3_step() has another row ready";
            break;
         case SQLITE_DONE:
            message = "Error Code: 101, Message: sqlite3_step() has finished executing";
            break;
         default:
            message = "Unknown error code";
      }

      return message;
   }
};