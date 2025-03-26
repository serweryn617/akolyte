#include "akolyte/i2c_worker.hpp"

#include <optional>

using namespace lib::communication;
using namespace lib::keypad;

i2c_worker::i2c_worker(communication &_comms, Keypad &_keypad)
    : comms(_comms)
    , keypad(_keypad)
{
}

void i2c_worker::process_commands() {
    std::optional<command> cmd = comms.get_command();

    if (!cmd) {
        return;
    }

    if (cmd->get_type() == command_type::capture_keys) {
        state = keypad.get_state();
    }
}

bool i2c_worker::process_slave_request() {
    bool requested = comms.slave_requested();
    if (requested) {
        comms.slave_write_byte((state >> 0) & 0xff);
        comms.slave_write_byte((state >> 8) & 0xff);
        comms.slave_write_byte((state >> 16) & 0xff);
        comms.slave_write_byte((state >> 24) & 0xff);

        comms.clear_slave_request();
    }
    return requested;
}

void i2c_worker::loop()
{
    uint64_t last_reqest_time = time_us_64();

    // TODO: assert i2c is set to slave mode
    while (true)
    {
        process_commands();

        if (process_slave_request()) {
            last_reqest_time = time_us_64();
        }

        uint64_t time_since_request = time_us_64() - last_reqest_time;
        if (time_since_request > 100'000) {
            break;
        }
    }
}
