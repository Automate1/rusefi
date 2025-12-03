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
    /**
     * @param bus Pointer to i2cDevice (bit-bang)
     * @param address 7-bit I2C address (0x58–0x5B)
     */
    Dfr0971(i2cDevice* bus, uint8_t address);

    /** Initialize the DAC module */
    void init();

    /** Set channel output using raw 12-bit DAC value (0–4095) */
    void setRaw(uint8_t channel, uint16_t value);

    /** Set channel output using percent (0–100%) */
    void setPercent(uint8_t channel, float percent);

private:
    i2cDevice* m_bus;
    uint8_t m_addr;

    void writeDac(uint8_t channel, uint16_t value);
};
