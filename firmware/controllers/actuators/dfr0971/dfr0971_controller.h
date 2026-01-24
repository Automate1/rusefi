#pragma once

#if defined(DFROBOT_DAC)

#include "dfrobot_dac_config"
#include <cstddef>
#include <cstdint>

void initDfr0971();

void dfr0971SetPercent(size_t board,
                       uint8_t channel,
                       float percent);


#endif // DFROBOT_DAC
