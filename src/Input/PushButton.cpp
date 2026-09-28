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

  // button is currently hold.
  if (pressed && wasPressed) {

    // record start hhold time
    const unsigned long heldTime = now - pressStartTime;

    // long press event : emit once
    if (!longPressSent && heldTime >= SystemTiming::LONGPRESS_MS) {

      // button pressed more than timing LONGPRESS_MS, set true.
      longPressSent = true;

      // this condition not repeat event, set false
      repeatStarted = false;

      // update last repeat time
      lastRepeatTime = now;

      // return ButtonEvent : BTN_LONG_PRESS
      return BTN_LONG_PRESS;
    }

    // repeat event begin after REPEAT_START_MS
    if (longPressSent) {

      // record repeat time
      const unsigned long repeatTime = now - lastRepeatTime;

      // first time repeat start event
      if (!repeatStarted) {

        // ButtonEvent Repeat is started after REPEAT_START_MS
        if (heldTime >= SystemTiming::LONGPRESS_MS + SystemTiming::REPEAT_START_MS) {

          // this condition repeat, set true
          repeatStarted = true;

          // update last repeat time
          lastRepeatTime = now;

          // return ButtonEvent : BTN_REPEAT
          return BTN_REPEAT;
        }

        // condition for continuous repeat after REPEAT_INTERVAL_MS
      } else if (repeatTime >= SystemTiming::REPEAT_INTERVAL_MS) {

        // update repeat time
        lastRepeatTime = now;

        // return ButtonEvent : BTN_REPEAT
        return BTN_REPEAT;
      }
    }

    // return ButtonEvent : BTN_NONE
    return BTN_NONE;
  }

  // button has just been released
  if (!pressed && wasPressed) {

    // record held time
    const unsigned long heldTime = now - pressStartTime;

    // update state for button is released
    wasPressed = false;

    // if long press was already emitted, don't generate a short press
    if (longPressSent) {

      // long press state, set false
      longPressSent = false;

      // repeat state , set false
      repeatStarted = false;

      // ButtonEvent : BTN_NONE
      return BTN_NONE;
    }

    // release before long-press threshold
    if (heldTime < SystemTiming::LONGPRESS_MS) {

      // ButtonEvent:BTN_SHORT_PRESS
      return BTN_SHORT_PRESS;
    }

    // ButtonEvent :BTN_NONE
    return BTN_NONE;
  }

  // ButtonEvent : BTN_NONE
  return BTN_NONE;
}