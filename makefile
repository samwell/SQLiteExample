all: sqlite3.o
		g++ sqlite3.o DatabaseConnection.cpp SQLiteExample.cpp -lpthread -ldl

sqlite3.o:
		gcc sqlite3.c -c