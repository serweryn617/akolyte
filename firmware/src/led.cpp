#include "hardware/pio.h"
#include "led.hpp"
#include "ws2812.pio.h"

Led::Led(uint8_t _pin)
    : pin(_pin)
{
}

void Led::init()
{
    PIO pio = pio0;
    int sm = 0;
    uint offset = pio_add_program(pio, &ws2812_program);

    ws2812_program_init(pio, sm, offset, pin, 800000, true);
}

uint32_t Led::urgb_u32(uint8_t red, uint8_t green, uint8_t blue)
{
    return ((uint32_t)(red) << 8) | ((uint32_t)(green) << 16) | (uint32_t)(blue);
}

void Led::set(uint8_t red, uint8_t green, uint8_t blue)
{
    sleep_ms(10);

    uint32_t color = urgb_u32(red, green, blue);
    pio_sm_put_blocking(pio0, 0, color << 8u);

    sleep_ms(10);
    // TODO: sleep >50us
}
