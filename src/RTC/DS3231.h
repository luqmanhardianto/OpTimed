
#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <Wire.h>

#include "DateTime.h"

class DS3231 {
private:
  static constexpr uint8_t I2C_ADDRESS = 0x68;

  static constexpr uint8_t REG_SECONDS = 0x00;
  static constexpr uint8_t REG_MINUTES = 0x01;
  static constexpr uint8_t REG_HOURS = 0x02;

  static constexpr uint8_t REG_DAY = 0x03;
  static constexpr uint8_t REG_DATE = 0x04;
  static constexpr uint8_t REG_MONTH = 0x05;
  static constexpr uint8_t REG_YEAR = 0x06;

  static constexpr uint8_t REG_CONTROL = 0x0E;
  static constexpr uint8_t REG_STATUS = 0x0F;

  static constexpr uint8_t CONTROL_RS1 = 3;
  static constexpr uint8_t CONTROL_RS2 = 4;
  static constexpr uint8_t CONTROL_INTCN = 2;

  static constexpr uint8_t STATUS_OSF = 7;

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

  bool readDateTime(DateTime &dateTime);
  bool writeDateTime(const DateTime &dateTime);

  bool set24HourMode();
  bool setSqw1Hz();

  bool isOscillatorStopped();
  bool clearOscillatorStopFlag();

  bool isConnected();
};