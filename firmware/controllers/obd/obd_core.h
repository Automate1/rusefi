@file obd_core.cpp
 *
 * ISO 15765-4
 * http://en.wikipedia.org/wiki/OBD-II_PIDs
 *
 * @date Jan 7, 2026
 * @author Automate
 *
 * This file is part of rusEfi - see http://rusefi.com
 *
 * rusEfi is free software; you can redistribute it and/or modify it under the terms of
 * the GNU General Public License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * rusEfi is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program.
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <cstdint>

// Result status for OBD core lookup
enum class ObdStatus : uint8_t {
    Ok = 0,
    UnsupportedMode,
    UnsupportedPid
};

// Raw OBD response (transport-agnostic)
struct ObdResponse {
    uint8_t  numBytes;  // number of data bytes (A, A+B, etc)
    uint32_t value;     // raw integer value before transport encoding
};

// Main OBD dispatcher (transport-agnostic)
//
// mode: OBD mode (e.g. 0x01)
// pid:  PID within that mode
// out:  Filled on success
//
ObdStatus obdHandleRequest(uint8_t mode, uint8_t pid, ObdResponse& out);