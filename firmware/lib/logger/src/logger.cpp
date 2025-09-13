#include <cstdio>
#include <cstdint>
#include <cstdarg>

#include "logger/logger.hpp"
#include "pico/stdlib.h"
#include "hardware/uart.h"

Logger::Logger()
{
    // TODO: uses the same pins as I2C
    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);
    uart_init(uart0, 115200);
}

void Logger::print(const char *format, ...)
{
    constexpr uint32_t buffer_size = 256;
    char buffer[buffer_size];

    va_list args;
    va_start(args, format);

    vsnprintf(buffer, buffer_size, format, args);
    va_end(args);

    uart_puts(uart0, buffer);
    uart_puts(uart0, "\n");
}

Logger g_logger;
