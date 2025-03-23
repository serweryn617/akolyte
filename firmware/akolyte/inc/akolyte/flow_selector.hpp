#pragma once

#include "pico/util/queue.h"

#include "tinyusb.hpp"
#include "types.h"
#include "usb_manager.hpp"
#include "i2c_worker.hpp"
#include "communication/communication.hpp"

class flow_selector
{
private:
    TinyUSB &tiny_usb;
    tinyusb_callback &tusb_cb;
    lib::communication::communication &comms;

    usb_manager &manager;
    i2c_worker &worker;

public:
    flow_selector(TinyUSB &_tiny_usb, lib::communication::communication &_comms, tinyusb_callback &_tusb_cb, usb_manager &_manager, i2c_worker &_worker);
    void init_all();
    void start();
};
