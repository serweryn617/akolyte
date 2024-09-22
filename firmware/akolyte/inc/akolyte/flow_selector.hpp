#pragma once

#include "pico/util/queue.h"

#include "tinyusb.hpp"
#include "i2c/i2c_driver.h"
#include "types.h"
#include "usb_manager.hpp"
#include "i2c_worker.hpp"
#include "logger.hpp"

class flow_selector
{
private:
    TinyUSB &tiny_usb;
    drivers::i2c::I2CDriver &i2c_driver;
    queue_t &inter_core_queue;
    tinyusb_callback &tusb_cb;

    usb_manager &manager;
    i2c_worker &worker;
    Logger &log;

public:
    flow_selector(TinyUSB &_tiny_usb, drivers::i2c::I2CDriver &_i2c_driver, queue_t &inter_core_queue_, tinyusb_callback &_tusb_cb, usb_manager &_manager, i2c_worker &_worker, Logger &_log);
    void init_all();
    void start();
};

