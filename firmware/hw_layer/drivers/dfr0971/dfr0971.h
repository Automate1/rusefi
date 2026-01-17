#pragma once

#if DFR0971_BOARD_COUNT > 0

#include "pch.h"          // REQUIRED: brings in stdint, size_t, ChibiOS, etc.

class BitbangI2c;

/**
 * Minimal driver for DFRobot DFR0971 (2-channel I2C DAC)
 *
 * Responsibilities:
 *  - Write raw DAC values to a specific device address
 *
 * Does NOT:
 *  - Own pins
 *  - Own the I2C bus
 *  - Perform scaling or safety checks
 */
class Dfr0971 {
public:
    Dfr0971(BitbangI2c& i2c, uint8_t i2cAddress);

    // channel: 0 or 1
    // value:   raw DAC value (driver does not scale)
    void setOutput(uint8_t channel, uint16_t value);

private:
    BitbangI2c& m_i2c;
    uint8_t     m_address;
};

#endif



#pragma once

#include <cstdint>

class BitbangI2c;

class Dfr0971 {
public:
    explicit Dfr0971(BitbangI2c& i2c, uint8_t address);

    void setOutput(uint8_t channel, uint16_t value);

private:
    BitbangI2c& m_i2c;
    uint8_t m_address;
};#pragma once

#ifndef DFR0971_BOARD_COUNT
#define DFR0971_BOARD_COUNT 0
#endif

#if DFR0971_BOARD_COUNT > 0

#include <cstdint>

class BitbangI2c;

class Dfr0971 {
public:
    Dfr0971(BitbangI2c* i2c, uint8_t address);

    void setOutput(uint8_t channel, uint16_t value);

private:
    BitbangI2c* m_i2c;
    uint8_t m_address;
};

#endif // DFR0971_BOARD_COUNT > 0