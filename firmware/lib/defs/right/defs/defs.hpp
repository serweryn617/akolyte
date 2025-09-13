#ifndef DEFS_DEFS_HPP
#define DEFS_DEFS_HPP

#include "defs/base.hpp"
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <array>

namespace config {
    constexpr uint left = 0;
    constexpr uint right = 1;
    constexpr uint side = right;
}

constexpr std::array<uint, num_in_pins> keypad_in_pins = { 12, 10, 13, 14 };
constexpr std::array<uint, num_out_pins> keypad_out_pins = { 4, 5, 6, 7, 8, 9 };

constexpr uint ext_i2c_scl = 3;
constexpr uint ext_i2c_sda = 2;

constexpr i2c_inst_t *oled_i2c = i2c0;
constexpr uint oled_i2c_sda = 0;
constexpr uint oled_i2c_scl = 1;
constexpr uint oled_i2c_address = 0x3C;

constexpr uint led_builtin = 16;

#endif  // DEFS_DEFS_HPP
