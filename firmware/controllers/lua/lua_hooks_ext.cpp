#include "pch.h"

#include "rusefi_lua.h"
#include "lua_hooks.h"

#if defined(DFR0971_BOARD_COUNT) && DFR0971_BOARD_COUNT > 0
#include "controllers/actuators/dfr0971/dfr0971_controller.h"
#endif

#if !defined(STM32F4) && EFI_CAN_SUPPORT
// existing CAN-related hooks would live here
#endif // !defined(STM32F4) && EFI_CAN_SUPPORT

#if defined(DFR0971_BOARD_COUNT) && DFR0971_BOARD_COUNT > 0
/**
 * Lua: dfr0971SetPercent(board, channel, percent)
 *  board   : 0-based DFR0971 board index
 *  channel : 0-3 (DFR0971 output channel)
 *  percent : 0.0 - 100.0
 */
static int luaDfr0971SetPercent(lua_State* L) {
    // Argument checking (rusEFI-style defensive Lua)
    int board = static_cast<int>(luaL_checkinteger(L, 1));
    int channel = static_cast<int>(luaL_checkinteger(L, 2));
    float percent = static_cast<float>(luaL_checknumber(L, 3));

    dfr0971SetPercent(static_cast<size_t>(board),
                      static_cast<uint8_t>(channel),
                      percent);

    return 0; // no return values
}
#endif // DFR0971_BOARD_COUNT > 0

void configureRusefiLuaHooksExt(lua_State* lState) {
#if !defined(STM32F4) && EFI_CAN_SUPPORT
    // existing CAN Lua registrations would go here
#endif // !defined(STM32F4) && EFI_CAN_SUPPORT

#if defined(DFR0971_BOARD_COUNT) && DFR0971_BOARD_COUNT > 0
    // Register DFR0971 Lua API
    lua_register(lState, "dfr0971SetPercent", luaDfr0971SetPercent);
#endif
}