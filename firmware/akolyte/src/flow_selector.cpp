#include "akolyte/flow_selector.hpp"

flow_selector::flow_selector(TinyUSB &_tiny_usb, lib::communication::communication &_comms, tinyusb_callback &_tusb_cb,  usb_manager &_manager, i2c_worker &_worker)
    : tiny_usb(_tiny_usb)
    , tusb_cb(_tusb_cb)
    , manager(_manager)
    , worker(_worker)
    , comms(_comms)
{
}

void flow_selector::init_all()
{
    tiny_usb.init();
    comms.init();
    comms.set_slave_mode(true);
}

void flow_selector::start()
{
    uint64_t timestamp = time_us_64();

    while (true) {
        uint8_t message_none = 0;
        // queue_add_blocking(&inter_core_queue, &message_none);

        tiny_usb.device_task();
        tiny_usb.hid_task();

        if (tiny_usb.ready()) {
            uint8_t message = 1;
            // queue_add_blocking(&inter_core_queue, &message);

            comms.set_slave_mode(false);
            manager.loop();
            comms.set_slave_mode(true);
        }

        if (comms.slave_requested()) {
            uint8_t message = 2;
            // queue_add_blocking(&inter_core_queue, &message);

            worker.loop();
        }

        while (time_us_64() < timestamp + 1000);
        timestamp = time_us_64();
    }
}
