#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/util/queue.h"

#include "i2c/i2c_driver.h"
#include "defs.hpp"
#include "keypad/keypad.hpp"
#include "tinyusb.hpp"
#include "types.h"
#include "flow_selector.hpp"
#include "usb_manager.hpp"
#include "i2c_worker.hpp"
#include "logger.hpp"
#include "ssd1306.h"

using namespace lib::keypad;

tinyusb_callback global_tinyusb_callback {
    .complete = true,
    .leds = 0,
    .mounted = false,
    .suspended = false,
};
queue_t inter_core_queue;

void core1_main()
{
    drivers::i2c::I2CDriver i2c_driver(oled_i2c, oled_i2c_sda, oled_i2c_scl, oled_i2c_address);
    i2c_driver.init();

    ssd1306 oled(i2c_driver);
    oled.init();

    uint8_t last_message = 0;

    while(true) {
        oled.set_cursor(0, 0);
        switch (last_message) {
            case 0:
                oled.print_string("None");
                break;
            case 1:
                oled.print_string("Running primary");
                oled.set_cursor(0, 8);
                oled.print_string("Line 1");
                oled.set_cursor(0, 16);
                oled.print_string("Line 2");
                oled.set_cursor(0, 24);
                oled.print_string("Line 3");
                break;
            case 2:
                oled.print_string("Running secondary");
                break;
            default:
                oled.print_string("ERROR");
                break;
        }
        oled.display();
        queue_remove_blocking(&inter_core_queue, &last_message);
    }
}

int main()
{
    queue_init(&inter_core_queue, sizeof(uint8_t), 16);
    multicore_launch_core1(core1_main);

    Logger log;
    log.set_on(true);

    TinyUSB t_usb(global_tinyusb_callback);
    drivers::i2c::I2CDriver i2c_driver(i2c1, ext_i2c_sda, ext_i2c_scl, 0x55);
    Keypad keypad(keypad_in_pins, keypad_out_pins);

    keypad.init_gpio();

    usb_manager manager(t_usb, i2c_driver, global_tinyusb_callback, keypad, log);
    i2c_worker worker(i2c_driver, keypad);

    flow_selector selector(t_usb, i2c_driver, inter_core_queue, global_tinyusb_callback, manager, worker, log);

    log.print("Starting\r\n");

    selector.init_all();
    selector.start();
}
