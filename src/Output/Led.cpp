#include "Led.h"
#include <Arduino.h>
void Led::begin(uint8_t pin) {
  _pin = pin;
  pinMode(_pin, OUTPUT);
  digitalWrite(_pin, LOW);
}

void Led::on() {
  _state = true;
  digitalWrite(_pin, _state);
}

void Led::off() {
  _state = false;
  digitalWrite(_pin, _state);
}

bool Led::getState() const {
  return _state;
}