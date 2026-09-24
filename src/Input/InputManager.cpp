#include <Arduino.h>
#include <stdint.h>

#include "InputManager.h"
#include "../HardwareMap.h"

void InputManager::begin(uint8_t pin) {
  this->pin = pin;
  pinMode(this->pin, INPUT_PULLUP);
}

void InputManager::readState() {
  bool currentInputState = digitalRead(pin);

  if (currentInputState != lastInputState) {
    lastTimeStateChanged = millis();
  }

  if ((millis() - lastTimeStateChanged) > debounceTimeMs) {

    if (currentInputState != stableinputState) {
      stableinputState = currentInputState;
    }
  }
  lastInputState = currentInputState;
}

bool InputManager::isActive() const {
  return stableinputState == LOW;
}