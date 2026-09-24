#pragma once

#define I2C_PIN_SDA A4
#define I2C_PIN_SCL A5

namespace SystemTiming {
constexpr uint16_t DEBOUNCE_MS = 100;
constexpr uint16_t LONGPRESS_MS = 1000;
constexpr uint16_t BLINK_MS = 500;
}
