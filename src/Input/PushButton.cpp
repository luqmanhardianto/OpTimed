#include <Arduino.h>
#include "PushButton.h"

void PushButton::begin(uint8_t pin) {
  this->input.begin(pin);
}

void PushButton::readState() {
  input.readState();
}

bool PushButton::isPressed() const {
  return input.isActive();
}