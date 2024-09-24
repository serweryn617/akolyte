#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/util/queue.h"

#include "i2c/i2c_driver.h"
#include "akolyte/defs.hpp"
#include "keypad/keypad.hpp"
#include "queue/queue.hpp"
#include "tinyusb.hpp"
#include "types.h"
#include "akolyte/flow_selector.hpp"
#include "akolyte/usb_manager.hpp"
#include "akolyte/i2c_worker.hpp"
#include "ssd1306.h"

using namespace lib::keypad;
using namespace lib::queue;

tinyusb_callback global_tinyusb_callback {
    .complete = true,
    .leds = 0,
    .mounted = false,
    .suspended = false,
};

void core1_main()
{
    Queue queue;
    drivers::i2c::I2CDriver i2c_driver(oled_i2c, oled_i2c_sda, oled_i2c_scl, oled_i2c_address);
    i2c_driver.init();

    ssd1306 oled(i2c_driver);
    oled.init();

    Command command;

    while(true) {
        oled.set_cursor(0, 0);

        command = queue.get();
        if (command == Command::caps_on) {
            oled.print_string("MEGA TEXT");
        } else if (command == Command::caps_off) {
            oled.print_string("mini text");
        }

        oled.display();
    }
}

int main()
{
    Queue queue;
    queue.initialize();

    TinyUSB t_usb(global_tinyusb_callback);
    drivers::i2c::I2CDriver i2c_driver(i2c1, ext_i2c_sda, ext_i2c_scl, 0x55);
    Keypad keypad(keypad_in_pins, keypad_out_pins);
    usb_manager manager(t_usb, i2c_driver, global_tinyusb_callback, keypad, queue);
    i2c_worker worker(i2c_driver, keypad);
    flow_selector selector(t_usb, i2c_driver, global_tinyusb_callback, manager, worker);

    multicore_launch_core1(core1_main);

    keypad.init_gpio();
    selector.init_all();
    selector.start();
}
