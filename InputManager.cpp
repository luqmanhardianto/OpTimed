#include "InputManager.h"
#include "HardwareMap.h"

#include <Arduino.h>
#include <stdint.h>

void InputManager::begin(DigitalInput input) {
  this->pin = DI_PINS[static_cast<uint8_t>(input)];
  pinMode(this->pin, INPUT_PULLUP);
}

void InputManager::readState() {
}

bool InputManager::isActive() const {
  return stableinputState == LOW;
}