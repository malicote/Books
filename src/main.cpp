#include "SQLDatabase.h"
#include <iostream>
#include "money.h"
#include "transaction.h"

extern bool moneyTestMain(bool);
extern bool transactionTest_main();

void printResult(const std::string testName, bool result);

int main() {
	printResult("Money test: ", moneyTestMain(true));
	printResult("Transaction test: ", transactionTest_main());
	
	return 0;
}

void printResult(const std::string testName, bool result) {
	std::cout << testName
						<< ((result) ? "PASSED" : "FAILED")
						<< std::endl;
}
