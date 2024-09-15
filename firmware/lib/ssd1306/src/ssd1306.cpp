#include "ssd1306.h"
#include "font.h"

void ssd1306::write_command(uint8_t cmd)
{
    uint8_t command_bytes[2] = {0x80, cmd};
    i2c_driver.write_data(command_bytes, sizeof(command_bytes));
}

void ssd1306::write_data(uint8_t data)
{
    uint8_t data_bytes[2] = {0x40, data};
    i2c_driver.write_data(data_bytes, sizeof(data_bytes));
}

void ssd1306::init()
{
    write_command(0xAE);
    write_command(0x00);
    write_command(0x10);
    write_command(0x40);
    write_command(0xB0);
    write_command(0x81);
    write_command(0xCF);
    write_command(0xA1);
    write_command(0xA8);
    write_command(0x1F);
    write_command(0xC8);
    write_command(0xD3);
    write_command(0x00);
    write_command(0xD5);
    write_command(0x80);
    write_command(0xD9);
    write_command(0xF1);
    write_command(0xDA);
    write_command(0x02);
    write_command(0xDB);
    write_command(0x40);
    write_command(0x8D);
    write_command(0x14);
    write_command(0xA6);
    write_command(0xAF);

    sleep_ms(100);
    fill(0);
}

void ssd1306::set_staring_column()
{
    // Set column to 00
    write_command(0x00);
    write_command(0x10);
}

void ssd1306::display()
{
    for (size_t i = 0; i < oledPages; i++)
    {
        set_staring_column();
        write_command(0xB0 + i);
        for (size_t j = 0; j < oledWidth; j++)
        {
            uint8_t data = 0;
            for (size_t k = 0; k < 8; k++)
            {
                data |= (displayBuffer[j][i*8+k] << k);
            }

            write_data(data);
        }
    }
}

void ssd1306::fill(bool val)
{
    for (size_t i = 0; i < oledWidth; i++)
    {
        for (size_t j = 0; j < oledHeight; j++)
        {
            displayBuffer[i][j] = val;
        }
    }
}

void ssd1306::set_pixel(uint8_t x, uint8_t y, bool val)
{
    displayBuffer[x][y] = val;
}

void ssd1306::print_char(uint8_t c)
{
    for (size_t i = 0; i < 2; i++)
    {
        for (size_t j = 0; j < 10; j++)
        {
            for (size_t k = 0; k < 8; k++)
            {
                displayBuffer[cursor_x+j][cursor_y+i*8+k] = (ascii_16x[c][i*10+j] >> k) & 0b1;
            }
        }
    }
}

void ssd1306::set_cursor(uint8_t x, uint8_t y)
{
    cursor_x = x;
    cursor_y = y;
}

void ssd1306::print_string(std::string str)
{
    for (auto &&c : str)
    {
        print_char(c - 32);
        cursor_x += 12;
    }
}
