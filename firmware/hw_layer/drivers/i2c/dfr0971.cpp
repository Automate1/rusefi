#include "dfr0971.h"
#include "i2c_bb.h"

Dfr0971::Dfr0971(BitbangI2c* bus, uint8_t address)
    : m_bus(bus), m_address(address)
{
}

void Dfr0971::init() {
    // Optional: reset or configure the DAC
}

void Dfr0971::setPercent(uint8_t channel, float percent) {
    if (percent < 0.0f) percent = 0.0f;
    if (percent > 100.0f) percent = 100.0f;

    uint16_t value = percentToValue(percent);
    writeChannel(channel, value);
}

uint16_t Dfr0971::percentToValue(float percent) {
    return (uint16_t)((percent / 100.0f) * 4095.0f);  // 12-bit DAC
}

void Dfr0971::writeChannel(uint8_t channel, uint16_t value) {
    uint8_t data[2];

    data[0] = (value >> 4) & 0xFF;       // high 8 bits
    data[1] = (value & 0x0F) << 4;       // low 4 bits in high nibble

    uint8_t reg = 0x30 | (channel & 0x01);

    m_bus->writeRegister(m_address, reg, data[0]);
    m_bus->writeRegister(m_address, reg + 1, data[1]);
}
