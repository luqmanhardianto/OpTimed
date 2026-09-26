#pragma once

#define I2C_PIN_SDA A4
#define I2C_PIN_SCL A5

/*
system timing using millis()
e.g. debounce, event, blink, and other timing
this timing not use for timing reference for
clock, stopwatch, countdown
*/
namespace SystemTiming {
// input deboucne timing
constexpr uint16_t DEBOUNCE_MS = 100;
// input longpress event timing
constexpr uint16_t LONGPRESS_MS = 1000;
// repeat event start timing
constexpr uint16_t REPEAT_START_MS = 500;
// repeat interval timing
constexpr uint16_t REPEAT_INTERVAL_MS = 150;
// blink timing
constexpr uint16_t BLINK_MS = 500;
}
