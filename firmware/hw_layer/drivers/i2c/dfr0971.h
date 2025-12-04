#pragma once

#include "i2c_bb.h"  // bit-bang I2C for f407-discovery

/**
 * DFRobot DFR0971 DAC driver (2-channel 12-bit DAC, 0-5V output)
 *
 * Designed for rusEFI f407-discovery board using i2c_bb.
 * Supports addresses 0x58–0x5B set via DIP switches.
 */

#include <stdint.h>

class BitbangI2c;

class Dfr0971 {
public:
    // Constructor: pass BitbangI2c object and I2C address
    Dfr0971(BitbangI2c* bus, uint8_t address);

    // Initialize DAC (optional: reset or configure)
    void init();

    // Set DAC channel output as percentage (0.0–100.0)
    void setPercent(uint8_t channel, float percent);

private:
    BitbangI2c* m_bus;
    uint8_t m_address;

    // Convert percentage to raw 12-bit DAC value
    uint16_t percentToValue(float percent);

    // Write 12-bit value to a specific channel
    void writeChannel(uint8_t channel, uint16_t value);
};
