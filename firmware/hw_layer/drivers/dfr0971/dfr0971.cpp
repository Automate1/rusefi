
#include <stdint.h>   // use C-style header to match rusEFI
#include <stdint.h>

#include "i2c_bb.h"   // pointer usage only; no brain_pin_e needed
#include "dfr0971.h"

Dfr0971::Dfr0971(BitbangI2c* bus, uint8_t addr)
    : i2c(bus), address(addr)
{
}

void Dfr0971::setOutput(uint8_t channel, uint16_t value)
{
    // DFR0971 protocol: 3-byte write (channel + MSB + LSB)
    uint8_t buf[3];
    buf[0] = channel;
    buf[1] = (value >> 8) & 0xFF;
    buf[2] = value & 0xFF;

    i2c->write(address, buf, 3);  // matches i2c_bb::write(uint8_t addr, const uint8_t* data, size_t size)
}
