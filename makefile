FLAGS=-Wall -Werror
LIBS=-lpthread -ldl
all: sqlite3.o
		g++ $(FLAGS) sqlite3.o DatabaseConnection.cpp SQLiteExample.cpp $(LIBS)  

sqlite3.o:
		gcc $(FLAGS) sqlite3.c -c