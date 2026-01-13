#pragma once

#if defined(HELLEN_UAEFI)

#include "controllers/core/brain_pin.h"

static constexpr brain_pin_e DFR0971_SCL = Gpio_E13;
static constexpr brain_pin_e DFR0971_SDA = Gpio_E14;

#else
#error "DFR0971 pins not defined for this board"
#endif