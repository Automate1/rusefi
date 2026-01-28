#include "pch.h"

#include "rusefi_lua.h"
#include "lua_hooks.h"
#include "lua_helpers.h"

#if defined(DFROBOT_DAC)
	#include "dfrobot_dac_controller.h"
#endif

#if !defined(STM32F4) && EFI_CAN_SUPPORT
// existing CAN-related hooks would live here
#endif // !defined(STM32F4) && EFI_CAN_SUPPORT

#if defined(DFROBOT_DAC)

LUA_FUNCTION(dfr_dac_set) {
    int board   = luaL_checkinteger(L, 1);
    int channel = luaL_checkinteger(L, 2);
    float pct   = luaL_checknumber(L, 3);

    dfrobotDacSetPercent(
        static_cast<size_t>(board),
        static_cast<uint8_t>(channel),
        pct
    );
    return 0;
}
#endif //DFROBOT_DAC

void configureRusefiLuaHooksExt(lua_State* lState) {
#if !defined(STM32F4) && EFI_CAN_SUPPORT
    // existing CAN Lua registrations would go here
#endif // !defined(STM32F4) && EFI_CAN_SUPPORT


#if defined(DFROBOT_DAC)
    LUA_REGISTER(dfr_dac_set);
#endif

}
