#include <stdio.h>

#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "pico/util/queue.h"

#include "i2c/i2c_driver.h"
#include "communication/communication.hpp"
#include "defs/defs.hpp"
#include "keypad/keypad.hpp"
#include "queue/queue.hpp"
#include "tinyusb.hpp"
#include "types.h"
#include "akolyte/flow_selector.hpp"
#include "akolyte/usb_manager.hpp"
#include "akolyte/i2c_worker.hpp"
#include "akolyte/keycodes.hpp"
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

        oled.display();
        sleep_ms(10);
    }
}

int main()
{
    Queue queue;
    queue.initialize();

    TinyUSB t_usb(global_tinyusb_callback);
    drivers::i2c::I2CDriver i2c_driver(i2c1, ext_i2c_sda, ext_i2c_scl, 0x55);
    lib::communication::communication comms(i2c_driver);

    Keypad keypad(keypad_in_pins, keypad_out_pins);
    usb_manager manager(t_usb, comms, global_tinyusb_callback, keypad, queue);
    i2c_worker worker(comms, keypad);
    flow_selector selector(t_usb, comms, global_tinyusb_callback, manager, worker);

    multicore_launch_core1(core1_main);

    keypad.init_gpio();
    selector.init_all();
    selector.start();
}
