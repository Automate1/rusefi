#pragma once

#include <cstdint>
#include "ch.h"
#include "hal.h"

// ---------- UART / board definitions ----------

// Serial device (secondary UART)
#ifndef ELM327_SERIAL_DEVICE
// #define ELM327_SERIAL_DEVICE SD2
#define ELM327_SERIAL_DEVICE (&SD2)
#endif

#ifndef ELM327_SERIAL_DEVICE_RX
#define ELM327_SERIAL_DEVICE_RX H144_UART2_RX
#endif

#ifndef ELM327_SERIAL_DEVICE_TX
#define ELM327_SERIAL_DEVICE_TX H144_UART2_TX
#endif

// ---------- Public API ----------

/**
 * Initialize and start ELM327 emulation.
 * Claims the secondary UART pins and starts the background thread.
 */
void initElm327Emulate();

/**
 * Stop ELM327 emulation.
 * Terminates the thread and releases resources.
 */
void stopElm327Emulate();

/**
 * Start ELM327 emulation.
 * Terminates the thread and releases resources.
 */
void startElm327Emulate();


/**
 * Handle a single byte received from the UART.
 * Currently just logs the byte to the console.
 */
void elm327EmulateOnByte(uint8_t rxByte);
