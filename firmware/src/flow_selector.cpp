#include "flow_selector.hpp"

flow_selector::flow_selector(TinyUSB &_tiny_usb, drivers::pico::PicoI2CDriver &_i2c_driver, Led &_led, tinyusb_callback &_tusb_cb,  usb_manager &_manager, i2c_worker &_worker, Logger &_log)
    : tiny_usb(_tiny_usb)
    , i2c_driver(_i2c_driver)
    , led(_led)
    , tusb_cb(_tusb_cb)
    , manager(_manager)
    , worker(_worker)
    , log(_log)
{
}

void flow_selector::init_all()
{
    tiny_usb.init();
    led.init();
    i2c_driver.init();
    i2c_driver.set_slave_mode(true);
}

void flow_selector::start()
{
    uint64_t timestamp = time_us_64();

    while (true) {
        log.print("flow sel loop\r\n");

        tiny_usb.device_task();
        tiny_usb.hid_task();

        if (tiny_usb.ready()) {
            log.print("entering manager\r\n");

            i2c_driver.set_slave_mode(false);
            manager.loop();
            i2c_driver.set_slave_mode(true);
        }

        if (i2c_driver.slave_requested()) {
            log.print("entering worker\r\n");

            worker.loop();
        }

        while (time_us_64() < timestamp + 1000);
        timestamp = time_us_64();
    }
}