#pragma once

#include <stdint.h>

// Called when feature is enabled (via TS)
void elm327EmulateInit();

// Called for every received UART byte
void elm327EmulateOnByte(uint8_t byte);

// Optional cleanup if UART is released
void elm327EmulateStop();