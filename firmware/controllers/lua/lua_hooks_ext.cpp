#include "pch.h"

#include "rusefi_lua.h"
#include "lua_hooks.h"

#if defined(DFROBOT_DAC)
	#include "dfrobot_dac_controller.h"
#endif

#if !defined(STM32F4) && EFI_CAN_SUPPORT
// existing CAN-related hooks would live here
#endif // !defined(STM32F4) && EFI_CAN_SUPPORT

#if defined(DFROBOT_DAC)

static int dfr_dac_set(lua_State* L) {
    int idx = luaL_checkinteger(L, 1);
    float percent = luaL_checknumber(L, 2);

	const int maxChannels = (int)getDfrobotDacTotalChannels();

	if (idx < 0 || idx >= maxChannels) {
    return 0;
	}

    dfrobotDacOutputPercent[idx] = percent;
    return 0; // no return values
}

static int dfr_dac_get(lua_State* L) {
    int idx = luaL_checkinteger(L, 1);

	const int maxChannels = (int)getDfrobotDacTotalChannels();

	if (idx < 0 || idx >= maxChannels) {
    return 0;
	}

    lua_pushnumber(L, dfrobotDacOutputPercent[idx]);
    return 1;
}
#endif //DFROBOT_DAC

void configureRusefiLuaHooksExt(lua_State* lState) {
#if !defined(STM32F4) && EFI_CAN_SUPPORT
    // existing CAN Lua registrations would go here
#endif // !defined(STM32F4) && EFI_CAN_SUPPORT

#if defined(DFROBOT_DAC)
    lua_register(lState, "dfr_dac_set", dfr_dac_set);
    lua_register(lState, "dfr_dac_get", dfr_dac_get);
#endif
}
