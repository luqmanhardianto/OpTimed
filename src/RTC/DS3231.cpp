#include "DS3231.h"
#include <Wire.h>


bool DS3231::begin() {
  Wire.begin();
  return isCOnnected();
}

bool DS3231::readDateTIme(DateTime &dateTime);
bool DS3231::writeDateTime(const DateTime &dateTime);

bool DS3231::set24HourMode();
bool DS3231::setSqw1Hz();

bool DS3231::isOscillatorStopped();
bool DS3231::clearOscillatorStopFlag();

bool DS3231::isCOnnected() {
  Wire.beginTransmission(I2C_ADDRESS);
  return Wire.endTransmission() == 0;
}