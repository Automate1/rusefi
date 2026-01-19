#ifndef DFR0971_BOARD_COUNT
#define DFR0971_BOARD_COUNT 1
#endif

#if DFR0971_BOARD_COUNT > 0

#pragma once

#ifndef DFR0971_BOARD_COUNT
#define DFR0971_BOARD_COUNT 0
#endif

#if DFR0971_BOARD_COUNT > 0

#include <cstddef>
#include <cstdint>

void initDfr0971();

void dfr0971SetPercent(size_t board,
                       uint8_t channel,
                       float percent);


#endif // DFR0971_BOARD_COUNT > 0
