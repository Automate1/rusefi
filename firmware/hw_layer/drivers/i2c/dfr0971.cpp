#include "dfr0971.h"

#define DFR0971_MAX_VALUE 4095

Dfr0971::Dfr0971(BitbangI2c* bus, uint8_t address)
    : m_bus(bus), m_addr(address) {}

void Dfr0971::init() {
    // Test write — writes 0 to channel 0
    writeDac(0, 0);
}

void Dfr0971::setRaw(uint8_t channel, uint16_t value) {
    if (value > DFR0971_MAX_VALUE)
        value = DFR0971_MAX_VALUE;

    writeDac(channel, value);
}

void Dfr0971::setPercent(uint8_t channel, float percent) {
    if (percent < 0.0f) percent = 0.0f;
    if (percent > 100.0f) percent = 100.0f;

    uint16_t val = (uint16_t)((percent / 100.0f) * DFR0971_MAX_VALUE);
    setRaw(channel, val);
}

void Dfr0971::writeDac(uint8_t channel, uint16_t value) {
    uint8_t reg = 0x40 + channel;

    uint8_t buf[2];
    buf[0] = 0x30 | ((value >> 8) & 0x0F);
    buf[1] = value & 0xFF;

    // Bit-bang I2C call
    m_bus->writeRegister(m_addr, reg, buf[0]);
    m_bus->writeRegister(m_addr, reg + 1, buf[1]);
}
