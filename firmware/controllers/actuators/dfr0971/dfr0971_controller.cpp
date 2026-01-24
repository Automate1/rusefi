
#if defined(DFROBOT_DAC)

	#include "pch.h"
	#include "dfrobot_dac_config.h"       
	#include "dfr0971.h"
	#include "dfr0971_controller.h"
	#include "i2c_bb.h"

           // include standard rusEFI headers

// Single I2C bus for all DFR0971 boards
static BitbangI2c dfrI2c;

// Initialize all DFR0971 boards
void initDfr0971() {
    // Initialize the I2C bus with fixed pins for uaEFI board
    dfrI2c.init((brain_pin_e) Gpio_E13, (brain_pin_e) Gpio_E14);

    // Create instances
    static Dfr0971 instances[DFROBOT_DAC_BOARD_COUNT] = {
        Dfr0971(&dfrI2c, dfrAddresses[0]),
#if DFROBOT_DAC_BOARD_COUNT > 1
        Dfr0971(&dfrI2c, dfrAddresses[1]),
#endif
    };

    // Save pointers for global access
    for (size_t i = 0; i < DFROBOT_DAC_BOARD_COUNT; i++) {
        dfrBoards[i] = &instances[i];
    }
}

// Set a DFR0971 output by board number and channel
// Input percent: 0.0 - 100.0, scaled internally to 0-4095
void dfr0971SetPercent(size_t board, uint8_t channel, float percent) {
    if (board >= DFROBOT_DAC_BOARD_COUNT) {
        return; // invalid board index
    }

    // Clamp percent
    if (percent < 0.0f) percent = 0.0f;
    if (percent > 100.0f) percent = 100.0f;

    // Scale 0-100% to 0-4095
    uint16_t value = static_cast<uint16_t>((percent / 100.0f) * 4095.0f);

    // Write value to DFR0971
    dfrBoards[board]->setOutput(channel, value);
}

#endif // DFROBOT_DAC