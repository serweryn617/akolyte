#pragma once

#include "keypad/keypad.hpp"
#include "communication/communication.hpp"
#include "queue/queue.hpp"

class i2c_worker
{
private:
    lib::communication::communication &comms;
    lib::keypad::Keypad &keypad;
    uint32_t state = 0;
    lib::queue::Queue &queue;

    void process_commands();
    bool process_slave_request();
    void process_leds(uint8_t leds);
    void process_layer(uint8_t layer);

public:
    i2c_worker(lib::communication::communication &_comms, lib::keypad::Keypad &_keypad, lib::queue::Queue &queue_);
    void loop();
};
