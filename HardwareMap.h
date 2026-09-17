#pragma once

#include <stdint.h>

enum class DigitalInput : uint8_t {
  BUTTON_POWER = 0,
  BUTTON_SELECT,
  BUTTON_NEXT,
  BUTTON_UP,
  BUTTON_DOWN
};

constexpr uint8_t DI_PINS[] = {
  4, 5, 6, 7, 8
};