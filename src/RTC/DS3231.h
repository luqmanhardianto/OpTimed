
#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>

#include "DateTime.h"

class DS3231 {
private:
  bool readRegisters(
    uint8_t address,
    uint8_t *buffer,
    uint8_t length);
  bool writeRegisters(
    uint8_t address,
    const uint8_t *buffer,
    uint8_t length);

  uint8_t bcdToDec(uint8_t value);
  uint8_t decToBcd(uint8_t value);
public:
  bool begin();

  bool readDateTIme(DateTime &dateTime);
  bool writeDateTime(const DateTime &dateTime);

  bool set24HourMode();
  bool setSqw1Hz();

  bool isOscillatorStopped();
  bool clearOscillatorStopFlag();

  bool isCOnnected();
};