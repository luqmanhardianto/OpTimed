#include "DateTime.h"
#include "DS3231.h"
#include <Wire.h>

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

// convert packed BCD to DEC e.g. value is 0001_0010
uint8_t DS3231::bcdToDec(uint8_t value) {
  // left get upper nibble + right lower nibble
  // left side
  // 0000_0001 -> (1) * 10 = (10)
  // right side
  // 0001_0010 & 0000_1111 = 0000_0010 -> (2)
  // return is 10 + 2 = 12 DEC
  return ((value >> 4) * 10 + (value & 0x0F));  // 0x0F = 0000_1111 (masking)
}

// convert DEC to BCD e.g. value is 12
uint8_t DS3231::decToBcd(uint8_t value) {
  // left get upper nibble and right side get lower nibble and combine it
  // left side
  // 12 / 10 = 1 -> 0000_0001 << 4 = 0001_0000
  // right side
  // 12 % 10 = 2 -> 0000_0010
  // result is combine both using bitwise OR operation
  // 0001_0000 | 0000_0010 = 0001_0010
  return ((value / 10) << 4 | (value % 10));
}

bool DS3231::readDateTime(DateTime &dateTime) {
  uint8_t registers[7];

  if (!readRegisters(
        REG_SECONDS,
        registers,
        sizeof(registers))) {
    return false;
  }

  uint8_t seconds = registers[0] & 0x7F;  // 0x7F = 0111_1111
  uint8_t minutes = registers[1] & 0x7F;
  uint8_t hoursRegister = registers[2];

  uint8_t hours;

  // DS3231 hour register:
  // bit 6 = 12/24-hour mode
  // bit 5 = AM/PM in 12-hour mode
  if (hoursRegister & 0x40) {  //  0x40 = 0100_0000
    // 12-hour mode
    uint8_t hour12 = bcdToDec(hoursRegister & 0x1F);  //  0x1F = 0001_1111
    bool pm = (hoursRegister & 0x20) != 0;            //  0x20 = 0010_0000

    if (hour12 < 1 || hour12 > 12) {
      return false;
    }

    if (pm) {
      hours = (hour12 == 12) ? 12 : hour12 + 12;
    } else {
      hours = (hour12 == 12) ? 0 : hour12;
    }

  } else {
    // 24-hour mode
    hours = bcdToDec(hoursRegister & 0x3F);  // 0x3F = 0011_1111 (masking)
  }

  uint8_t day = registers[3] & 0x07;              // 0x07 = 0000_0111
  uint8_t date = bcdToDec(registers[4] & 0x3F);   // 0x3F = 0011_1111
  uint8_t month = bcdToDec(registers[5] & 0x1F);  // 0x1F = 0001_1111
  uint8_t year = bcdToDec(registers[6]);

  // ds3231 year register represents 00-99.
  // optimed currenlty supports 200-2099.
  uint16_t fullYear = 2000 + year;

  // day-of-week is stored in the rtc but is not part
  // of DateTime, so only validate its register range.
  if (day < 1 || day > 7) {
    return false;
  }

  DateTime result;

  result.year = fullYear;
  result.month = month;
  result.day = day;
  result.hour = hours;
  result.minute = bcdToDec(minutes);
  result.second = bcdToDec(seconds);

  if (!result.isValid()) {
    return false;
  }

  dateTime = result;

  return true;
}

bool DS3231::writeDateTime(const DateTime &dateTime) {
  // validate rtc
  if (!dateTime.isValid()) {
    return false;
  }

  uint8_t registers[7];

  // put data second, minute into registers
  registers[0] = decToBcd(dateTime.second);
  registers[1] = decToBcd(dateTime.minute);

  // always write 24-hour mode.
  registers[2] = decToBcd(dateTime.hour);

  // day-of-week is not represented by DateTime.
  // use 1 as a valid default value.
  registers[3] = 1;

  // put data day,month, year to registers
  registers[4] = decToBcd(dateTime.day);
  registers[5] = decToBcd(dateTime.month);
  registers[6] = decToBcd(dateTime.year - 2000);

  // write all data to rtc
  return writeRegisters(
    REG_SECONDS,
    registers,
    sizeof(registers));
}

bool DS3231::set24HourMode() {

  uint8_t hoursRegister;

  // validate read data hour only
  if (!readRegisters(
        REG_HOURS,
        &hoursRegister,
        1)) {
    return false;
  }

  // if already in 24-hour mode, nothing to change.
  // 0x40 = 0[1]00_0000
  // bit 6 = 0 -> 24-hour mode
  if ((hoursRegister & 0x40) == 0) {
    return true;
  }

  // masking get data 12-hour mode
  // 0x1F = 0001_1111
  uint8_t hour12 = bcdToDec(hoursRegister & 0x1F);

  // get AM/PM state in 12-hour mode.
  // 0x20 = 00[1]0_0000
  // bit 5 = 1 -> PM
  bool pm = (hoursRegister & 0x20) != 0;

  // validate 12-hour mode data range (1-12)
  if (hour12 < 1 || hour12 > 12) {
    return false;
  }

  uint8_t hour24;

  // convert 12-hour format to 24-hor format
  if (pm) {
    hour24 = (hour12 == 12) ? 12 : hour12 + 12;
  } else {
    hour24 = (hour12 == 12) ? 0 : hour12;
  }

  // put data 24-hour format to hoursRegister
  // e.g. hour24 = 23
  // result decToBcd = 0[0]10_0011
  // bit 6 = 0 -> 24-hour format
  hoursRegister = decToBcd(hour24);

  // write data 24-hour mode to rtc
  return writeRegisters(
    REG_HOURS,
    &hoursRegister,
    1);
}

bool DS3231::setSqw1Hz() {

  uint8_t control;

  // validate read control register only
  if (!readRegisters(
        REG_CONTROL,
        &control,
        1)) {
    return false;
  }

  /*
  RS1 = 0
  RS2 = 0
  INTCN = 0
  result:
  SQW output = 1Hz
  SQW/INT is used as square-wave output
  */

  // set bit 3 RS1 = 0
  control &= ~(1 << CONTROL_RS1);
  // set bit 4 RS2 = 0
  control &= ~(1 << CONTROL_RS2);
  // set bit 2 INTCN = 0
  control &= ~(1 << CONTROL_INTCN);

  // write config RS1,RS2,INTCN to rtc
  return writeRegisters(
    REG_CONTROL,
    &control,
    1);
}

bool DS3231::isOscillatorStopped() {

  uint8_t status;

  // validate communication read status register only
  if (!readRegisters(
        REG_STATUS,
        &status,
        1)) {
    /*
      communication failure is not same
      as an oscillator-stop indication.
      */
    return false;
  }

  // return status OSF
  // 1 = stop
  // 0 = running
  return (status & (1 << STATUS_OSF) != 0);
}

bool DS3231::clearOscillatorStopFlag() {

  uint8_t status;

  // validate communication read status OSF only
  if (!readRegisters(
        REG_STATUS,
        &status,
        1)) {
    // communication failure
    return false;
  }

  // change bit 7 OSF from 1 to 0
  status &= ~(1 << STATUS_OSF);

  // write OSF status = 0 to rtc
  return writeRegisters(
    REG_STATUS,
    &status,
    1);
}