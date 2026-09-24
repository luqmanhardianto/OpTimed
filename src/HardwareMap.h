#pragma once
/*  
single source of truth for every pin.
no logic here, ever, every other file includes THIS instead of
writing a raw pin number
*/
#include <stdint.h>
#include <Arduino.h>

namespace DigitalInput {
enum Pin : uint8_t {
  BUTTON_POWER = 4,
  BUTTON_SELECT,
  BUTTON_NEXT,
  BUTTON_UP,
  BUTTON_DOWN,
};
}

namespace DigitalOutput {
enum Pin : uint8_t {
  BUZZER = 3,
  POWER_LED = 12,
};
}
