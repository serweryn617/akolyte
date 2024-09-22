#pragma once

#include "hid_keycodes.hpp"
#include "pico/stdlib.h"
#include "types.h"

constexpr int num_keycodes = 12;

typedef struct __attribute__((packed))
{
    uint8_t modifiers;              /**< Keyboard modifier (KEYBOARD_MODIFIER_* masks). */
    uint8_t reserved;               /**< Reserved for OEM use, always set to 0. */
    uint8_t keycodes[num_keycodes]; /**< Key codes of the currently pressed keys. */
} hid_keyboard_report;

class TinyUSB
{
private:
    uint8_t keycodes[num_keycodes];
    uint8_t index;
    uint8_t modifiers;

    bool reversed_shift;
    tinyusb_callback &tusb_cb;

    bool set_modifiers(uint8_t keycode, bool state);
    void set_modifier_bit(uint8_t bit, bool state);
    void add_keycode(uint8_t keycode);
    void remove_keycode(uint8_t keycode);
    void reverse_shift();

    void send_report();
    bool keyboard_report();
    bool send_hid_report(uint8_t report_id);

public:
    TinyUSB(tinyusb_callback &_tusb_cb);
    void init();
    void device_task();
    void set_key(hid_key key, bool state);
    bool hid_task();
    bool ready();
};
