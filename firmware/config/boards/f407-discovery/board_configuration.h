#pragma once

#include "dfr0971.h"

// Forward declaration of BitbangI2c
class BitbangI2c;

// Only declare DAC here so other files can reference it
extern Dfr0971 dac1;
extern BitbangI2c bbI2C;

// void registerDACLuaFunctions(lua_State* L);
