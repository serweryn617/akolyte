#include "i2c/i2c_driver.h"
#include "pico/i2c_slave.h"

namespace drivers::i2c {

static constexpr unsigned command_buffer_size = 16;

volatile static bool to_send = 0;
volatile static bool to_receive = 0;

static struct {
    uint8_t state[4] = {};

    uint8_t command[command_buffer_size] = {};
    uint8_t command_size = 0;
    bool command_ready = false;
} global_context;

void i2c_slave_handler(i2c_inst_t *i2c, i2c_slave_event_t event) {
    switch (event) {
    case I2C_SLAVE_RECEIVE:
        to_receive = true;

        if (global_context.command_ready == true) {
            global_context.command_ready = false;
            global_context.command_size = 0;
        }

        if (global_context.command_size < command_buffer_size) {
            global_context.command[global_context.command_size++] = i2c_read_byte_raw(i2c);
        }

        break;
    case I2C_SLAVE_REQUEST:
        to_send = true;
        break;
    case I2C_SLAVE_FINISH:
        global_context.command_ready = true;
        break;
    default:
        break;
    }
}

I2CDriver::I2CDriver(i2c_inst_t *i2c_inst, uint8_t pin_sda, uint8_t pin_scl, uint8_t i2c_address)
    : i2c_inst_(i2c_inst)
    , i2c_address_(i2c_address)
    , pin_sda_(pin_sda)
    , pin_scl_(pin_scl)
{
}

void I2CDriver::init()
{
    i2c_init(i2c_inst_, 800 * 1000);
    gpio_set_function(pin_sda_, GPIO_FUNC_I2C);
    gpio_set_function(pin_scl_, GPIO_FUNC_I2C);
    gpio_pull_up(pin_sda_);
    gpio_pull_up(pin_scl_);
}

int I2CDriver::read_data(uint8_t *buffer, uint32_t length, uint32_t timeout)
{
    if (timeout) {
        return i2c_read_timeout_us(i2c_inst_, i2c_address_, buffer, length, false, timeout);
    } else {
        return i2c_read_blocking(i2c_inst_, i2c_address_, buffer, length, false);
    }
}

int I2CDriver::write_data(const uint8_t *buffer, uint32_t length, uint32_t timeout)
{
    if (timeout) {
        return i2c_write_timeout_us(i2c_inst_, i2c_address_, buffer, length, false, timeout);
    } else {
        return i2c_write_blocking(i2c_inst_, i2c_address_, buffer, length, false);
    }
}

bool I2CDriver::slave_requested()
{
    return to_send;
}

void I2CDriver::clear_slave_request()
{
    to_send = 0;
}

void I2CDriver::slave_write_byte(uint8_t byte)
{
    return i2c_write_byte_raw(i2c_inst_, byte);
}

bool I2CDriver::slave_received()
{
    bool temp = to_receive;
    to_receive = 0;
    return temp;
}

uint8_t I2CDriver::slave_read_byte()
{
    return i2c_read_byte_raw(i2c_inst_);
}

void I2CDriver::set_slave_mode(bool slave)
{
    if (slave) {
        i2c_slave_init(i2c_inst_, i2c_address_, &i2c_slave_handler);
    } else {
        i2c_slave_deinit(i2c_inst_);
    }
}

uint8_t* I2CDriver::get_command_address() {
    return global_context.command;
}

uint8_t I2CDriver::get_command_size() {
    if (global_context.command_ready) {
        return global_context.command_size;
    }

    return 0;
}

}  // namespace drivers::i2c
