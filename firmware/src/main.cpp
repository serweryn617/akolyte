#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/util/queue.h"

#include "pico_i2c_driver.h"
#include "defs.hpp"
#include "keypad.hpp"
#include "led.hpp"
#include "tinyusb.hpp"
#include "types.h"
#include "flow_selector.hpp"
#include "usb_manager.hpp"
#include "i2c_worker.hpp"
#include "logger.hpp"
#include "ssd1306.h"

tinyusb_callback g_tinyusb_callback {
    .complete = true,
    .leds = 0,
    .mounted = false,
    .suspended = false,
};

queue_t inter_core_queue;

void core1_main()
{
    drivers::pico::PicoI2CDriver i2c_driver(oled_i2c, oled_i2c_sda, oled_i2c_scl, oled_i2c_address);
    i2c_driver.init();

    ssd1306 oled(i2c_driver);
    oled.init();

    uint8_t last_message = 0;

    while(true) {
        oled.set_cursor(0, 0);
        oled.print_string("Running primary");
        oled.display();
        
        // switch (last_message) {
        //     case 1:
        //         oled.print_string("Running primary");
        //         break;
        //     case 2:
        //         oled.print_string("Running secondary");
        //         break;
        //     default:
        //         oled.print_string("ERROR");
        //         break;
        // }
        // oled.display();
        // queue_try_remove(&inter_core_queue, &last_message);
    }
}

int main()
{
    queue_init(&inter_core_queue, sizeof(uint8_t), 16);
    multicore_launch_core1(core1_main);

    Logger log;
    log.set_on(true);

    TinyUSB t_usb(g_tinyusb_callback);
    drivers::pico::PicoI2CDriver i2c_driver(i2c1, ext_i2c_sda, ext_i2c_scl, 0x55);
    Led led(led_builtin);
    Keypad keypad;

    keypad.init_gpio();

    usb_manager manager(t_usb, i2c_driver, led, g_tinyusb_callback, keypad, log);
    i2c_worker worker(i2c_driver, keypad, led);

    flow_selector selector(t_usb, i2c_driver, inter_core_queue, led, g_tinyusb_callback, manager, worker, log);

    log.print("Starting\r\n");

    selector.init_all();
    selector.start();
}
