#include "SQLDatabase.h"
#include <sys/stat.h>
#include <assert.h>
//Temp:
#include <iostream>

SQLDatabase::SQLDatabase() : mDB(0), isReady(false) {

}

//Attempts to open an already existing database.
void SQLDatabase::openDatabase(const std::string filename) {
	std::cout << filename;
	int status = 0;
	struct stat permissions;

	//Can't open something that already exists
	assert(!mDB);

	//Just open the database, that's it.  If it doesn't exist
	//then throw the correct error.
	status = stat(filename.c_str(), &permissions);
	if (status == ENOENT) {
		throw DATABASE_NOT_FOUND;
	} else {
		throw DATABASE_GENERAL_ERROR;
	}
	
	//Attempt to open the database
	status = sqlite3_open(filename.c_str(), &mDB);

	if (status != SQLITE_OK || !mDB) {
		closeDatabase();
		throw DATABASE_CONNECTION_FAIL;
	}
}

void SQLDatabase::closeDatabase() {
	//Nop on null pointer
	sqlite3_close(mDB);
	mDB = 0;
}

SQLDatabase::~SQLDatabase() {
	closeDatabase();
}
