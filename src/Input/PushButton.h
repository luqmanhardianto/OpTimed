#pragma once

#include <Arduino.h>

#include "InputManager.h"
#include "../HardwareMap.h"

class PushButton {
private:
  InputManager input;
public:
  void begin(uint8_t pin);
  void readState();
  bool isPressed() const;
};