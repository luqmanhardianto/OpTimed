
#pragma once

#include <Arduino.h>
#include <cstdint>
class Led {
private:
  uint8_t _pin;
  bool _state = false;
public:
  void begin(uint8_t pin);
  void on();
  void off();
};