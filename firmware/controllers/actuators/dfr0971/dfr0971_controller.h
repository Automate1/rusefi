#pragma once

#if defined(DFR0971_BOARD_COUNT) && DFR0971_BOARD_COUNT > 0


#include <cstddef>
#include <cstdint>

void initDfr0971();

void dfr0971SetPercent(size_t board,
                       uint8_t channel,
                       float percent);


#endif // DFR0971_BOARD_COUNT > 0
