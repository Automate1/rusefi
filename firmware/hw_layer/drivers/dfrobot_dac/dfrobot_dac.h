#pragma once

#if defined(DFROBOT_DAC)

#include <cstdint>

class BitbangI2c;

class DfrobotDac {
public:
    DfrobotDac() = default;

    void init(BitbangI2c* i2c, uint8_t address, uint8_t channelCount) {
        m_i2c = i2c;
        m_address = address;
        m_channelCount = channelCount;
    }

    void setOutput(uint8_t channel, uint16_t value);

private:
    BitbangI2c* m_i2c = nullptr;
    uint8_t m_address = 0;
    uint8_t m_channelCount = 0;
};


#endif // DFROBOT_DAC