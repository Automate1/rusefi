#pragma once

#include "i2c_bus.h"

/**
 * Driver for the DFRobot DFR0971 DAC module.
 *
 * This module contains a GP8403 DAC plus an onboard MCU that provides
 * selectable I2C addresses and handles protocol translation. Therefore,
 * this driver is DFR0971-specific and not a generic GP8403 driver.
 *
 * Address range: 0x58–0x5B per DIP switches (2-channel DAC)
 */

class Dfr0971 {
public:
    /**
     * @param bus    I2C bus instance (I2C_DEVICE_x)
     * @param address 7-bit I2C address (0x58–0x5B)
     */
    Dfr0971(i2cDevice* bus, uint8_t address);

    /** Initialize the module */
    void init();

    /** Set channel output using raw 12-bit DAC value */
    void setRaw(uint8_t channel, uint16_t value);

    /** Set channel output using percent (0–100%) */
    void setPercent(uint8_t channel, float percent);

private:
    i2cDevice* m_bus;
    uint8_t m_addr;

    void writeDac(uint8_t channel, uint16_t value);
};
