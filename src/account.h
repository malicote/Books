#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#include <string>
#include <vector>

class Account {

public:

  virtual Account() = 0;
  virtual setUpAccount(std:string::type,
                       std::name,
                       std::ID,
                       std:vector<Transaction> transactions) = 0;
  /* Will eventually throw exception on error */
  virtual void addTransaction(Transaction transaction) = 0;
  virtual void removeTransaction(std::ID ID) = 0;
  virtual void removeTransaction(Transaction transaction) = 0;

  virtual long long getBalance() {
    return accountBalance_;
  }

  /* Filters transactions based on the filter sample transaction.
     Returns number of results found.
     To select all of a certain field, leave that field empty for
     strings or 0 for integer values and dates.
     Results are added to results parameter.
   */
  virtual int filterTransactions(Transaction filter,
                                 std::vector& <Transaction> results) = 0;

  /* Returns all transactions between start and end, returns number
     of entries found and places results in reults.
     Leave a date = 0 to start from beginning or go to end of list.
  */
  virtual int filterDates(const struct tm& start,
                          const struct tm& end,
                          std::vector& <Transaction> results) = 0;

  /* Finds all transactions that match filter between dates start
     and end based on filter.  Results given in results and number
     of results returned.
     Leave a date = 0 to start from beginning or go to end of list.
  */
  virtual int filterDatesWithType(const struct tm& start,
                       const struct tm& end,
                       Transaction filter,
                       std::vector& <Transaction> results) = 0;



protected:
  std::string accountType_;
  std::string accountName_;
  std::string accountID_;
  long long accountBalance_;

private:
  std::vector<Transaction> transactions_;

};
#endif
