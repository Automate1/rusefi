// firmware/controllers/obd/elm327_emulate/elm327_emulate.cpp

#include "rusefi_console.h"
#include "elm327_emulate.h"
#include "engine_configuration.h"
#include "uart.h"

// Logging prefix
#define ELM_LOG_PREFIX "[ELM327] "
#define elmLog(...) rusefi_printf(ELM_LOG_PREFIX __VA_ARGS__)

// Global flag to track whether ELM327 emulation is enabled
static bool elmEnabled = false;

/**
 * Enable / start ELM327 emulation
 */
void elm327EmulateInit() {
    if (elmEnabled) {
        return; // already running
    }

    elmEnabled = true;

    elmLog("Starting emulation on UART2\r\n");

    // Start UART RX
    uartStartRx(UART2, uartRxDispatcher);

    elmLog("Ready\r\n");
}

/**
 * Stop ELM327 emulation
 */
void elm327EmulateStop() {
    if (!elmEnabled) {
        return; // already stopped
    }

    elmEnabled = false;

    elmLog("ELM327 emulation disabled\r\n");

    // Optional: stop UART RX if desired
    // uartStopRx(UART2);
}

/**
 * RX dispatcher: called for each received byte
 */
void elm327EmulateOnByte(uint8_t byte) {
    if (!elmEnabled) {
        return;
    }

    // For now: just log incoming bytes
    if (byte >= 32 && byte <= 126) {
        elmLog("RX '%c' (0x%02X)\r\n", byte, byte);
    } else {
        elmLog("RX 0x%02X\r\n", byte);
    }

    // TODO: parse ELM327 commands and respond via uartTx(UART2,...)
}

/**
 * UART RX dispatcher: forwards to ELM327
 */
static void uartRxDispatcher(uint8_t byte) {
    elm327EmulateOnByte(byte);
}