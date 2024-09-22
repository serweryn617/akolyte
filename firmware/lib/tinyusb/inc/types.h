#ifndef LIB_TINYUSB_CALLBACK_TYPES_H
#define LIB_TINYUSB_CALLBACK_TYPES_H

#include "pico/stdlib.h"

typedef struct {
    bool complete;
    uint8_t leds;
    bool mounted;
    bool suspended;
} tinyusb_callback;

#endif  // LIB_TINYUSB_CALLBACK_TYPES_H