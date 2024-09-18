#include <cstdint>
#include <string>

#include "pico/stdlib.h"
#include "pico_i2c_driver.h"

constexpr uint8_t oledWidth = 128;
constexpr uint8_t oledHeight = 32;
constexpr uint8_t oledPages = oledHeight / 8;

class ssd1306
{
public:
    ssd1306(drivers::pico::PicoI2CDriver &i2c_driver_) : i2c_driver(i2c_driver_) {};
    ~ssd1306() {};

    void init();
    void write_command(uint8_t cmd);
    void fill(bool val);
    void set_pixel(uint8_t x, uint8_t y, bool val);
    void print_char(uint8_t c);
    void print_string(std::string str);
    void display();
    void set_cursor(uint8_t x, uint8_t y);

private:
    drivers::pico::PicoI2CDriver &i2c_driver;
    uint8_t displayBuffer[oledPages][oledWidth];
    uint8_t cursor_x = 0;
    uint8_t cursor_y = 0;
};
