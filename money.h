#ifndef _MONEY_H_
#define _MONEY_H_

#include <string>

/* Things this class should do:
-store money
-translate string to money
-return string rep of money
-assumes USD for now
-translate float to money
-return float rep of money
*/
class Currency {
public:
  /* Consts */

  //Trillion dollars max
  static const size_t MAX_DOLLAR_DIGITS = 12;

  /* Constructors */
  Currency();
  Currency(unsigned long long, unsigned long long);
  Currency(std::string amount);

  std::string toString();
  double toDecimal();
  void setAmount(std::string amount);
  void setAmount(unsigned long long, unsigned long long);

  //May want to overload = operator with string / decimal
  //Also overload < > <= >= and ==
  //May want to overload stream operator to print nicely.
  //May want to overload +/- too.
  //And * /
  //And the iostream

  /* Returns true if only decimal numbers and a single
   * decimal place are present.
   */
  static bool isCurrencyDecimal(std::string);

  inline unsigned long long getAmount() {
    return cents_;
  }

private:

  /* Store everything as cents for now  */
  unsigned long long cents_;



};
#endif
