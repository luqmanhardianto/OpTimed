#include "PushButton.h"

void PushButton::begin(DigitalInput input) {
  this->input.begin(input);
}

void PushButton::readState() {
}

bool PushButton::isPressed() {
}