#ifndef DRIVERS_I2C_I2C_DRIVER_H
#define DRIVERS_I2C_I2C_DRIVER_H

#include "hardware/i2c.h"
#include "pico/stdlib.h"

namespace drivers::i2c {

class I2CDriver
{
private:
    i2c_inst_t *i2c_inst_;
    uint8_t i2c_address_;
    uint8_t pin_sda_;
    uint8_t pin_scl_;

public:
    I2CDriver(i2c_inst_t *i2c_inst, uint8_t pin_sda, uint8_t pin_scl, uint8_t i2c_address);

    void init();
    int read_data(uint8_t *buffer, uint32_t length = 1, uint32_t timeout = 0);
    int write_data(const uint8_t *buffer, uint32_t length = 1, uint32_t timeout = 0);
    void set_slave_mode(bool is_slave);
    bool slave_requested();
    void clear_slave_request();
    void slave_write_byte(uint8_t byte);
    bool slave_received();
    uint8_t slave_get_byte();
};

}  // namespace drivers::i2c

#endif  // DRIVERS_I2C_I2C_DRIVER_H