#ifndef _MONEY_H_
#define _MONEY_H_

#include <string>
#include <iostream>

/* Safe to use copy constructor with no overloading */
class Currency {
public:
  /* Consts */

  //Trillion dollars max
  static const size_t MAX_DOLLAR_DIGITS = 12;

  /* Constructors */
  Currency();
  Currency(long long dollars, long long cents);
  Currency(std::string amount);

  // Can be > 99;
  Currency(long long cents);
  Currency(double amount);

  /* Return as string, padding whole number with zeros
   * to at least minDigits.  Note minDigits=0 will still
   * print leading zero when amount < $1.
   */
  std::string toString(bool wDollarSign,
                       unsigned int minDigits) const;


  /* With no arguments, uses format set by setFormat */
  std::string toString() const;

  double toDecimal();
  void setAmount(std::string amount);
  void setAmount(long long dollars, long long cents);

  /* Returns true if only decimal numbers and a single
   * decimal place are present.
   */
  static bool isCurrencyDecimal(std::string);

  inline long long getAmount() const{
    return cents_;
  }

  void setFormat(bool wDollarSign, unsigned int numZerosPadded);

  Currency& operator+=(const Currency& rhs) {
    cents_ += rhs.getAmount();
    return *this;
  }

  Currency& operator-=(const Currency& rhs) {
    cents_ -= rhs.getAmount();
    return *this;
  }
  // Print to stream with set formatting.
  friend std::ostream& operator<< (std::ostream& os, const Currency& c);

private:

  /* Store everything as cents for now  */
  long long cents_;

  bool printWithDollarSign_;
  unsigned int numZeroPadding_;
};

inline bool operator==(const Currency& lhs, const Currency& rhs) {
  return (lhs.getAmount() == rhs.getAmount());
}
inline bool operator!=(const Currency& lhs, const Currency& rhs) {
  return ( !operator==(lhs, rhs) );
}
inline bool operator<(const Currency& lhs, const Currency& rhs) {
  return ( lhs.getAmount() < rhs.getAmount() );
}
inline bool operator>(const Currency& lhs, const Currency& rhs) {
  return ( operator<(rhs, lhs) );
}
inline bool operator<=(const Currency& lhs, const Currency& rhs) {
  return ( !operator>(lhs, rhs) );
}
inline bool operator>=(const Currency& lhs, const Currency& rhs) {
  return ( !operator<(lhs, rhs) );
}

inline Currency operator+(Currency lhs, const Currency& rhs) {
  lhs += rhs;
  return lhs;
}

inline Currency operator-(Currency lhs, const Currency& rhs) {
  lhs -= rhs;
  return lhs;
}
#endif
