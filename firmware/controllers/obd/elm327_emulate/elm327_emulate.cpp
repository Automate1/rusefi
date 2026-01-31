#include "elm327_emulate.h"

#include "efi_printf.h"
#include "engine_configuration.h"

#define ELM_LOG_PREFIX "[ELM327] "

static bool elmEnabled = false;

void elm327EmulateInit() {
	if (elmEnabled) {
		return;
	}

	elmEnabled = true;
	efiPrintf(ELM_LOG_PREFIX "ELM327 emulation enabled");
}

void elm327EmulateStop() {
	if (!elmEnabled) {
		return;
	}

	elmEnabled = false;
	efiPrintf(ELM_LOG_PREFIX "ELM327 emulation disabled");
}

void elm327EmulateOnByte(uint8_t byte) {
	if (!elmEnabled) {
		return;
	}

	// For now: just log what we see
	if (byte >= 32 && byte <= 126) {
		efiPrintf(ELM_LOG_PREFIX "RX '%c' (0x%02X)", byte, byte);
	} else {
		efiPrintf(ELM_LOG_PREFIX "RX 0x%02X", byte);
	}
}