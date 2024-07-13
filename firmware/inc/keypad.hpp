#pragma once
#include "pico/stdlib.h"

class Keypad
{
private:

public:
    Keypad();
    void init_gpio();
    uint32_t get_state();
};
