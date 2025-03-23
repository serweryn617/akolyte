#include "akolyte/i2c_worker.hpp"

using namespace lib::keypad;

i2c_worker::i2c_worker(lib::communication::communication &_comms, Keypad &_keypad)
    : comms(_comms)
    , keypad(_keypad)
{
}

void i2c_worker::loop()
{
    uint64_t last_reqest_time = time_us_64();
    uint32_t state = 0;

    // TODO: assert i2c is set to slave mode
    while (true)
    {
        if (comms.capture_keys_requested()) {
            state = keypad.get_state();
        }

        if (comms.slave_requested()) {

            comms.slave_write_byte((state >> 0) & 0xff);
            comms.slave_write_byte((state >> 8) & 0xff);
            comms.slave_write_byte((state >> 16) & 0xff);
            comms.slave_write_byte((state >> 24) & 0xff);

            comms.clear_slave_request();
            last_reqest_time = time_us_64();
        }

        uint64_t time_since_request = time_us_64() - last_reqest_time;
        if (time_since_request > 100'000) {
            break;
        }
    }
}
