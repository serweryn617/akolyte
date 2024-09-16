#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/multicore.h"

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

void core1_main()
{
    drivers::pico::PicoI2CDriver i2c_driver(oled_i2c, oled_i2c_sda, oled_i2c_scl, oled_i2c_address);
    i2c_driver.init();

    ssd1306 oled(i2c_driver);
    oled.init();

    oled.set_cursor(0, 0);
    oled.print_string("test...");
    oled.display();

    while(true);
}

int main()
{
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

    flow_selector selector(t_usb, i2c_driver, led, g_tinyusb_callback, manager, worker, log);

    log.print("Starting\r\n");

    selector.init_all();
    selector.start();
}
