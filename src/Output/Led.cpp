#include "Led.h"
#include <Arduino.h>
void Led::begin(uint8_t pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
}

// void Led::on();
// void Led::off();