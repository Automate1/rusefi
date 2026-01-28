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

static int lua_dfr_dac_set(lua_State* lState) {
    int board   = luaL_checkinteger(lState, 1);
    int channel = luaL_checkinteger(lState, 2);
    float pct   = luaL_checknumber(lState, 3);

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
    lua_register(lstate, "dfr_dac_set", lua_dfr_dac_set);
#else
    (void)lState;
#endif

}
