#pragma once

#include <Arduino.h>

#include "InputManager.h"
#include "HardwareMap.h"

class PushButton {
private:
  InputManager input;
public:
  void begin(DigitalInput input);
  void readState();
  bool isPressed();
};