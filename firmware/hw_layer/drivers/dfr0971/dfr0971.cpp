#include "dfr0971.h"
#include <stdint.h>

Dfr0971::Dfr0971(BitbangI2c* i2cBus, uint8_t i2cAddress) {
    i2c = i2cBus;
    address = i2cAddress;
}

void Dfr0971::setOutput(uint8_t channel, uint16_t value) {
    // Convert 16-bit value to two bytes
    uint8_t data[2] = { (uint8_t)(value >> 8), (uint8_t)(value & 0xFF) };

    // Pack channel + data into buffer for i2c_bb write
    uint8_t buf[3] = { channel, data[0], data[1] };

    i2c->write(address, buf, 3);  // matches i2c_bb signature
}