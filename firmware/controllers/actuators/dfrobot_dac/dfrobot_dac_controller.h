#pragma once

#if defined(DFROBOT_DAC)

#include "dfrobot_dac_config.h"
#include <cstddef>
#include <cstdint>

void initDfrobotDac();

void dfrobotDacSetPercent(size_t board,
                       uint8_t channel,
                       float percent);


// Total number of exposed DAC channels
constexpr size_t DFROBOT_DAC_TOTAL_CHANNELS =
    DFROBOT_DAC_BOARD_COUNT * DFROBOT_DAC_CHANNELS_PER_BOARD;

// Backing storage for TS + Lua
extern float dfrobotDacOutputPercent[DFROBOT_DAC_TOTAL_CHANNELS];

#endif // DFROBOT_DAC

