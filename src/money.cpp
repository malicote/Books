#include "money.h"
#include <stdlib.h>

Currency::Currency()
: cents_(0), printWithDollarSign_(0), numZeroPadding_(0)
{}

//Can instantiate with dollars and cents.
Currency::Currency(long long dollars,
                   long long cents)
: printWithDollarSign_(0), numZeroPadding_(0)
{
  setAmount(dollars, cents);
}

// Useful for comparison with ints.
Currency::Currency(long long cents)
: printWithDollarSign_(0), numZeroPadding_(0)
{
  setAmount(0, cents);
}

// Useful for comparisons with int
Currency::Currency(double amount)
{
    char* amount_c_str = NULL;

    sprintf(amount_c_str, "%.2f", amount);

    std::string amountString(amount_c_str);

    setAmount(amountString);

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

  //Check leading negative sign
  if(num[0] == '-') {
    num.erase(num.begin());
  }

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
  int sign = 1;

  //Check negative sign
  if (amount[0] == '-') {
    amount.erase(amount.begin());
    sign = -1;
  }

  //Check leading dollar sign (after deleting leading -)
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

  //Set correct sign
  cents_ *= sign;
}

void Currency::setAmount(long long dollars, long long cents) {

  int sign = 1;

  // Either or both can be negative, and it will count as negative.
  if (dollars < 0) {
    sign = -1;
    dollars *= sign;
  } if(cents < 0) {
    sign = -1;
    cents *= sign;
  }

  cents_ = cents;
  cents_ += dollars*100;
  cents_ *= sign;
}

std::string Currency::toString() const{
  return toString(printWithDollarSign_, numZeroPadding_);
}

// Returns formatted as $X---X.XX
std::string Currency::toString(bool wDollarSign, unsigned int minDigits) const {

  int length = 0;
  //Max digits + '-', $, '.', and 2 decimals, and null
  char value[MAX_DOLLAR_DIGITS + 6] = {0};
  int sign = 1;

  if (cents_ < 0) {
    sign = -1;
  }

  long long dollars = (sign * cents_) / 100;
  long long cents = (sign * cents_) % 100;

  const char *minusSign = (sign == -1) ? "-" : "";
  const char *dollarSign = (wDollarSign) ? "$" : "";

  length += snprintf(value, MAX_DOLLAR_DIGITS+5, "%s%s%0*llu.%02llu",
                           minusSign, dollarSign,
                           minDigits, dollars, cents);

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
