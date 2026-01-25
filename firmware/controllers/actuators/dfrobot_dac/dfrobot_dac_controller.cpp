
#if defined(DFROBOT_DAC)

	#include "pch.h"
	#include "dfrobot_dac_config.h"       
	#include "dfrobot_dac.h"
	#include "dfrobot_dac_controller.h"
	#include "i2c_bb.h"

// Single I2C bus for all DFR0971 boards
static BitbangI2c dfrobotI2c;

// One instance per board
// static DfrobotDac* dfrobotBoards[DFROBOT_DAC_BOARD_COUNT];  //unused

static constexpr size_t DFROBOT_DAC_TOTAL_CHANNELS =
    DFROBOT_DAC_BOARD_COUNT * DFROBOT_DAC_CHANNELS_PER_BOARD;

float dfrobotDacOutputPercent[DFROBOT_DAC_TOTAL_CHANNELS] = {0};

size_t getDfrobotDacTotalChannels() {
    return DFROBOT_DAC_TOTAL_CHANNELS;

// Initialize all DFRobot DAC boards
void initDfrobotDac() {
    // Fixed pins for uaEFI board
	dfrobotI2c.init(DFROBOT_DAC_SCL_PIN, DFROBOT_DAC_SDA_PIN);

    static DfrobotDac instances[DFROBOT_DAC_BOARD_COUNT];

    for (size_t i = 0; i < DFROBOT_DAC_BOARD_COUNT; i++) {
        instances[i].init(
            &dfrobotI2c,
            dfrobotDacBoards[i].i2cAddress,
            dfrobotDacBoards[i].channelCount
        );

        dfrobotBoards[i] = &instances[i];
    }
}

// Set a DFR output by board number and channel
// Input percent: 0.0 - 100.0, scaled internally to 0-4095
void dfrobotDacSetPercent(size_t board, uint8_t channel, float percent) {
    if (board >= DFROBOT_DAC_BOARD_COUNT) {
        return; // invalid board index
    }

	const auto& cfg = dfrobotDacBoards[board];

    if (channel >= cfg.channelCount) {
        return;
	}

    // Clamp percent
    percent = clampF(percent, 0.0f, 100.0f);

    float userVolt = (percent / 100.0f) * cfg.maxUserVolt;

    float dacFraction = userVolt / cfg.maxHardwareVolt;

    uint16_t value = static_cast<uint16_t>(
        dacFraction * cfg.dacFullScale

    // Write value to DFR
    dfrobotBoards[board]->setOutput(channel, value);
}

#endif // DFROBOT_DAC

