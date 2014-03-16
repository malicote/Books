#ifndef _MONEY_H_
#define _MONEY_H_

#include <string>
#include <iostream>

/* Things this class should do:
-store money
-translate string to money
-return string rep of money
-assumes USD for now
-translate float to money
-return float rep of money
*/

/* Safe to use copy constructor with no overloading */
class Currency {
public:
  /* Consts */

  //Trillion dollars max
  static const size_t MAX_DOLLAR_DIGITS = 12;

  /* Constructors */
  Currency();
  Currency(unsigned long long dollars, unsigned long long cents);
  Currency(std::string amount);

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
  void setAmount(unsigned long long dollars, unsigned long long cents);

  //May want to overload = operator with string / decimal
  //May want to overload +/- too.
  //And * /

  /* Returns true if only decimal numbers and a single
   * decimal place are present.
   */
  static bool isCurrencyDecimal(std::string);

  inline unsigned long long getAmount() const{
    return cents_;
  }

  void setFormat(bool wDollarSign, unsigned int numZerosPadded);

  // Print to stream with set formatting.
  friend std::ostream& operator<< (std::ostream& os, const Currency& c);

private:

  /* Store everything as cents for now  */
  unsigned long long cents_;

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

#endif
