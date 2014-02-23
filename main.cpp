#include "SQLDatabase.h"
#include <iostream>

int main() {
	SQLDatabase db;
	try {
		db.openDatabase("File name!\n");
	} catch (int exc) {
		std::cout << "Database open() error = " << exc << std::endl;
	}
	std::cout << "Hello World\n";

	return 0;
}

