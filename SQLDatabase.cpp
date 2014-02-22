#include "SQLDatabase.h"

//Temp:
#include <iostream>

SQLDatabase::SQLDatabase() : mDB(0), isReady(false) {

}

void SQLDatabase::openDatabase(const std::string filename) {
	std::cout << filename;
	int status = 0;

	status = sqlite3_open(filename.c_str(), &mDB);

	if (status != SQLITE_OK || !mDB) {
		throw DATABASE_CONNECTION_FAIL;
	}
}

void SQLDatabase::closeDatabase() {
	//Nop on null pointer
	sqlite3_close(mDB);
}

SQLDatabase::~SQLDatabase() {
	closeDatabase();
}
