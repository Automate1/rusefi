
#ifndef DFR0971_BOARD_COUNT
	#define DFR0971_BOARD_COUNT 1
#endif

#if DFR0971_BOARD_COUNT > 0

#include "dfr0971.h"
#include "i2c_bb.h"
#include "engine.h"
#include <algorithm>

static BitbangI2c dfrI2c;

static Dfr0971* dfrBoards[DFR0971_BOARD_COUNT];

static constexpr uint8_t baseAddress = 0x60; // first DFR0971

static uint16_t percentToDac(float percent) {
    percent = std::clamp(percent, 0.0f, 100.0f);
    return static_cast<uint16_t>((percent / 100.0f) * 4095.0f);
}

void initDfr0971Controller() {
    // Pins are board-family specific
    dfrI2c.init(Gpio_E13, Gpio_E14);

    for (uint8_t i = 0; i < DFR0971_BOARD_COUNT; i++) {
        dfrBoards[i] = new Dfr0971(dfrI2c, baseAddress + i);
    }
}

void dfr0971SetOutput(uint8_t board, uint8_t channel, float percent) {
    if (board >= DFR0971_BOARD_COUNT || channel >= 4) {
        return;
    }

    uint16_t value = percentToDac(percent);
    dfrBoards[board]->setOutput(channel, value);
}
#endif // USE_DFR0971