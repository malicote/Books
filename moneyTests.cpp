/* Just a suite of tests for the money class.
 */

 #include "money.h"
 #include <iostream>
 #include <string>

static bool printOut = true;

int constructorTestSuite();
int setAmountTestSuite();
int toStringTestSuite();
int toDecimalTestSuite();
int operatorTestSuite();

bool emptyConstructorTest();
bool longConstructorTest(unsigned long long,
                         unsigned long long,
                         unsigned long long);

bool stringConstructorTest(std::string, unsigned long long);
bool longSetAmountTest(unsigned long long,
                       unsigned long long,
                       unsigned long long);
bool stringSetAmountTest(std::string, unsigned long long);
bool toStringTest(unsigned long long, std::string,
                  bool wDollarSign,
                  unsigned int minDigits,
                  bool useSetFormat);
bool toStreamTest(unsigned long long, std::string,
                  bool wDollarSign,
                  unsigned int minDigits);
bool toDecimalTest(unsigned long long amount, double expected);
bool operatorTest(unsigned long long lhs, unsigned long long rhs,
                  const std::string& op);

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

  std::cout << "Running comparison operator tests...\n";
  numFailed += operatorTestSuite();
  std::cout << numFailed << " comparison tests failed" << std::endl;

  return (numFailed == 0);
}

int operatorTestSuite() {
  int testsFailed = 0;

  //Simple zeros test.
  testsFailed += operatorTest(0, 0, "==");
  testsFailed += operatorTest(0, 0, "!=");
  testsFailed += operatorTest(0, 0, ">");
  testsFailed += operatorTest(0, 0, "<");
  testsFailed += operatorTest(0, 0, ">=");
  testsFailed += operatorTest(0, 0, "<=");

  //Left side
  testsFailed += operatorTest(100, 0, "==");
  testsFailed += operatorTest(100, 0, "!=");
  testsFailed += operatorTest(100, 0, ">");
  testsFailed += operatorTest(100, 0, "<");
  testsFailed += operatorTest(100, 0, ">=");
  testsFailed += operatorTest(100, 0, "<=");

  //Right side
  testsFailed += operatorTest(0, 100, "==");
  testsFailed += operatorTest(0, 100, "!=");
  testsFailed += operatorTest(0, 100, ">");
  testsFailed += operatorTest(0, 100, "<");
  testsFailed += operatorTest(0, 100, ">=");
  testsFailed += operatorTest(0, 100, "<=");

  return testsFailed;
}

bool operatorTest(unsigned long long lhs, unsigned long long rhs,
                  const std::string& op)
{
  Currency testLHS(0, lhs);
  Currency testRHS(0, rhs);
  /* 0 = print bool comparisons, 1 = print math ops */
  int printSwitch = 0;
  std::string expectedString;
  std::string actualString;

  bool result = false;
  bool expected = false;
  bool actual = false;

  if (op == "==") {
    expected = (lhs == rhs);
    actual = (testLHS == testRHS);
  } else if (op == "!=") {
    expected = (lhs != rhs);
    actual = (testLHS != testRHS);
  } else if (op == ">") {
    expected = (lhs > rhs);
    actual = (testLHS > testRHS);
  } else if (op == ">=") {
    expected = (lhs >= rhs);
    actual = (testLHS >= testRHS);
  } else if (op == "<") {
    expected = (lhs < rhs);
    actual = (testLHS < testRHS);
  } else if (op == "<=") {
    expected = (lhs <= rhs);
    actual = (testLHS <= testRHS);
  }

  result = (actual == expected);

  switch(printSwitch) {
    case 0:
      expectedString = ((expected) ? "TRUE" : "FALSE");
      actualString = ((actual) ? "TRUE" : "FALSE");
      break;
    case 1:
      expectedString = expected;
      actualString = actual;
    default:
      break;
  }

  if (printOut) {
    std::cout << "Testing comparison: \"" << lhs  << " "
       << op << " " << rhs << "\""
       << "; TEST: " << ((result) ? "PASSSED" : "FAILED")
       << " | Expected value: [" << expectedString << "]"
       << " | Actual value: [" << actualString << "]"
       << std::endl;
  }
  // Return true if it failed.
  return !result;
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

  //Standard tests
  testsFailed += toStringTest(100, "$1.00", true, 0, false);
  testsFailed += toStringTest(10, "$0.10", true, 0, false);
  testsFailed += toStringTest(0, "$0.00", true, 0, false);
  testsFailed += toStringTest(1000, "$10.00", true, 0, false);
  testsFailed += toStringTest(1000010, "$10000.10", true, 0, false);
  testsFailed += toStringTest(1, "$0.01", true, 0, false);

  //With padding
  testsFailed += toStringTest(99, "$00.99", true, 2, false);
  testsFailed += toStringTest(100, "$001.00", true, 3, false);
  testsFailed += toStringTest(1000, "$00010.00", true, 5, false);
  testsFailed += toStringTest(12345, "$00123.45", true, 5, false);

  //With padding and no dollar sign
  testsFailed += toStringTest(99, "00.99", false, 2, false);
  testsFailed += toStringTest(100, "001.00", false, 3, false);
  testsFailed += toStringTest(1000, "00010.00", false, 5, false);
  testsFailed += toStringTest(12345, "00123.45", false, 5, false);

  //Now the same only using setFormat instead
  testsFailed += toStringTest(99, "$00.99", true, 2, true);
  testsFailed += toStringTest(100, "$001.00", true, 3, true);
  testsFailed += toStringTest(1000, "$00010.00", true, 5, true);
  testsFailed += toStringTest(12345, "$00123.45", true, 5, true);
  testsFailed += toStringTest(99, "00.99", false, 2, true);
  testsFailed += toStringTest(100, "001.00", false, 3, true);
  testsFailed += toStringTest(1000, "00010.00", false, 5, true);
  testsFailed += toStringTest(12345, "00123.45", false, 5, true);

  //Using streams
  testsFailed += toStreamTest(100, "$001.00", true, 3);
  testsFailed += toStreamTest(199, "$1.99", true, 0);
  testsFailed += toStreamTest(100, "001.00", false, 3);
  testsFailed += toStreamTest(10000, "100.00", false, 0);

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
bool toStringTest(unsigned long long amount, std::string expected,
                  bool wDollarSign, unsigned int minDigits, bool useSetFormat)
{
    Currency testCurrency(0, amount);
    bool testPassed = false;
    std::string result;

    if (useSetFormat) {
      testCurrency.setFormat(wDollarSign, minDigits);
      result = testCurrency.toString();
    } else {
      result = testCurrency.toString(wDollarSign, minDigits);
    }

    testPassed = !expected.compare(result);

    if (printOut) {
      std::cout << "Testing string conversion ["
              << amount << "] | "
              << "TEST "
              << ((testPassed) ? "PASSED" : "FAILED")
              << ": ["
              << result << "]"
              << " expected: [" << expected << "]"
              << std::endl;
    }

    return !testPassed;
}

/* Run test with string and compare to expected value. */
bool toStreamTest(unsigned long long amount, std::string expected,
                  bool wDollarSign, unsigned int minDigits)
{
    Currency testCurrency(0, amount);

    testCurrency.setFormat(wDollarSign, minDigits);

    if (printOut) {
      std::cout << "Testing string conversion ["
              << amount << "] | "
              << "VISUAL TEST "
              << ": ["
              << testCurrency << "]"
              << " expected: [" << expected << "]"
              << std::endl;
    }

    return !true;
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
