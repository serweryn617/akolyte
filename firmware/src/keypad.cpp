#include "pico/stdlib.h"
#include "keypad.hpp"
#include "defs.hpp"

Keypad::Keypad()
{
}

void Keypad::init_gpio()
{
    for (auto &&pin : keypad_in_pins) {
        gpio_init(pin);
        gpio_set_dir(pin, false);
        gpio_pull_down(pin);
    }

    for (auto &&pin : keypad_out_pins) {
        gpio_init(pin);
        gpio_set_dir(pin, true);
    }
}

uint32_t Keypad::get_state()
{
    uint32_t state = 0;

    // Columns
    for (size_t col = 0; col < 6; col++) {
        // Clear columns
        for (auto &&pin : keypad_out_pins) {
            gpio_put(pin, false);
        }
        sleep_us(1);

        // Set i-th column
        auto ith_col_pin = keypad_out_pins[col];
        gpio_put(ith_col_pin, true);
        sleep_us(1);

        // Read rows
        for (size_t row = 0; row < 5; row++) {
            auto jth_row_pin = keypad_in_pins[row];
            state |= gpio_get(jth_row_pin) << (row * 6 + col);
        }
    }

    return state;
}
