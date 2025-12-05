#include "Dfr0971.h"

Dfr0971::Dfr0971(BitbangI2c *i2cBus, uint8_t i2cAddress) {
    i2c = i2cBus;
    address = i2cAddress;
}

void Dfr0971::setOutput(uint8_t channel, uint16_t value) {
    if (channel > 1) return;      // 2 channels per device
    if (value > 0xFFF) value = 0xFFF; // clamp to 12-bit

    uint8_t data[2];
    data[0] = ((value >> 8) & 0x0F); // upper 4 bits
    data[1] = value & 0xFF;          // lower 8 bits

    // Write 2 bytes to DAC register corresponding to channel
    i2c->write(address, channel, data, 2);
}
