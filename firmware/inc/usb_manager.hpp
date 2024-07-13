#pragma once

#include "pico/stdlib.h"
#include "../drivers/pico/i2c/inc/pico_i2c_driver.h"
#include "hid_keycodes.hpp"
#include "led.hpp"
#include "tinyusb.hpp"
#include "types.h"
#include "keypad.hpp"
#include "logger.hpp"
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
    drivers::pico::PicoI2CDriver &i2c_driver;
    Led &led;
    tinyusb_callback &tusb_cb;
    Keypad &keypad;
    Logger &log;

public:
    usb_manager(TinyUSB &_tinyusb, drivers::pico::PicoI2CDriver &_i2c_driver, Led &_led, tinyusb_callback &_tusb_cb, Keypad &_keypad, Logger &_log);
    void loop();

    void get_state();
    void process_keys(uint32_t state, uint32_t changed, const std::array<hid_key, 30> &key_arr);
    void update_layers();
    void set_leds();
};

