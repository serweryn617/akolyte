#pragma once

#include "pico/stdlib.h"
#include "i2c/i2c_driver.h"
#include "hid_keycodes.hpp"
#include "tinyusb.hpp"
#include "types.h"
#include "keypad/keypad.hpp"
#include <array>

class usb_manager
{
private:
    uint32_t state_left = 0;
    uint32_t state_right = 0;
    uint32_t state_left_previous = 0;
    uint32_t state_right_previous = 0;

    uint8_t layer = 0;
    bool worker_connected = false;

    TinyUSB &tinyusb;
    drivers::i2c::I2CDriver &i2c_driver;
    tinyusb_callback &tusb_cb;
    lib::keypad::Keypad &keypad;

public:
    usb_manager(TinyUSB &_tinyusb, drivers::i2c::I2CDriver &_i2c_driver, tinyusb_callback &_tusb_cb, lib::keypad::Keypad &_keypad);
    void loop();

    void get_state();
    void process_keys(uint32_t state, uint32_t changed, const std::array<hid_key, 30> &key_arr);
    void update_layers();
};

