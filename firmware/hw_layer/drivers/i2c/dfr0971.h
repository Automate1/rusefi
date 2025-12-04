#pragma once

#include "i2c_bb.h"  // bit-bang I2C for f407-discovery

/**
 * DFRobot DFR0971 DAC driver (2-channel 12-bit DAC, 0-5V output)
 *
 * Designed for rusEFI f407-discovery board using i2c_bb.
 * Supports addresses 0x58–0x5B set via DIP switches.
 */

class Dfr0971 {
public:
    Dfr0971(BitbangI2c* bus, uint8_t address);

    void init();
    void setRaw(uint8_t channel, uint16_t value);
    void setPercent(uint8_t channel, float percent);

private:
    BitbangI2c* m_bus;
    uint8_t m_addr;

    void writeDac(uint8_t channel, uint16_t value);
};
