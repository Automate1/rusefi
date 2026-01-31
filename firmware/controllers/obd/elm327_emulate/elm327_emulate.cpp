// firmware/controllers/obd/elm327_emulate/elm327_emulate.cpp

#include <cstdint>
#include "efi_printf.h"         // logging
#include "elm327_emulate.h"
#include "engine_configuration.h"

// Logging prefix
#define ELM_LOG_PREFIX "[ELM327] "
#define elmLog(...) efiPrintf(ELM_LOG_PREFIX __VA_ARGS__)

// Tracks whether ELM327 emulation is active
static bool elmEnabled = false;

// Forward declaration of RX dispatcher
[[maybe_unused]] static void uartRxDispatcher(uint8_t byte);

/**
 * Initialize ELM327 emulation.
 * Hook this into your board's UART thread (TS secondary or dedicated thread).
 */
void elm327EmulateInit() {
    if (elmEnabled) return;

    elmEnabled = true;
    elmLog("Starting ELM327 emulation on secondary UART\r\n");

    // TODO: hook uartRxDispatcher to UART hardware / thread

    elmLog("Ready\r\n");
}

/**
 * Stop ELM327 emulation.
 * Detach UART RX if you hooked it in Init().
 */
void elm327EmulateStop() {
    if (!elmEnabled) return;

    elmEnabled = false;
    elmLog("ELM327 emulation disabled\r\n");

    // TODO: stop UART thread / detach callback if needed
}

/**
 * Called for every byte received from UART.
 * For now: just log what we see.
 */
void elm327EmulateOnByte(uint8_t byte) {
    if (!elmEnabled) return;

    if (byte >= 32 && byte <= 126) {
        elmLog("RX '%c' (0x%02X)\r\n", byte, byte);
    } else {
        elmLog("RX 0x%02X\r\n", byte);
    }

    // TODO: parse AT commands and respond via UART
}

/**
 * RX dispatcher: forwards received byte to ELM327 parser
 */
[[maybe_unused]] static void uartRxDispatcher(uint8_t byte) {
    elm327EmulateOnByte(byte);
}