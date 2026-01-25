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
size_t getDfrobotDacTotalChannels();

// Backing storage for TS + Lua
extern float dfrobotDacOutputPercent[];

#endif // DFROBOT_DAC

