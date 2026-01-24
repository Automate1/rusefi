#pragma once

#if defined(DFROBOT_DAC)

#include <cstdint>

class BitbangI2c;

class DfrobotDAC {
public:
    DfrobotDAC(BitbangI2c* i2c, uint8_t address);

	// channel: 0 or 1
    // value:   raw DAC value (driver does not scale)
    void setOutput(uint8_t channel, uint16_t value);

private:
    BitbangI2c* m_i2c;
    uint8_t m_address;
};

#endif // DFROBOT_DAC