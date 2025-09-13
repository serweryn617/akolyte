#include "akolyte/core1.hpp"
#include "akolyte/keycodes.hpp"
#include "defs/defs.hpp"
#include "ssd1306.h"
#include "queue/queue.hpp"

using namespace lib::queue;
using namespace drivers::i2c;

void core1_main()
{
    Queue queue;

    I2CDriver i2c_driver(oled_i2c, oled_i2c_sda, oled_i2c_scl, oled_i2c_address);
    ssd1306 oled(i2c_driver);

    i2c_driver.init();
    oled.init();

    uint layer = 0;
    bool caps_lock = false;
    bool num_lock = false;

    Command command = Command::none;
    while(true) {
        command = queue.get();

        switch (command) {
            case Command::caps_on:
                caps_lock = true;
                break;
            case Command::caps_off:
                caps_lock = false;
                break;
            case Command::num_on:
                num_lock = true;
                break;
            case Command::num_off:
                num_lock = false;
                break;
            case Command::layer_0:
                layer = 0;
                break;
            case Command::layer_1:
                layer = 1;
                break;
            case Command::layer_2:
                layer = 2;
                break;
            case Command::layer_3:
                layer = 3;
                break;
            case Command::layer_4:
                layer = 4;
                break;
            case Command::layer_5:
                layer = 5;
                break;
        }

        oled.set_cursor(0, 0);
        oled.print_string(layers[layer].name, 16);

        oled.set_cursor(0, 16);
        oled.print_indicator(num_lock, 16);
        oled.print_string("Num ", 16);
        oled.print_indicator(caps_lock, 16);
        oled.print_string("Caps", 16);

        oled.display();
        sleep_ms(10);
    }
}
