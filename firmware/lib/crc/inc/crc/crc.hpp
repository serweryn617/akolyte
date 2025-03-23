#ifndef LIB_CRC_CRC_HPP
#define LIB_CRC_CRC_HPP

#include "pico/stdlib.h"

namespace lib::crc {

uint8_t crc8(const uint8_t *data, size_t length);

}  // namespace lib::crc

#endif  // LIB_CRC_CRC_HPP
