#pragma once  // TODO: use ifdef

#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include <array>

constexpr uint num_in_pins = 4;
constexpr uint num_out_pins = 6;
constexpr uint num_keys = num_in_pins * num_out_pins;
static_assert(num_keys <= 32, "Number of keys must be <=32 as uint32_t is used to keep state information.");

constexpr uint i2c_baudrate = 200'000;

#if SIDE == 0 // left

constexpr std::array<uint, num_in_pins> keypad_in_pins = { 6, 7, 5, 4 };
constexpr std::array<uint, num_out_pins> keypad_out_pins = { 13, 14, 15, 12, 11, 10 };

constexpr uint ext_i2c_scl = 3;
constexpr uint ext_i2c_sda = 2;

constexpr i2c_inst_t *oled_i2c = i2c0;
constexpr uint oled_i2c_sda = 0;
constexpr uint oled_i2c_scl = 1;
constexpr uint oled_i2c_address = 0x3C;

constexpr uint led_builtin = 16;

#elif SIDE == 1 // right

constexpr std::array<uint, num_in_pins> keypad_in_pins = { 12, 10, 13, 14 };
constexpr std::array<uint, num_out_pins> keypad_out_pins = { 4, 5, 6, 7, 8, 9 };

constexpr uint ext_i2c_scl = 3;
constexpr uint ext_i2c_sda = 2;

constexpr i2c_inst_t *oled_i2c = i2c0;
constexpr uint oled_i2c_sda = 0;
constexpr uint oled_i2c_scl = 1;
constexpr uint oled_i2c_address = 0x3C;

constexpr uint led_builtin = 16;

#endif