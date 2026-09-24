#include <cstdint>
#include "DS3231.h"
#include <Wire.h>

uint8_t DS3231::bcdToDec(uint8_t value);
uint8_t DS3231::decToBcd(uint8_t value);

bool DS3231::begin() {
  Wire.begin();
  return isConnected();
}

bool DS3231::isConnected() {
  Wire.beginTransmission(I2C_ADDRESS);
  return Wire.endTransmission() == 0;
}

bool DS3231::readRegisters(
  uint8_t address,
  uint8_t *buffer,
  uint8_t length) {
  if (buffer == nullptr || length == 0) {
    return false;
  }

  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(address);

  if (Wire.endTransmission(false) != 0) {
    return false;
  }

  uint8_t received = Wire.requestFrom(
    I2C_ADDRESS,
    length);

  if (received != length) {
    return false;
  }

  for (uint8_t i = 0; i < length; ++i) {
    buffer[i] = Wire.read();
  }

  return true;
}

bool DS3231::writeRegisters(
  uint8_t address,
  const uint8_t *buffer,
  uint8_t length) {

  if (buffer == nullptr || length == 0) {
    return false;
  }

  Wire.beginTransmission(I2C_ADDRESS);
  Wire.write(address);

  for (uint8_t i = 0; i < length; ++i) {
    Wire.write(buffer[i]);
  }

  return Wire.endTransmission() == 0;
}

bool DS3231::readDateTime(DateTime &dateTime);
bool DS3231::writeDateTime(const DateTime &dateTime);

bool DS3231::set24HourMode();
bool DS3231::setSqw1Hz();

bool DS3231::isOscillatorStopped();
bool DS3231::clearOscillatorStopFlag();
