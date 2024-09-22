#pragma once

#include "i2c/i2c_driver.h"
#include "keypad/keypad.hpp"

class i2c_worker
{
private:
    drivers::i2c::I2CDriver &i2c_driver;
    lib::keypad::Keypad &keypad;

public:
    i2c_worker(drivers::i2c::I2CDriver &_i2c_driver, lib::keypad::Keypad &_keypad);
    void loop();
};

