#include "account.h"

/* Protected to prevent anyone except derived classes from using this */
Account::Account()
: accountType_(""), accountName_(""), accountID_(""), accountBalance_(0LL)
{

}

/* Standard constructor which sets up the account */
Account::Account(const std::string& type,
                 const std::string& name,
                 const std::string& ID)
{
  accountType_ = type;
  accountName_ = name;
  accountID_ = ID;
  accountBalance_ = 0LL;
}

Account::Account(const std::string& type,
                 const std::string& name,
                 const std::string& ID,
                 const std::vector<Transaction>& transactions)
{
  accountType_ = type;
  accountName_ = name;
  accountID_ = ID;
  transactions_ = transactions;
  updateAccountBalance();
}

void Account::addTransaction(const Transaction& transaction)
{

}

void Account::removeTransaction(const std::string& ID)
{

}

void Account::removeTransaction(const Transaction& transaction)
{

}

int Account::filterTransactions(const Transaction& filter,
                                std::vector<Transaction>& results)
{
  return 0;
}

int Account::filterDates(const struct tm& start,
                         const struct tm& end,
                         std::vector<Transaction>& results)
{
  return 0;
}

int Account::filterDatesWithType(const struct tm& start,
                     const struct tm& end,
                     const Transaction& filter,
                     std::vector<Transaction>& results)
{
  return 0;
}

void Account::updateAccountBalance() {

}
