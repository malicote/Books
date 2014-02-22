#include "SQLDatabase.h"
#include <iostream>

int main() {
	SQLDatabase db;
	db.openDatabase("File name!\n");
	std::cout << "Hello World\n";

	return 0;
}

