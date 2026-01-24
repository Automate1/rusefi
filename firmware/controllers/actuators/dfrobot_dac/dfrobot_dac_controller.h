#pragma once

#if defined(DFROBOT_DAC)

#include "dfrobot_dac_config.h"
#include <cstddef>
#include <cstdint>

void initDfrobotDac();

void dfrobotDacSetPercent(size_t board,
                       uint8_t channel,
                       float percent);


#endif // DFROBOT_DAC
