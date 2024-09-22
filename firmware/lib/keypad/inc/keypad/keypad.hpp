#ifndef LIB_KEYPAD_KEYPAD_HPP
#define LIB_KEYPAD_KEYPAD_HPP

#include "pico/stdlib.h"
#include <array>

namespace lib::keypad {

class Keypad
{
public:
    Keypad(const std::array<uint, 5UL> &in_pins_, const std::array<uint, 6UL> &out_pins_);
    void init_gpio();
    uint32_t get_state();

private:
    const std::array<uint, 5UL> &in_pins;
    const std::array<uint, 6UL> &out_pins;
};

}  // namespace lib::keypad

#endif  // LIB_KEYPAD_KEYPAD_HPP