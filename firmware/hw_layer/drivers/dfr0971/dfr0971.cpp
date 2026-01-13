#include "pch.h"

#include "dfr0971.h"
#include "i2c/i2c_bb.h"

Dfr0971::Dfr0971(BitbangI2c& i2c, uint8_t i2cAddress)
    : m_i2c(i2c)
    , m_address(i2cAddress) {
}

void Dfr0971::setOutput(uint8_t channel, uint16_t value) {
    // DFR0971 expects:
    // [command/channel byte] [MSB] [LSB]
    uint8_t buf[3];

    buf[0] = channel & 0x01;      // channel select
    buf[1] = (value >> 8) & 0xFF; // MSB
    buf[2] = value & 0xFF;        // LSB

    m_i2c.write(m_address, buf, sizeof(buf));
}
