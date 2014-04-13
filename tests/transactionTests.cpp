#include "transaction.h"
#include <iostream>
#include <string>

static bool transactionTests();
static int constructionTestSuite();
static int operatorTestSuite();

static int emptyConstruction();
static int specifiedConstruction(unsigned long long ID, std::string description, std::string majorCategory,
                          std::string minorCategory, const struct tm& date, const Currency& amount, std::string transactionType);

 
int transactionTest_main() {
  std::cout << "Starting transaction tests!" << std::endl;
  
  int ret = transactionTests();
  return ret;
}

bool transactionTests() {
  int totalTestFailed = 0;
  
  totalTestFailed += constructionTestSuite();
  totalTestFailed += operatorTestSuite();

  return totalTestFailed == 0;
}

int constructionTestSuite() {
  int testFailed = 0;
  struct tm testDate;
  testDate.tm_sec = 30;
  testDate.tm_hour = 12;
  testDate.tm_min = 20;
  
  testFailed += emptyConstruction();  
  testFailed += specifiedConstruction(200, "This is a description", "BILLS", "PHONE", testDate, 100ll, "DEBIT");

  return testFailed;
}

int operatorTestSuite() {
  struct tm testDate;
  testDate.tm_sec = 10;
  testDate.tm_hour = 2;
  testDate.tm_min = 20;
  
  Transaction transactionA (100ull, "Description!", "DEBIT", "BILLS", 
                            "PHONE", testDate, 1000ll);

    
  Transaction transactionB (8672ull, "My 2nd!", "CASH", "DINING", 
                            "Coffee", testDate, 3320ll);
  
  if (transactionA == transactionB) {
    std::cout << "Comparison test failed!" << std::endl;
    return 1;
  } else {
    std::cout << "Comparison test passed!" << std::endl;
  }

  transactionB = transactionA;

  if (transactionA != transactionB) {
    std::cout << "Assignment operator test failed!" << std::endl;
    return 1;
  } else {
    std::cout << "Assignment operator test passed!" << std::endl;
  }

  return 0;
}

int emptyConstruction() {
  int result = 1;

  Transaction record;
  
  struct tm zero_date;

  clearTime(zero_date);

  std::cout << "Testing empty construction... ";

  if (  record.ID == 0ull &&
        record.description == "" &&
        record.majorCategory == "" &&
        record.minorCategory == "" &&
        record.transactionType == "" &&
        record.transactionAmount == 0ll &&
        isSameDate(record.transactionDate, zero_date)   
  ) {
    std::cout << "Test PASSED!" << std::endl;
    result = 0;
  } else {
    std::cout << "Test FAILED!" << std::endl;
  }

  return result;
}

int specifiedConstruction(unsigned long long ID, std::string description, std::string majorCategory,
                          std::string minorCategory, const struct tm& date, const Currency& amount,
                          std::string transactionType) 
{
  Transaction record(ID, description, transactionType, majorCategory, minorCategory, date, amount);
  int result = 1;

    
  std::cout << "Testing specified  construction... ";
  std::cout << "ID = " << ID << "\n"
            << "Description = " << description << "\n"
            << "Type = " << transactionType << "\n"
            << "Major Category = " << majorCategory << "\n"
            << "Minor Category = " << minorCategory << "\n"
            << "Date = " << /* TODO */ "\n"
            << "Amount = " << amount.getAmount() << std::endl;
          
  if (  record.ID == ID &&
        record.description == description &&
        record.transactionType == transactionType &&
        record.majorCategory == majorCategory &&
        record.minorCategory == minorCategory &&
        record.transactionAmount == amount &&
        isSameDate(record.transactionDate, date)    
  ) {
    std::cout << "Test PASSED!" << std::endl;
    result = 0;
  } else {
    std::cout << "Test FAILED!" << std::endl;
  }

  return result;
}

