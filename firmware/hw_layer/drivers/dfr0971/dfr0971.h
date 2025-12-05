#pragma once
#include "i2c_bb.h"
#include <stdint.h>

/**
 * Driver for DFRobot DFR0971 12-bit DAC
 * Supports 2 channels per device
 */
class Dfr0971 {
public:
    Dfr0971(BitbangI2c *i2cBus, uint8_t i2cAddress);

    /**
     * Set output for a DAC channel
     * @param channel 0..1
     * @param value 0..4095
     */
    void setOutput(uint8_t channel, uint16_t value);

private:
    BitbangI2c *i2c;
    uint8_t address;
};
