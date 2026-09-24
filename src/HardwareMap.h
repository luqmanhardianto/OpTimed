#pragma once
/*  
single source of truth for every pin.
no logic here, ever, every other file includes THIS instead of
writing a raw pin number
*/
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

enum class DigitalOutput : uint8_t {
  BUZZER = 0,
  POWER_LED,
};

constexpr uint8_t DO_PINS[]{
  3, 12
};