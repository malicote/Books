#ifndef _ACCOUNT_H_
#define _ACCOUNT_H_

#include <string>
#include <vector>

#include "transaction.h"

/* TODO: Add destructors. */

class Account {

public:

  Account(const std::string& type,
                  const std::string& name,
                  const std::string& ID);

  /* Use if we already have a transactions list */
  Account(const std::string& type,
                  const std::string& name,
                  const std::string& ID,
                  const std::vector<Transaction>& transactions);

  /* Will eventually throw exception on error */
  virtual void addTransaction(const Transaction& transaction);
  virtual void removeTransaction(const std::string& ID);
  virtual void removeTransaction(const Transaction& transaction);

  virtual long long getBalance() {
    return accountBalance_;
  }

  /* Filters transactions based on the filter sample transaction.
     Returns number of results found.
     To select all of a certain field, leave that field empty for
     strings or 0 for integer values and dates.
     Results are added to results parameter.
   */
  virtual int filterTransactions(const Transaction& filter,
                                 std::vector<Transaction>& results);

  /* Returns all transactions between start and end, returns number
     of entries found and places results in reults.
     Leave a date = 0 to start from beginning or go to end of list.
  */
  virtual int filterDates(const struct tm& start,
                          const struct tm& end,
                          std::vector<Transaction>& results);

  /* Finds all transactions that match filter between dates start
     and end based on filter.  Results given in results and number
     of results returned.
     Leave a date = 0 to start from beginning or go to end of list.
  */
  virtual int filterDatesWithType(const struct tm& start,
                       const struct tm& end,
                       const Transaction& filter,
                       std::vector<Transaction>& results);

protected:
  // TODO: Make derived classes have this available
  Account();

private:
  std::string accountType_;
  std::string accountName_;
  std::string accountID_;
  long long accountBalance_;
  std::vector<Transaction> transactions_;

  /* TODO: Move this to implementation and hide. */
  /* Updates balance */
  void updateAccountBalance();
};
#endif
