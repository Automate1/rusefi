#include "pch.h"

#include "rusefi_lua.h"
#include "lua_api.h"
#include "lua_hooks.h"

#include "pch.h"

#include "lua/lua_api.h"
#include "lua/lua_hooks.h"

#if defined(DFROBOT_DAC)
	#include "dfrobot_dac.h"
#endif

#if !defined(STM32F4) && EFI_CAN_SUPPORT
// existing CAN-related hooks would live here
#endif // !defined(STM32F4) && EFI_CAN_SUPPORT

#if defined(DFROBOT_DAC)
// Set a DAC output by board and channel (0-based)
LUA_FUNCTION(dfr_dac_set) {
    size_t board   = luaL_checkinteger(L, 1);
    size_t channel = luaL_checkinteger(L, 2);
    float percent  = luaL_checknumber(L, 3);

    if (board >= DFROBOT_DAC_BOARD_COUNT) return 0;
    if (channel >= dfrobotBoards[board]->getChannelCount()) return 0;

    dfrobotBoards[board]->setPercent(channel, percent);

    return 0; // no return values
}

// Get DAC output percent by board and channel (0-based)
LUA_FUNCTION(dfr_dac_get) {
    size_t board   = luaL_checkinteger(L, 1);
    size_t channel = luaL_checkinteger(L, 2);

    if (board >= DFROBOT_DAC_BOARD_COUNT) return 0;
    if (channel >= dfrobotBoards[board]->getChannelCount()) return 0;

    lua_pushnumber(L, dfrobotBoards[board]->getPercent());
    return 1; // return 1 value
}
#endif

void configureRusefiLuaHooksExt(lua_State* lState) {
#if !defined(STM32F4) && EFI_CAN_SUPPORT
    // existing CAN Lua registrations would go here
#endif // !defined(STM32F4) && EFI_CAN_SUPPORT

#if defined(DFROBOT_DAC)
    LUA_REGISTER(dfr_dac_set);
    LUA_REGISTER(dfr_dac_get);
#endif
}