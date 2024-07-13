#pragma once
#include "pico/stdlib.h"

typedef struct {
    bool complete;
    uint8_t leds;
    bool mounted;
    bool suspended;
} tinyusb_callback;