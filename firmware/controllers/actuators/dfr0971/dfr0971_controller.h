#pragma once
#if DFR0971_BOARD_COUNT > 0

#include "pch.h"

/**
 * Controller for one or more DFR0971 DACs.
 *
 * Public API is intentionally minimal and unit-safe.
 */
class Dfr0971Controller {
public:
    void init();

    // percent: 0.0 – 100.0
    void setOutputPercent(uint8_t device,
                          uint8_t channel,
                          float percent);

private:
    bool m_initialized = false;
};

#endif