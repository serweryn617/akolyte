#include "pico/multicore.h"

#include "akolyte/core1.hpp"
#include "akolyte/flow_selector.hpp"
#include "akolyte/i2c_worker.hpp"
#include "akolyte/usb_manager.hpp"
#include "communication/communication.hpp"
#include "defs/defs.hpp"
#include "i2c/i2c_driver.h"
#include "keypad/keypad.hpp"
#include "queue/queue.hpp"
#include "tinyusb.hpp"
#include "types.h"

using namespace drivers::i2c;
using namespace lib::communication;
using namespace lib::keypad;
using namespace lib::queue;

tinyusb_callback global_tinyusb_callback {
    .complete = true,
    .leds = 0,
    .mounted = false,
    .suspended = false,
};

int main()
{
    Queue queue;
    queue.initialize();

    TinyUSB t_usb(global_tinyusb_callback);
    I2CDriver i2c_driver(i2c1, ext_i2c_sda, ext_i2c_scl, 0x55);
    communication comms(i2c_driver);

    Keypad keypad(keypad_in_pins, keypad_out_pins);
    usb_manager manager(t_usb, comms, global_tinyusb_callback, keypad, queue);
    i2c_worker worker(comms, keypad);
    flow_selector selector(t_usb, comms, global_tinyusb_callback, manager, worker);

    multicore_launch_core1(core1_main);

    keypad.init_gpio();
    selector.init_all();
    selector.start();
}
