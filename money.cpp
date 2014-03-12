#include "money.h"
#include <stdlib.h>
Currency::Currency()
: cents_(0), printWithDollarSign_(0), numZeroPadding_(0)
{}

//Can instantiate with dollars and cents.
//Cents can be > 0 to instantiate only with
//cents.
Currency::Currency(unsigned long long dollars,
                   unsigned long long cents)
: printWithDollarSign_(0), numZeroPadding_(0)
{
  setAmount(dollars, cents);
}

Currency::Currency(std::string amount)
: printWithDollarSign_(0), numZeroPadding_(0)
{
  setAmount(amount);
}

//Returns true iff it's a decimal number with only
//one decimal place.
bool Currency::isCurrencyDecimal(std::string num) {
  int decimalCount = 0;

  //Check leading dollar sign
  if(num[0] == '$') {
    num.erase(num.begin());
  }

  for (size_t i = 0; i < num.length(); i++) {
    if (num[i] == '.') {
        decimalCount++;
    } else if (num[i] < '0' || num[i] > '9') {
        return false;
    }
  }

  //By here we know theres only decimals and zeros,
  //but how many?
  return (decimalCount <= 1);
}

double Currency::toDecimal() {
  return cents_ / 100.0;
}


//Using std::string in form "X---X.XX"
//Always assumes 1 or 2 decimal places.
//Will take up to 9 (trillion) dollars.
//Will ignore leading dollar sign ($)
void Currency::setAmount(std::string amount) {
  //Holds index of decimal
  size_t decimalIndex = 0;

  //Check leading dollar sign
  if (amount[0] == '$') {
    amount.erase(amount.begin());
  }

  //If not decimal then just set to 0;
  if (!isCurrencyDecimal(amount)) {
    cents_ = 0;
    return;
  }

  //Find place of first decimal, we only accept 9 figures.
  decimalIndex = amount.find('.');
  if (decimalIndex > MAX_DOLLAR_DIGITS && decimalIndex != std::string::npos) {
    cents_ = 0;
    return;
  }

  //Get dollars ending at decimal place.
  std::string substr = amount.substr(0, decimalIndex);
  cents_ = strtoull(substr.c_str(), NULL, 10)*100;

  //Get cents; if decimalIndex is present:
  if (decimalIndex != std::string::npos) {
    substr = amount.substr(decimalIndex+1,2);
    cents_ += strtoull(substr.c_str(), NULL, 10);
  }
}

void Currency::setAmount(unsigned long long dollars, unsigned long long cents) {
  cents_ = cents;
  cents_ += dollars*100;
}

std::string Currency::toString() const{
  return toString(printWithDollarSign_, numZeroPadding_);
}

// Returns formatted as $X---X.XX
std::string Currency::toString(bool wDollarSign, unsigned int minDigits) const {

  int length = 0;

  //Max digits + $, '.', and 2 decimals, and null
  char value[MAX_DOLLAR_DIGITS + 5] = {0};

  unsigned long long dollars = cents_ / 100;
  unsigned long long cents = cents_ % 100;
  const char *dollarSign = (wDollarSign) ? "$" : "";

  length += snprintf(value, MAX_DOLLAR_DIGITS+5, "%s%0*llu.%02llu",
                           dollarSign, minDigits, dollars, cents);

  if (*value == '\0' || length < 0) {
    return "$0.00";
  }

  std::string result(value, length);
  return result;
}

/* For use with ostreams */
void Currency::setFormat(bool wDollarSign, unsigned int numZerosPadded) {
  printWithDollarSign_ = wDollarSign;
  numZeroPadding_ = numZerosPadded;
}

// Print to stream with set formatting.
std::ostream& operator<< (std::ostream& os, const Currency& c) {
  os << c.toString();
  return os;
}
