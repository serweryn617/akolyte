#pragma once

#include "pico/stdlib.h"
#include "i2c/i2c_driver.h"
#include "hid_keycodes.hpp"
#include "tinyusb.hpp"
#include "types.h"
#include "keypad/keypad.hpp"
#include "akolyte/keycodes.hpp"
#include "queue/queue.hpp"
#include <array>

class usb_manager
{
private:
    uint32_t state_this = 0;
    uint32_t state_other = 0;
    uint32_t state_this_previous = 0;
    uint32_t state_other_previous = 0;

    uint8_t leds = 0;
    uint8_t leds_previous = 0;

    uint8_t base_layer = 0;
    uint8_t layer = 0;
    bool worker_connected = false;

    TinyUSB &tinyusb;
    drivers::i2c::I2CDriver &i2c_driver;
    tinyusb_callback &tusb_cb;
    lib::keypad::Keypad &keypad;
    lib::queue::Queue &queue;

public:
    usb_manager(TinyUSB &_tinyusb, drivers::i2c::I2CDriver &_i2c_driver, tinyusb_callback &_tusb_cb, lib::keypad::Keypad &_keypad, lib::queue::Queue &queue_);
    void loop();

    void get_state();
    void process_keys(uint32_t state, uint32_t changed, const keycodes &key_arr);
    void update_layers();
    void get_leds();
    void process_leds();
};
