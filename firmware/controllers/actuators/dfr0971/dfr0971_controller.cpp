#if DFR0971_BOARD_COUNT > 0

#include "pch.h"

// #include "dfr0971_controller.h"
#include "dfr0971.h"
#include "i2c_bb.h"
#include "lua_hooks.h"
#include "pch.h"


#include "dfr0971.h"
#include "dfr0971_board.h"

#include "i2c_bb.h"
#include "module.h"

#include <algorithm>

// -----------------------------------------------------------------------------
// Constants
// -----------------------------------------------------------------------------

static constexpr uint16_t DFR0971_MAX = 4095;

// -----------------------------------------------------------------------------
// Static objects (firmware lifetime)
// -----------------------------------------------------------------------------

static BitbangI2c dfrI2c;
static Dfr0971 dfr0971(dfrI2c, 0x2C);   // default DFR0971 address

// -----------------------------------------------------------------------------
// Internal helpers
// -----------------------------------------------------------------------------

static uint16_t percentToDac(float percent) {
    if (percent <= 0.0f) {
        return 0;
    }
    if (percent >= 100.0f) {
        return DFR0971_MAX;
    }

    return static_cast<uint16_t>(
        (percent * DFR0971_MAX + 50.0f) / 100.0f
    );
}

// -----------------------------------------------------------------------------
// Public controller API (used by Lua / future callers)
// -----------------------------------------------------------------------------

void dfr0971SetPercent(uint8_t channel, float percent) {
    const uint16_t dac = percentToDac(percent);
    dfr0971.setOutput(channel, dac);
}

// -----------------------------------------------------------------------------
// Module init
// -----------------------------------------------------------------------------

static void initDfr0971() {
    dfrI2c.init(DFR0971_SCL, DFR0971_SDA);
}

// -----------------------------------------------------------------------------
// Module registration
// -----------------------------------------------------------------------------

struct Dfr0971Module final : public Module {
    Dfr0971Module() : Module("DFR0971") {}

    void init() override {
        initDfr0971();
    }
};

static Dfr0971Module dfr0971Module;

#endif // USE_DFR0971