#pragma once

#include "keypad/keypad.hpp"
#include "communication/communication.hpp"

class i2c_worker
{
private:
    lib::communication::communication &comms;
    lib::keypad::Keypad &keypad;

public:
    i2c_worker(lib::communication::communication &_comms, lib::keypad::Keypad &_keypad);
    void loop();
};
