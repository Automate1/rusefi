#pragma once

#if defined(DFROBOT_DAC)

constexpr size_t DFROBOT_DAC_BOARD_COUNT = 1;

struct DfrobotDacBoardConfig {
    uint8_t i2cAddress;
    uint8_t channelCount;
    float minVoltage;
    float maxVoltage;
	float maxUserVolt;
};

constexpr DfrobotDacBoardConfig dfrobotDacBoards[DFROBOT_DAC_BOARD_COUNT] = {
    {
        .i2cAddress = 0x60,
        .channelCount = 2,
        .minVoltage = 0.0f,
        .maxVoltage = 10.0f,
		.maxUserVolt = 5.0f,
    }
};

#endif