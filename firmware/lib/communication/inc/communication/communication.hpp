#ifndef LIB_COMMUNICATION_COMMUNICATION_HPP
#define LIB_COMMUNICATION_COMMUNICATION_HPP

#include <span>
#include "pico/stdlib.h"
#include "i2c/i2c_driver.h"

namespace lib::communication {

enum class command_type : uint8_t {
    none,
    capture_keys,
};

class command
{
private:
    command_type type = command_type::none;
    std::span<uint8_t> payload;
    uint8_t crc = 0;

public:
    command(command_type _type, std::span<uint8_t> _payload, uint8_t _crc)
        : type(_type)
        , payload(_payload)
        , crc(_crc)
    {}

    command_type get_type();
    std::span<uint8_t> get_payload();
    bool validate();
};

class communication
{
private:
    drivers::i2c::I2CDriver &i2c_driver;
    uint8_t* command_buffer = nullptr;

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
