#include <Arduino.h>
#include "PushButton.h"

void PushButton::begin(uint8_t pin) {
  this->input.begin(pin);

  // init first state private variable value
  wasPressed = false;
  longPressSent = false;
  repeatStarted = false;

  pressStartTime = 0;
  lastRepeatTime = 0;
}

void PushButton::readState() {
  input.readState();
}

bool PushButton::isPressed() const {
  return input.isActive();
}