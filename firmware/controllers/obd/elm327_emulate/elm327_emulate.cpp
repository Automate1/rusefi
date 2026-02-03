#include "pch.h"
#include "console_io.h"
#include "elm327_emulate.h"
#include "hellen_meta.h"
#include <cstdint>
#include <cstring>

// Optional: define logging prefix
#define ELM_LOG_PREFIX "ELM327: "

// Thread stack
static THD_WORKING_AREA(elmThreadStack, 512);
static thread_t *elm327ThreadHandle = nullptr;

// Minimal serial config for the secondary UART
static SerialConfig elmSerialConfig = {
#if EFI_PROD_CODE
    .speed = 38400,
    .cr1 = 0,
    .cr2 = USART_CR2_STOP1_BITS,
    .cr3 = 0
#endif
};

// Enabled flag
static bool elmEnabled = false;

// Logging helper
#define elmLog(fmt, ...) consolePrintf(ELM_LOG_PREFIX fmt, ##__VA_ARGS__)

// ELM327 thread: reads bytes and logs them
static THD_FUNCTION(elm327Thread, arg) {
    (void)arg;
    uint8_t rxBuf[16];

    while (elmEnabled) {
        // Read up to 16 bytes, non-blocking
        int bytesRead = sdReadTimeout(ELM327_SERIAL_DEVICE, rxBuf, sizeof(rxBuf), TIME_MS2I(10));

        if (bytesRead > 0) {
            for (int i = 0; i < bytesRead; i++) {
                uint8_t b = rxBuf[i];
                if (b >= 32 && b <= 126) {
                    elmLog(ELM_LOG_PREFIX "RX '%c' (0x%02X)\r\n", b, b);
                } else {
                    elmLog(ELM_LOG_PREFIX "RX 0x%02X\r\n", b);
                }

                // For now, just echo back
                sdWriteTimeout(ELM327_SERIAL_DEVICE, &b, 1, TIME_MS2I(10));
            }
        }

        chThdSleepMilliseconds(5);
    }
}

// Public API
void initElm327Emulate(){
	startElm327Emulate();
}

void startElm327Emulate() {

  
    if (elmEnabled) return;

    elmEnabled = true;
    elmLog(ELM_LOG_PREFIX "ELM327 emulation enabled\r\n");

    #if EFI_PROD_CODE
		efiSetPadMode("ELM UART RX", Gpio::ELM327_SERIAL_DEVICE_RX,
    	PAL_MODE_ALTERNATE(TS_SERIAL_AF));
		efiSetPadMode("ELM UART TX", Gpio::ELM327_SERIAL_DEVICE_TX,
    	PAL_MODE_ALTERNATE(TS_SERIAL_AF));
	#endif

    // Start UART
    sdStart(&ELM327_SERIAL_DEVICE, &elmSerialConfig);

    // Start thread
    elm327ThreadHandle = chThdCreateStatic(elmThreadStack,
                                           sizeof(elmThreadStack),
                                           NORMALPRIO + 1,
                                           elm327Thread,
                                           nullptr);

	elmLog("started on secondary UART\r\n");
}

void stopElm327Emulate() {
    if (!elmEnabled) return;
    elmEnabled = false;
    elmLog(ELM_LOG_PREFIX "ELM327 emulation disabled\r\n");

    if (elm327ThreadHandle) {
        chThdTerminate(elm327ThreadHandle);
        elm327ThreadHandle = nullptr;
    }
}
void elm327EmulateOnByte(uint8_t rxByte) {
    if (!elmEnabled) return;
    // For now, log incoming byte
    if (byte >= 32 && byte <= 126) {
        elmLog(ELM_LOG_PREFIX "RX '%c' (0x%02X)\r\n", byte, byte);
    } else {
        elmLog(ELM_LOG_PREFIX "RX 0x%02X\r\n", byte);
    }
}
