#include "pico/stdlib.h"
#include "communication/communication.hpp"

namespace lib::communication {

enum class command : uint8_t {
    capture_keys,
};

communication::communication(drivers::i2c::I2CDriver &_i2c_driver)
    : i2c_driver(_i2c_driver)
{
}

void communication::init() {
    i2c_driver.init();
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
    uint8_t command = static_cast<uint8_t>(command::capture_keys);
    i2c_driver.write_data(&command, 1, 0);
}

bool communication::capture_keys_requested() {
    return true;
}

}  // namespace lib::communication
