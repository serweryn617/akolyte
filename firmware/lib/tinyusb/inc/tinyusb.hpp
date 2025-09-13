#pragma once

#include "hid_keycodes.hpp"
#include "pico/stdlib.h"
#include "types.h"

constexpr int num_bytes = 28;

typedef struct __attribute__((packed))
{
    uint8_t modifiers;
    uint8_t reserved;
    uint8_t keycodes[num_bytes];
} hid_keyboard_report;

class TinyUSB
{
private:
    uint8_t keycodes[num_bytes * 8];
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
