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

ButtonEvent PushButton::update() {

  // record millis
  const unsigned long now = millis();

  // state push button
  const bool pressed = isPressed();

  // button has just been pressed.
  if (pressed && !wasPressed) {
    // record start press time
    pressStartTime = now;

    // record last repeat time
    lastRepeatTime = now;

    // this condition is not long press button event, set false
    longPressSent = false;

    // this condition is not repeat button event, set false
    repeatStarted = false;

    // this condition is button pressed, set true
    wasPressed = true;

    // return button event BTN_NONE
    return BTN_NONE;
  }
}