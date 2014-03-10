#include "SQLDatabase.h"
#include <iostream>
#include "money.h"

extern bool moneyTestMain(bool);

int main() {
	bool testPassed = moneyTestMain(true);

	std::cout << "Money tests "
						<< ((testPassed) ? "PASSED" : "FAILED")
						<< "\n";

	return 0;
}
