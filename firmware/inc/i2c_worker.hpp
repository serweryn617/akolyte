#pragma once

#include "pico_i2c_driver.h"
#include "keypad.hpp"
#include "led.hpp"

class i2c_worker
{
private:
    drivers::pico::PicoI2CDriver &i2c_driver;
    Keypad &keypad;
    Led &led;

public:
    i2c_worker(drivers::pico::PicoI2CDriver &_i2c_driver, Keypad &_keypad, Led &_led);
    void loop();
};

