#include "pch.h"

#include "controllers/actuators/dfr0971/dfr0971_controller.h"
#include "hw_layer/drivers/dfr0971/dfr0971.h"
#include "hw_layer/drivers/i2c/i2c_bb.h"
#include "configuration.h"
#include "lua/lua_hooks.h"

// ---- constants ----
static constexpr uint16_t DFR0971_MAX = 4095;
static constexpr uint8_t  MAX_DEVICES = 2;

// ---- hardware ownership ----
static BitbangI2c dfrI2c;
static Dfr0971*   dacs[MAX_DEVICES];

// ---- controller instance ----
static Dfr0971Controller dfrController;

void Dfr0971Controller::init() {
    if (m_initialized) {
        return;
    }

    if (!boardConfiguration->i2c_bb_scl.isValid()) {
        return;
    }

    dfrI2c.init(
        boardConfiguration->i2c_bb_scl,
        boardConfiguration->i2c_bb_sda
    );

    dacs[0] = new Dfr0971(dfrI2c, 0x60);
    dacs[1] = new Dfr0971(dfrI2c, 0x61);

    m_initialized = true;
}

void Dfr0971Controller::setOutputPercent(uint8_t device,
                                         uint8_t channel,
                                         float percent) {
    if (!m_initialized) {
        return;
    }

    if (device >= MAX_DEVICES || channel > 1) {
        return;
    }

    // ---- clamp percent ----
    if (percent < 0.0f) {
        percent = 0.0f;
    } else if (percent > 100.0f) {
        percent = 100.0f;
    }

    // ---- scale to DAC range ----
    uint16_t value = static_cast<uint16_t>(
        (percent / 100.0f) * DFR0971_MAX + 0.5f
    );

    dacs[device]->setOutput(channel, value);
}