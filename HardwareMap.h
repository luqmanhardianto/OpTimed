#pragma once

#include <stdint.h>

enum class DigitalInput : uint8_t {
  BUTTON_POWER = 0,
  BUTTON_SELECT,
  BUTTON_NEXT,
  BUTTON_UP,
  BUTTON_DOWN
};