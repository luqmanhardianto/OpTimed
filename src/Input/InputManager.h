#pragma once

#include <Arduino.h>
#include <stdint.h>

#include "../Config.h"
#include "../HardwareMap.h"

class InputManager {
private:
  uint8_t pin;

  bool lastInputState = HIGH;
  bool stableinputState = HIGH;

  unsigned long lastTimeStateChanged = 0;
  unsigned long debounceTimeMs = INPUT_DEBOUNCE_MS;

public:
  void begin(DigitalInput input);
  void readState();
  bool isActive() const;
};