#pragma once
#include <cstdint>
#include "i2c_bb.h"

/**
 * Driver for DFRobot DFR0971 12-bit DAC
 * Supports 2 channels per device
 */

// class BitbangI2c;  // forward declaration is sufficient

private:
	BitbangI2c dfr_i2c;
    uint8_t address;

class Dfr0971 {
public:
	void init(brain_pin_e scl, brain_pin_e sda);
    // Dfr0971(BitbangI2c* bus, uint8_t addr);

    // Set output on a single DAC channel
    void setOutput(uint8_t channel, uint16_t value);
};
