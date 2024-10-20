#ifndef LIB_KEYPAD_KEYPAD_HPP
#define LIB_KEYPAD_KEYPAD_HPP

#include "pico/stdlib.h"
#include "defs/defs.hpp"
#include <array>

namespace lib::keypad {

class Keypad
{
public:
    typedef std::array<uint, num_in_pins> in_array;
    typedef std::array<uint, num_out_pins> out_array;

    Keypad(const in_array &in_pins_, const out_array &out_pins_);
    void init_gpio();
    uint32_t get_state();
private:
    const in_array &in_pins;
    const out_array &out_pins;
};

}  // namespace lib::keypad

#endif  // LIB_KEYPAD_KEYPAD_HPP