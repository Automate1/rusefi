#pragma once
#include "dfr0971_config.h"

#if DFR0971_BOARD_COUNT > 0

#include <cstdint>

class BitbangI2c;

class Dfr0971 {
public:
    Dfr0971(BitbangI2c* i2c, uint8_t address);

	// channel: 0 or 1
    // value:   raw DAC value (driver does not scale)
    void setOutput(uint8_t channel, uint16_t value);

private:
    BitbangI2c* m_i2c;
    uint8_t m_address;
};

#endif // DFR0971_BOARD_COUNT > 0