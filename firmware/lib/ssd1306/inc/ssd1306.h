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
    void io_init();
    void write_command(uint8_t);
    void write_data(uint8_t);
    void set_staring_column();
    void fill(bool);
    void set_pixel(uint8_t, uint8_t, bool);
    void print_char(uint8_t);
    void print_string(std::string);
    void display();
    void set_cursor(uint8_t, uint8_t);

private:
    drivers::pico::PicoI2CDriver &i2c_driver;
    bool displayBuffer[oledWidth][oledHeight];
    uint8_t cursor_x = 0;
    uint8_t cursor_y = 0;
};
