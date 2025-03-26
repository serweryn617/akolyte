#include <optional>
#include <span>
#include "pico/stdlib.h"
#include "communication/communication.hpp"
#include "crc/crc.hpp"

using namespace lib::crc;

namespace lib::communication {

command_type command::get_type() {
    return type;
}

std::span<uint8_t> command::get_payload() {
    return payload;
}

communication::communication(drivers::i2c::I2CDriver &_i2c_driver)
    : i2c_driver(_i2c_driver)
{
}

void communication::init() {
    i2c_driver.init();
    command_buffer = i2c_driver.get_command_address();
}

int communication::read_data(uint8_t *buffer, uint32_t length, uint32_t timeout) {
    return i2c_driver.read_data(buffer, length, timeout);
}

int communication::write_data(const uint8_t *buffer, uint32_t length, uint32_t timeout) {
    return i2c_driver.write_data(buffer, length, timeout);
}

void communication::set_slave_mode(bool is_slave) {
    i2c_driver.set_slave_mode(is_slave);
}

bool communication::slave_requested() {
    return i2c_driver.slave_requested();
}

bool communication::slave_received() {
    return i2c_driver.slave_received();
}

void communication::clear_slave_request() {
    i2c_driver.clear_slave_request();
}

void communication::slave_write_byte(uint8_t byte) {
    i2c_driver.slave_write_byte(byte);
}

void communication::request_capture_keys() {
    uint8_t type_value = static_cast<uint8_t>(command_type::capture_keys);

    uint8_t command_buffer[2];
    command_buffer[0] = type_value;
    command_buffer[1] = crc8(std::span<uint8_t>(&type_value, 1));

    i2c_driver.write_data(command_buffer, 2, 0);
}

std::optional<command> communication::get_command() {
    uint8_t command_size = i2c_driver.get_command_size();

    if (command_size < 2) {
        return std::nullopt;
    }

    uint8_t command_crc = command_buffer[command_size - 1];
    uint8_t expected_crc = crc8(std::span<uint8_t>(command_buffer, command_size - 1));
    if (command_crc != expected_crc) {
        return std::nullopt;
    }

    command_type type = static_cast<command_type>(command_buffer[0]);
    std::span<uint8_t> payload = std::span<uint8_t>(command_buffer + 1, command_size - 2);

    return command(type, payload);
}

}  // namespace lib::communication
