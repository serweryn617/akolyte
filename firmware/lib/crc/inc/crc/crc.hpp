#ifndef LIB_CRC_CRC_HPP
#define LIB_CRC_CRC_HPP

#include <span>
#include "pico/stdlib.h"

namespace lib::crc {

uint8_t crc8(std::span<uint8_t> data, uint8_t initial_value = 0);

}  // namespace lib::crc

#endif  // LIB_CRC_CRC_HPP
