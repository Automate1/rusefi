#pragma once

#if defined(DFROBOT_DAC)

// -------- I2C bus configuration --------
constexpr brain_pin_e DFROBOT_DAC_SCL_PIN = (brain_pin_e)Gpio_E13;
constexpr brain_pin_e DFROBOT_DAC_SDA_PIN = (brain_pin_e)Gpio_E14;

constexpr size_t DFROBOT_DAC_BOARD_COUNT = 1;

struct DfrobotDacBoardConfig {
    uint8_t i2cAddress;
    uint8_t channelCount;
 	float maxUserVolt;
	float maxHardwareVolt;  // e.g. 10.0f
    float maxUserVolt;      // e.g. 5.0f
    uint16_t dacFullScale;  // e.g. 4095
};

constexpr DfrobotDacBoardConfig dfrobotDacBoards[DFROBOT_DAC_BOARD_COUNT] = {
    {
        .i2cAddress = 0x60,
        .channelCount = 2,
        .maxUserVolt = 5.0f,
		.maxHardwareVolt = 10.0f,
		.dacFullScale = 4095
    }
};

#endif