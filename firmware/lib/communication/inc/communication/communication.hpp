#ifndef LIB_COMMUNICATION_COMMUNICATION_HPP
#define LIB_COMMUNICATION_COMMUNICATION_HPP

#include <optional>
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

public:
    command(command_type _type, std::span<uint8_t> _payload)
        : type(_type)
        , payload(_payload)
    {}

    command_type get_type();
    std::span<uint8_t> get_payload();
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
    std::optional<command> get_command();
};

}  // namespace lib::communication

#endif  // LIB_COMMUNICATION_COMMUNICATION_HPP
