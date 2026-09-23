#include <Arduino.h>
#include "PushButton.h"

void PushButton::begin(DigitalInput input) {
  this->input.begin(input);
}

void PushButton::readState() {
  input.readState();
}

bool PushButton::isPressed() const {
  return input.isActive();
}