#ifndef LIB_COMMUNICATION_COMMUNICATION_HPP
#define LIB_COMMUNICATION_COMMUNICATION_HPP

#include "pico/stdlib.h"
#include "i2c/i2c_driver.h"

namespace lib::communication {

enum class command : uint8_t {
    none,
    capture_keys,
};

class communication
{
private:
    drivers::i2c::I2CDriver &i2c_driver;

public:
    communication(drivers::i2c::I2CDriver &_i2c_driver);

    void init();
    int read_data(uint8_t *buffer, uint32_t length = 1, uint32_t timeout = 0);
    int write_data(const uint8_t *buffer, uint32_t length = 1, uint32_t timeout = 0);
    void set_slave_mode(bool is_slave);
    bool slave_requested();
    bool slave_received();
    void clear_slave_request();
    void slave_write_byte(uint8_t byte);

    void request_capture_keys();
    command get_command();
};

}  // namespace lib::communication

#endif  // LIB_COMMUNICATION_COMMUNICATION_HPP
