#ifndef _SQLDatabase_H
#define _SQLDatabase_H

#include <string>
#include <sqlite3.h>

class SQLDatabase {
	public:
		SQLDatabase();
		void openDatabase(const std::string);
		void closeDatabase();
		//executeQuery();
	
		~SQLDatabase();

		//Exception errors 
		static const int DATABASE_CONNECTION_FAIL = 1;
		static const int DATABASE_NOT_FOUND = 2;
		static const int DATABASE_GENERAL_ERROR = 3;
	private:
		sqlite3* mDB;
		bool isReady;
};

#endif
