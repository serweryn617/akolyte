#include "logger.hpp"
#include "pico/stdlib.h"

Logger::Logger()
{
    uart_init(uart0, 115200);
    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);
}

void Logger::set_on(bool on)
{
    is_on = on;
}

void Logger::print(const char *s)
{
    static const char *last = nullptr;

    if (!is_on) return;

    uart_puts(uart0, s);
}