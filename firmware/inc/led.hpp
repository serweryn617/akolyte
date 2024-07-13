#pragma once

#include "pico/stdlib.h"

class Led
{
private:
    uint8_t pin;
    uint32_t urgb_u32(uint8_t red, uint8_t green, uint8_t blue);

public:
    Led(uint8_t _pin);
    void init();
    void set(uint8_t red, uint8_t green, uint8_t blue);
};