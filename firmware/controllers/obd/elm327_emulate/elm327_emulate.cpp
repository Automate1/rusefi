// firmware/controllers/obd/elm327_emulate/elm327_emulate.cpp

#include "console_io.h"
#include "elm327_emulate.h"
#include "engine_configuration.h"
#include "uart.h"

// Logging prefix + helper
#define ELM_LOG_PREFIX "[ELM327] "
#define elmLog(...) consolePrintf(ELM_LOG_PREFIX __VA_ARGS__)

// Tracks whether emulation is active
static bool elmEnabled = false;

// Forward declaration
static void uartRxDispatcher(uint8_t byte);

void elm327EmulateInit() {
    if (elmEnabled) {
        return;
    }

    elmEnabled = true;

    elmLog("Starting emulation on UART2\r\n");

    uartStartRx(UART2, uartRxDispatcher);

    elmLog("Ready\r\n");
}

void elm327EmulateStop() {
    if (!elmEnabled) {
        return;
    }

    elmEnabled = false;

    elmLog("ELM327 emulation disabled\r\n");

    // Optionally stop the UART receive
    // uartStopRx(UART2);
}

void elm327EmulateOnByte(uint8_t byte) {
    if (!elmEnabled) {
        return;
    }

    if (byte >= 32 && byte <= 126) {
        elmLog("RX '%c' (0x%02X)\r\n", byte, byte);
    } else {
        elmLog("RX 0x%02X\r\n", byte);
    }

    // TODO: handle actual ELM commands here
}

static void uartRxDispatcher(uint8_t byte) {
    elm327EmulateOnByte(byte);
}