#pragma once

#include "tinyusb.hpp"
#include "../drivers/pico/i2c/inc/pico_i2c_driver.h"
#include "led.hpp"
#include "types.h"
#include "usb_manager.hpp"
#include "i2c_worker.hpp"
#include "logger.hpp"

class flow_selector
{
private:
    TinyUSB &tiny_usb;
    drivers::pico::PicoI2CDriver &i2c_driver;
    Led &led;
    tinyusb_callback &tusb_cb;

    usb_manager &manager;
    i2c_worker &worker;
    Logger &log;

public:
    flow_selector(TinyUSB &_tiny_usb, drivers::pico::PicoI2CDriver &_i2c_driver, Led &_led, tinyusb_callback &_tusb_cb, usb_manager &_manager, i2c_worker &_worker, Logger &_log);
    void init_all();
    void start();
};

