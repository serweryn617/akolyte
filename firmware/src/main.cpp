#include <stdio.h>

#include "pico/stdlib.h"

#include "../drivers/pico/i2c/inc/pico_i2c_driver.h"
#include "defs.hpp"
#include "keypad.hpp"
#include "led.hpp"
#include "tinyusb.hpp"
#include "types.h"
#include "flow_selector.hpp"
#include "usb_manager.hpp"
#include "i2c_worker.hpp"
#include "logger.hpp"

tinyusb_callback g_tinyusb_callback {
    .complete = true,
    .leds = 0,
    .mounted = false,
    .suspended = false,
};

int main()
{
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
