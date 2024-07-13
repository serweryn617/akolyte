#pragma once

#include "pico/stdlib.h"
#include <array>

constexpr uint i2c_baudrate = 200'000;

#if SIDE == 0 // left

constexpr std::array<uint, 5> keypad_in_pins = { 8, 6, 7, 5, 4 };
constexpr std::array<uint, 6> keypad_out_pins = { 13, 14, 15, 12, 11, 10 };

constexpr uint ext_i2c_scl = 3;
constexpr uint ext_i2c_sda = 2;

constexpr uint led_builtin = 16;

#elif SIDE == 1 // right

constexpr std::array<uint, 5> keypad_in_pins = { 11, 12, 10, 13, 14 };
constexpr std::array<uint, 6> keypad_out_pins = { 4, 5, 6, 7, 8, 9 };

constexpr uint ext_i2c_scl = 3;
constexpr uint ext_i2c_sda = 2;

constexpr uint led_builtin = 16;

#endif