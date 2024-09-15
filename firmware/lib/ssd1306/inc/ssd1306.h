#include <cstdint>
#include <string>

#include "pico/stdlib.h"
#include "hardware/i2c.h"


constexpr uint8_t oledWidth = 128;
constexpr uint8_t oledHeight = 32;
constexpr uint8_t oledPages = 4;

class ssd1306
{
public:
    ssd1306();
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
    i2c_inst_t *i2c = i2c0;
    uint sda_pin = 0;
    uint scl_pin = 1;
    uint8_t address = 0b111100;  // LSB=0 -> write

    bool displayBuffer[oledWidth][oledHeight];
    uint8_t cursor_x;
    uint8_t cursor_y;
};
