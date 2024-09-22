#include "pico/stdlib.h"
#include "keypad/keypad.hpp"

namespace lib::keypad {

Keypad::Keypad(const std::array<uint, 5UL> &in_pins_, const std::array<uint, 6UL> &out_pins_)
    : in_pins(in_pins_)
    , out_pins(out_pins_)
{
}

void Keypad::init_gpio()
{
    for (auto &&pin : in_pins) {
        gpio_init(pin);
        gpio_set_dir(pin, false);
        gpio_pull_down(pin);
    }

    for (auto &&pin : out_pins) {
        gpio_init(pin);
        gpio_set_dir(pin, true);
        gpio_put(pin, false);
    }
}

uint32_t Keypad::get_state()
{
    uint32_t state = 0;

    for (size_t col = 0; col < 6; col++) {
        auto ith_col_pin = out_pins[col];
        gpio_put(ith_col_pin, true);
        sleep_us(1);

        for (size_t row = 0; row < 5; row++) {
            auto jth_row_pin = in_pins[row];
            state |= gpio_get(jth_row_pin) << (row * 6 + col);
        }

        gpio_put(ith_col_pin, false);
    }

    return state;
}

}  // namespace lib::keypad
