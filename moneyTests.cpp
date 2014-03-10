/* Just a suite of tests for the money class.
 */

 #include "money.h"
 #include <iostream>

static bool printOut = true;

int constructorTestSuite();
int setAmountTestSuite();
int toStringTestSuite();
int toDecimalTestSuite();

bool emptyConstructorTest();
bool longConstructorTest(unsigned long long,
                         unsigned long long,
                         unsigned long long);

bool stringConstructorTest(std::string, unsigned long long);
bool longSetAmountTest(unsigned long long,
                       unsigned long long,
                       unsigned long long);
bool stringSetAmountTest(std::string, unsigned long long);
bool toStringTest(unsigned long long, std::string);
bool toDecimalTest(unsigned long long amount, double expected);


//Returns true if passed.
bool moneyTestMain(bool showPrintOuts) {

  printOut = showPrintOuts;

  /*Test constructors*/
  int numFailed = 0;

  std::cout << "**********************\n";
  std::cout << "MONEY TESTS\n";
  std::cout << "**********************\n";

  std::cout << "Running constructor tests...\n";
  numFailed += constructorTestSuite();
  std::cout << numFailed << " constructor tests failed" << std::endl;

  std::cout << "Running setAmount tests...\n";
  numFailed += setAmountTestSuite();
  std::cout << numFailed << " setAmount tests failed" << std::endl;

  std::cout << "Running toString tests...\n";
  numFailed += toStringTestSuite();
  std::cout << numFailed << " toString tests failed" << std::endl;

  std::cout << "Running toDecimal tests...\n";
  numFailed += toDecimalTestSuite();
  std::cout << numFailed << " toDecimal tests failed" << std::endl;

  return (numFailed == 0);
}

int setAmountTestSuite() {
  int testsFailed = 0;

  /*Test using dollars and cents */
  testsFailed += longSetAmountTest(100, 100, 10100);
  testsFailed += longSetAmountTest(0, 100, 100);
  testsFailed += longSetAmountTest(0, 0, 0);

  // NULL
  testsFailed += stringSetAmountTest("", 0);

  //Invalid string
  testsFailed += stringSetAmountTest("abc", 0);

  //Just a dollar sign
  testsFailed += stringSetAmountTest("$", 0);

  //Truncating values
  testsFailed += stringSetAmountTest("$150.2334", 15023);

  //Multiple zeros
  testsFailed += stringSetAmountTest("$000.00", 0);

  //Length limit (==12 digits)
  testsFailed += stringSetAmountTest("$999999999999.99", 99999999999999);

  //Over limit
  testsFailed += stringSetAmountTest("$9999999999999.99", 0);

  //Do not accept negative numbers
  testsFailed += stringSetAmountTest("-$150.23", 0);

  return testsFailed;
}

int constructorTestSuite() {
  int testsFailed = 0;

  /* Test default constructor */
  testsFailed += emptyConstructorTest();

  /*Test using dollars and cents */
  testsFailed += longConstructorTest(100, 100, 10100);
  testsFailed += longConstructorTest(0, 100, 100);
  testsFailed += longConstructorTest(0, 0, 0);

  // NULL
  testsFailed += stringConstructorTest("", 0);

  //Invalid string
  testsFailed += stringConstructorTest("abc", 0);

  //Just a dollar sign
  testsFailed += stringConstructorTest("$", 0);

  //Truncating values
  testsFailed += stringConstructorTest("$150.2334", 15023);

  //Multiple zeros
  testsFailed += stringConstructorTest("$000.00", 0);

  //Length limit (==12 digits)
  testsFailed += stringConstructorTest("$999999999999.99", 99999999999999);

  //Over limit
  testsFailed += stringConstructorTest("$9999999999999.99", 0);

  //Do not accept negative numbers
  testsFailed += stringConstructorTest("-$150.23", 0);

  //Just dollars
  testsFailed += stringConstructorTest("$200", 20000);

  //Just cents
  testsFailed += stringConstructorTest("$.20", 20);

  //Just period
  testsFailed += stringConstructorTest(".", 0);

  //Just period, no dollars
  testsFailed += stringConstructorTest(".20", 20);

  //No dollar sign
  testsFailed += stringConstructorTest("150.23", 15023);

  return testsFailed;
}

int toStringTestSuite() {
  int testsFailed = 0;

  testsFailed += toStringTest(100, "$1.00");
  testsFailed += toStringTest(10, "$0.10");
  testsFailed += toStringTest(0, "$0.00");
  testsFailed += toStringTest(1000, "$10.00");
  testsFailed += toStringTest(1000010, "$10000.10");
  testsFailed += toStringTest(1, "$0.01");
  testsFailed += toStringTest(99, "$0.99");

  return testsFailed;

}


int toDecimalTestSuite() {
  int testsFailed = 0;

  testsFailed += toDecimalTest(100, 1.0);
  testsFailed += toDecimalTest(1000, 10.0);
  testsFailed += toDecimalTest(1, 0.01);
  testsFailed += toDecimalTest(10, 0.1);
  testsFailed += toDecimalTest(99, 0.99);
  testsFailed += toDecimalTest(90, 0.90);

  return testsFailed;
}

/* Run test with default constructor */
bool emptyConstructorTest() {
  Currency testCurrency;
  bool testPassed = (testCurrency.getAmount() == 0ULL);

  if(printOut) {
    std::cout << "Empty constructor: " << testCurrency.getAmount()
              << " | TEST "
              << ((testPassed) ? "PASSED" : "FAILED")
              << std::endl;
  }
  return !testPassed;

}
/* RUn test with unsigned longs */
bool longConstructorTest(unsigned long long dollars,
                                unsigned long long cents,
                                unsigned long long expected)
{
  Currency testCurrency(dollars, cents);
  bool testPassed = (testCurrency.getAmount() == expected);

  if(printOut) {
    std::cout << "Test currency [ " << dollars << ',' << cents
              << " ] | "
              << "TEST "
              << ((testPassed) ? "PASSED" : "FAILED")
              << ": ["
              << testCurrency.getAmount() << "]"
              << " expected: [" << expected << "]"
              << std::endl;
  }

  return !testPassed;
}

bool longSetAmountTest(unsigned long long dollars,
                                unsigned long long cents,
                                unsigned long long expected)
{
  Currency testCurrency;
  testCurrency.setAmount(dollars, cents);
  bool testPassed = (testCurrency.getAmount() == expected);

  if(printOut) {
    std::cout << "Test currency [ " << dollars << ',' << cents
              << " ] | "
              << "TEST "
              << ((testPassed) ? "PASSED" : "FAILED")
              << ": ["
              << testCurrency.getAmount() << "]"
              << " expected: [" << expected << "]"
              << std::endl;
  }

  return !testPassed;
}

/* Run test with string and compare to expected value. */
bool stringSetAmountTest(std::string amount,
                                 unsigned long long expected)
{
  Currency testCurrency;
  testCurrency.setAmount(amount);
  bool testPassed = false;

  if(testCurrency.getAmount() == expected)
    testPassed = true;
  else
    testPassed = false;

  if(printOut) {
      std::cout << "Testing currency [" << amount << "]  | "
            << "TEST "
            << ((testPassed) ? "PASSED" : "FAILED")
            << ": ["
            << testCurrency.getAmount() << "]"
            << " expected: [" << expected << "]"
            << std::endl;
  }

  return !testPassed;
}

/* Run test with string and compare to expected value. */
bool stringConstructorTest(std::string amount,
                                 unsigned long long expected)
{
   Currency testCurrency(amount);
   bool testPassed = false;

   if(testCurrency.getAmount() == expected)
     testPassed = true;
   else
     testPassed = false;

   if(printOut) {
       std::cout << "Testing currency [" << amount << "]  | "
             << "TEST "
             << ((testPassed) ? "PASSED" : "FAILED")
             << ": ["
             << testCurrency.getAmount() << "]"
             << " expected: [" << expected << "]"
             << std::endl;
   }

   return !testPassed;
 }

/* Run test with string and compare to expected value. */
bool toStringTest(unsigned long long amount, std::string expected)
{
    Currency testCurrency(0, amount);
    bool testPassed = !expected.compare(testCurrency.toString());


    if (printOut) {
      std::cout << "Testing string conversion ["
              << amount << "] | "
              << "TEST "
              << ((testPassed) ? "PASSED" : "FAILED")
              << ": ["
              << testCurrency.toString() << "]"
              << " expected: [" << expected << "]"
              << std::endl;
    }

    return !testPassed;
}

/* Run test with string and compare to expected value. */
bool toDecimalTest(unsigned long long amount, double expected)
{
  double epsilon = 0.000001;
  Currency testCurrency(0, amount);
  bool testPassed = false;

  if (abs(testCurrency.toDecimal() - expected) <= epsilon) {
    testPassed = true;
  }


  if (printOut) {
    std::cout << "Testing string conversion ["
            << amount << "] | "
            << "TEST "
            << ((testPassed) ? "PASSED" : "FAILED")
            << ": ["
            << testCurrency.toDecimal() << "]"
            << " expected: [" << expected << "]"
            << std::endl;
  }

  return !testPassed;
}
