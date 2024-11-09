#include <cstdint>

#include "pico/stdlib.h"
#include "i2c/i2c_driver.h"

constexpr uint8_t oledWidth = 128;
constexpr uint8_t oledHeight = 32;
constexpr uint8_t oledPages = oledHeight / 8;

class ssd1306
{
public:
    ssd1306(drivers::i2c::I2CDriver &i2c_driver_) : i2c_driver(i2c_driver_) {};
    ~ssd1306() {};

    void init();
    void write_command(uint8_t cmd);
    void fill(bool val);
    void set_pixel(uint8_t x, uint8_t y, bool val);
    void print_string(const char *str, uint8_t font_size);
    void display();
    void set_cursor(uint8_t x, uint8_t y);

    template <typename font>
    void print_char(const font &font_, uint8_t c)
    {
        const auto &character = font_.characters[c - 32];
        const auto width = font_.width;
        const auto height = font_.height;

        for (size_t cx = 0; cx < width; cx++)
        {
            for (size_t cy = 0; cy < height; cy++)
            {
                set_pixel(cursor_x + cx, cursor_y + cy, (character.data[cx] >> cy) & 0b1);
            }
        }
    }

private:
    drivers::i2c::I2CDriver &i2c_driver;
    uint8_t displayBuffer[oledPages][oledWidth];
    uint8_t cursor_x = 0;
    uint8_t cursor_y = 0;
};
