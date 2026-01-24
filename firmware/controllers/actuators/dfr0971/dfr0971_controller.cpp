
#if defined(DFROBOT_DAC)

	#include "pch.h"
	#include "dfrobot_dac_config.h"       
	#include "dfr0971.h"
	#include "dfr0971_controller.h"
	#include "i2c_bb.h"

// Single I2C bus for all DFR0971 boards
static BitbangI2c dfrobotI2c;

// One instance per board
static DfrobotDAC* dfrobotBoards[DFROBOT_DAC_BOARD_COUNT];

// Initialize all DFRobot DAC boards
void initDfrobotDac() {
    // Fixed pins for uaEFI board
	dfrobotI2c.init(DFROBOT_DAC_SCL_PIN, DFROBOT_DAC_SDA_PIN);

    static DfrobotDAC instances[DFROBOT_DAC_BOARD_COUNT];

    for (size_t i = 0; i < DFROBOT_DAC_BOARD_COUNT; i++) {
        instances[i].init(
            &dfrobotI2c,
            dfrobotDacBoards[i].i2cAddress,
            dfrobotDacBoards[i].channelCount
        );

        dfrobotDacBoards[i] = &instances[i];
    }
}


// Set a DFR0971 output by board number and channel
// Input percent: 0.0 - 100.0, scaled internally to 0-4095
void dfrobotDacSetPercent(size_t board, uint8_t channel, float percent) {
    if (board >= DFROBOT_DAC_BOARD_COUNT) {
        return; // invalid board index
    }

    // Clamp percent
    if (percent < 0.0f) percent = 0.0f;
    if (percent > 100.0f) percent = 100.0f;

    // Scale 0-100% to 0-4095
    uint16_t value = static_cast<uint16_t>((percent / 100.0f) * 4095.0f);

    // Write value to DFR
    dfrobotBoards[board]->setOutput(channel, value);
}

#endif // DFROBOT_DAC