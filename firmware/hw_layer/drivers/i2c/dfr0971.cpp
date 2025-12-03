#include "dfr0971.h"
#include "os_access.h"
#include "i2c_bb.h"

#define DFR0971_MAX_VALUE   4095     // 12-bit DAC
#define DFR0971_NUM_CHANNELS 2

Dfr0971::Dfr0971(i2cDevice* bus, uint8_t address)
    : m_bus(bus), m_addr(address) {
}

void Dfr0971::init() {
    // No special initialization command required
    // The module will ACK if address is correct
    // A write to channel 0 with zero verifies presence
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
    if (percent < 0.0f) {
        percent = 0.0f;
    } else if (percent > 100.0f) {
        percent = 100.0f;
    }

    uint16_t value = (uint16_t)((percent / 100.0f) * DFR0971_MAX_VALUE);
    setRaw(channel, value);
}

void Dfr0971::writeDac(uint8_t channel, uint16_t value) {
    // The DFR0971 uses a 2-byte protocol: high byte + low byte
    // Upper 4 bits = configuration (0x30 high nibble)
    // Lower 12 bits = DAC value

    uint8_t buf[2];
    buf[0] = 0x30 | ((value >> 8) & 0x0F);
    buf[1] = value & 0xFF;

    // Module uses register 0x40 + channel for DAC writes
    uint8_t reg = 0x40 + channel;

    i2cWriteReg(m_bus, m_addr, reg, buf, 2);
}
