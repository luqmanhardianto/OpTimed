#include "DateTime.h"

bool isLeapYear(uint16_t year) {
  if ((year % 400) == 0) {
    return true;
  }

  if ((year % 100) == 0) {
    return false;
  }

  return (year % 4) == 0;
}

uint8_t daysInMonth(uint16_t year, uint8_t month) {
  switch (month) {
    case 1:
      return 31;

    case 2:
      return isLeapYear(year) ? 29 : 28;

    case 3:
      return 31;

    case 4:
      return 30;

    case 5:
      return 31;

    case 6:
      return 30;

    case 7:
      return 31;

    case 8:
      return 31;

    case 9:
      return 30;

    case 10:
      return 31;

    case 11:
      return 30;

    case 12:
      return 31;

    default:
      return 0;
  }
}

bool isValidDAteTime(const DateTime &dateTime);