
#include "dfr0971.h"
#include "i2c_bb.h"   // include real BitbangI2c
#include <cstdint>
#include <cstddef>

Dfr0971::Dfr0971(BitbangI2c* bus, uint8_t addr)
    : i2c(bus), address(addr)
{
}

void Dfr0971::setOutput(uint8_t channel, uint16_t value)
{
    uint8_t buf[3];
    buf[0] = channel;
    buf[1] = (value >> 8) & 0xFF;
    buf[2] = value & 0xFF;

    i2c->write(address, buf, 3);  // safe, no brain_pin_e needed
}
