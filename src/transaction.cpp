#include "transaction.h"

//Helper function to clear the time.
//Sets time to January 1, 1900; 12:00:00 AM
void clearTime(struct tm& date) {
  date.tm_sec = 0;
  date.tm_min = 0;
  date.tm_hour = 0;
  date.tm_mday = 1;
  date.tm_mon = 0;
  date.tm_year = 0;
  date.tm_wday = 0;
  date.tm_yday = 0;
  date.tm_isdst = 0;
}

//Helper function to compare two date structs
//Only compares: s/m/hr/day/month/year
bool isSameDate(const struct tm& lhs, 
                const struct tm& rhs) {
  return (
    lhs.tm_sec == rhs.tm_sec &&
    lhs.tm_min == rhs.tm_min &&
    lhs.tm_hour == rhs.tm_hour &&
    lhs.tm_mday == rhs.tm_mday &&
    lhs.tm_mon == rhs.tm_mon &&
    lhs.tm_year == rhs.tm_year
  );

}
