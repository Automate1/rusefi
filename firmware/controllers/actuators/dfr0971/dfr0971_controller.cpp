#ifndef DFR0971_BOARD_COUNT
#define DFR0971_BOARD_COUNT 1
#endif

#if DFR0971_BOARD_COUNT > 0

#include "dfr0971_controller.h"
#include "hw_layer/drivers/dfr0971/dfr0971.h"
#include "hw_layer/drivers/i2c/i2c_bb.h"
#include "boards.h"

static BitbangI2c dfrI2c;
static Dfr0971* dfrBoards[DFR0971_BOARD_COUNT];

static constexpr brain_pin_e DFR0971_SCL_PIN = Gpio_E13;
static constexpr brain_pin_e DFR0971_SDA_PIN = Gpio_E14;

static constexpr uint8_t dfrAddresses[DFR0971_BOARD_COUNT] = {
    0x60,
#if DFR0971_BOARD_COUNT > 1
    0x61,
#endif
};

void initDfr0971() {
    dfrI2c.init(DFR0971_SCL_PIN, DFR0971_SDA_PIN);

    static Dfr0971 instances[DFR0971_BOARD_COUNT] = {
        Dfr0971(&dfrI2c, dfrAddresses[0]),
#if DFR0971_BOARD_COUNT > 1
        Dfr0971(&dfrI2c, dfrAddresses[1]),
#endif
    };

    for (size_t i = 0; i < DFR0971_BOARD_COUNT; i++) {
        dfrBoards[i] = &instances[i];
    }
}

void dfr0971SetPercent(size_t board, uint8_t channel, float percent) {
    if (board >= DFR0971_BOARD_COUNT) {
        return;
    }

    if (percent < 0.0f) percent = 0.0f;
    if (percent > 100.0f) percent = 100.0f;

    uint16_t value = static_cast<uint16_t>((percent / 100.0f) * 4095.0f);
    dfrBoards[board]->setOutput(channel, value);
}

#endif