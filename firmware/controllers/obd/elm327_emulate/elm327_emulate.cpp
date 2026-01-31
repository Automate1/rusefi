#include <cstdint>

#include "console_io.h"
#include "elm327_emulate.h"

#define ELM_LOG_PREFIX "[ELM327] "
#define elmLog(...) consolePrintf(ELM_LOG_PREFIX __VA_ARGS__)

static bool elmEnabled = false;

void elm327EmulateInit() {
	if (elmEnabled) {
		return;
	}

	elmEnabled = true;
	elmLog("ELM327 emulation enabled\r\n");
}

void elm327EmulateStop() {
	if (!elmEnabled) {
		return;
	}

	elmEnabled = false;
	elmLog("ELM327 emulation disabled\r\n");
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
}