#include "dfr0971.h"

#define DFR0971_MAX_VALUE    4095
#define DFR0971_NUM_CHANNELS 2

Dfr0971::Dfr0971(i2cDevice* bus, uint8_t address)
    : m_bus(bus), m_addr(address) {
}

void Dfr0971::init() {
    // Write zero to channel 0 to verify communication
    writeDac(0, 0);
}

void Dfr0971::setRaw(uint8_t channel, uint16_t value) {
    if (channel >= DFR0971_NUM_CHANNELS)
        return;

    if (value > DFR0971_MAX_VALUE)
        value = DFR0971_MAX_VALUE;

    writeDac(channel, value);
}

void Dfr0971::setPercent(uint8_t channel, float percent) {
    if (percent < 0.0f) percent = 0.0f;
    if (percent > 100.0f) percent = 100.0f;

    uint16_t value = static_cast<uint16_t>((percent / 100.0f) * DFR0971_MAX_VALUE);
    setRaw(channel, value);
}

void Dfr0971::writeDac(uint8_t channel, uint16_t value) {
    // Protocol: 2 bytes per write, high nibble config + 12-bit DAC value
    uint8_t buf[2];
    buf[0] = 0x30 | ((value >> 8) & 0x0F);
    buf[1] = value & 0xFF;

    // Register address: 0x40 + channel
    uint8_t reg = 0x40 + channel;

    // Use bit-bang I2C function
    i2cWriteReg(m_bus, m_addr, reg, buf, 2);
}
