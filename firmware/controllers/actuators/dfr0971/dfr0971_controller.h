#pragma once

#if defined(DFROBOT_DAC)


#include <cstddef>
#include <cstdint>

void initDfr0971();

void dfr0971SetPercent(size_t board,
                       uint8_t channel,
                       float percent);


#endif // DFR0971_BOARD_COUNT > 0
