
#ifndef DFR0971_BOARD_COUNT
#define DFR0971_BOARD_COUNT 1
#endif

#if DFR0971_BOARD_COUNT > 0

#include "dfr0971.h"
#include "i2c_bb.h"

#include "module.h"
#include "boards.h"

static BitbangI2c dfrI2c;
static Dfr0971* dfrDevices[DFR0971_BOARD_COUNT];

static constexpr brain_pin_e DFR0971_SCL_PIN = Gpio_E13;
static constexpr brain_pin_e DFR0971_SDA_PIN = Gpio_E14;

static constexpr uint8_t dfrAddresses[DFR0971_BOARD_COUNT] = {
    0x60, // board 0
#if DFR0971_BOARD_COUNT > 1
    0x61,
#endif
};

static void initDfr0971() {
    dfrI2c.init(DFR0971_SCL_PIN, DFR0971_SDA_PIN);

    for (int i = 0; i < DFR0971_BOARD_COUNT; i++) {
        static Dfr0971 devices[DFR0971_BOARD_COUNT] = {
            Dfr0971(&dfrI2c, dfrAddresses[0]),
#if DFR0971_BOARD_COUNT > 1
            Dfr0971(&dfrI2c, dfrAddresses[1]),
#endif
        };
        dfrDevices[i] = &devices[i];
    }
}