#ifndef BASE_DEFS_HPP
#define BASE_DEFS_HPP

#include "pico/stdlib.h"

constexpr uint num_in_pins = 4;
constexpr uint num_out_pins = 6;
constexpr uint num_keys = num_in_pins * num_out_pins;
static_assert(num_keys <= 32, "Number of keys must be <=32 as uint32_t is used to keep state information.");

constexpr uint i2c_baudrate = 400'000;

#endif  // INC_DEFS_HPP
