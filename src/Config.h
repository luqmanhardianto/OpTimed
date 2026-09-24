#pragma once

#define I2C_PIN_SDA A4
#define I2C_PIN_SCL A5

namespace SystemTiming {
constexpr uint8_t DEBOUNCE_MS = 100;
constexpr uint8_t LONGPRESS_MS = 1000;
constexpr uint8_t BLINK_MS = 500;
}

#define DS3231_ADDRESS 0x68