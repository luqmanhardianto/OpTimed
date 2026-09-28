
#pragma once

#include <Arduino.h>

#include "InputManager.h"
#include "../HardwareMap.h"

enum ButtonEvent : uint8_t {
  BTN_NONE = 0,
  BTN_SHORT_PRESS,
  BTN_LONG_PRESS,
  BTN_REPEAT
};

class PushButton {
private:
  InputManager input;

  bool wasPressed = false;
  bool longPressSent = false;
  bool repeatStarted = false;

  unsigned long pressStartTime = 0;
  unsigned long lastRepeatTime = 0;
public:
  void begin(uint8_t pin);
  void readState();
  bool isPressed() const;
  ButtonEvent update();
};