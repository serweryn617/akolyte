#include <optional>
#include <span>
#include <cstdint>
#include "akolyte/i2c_worker.hpp"
#include "tusb.h"

using namespace lib::communication;
using namespace lib::keypad;
using namespace lib::queue;

i2c_worker::i2c_worker(communication &_comms, Keypad &_keypad, Queue &queue_)
    : comms(_comms)
    , keypad(_keypad)
    , queue(queue_)
{
}

void i2c_worker::process_commands() {
    std::optional<command> cmd = comms.get_command();

    if (!cmd) {
        return;
    }

    switch (cmd->get_type())
    {
    case command_type::capture_keys:
        state = keypad.get_state();
        break;

    case command_type::set_layer:
        {
            std::span<uint8_t> payload = cmd->get_payload();
            if (payload.size() == 1) {
                uint8_t layer = payload[0];
                process_layer(layer);
            }
        }
        break;

    case command_type::set_leds:
        {
            std::span<uint8_t> payload = cmd->get_payload();
            if (payload.size() == 1) {
                uint8_t leds = payload[0];
                process_leds(leds);
            }
        }
        break;

    default:
        break;
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

void i2c_worker::process_leds(uint8_t leds)
{
    bool caps_led = leds & KEYBOARD_LED_CAPSLOCK;
    if (caps_led) {
        queue.add(Command::caps_on);
    } else {
        queue.add(Command::caps_off);
    }

    bool num_led = leds & KEYBOARD_LED_NUMLOCK;
    if (num_led) {
        queue.add(Command::num_on);
    } else {
        queue.add(Command::num_off);
    }
}

void i2c_worker::process_layer(uint8_t layer)
{
    if (layer == 0) queue.add(Command::layer_0);
    else if (layer == 1) queue.add(Command::layer_1);
    else if (layer == 2) queue.add(Command::layer_2);
    else if (layer == 3) queue.add(Command::layer_3);
    else if (layer == 4) queue.add(Command::layer_4);
    else if (layer == 5) queue.add(Command::layer_5);
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
