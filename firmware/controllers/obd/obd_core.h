/*
 * @file obd_core.h
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

#define OBD_TEST_REQUEST 0x7DF

#define OBD_TEST_RESPONSE 0x7E8

#define OBD_CURRENT_DATA 1
#define _OBD_2 2
#define OBD_STORED_DIAGNOSTIC_TROUBLE_CODES 3
#define OBD_PENDING_DIAGNOSTIC_TROUBLE_CODES 7

// https://en.wikipedia.org/wiki/OBD-II_PIDs

#define PID_SUPPORTED_PIDS_REQUEST_01_20 0x00
#define PID_MONITOR_STATUS 0x01
#define PID_FUEL_SYSTEM_STATUS 0x03
#define PID_ENGINE_LOAD 0x04
#define PID_COOLANT_TEMP 0x05
#define PID_STFT_BANK1 0x06
#define PID_STFT_BANK2 0x08
#define PID_FUEL_PRESSURE 0x0A
#define PID_INTAKE_MAP 0x0B
#define PID_RPM 0x0C
#define PID_SPEED 0x0D
#define PID_TIMING_ADVANCE 0x0E
#define PID_INTAKE_TEMP 0x0F
#define PID_INTAKE_MAF 0x10
#define PID_THROTTLE 0x11

#define PID_SUPPORTED_PIDS_REQUEST_21_40 0x20
#define PID_FUEL_AIR_RATIO_1 0x24

#define PID_SUPPORTED_PIDS_REQUEST_41_60 0x40
#define PID_CONTROL_UNIT_VOLTAGE 0x42
#define PID_ETHANOL 0x52
#define PID_OIL_TEMPERATURE 0x5C
#define PID_FUEL_RATE 0x5E
//todo#define PID_TURBO_RPM 0x74

#define ODB_RPM_MULT 4
#define ODB_TEMP_EXTRA 40
#define ODB_TPS_BYTE_PERCENT 2.55f


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