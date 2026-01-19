#ifndef DFR0971_BOARD_COUNT
	#define DFR0971_BOARD_COUNT 1
#endif

#if DFR0971_BOARD_COUNT > 0

#include "pch.h"
#include "i2c_bb.h"
#include "dfr0971.h"
#include <algorithm>

Dfr0971::Dfr0971(BitbangI2c* i2c, uint8_t address)
    : m_i2c(i2c)
    , m_address(address) {
}

void Dfr0971::setOutput(uint8_t channel, uint16_t value) {
    value = std::min<uint16_t>(value, 4095);

    uint8_t buf[3];
    buf[0] = channel;
    buf[1] = (value >> 8) & 0x0F;
    buf[2] = value & 0xFF;

    m_i2c->write(m_address, buf, sizeof(buf));
}

#endif // DFR0971_BOARD_COUNT > 0
