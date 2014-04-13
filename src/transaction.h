#ifndef _TRANSACTION_H_
#define _TRANSACTION_H_

#include <string>
#include <time.h>
#include "money.h"

//Helper function to compare two date structs
//Only compares: s/m/hr/day/month/year
bool isSameDate(const struct tm& lhs, const struct tm& rhs);

//Helper function to clear the time.
//Sets time to January 1, 1900; 12:00:00 AM
void clearTime(struct tm& date);

struct Transaction {
  unsigned long long ID;
  std::string description;
  std::string transactionType;
  std::string majorCategory;
  std::string minorCategory;
  struct tm transactionDate;
  Currency transactionAmount;

  //Emptry constructor to set up struct correctly.
  Transaction()
  : ID(0), description(""), transactionType(""),
    majorCategory(""), minorCategory(""), transactionAmount("")
  {
    clearTime(transactionDate);
  }
  
  Transaction(  unsigned long long ID_,
                const std::string& description_,
                const std::string& transactionType_,
                const std::string& majorCategory_,
                const std::string& minorCategory_,
                const struct tm& transactionDate_,
                const Currency& transactionAmount_ )
  {
    ID = ID_;
    description = description_;
    transactionType = transactionType_;
    majorCategory = majorCategory_;
    minorCategory = minorCategory_;
    transactionAmount = transactionAmount_;

    transactionDate.tm_sec = transactionDate_.tm_sec;
    transactionDate.tm_min = transactionDate_.tm_min;
    transactionDate.tm_hour = transactionDate_.tm_hour;
    transactionDate.tm_mday = transactionDate_.tm_mday;
    transactionDate.tm_mon = transactionDate_.tm_mon;
    transactionDate.tm_year = transactionDate_.tm_year;
    transactionDate.tm_wday = transactionDate_.tm_wday;
    transactionDate.tm_yday = transactionDate_.tm_yday;
    transactionDate.tm_isdst = transactionDate_.tm_isdst;
  }
  
  Transaction& operator=(const Transaction& rhs) {
    ID = rhs.ID;
    description = rhs.description;
    majorCategory = rhs.majorCategory;
    minorCategory = rhs.minorCategory;

    transactionAmount = rhs.transactionAmount;

    transactionDate.tm_sec = rhs.transactionDate.tm_sec;
    transactionDate.tm_min = rhs.transactionDate.tm_min;
    transactionDate.tm_hour = rhs.transactionDate.tm_hour;
    transactionDate.tm_mday = rhs.transactionDate.tm_mday;
    transactionDate.tm_mon = rhs.transactionDate.tm_mon;
    transactionDate.tm_year = rhs.transactionDate.tm_year;
    transactionDate.tm_wday = rhs.transactionDate.tm_wday; 
    transactionDate.tm_yday = rhs.transactionDate.tm_yday;
    transactionDate.tm_isdst = rhs.transactionDate.tm_isdst;

    return *this;
  }
  
  bool operator==(const Transaction& rhs) const {
    return  (
              ID == rhs.ID &&
              description == rhs.description &&
              majorCategory == rhs.majorCategory &&
              minorCategory == rhs.minorCategory &&
              transactionAmount == rhs.transactionAmount &&
              isSameDate(transactionDate, rhs.transactionDate)
            );  
  }
  bool operator!=(const Transaction& rhs) const {
    return !(*this == rhs);
  } 
};


#endif
