#include "i2c_worker.hpp"


i2c_worker::i2c_worker(drivers::pico::PicoI2CDriver &_i2c_driver, Keypad &_keypad, Led &_led)
    : i2c_driver(_i2c_driver)
    , keypad(_keypad)
    , led(_led)
{
}

void i2c_worker::loop()
{
    uint64_t last_reqest_time = time_us_64();

    // TODO: assert i2c is set to slave mode
    while (true)
    {
        if (i2c_driver.slave_requested()) {
            uint32_t state = keypad.get_state();

            i2c_driver.slave_write_byte((state >> 0) & 0xff);
            i2c_driver.slave_write_byte((state >> 8) & 0xff);
            i2c_driver.slave_write_byte((state >> 16) & 0xff);
            i2c_driver.slave_write_byte((state >> 24) & 0xff);

            i2c_driver.clear_slave_request();
            last_reqest_time = time_us_64();
            // uart_puts(uart0, "worker: requested, sent\r\n");
        }

        uint64_t time_since_request = time_us_64() - last_reqest_time;
        if (time_since_request > 100'000) {
            break;
        }
    }
}
