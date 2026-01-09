/*
 * @file obd_core.cpp
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


 

#include "pch.h"
#include "obd_core.h"

#include "obd2.h"               // PID definitions, mode constants
#include "sensor.h"             // Sensor::getOrZero()
#include "engine_math.h"        // efiRound(), etc (if needed)

static const int16_t supportedPids0120[] = {
	PID_MONITOR_STATUS,
	PID_FUEL_SYSTEM_STATUS,
	PID_ENGINE_LOAD,
	PID_COOLANT_TEMP,
	PID_STFT_BANK1,
	PID_STFT_BANK2,
	PID_INTAKE_MAP,
	PID_RPM,
	PID_SPEED,
	PID_TIMING_ADVANCE,
	PID_INTAKE_TEMP,
	PID_THROTTLE,
	-1
};

static const int16_t supportedPids2140[] = {
	PID_FUEL_AIR_RATIO_1,
	-1
};

static const int16_t supportedPids4160[] = {
	PID_CONTROL_UNIT_VOLTAGE,
	PID_ETHANOL,
	PID_FUEL_RATE,
	PID_OIL_TEMPERATURE,
	-1
};

#define _1_MODE 1

// Forward declarations of mode handlers
static ObdStatus obdHandleMode01(uint8_t pid, ObdResponse& out);

// ------------------------------------------------------------
// Core OBD dispatcher
// ------------------------------------------------------------

ObdStatus obdHandleRequest(uint8_t mode, uint8_t pid, ObdResponse& out) {
    switch (mode) {
        case _1_MODE:
            return obdHandleMode01(pid, out);

        default:
            return ObdStatus::UnsupportedMode;
    }
}

// ------------------------------------------------------------
// Mode 01 – Current data
// ------------------------------------------------------------


//void handleGetDataRequest(const CANRxFrame& rx, size_t busIndex) {
//	int pid = rx.data8[2];
static ObdStatus obdHandleMode01(uint8_t pid, ObdResponse& out) {

	switch (pid) {
	case PID_SUPPORTED_PIDS_REQUEST_01_20:
		obdWriteSupportedPids(pid, 1, supportedPids0120, busIndex);
		return ObdStatus::Ok;
	case PID_SUPPORTED_PIDS_REQUEST_21_40:
		obdWriteSupportedPids(pid, 0x21, supportedPids2140, busIndex);
		return ObdStatus::Ok;
	case PID_SUPPORTED_PIDS_REQUEST_41_60:
		obdWriteSupportedPids(pid, 0x41, supportedPids4160, busIndex);
		return ObdStatus::Ok;
	case PID_MONITOR_STATUS:
		out.numBytes = 4;
        out.value = 
		// obdSendPacket(1, pid, 4, 0, busIndex);	// todo: add statuses
		return ObdStatus::Ok;
	case PID_FUEL_SYSTEM_STATUS:
		// todo: add statuses
		out.numBytes = 2;
        out.value = (2<<8)|(0); // 2 = "Closed loop, using oxygen sensor feedback to determine fuel mix" 
		// obdSendValue(_1_MODE, pid, 2, (2<<8)|(0), busIndex);	// 2 = "Closed loop, using oxygen sensor feedback to determine fuel mix"
		return ObdStatus::Ok;
	case PID_ENGINE_LOAD:
		out.numBytes = 1;
        out.value = getFuelingLoad() * ODB_TPS_BYTE_PERCENT;
		// obdSendValue(_1_MODE, pid, 1, getFuelingLoad() * ODB_TPS_BYTE_PERCENT, busIndex);
		return ObdStatus::Ok;
	case PID_COOLANT_TEMP:
		out.numBytes = 1;
        out.value = Sensor::getOrZero(SensorType::Clt) + ODB_TEMP_EXTRA
		// obdSendValue(_1_MODE, pid, 1, Sensor::getOrZero(SensorType::Clt) + ODB_TEMP_EXTRA, busIndex);
		return ObdStatus::Ok;
	case PID_STFT_BANK1:
		out.numBytes = 1;
        out.value = 128 * engine->engineState.stftCorrection[0];
		// obdSendValue(_1_MODE, pid, 1, 128 * engine->engineState.stftCorrection[0], busIndex);
		return ObdStatus::Ok;
	case PID_STFT_BANK2:
		out.numBytes = 1;
        out.value = 128 * engine->engineState.stftCorrection[1];
		// obdSendValue(_1_MODE, pid, 1, 128 * engine->engineState.stftCorrection[1], busIndex);
		return ObdStatus::Ok;
	case PID_INTAKE_MAP:
		out.numBytes = 1;
        out.value = Sensor::getOrZero(SensorType::Map);
		// obdSendValue(_1_MODE, pid, 1, Sensor::getOrZero(SensorType::Map), busIndex);
		return ObdStatus::Ok;
	case PID_RPM:   // 0C – Engine RPM
		out.numBytes = 2;
        out.value = Sensor::getOrZero(SensorType::Rpm) * ODB_RPM_MULT;
		// obdSendValue(_1_MODE, pid, 2, Sensor::getOrZero(SensorType::Rpm) * ODB_RPM_MULT, busIndex);	//	rotation/min. (A*256+B)/4
		return ObdStatus::Ok;
	case PID_SPEED:
		out.numBytes = 1;
        out.value = Sensor::getOrZero(SensorType::VehicleSpeed);
		// obdSendValue(_1_MODE, pid, 1, Sensor::getOrZero(SensorType::VehicleSpeed), busIndex);
		return ObdStatus::Ok;
	case PID_TIMING_ADVANCE: {
		float timing = engine->engineState.timingAdvance[0];
		timing = (timing > 360.0f) ? (timing - 720.0f) : timing;
		out.numBytes = 1;
        out.value = (timing + 64.0f) * 2.0f; // angle before TDC.	(A/2)-64
		// obdSendValue(_1_MODE, pid, 1, (timing + 64.0f) * 2.0f, busIndex);		// angle before TDC.	(A/2)-64
		return ObdStatus::Ok;
		}
	case PID_INTAKE_TEMP:
		out.numBytes = 1;
	    out.value = Sensor::getOrZero(SensorType::Iat) + ODB_TEMP_EXTRA;
		// obdSendValue(_1_MODE, pid, 1, Sensor::getOrZero(SensorType::Iat) + ODB_TEMP_EXTRA, busIndex);
		return ObdStatus::Ok;
	case PID_INTAKE_MAF:
		out.numBytes = 2;
        out.value = Sensor::getOrZero(SensorType::Maf) * 100.0f; // grams/sec
		// obdSendValue(_1_MODE, pid, 2, Sensor::getOrZero(SensorType::Maf) * 100.0f, busIndex);	// grams/sec	(A*256+B)/100
		return ObdStatus::Ok;
	case PID_THROTTLE:
		out.numBytes = 1;
        out.value = Sensor::getOrZero(SensorType::Tps1) * ODB_TPS_BYTE_PERCENT;	// (A*100/255)
		// obdSendValue(_1_MODE, pid, 1, Sensor::getOrZero(SensorType::Tps1) * ODB_TPS_BYTE_PERCENT, busIndex);	// (A*100/255)
		return ObdStatus::Ok;
	case PID_FUEL_AIR_RATIO_1: {
		float lambda = clampF(0, Sensor::getOrZero(SensorType::Lambda1), 1.99f);

		uint16_t scaled = lambda * 32768;

		out.numBytes = 4;
        out.value = scaled << 16;
		// obdSendPacket(1, pid, 4, scaled << 16, busIndex);
		return ObdStatus::Ok;
	} case PID_FUEL_RATE: {

#ifdef MODULE_ODOMETER
		float gPerSecond = engine->module<TripOdometer>()->getConsumptionGramPerSecond();
#else
		float gPerSecond = 0;
#endif // MODULE_ODOMETER

		float gPerHour = gPerSecond * 3600;
		float literPerHour = gPerHour * 0.00139f;
		out.numBytes = 2;
        out.value = literPerHour * 20.0f; //	L/h.	(A*256+B)/20
		// obdSendValue(_1_MODE, pid, 2, literPerHour * 20.0f, busIndex);	//	L/h.	(A*256+B)/20
		return ObdStatus::Ok;
	} case PID_CONTROL_UNIT_VOLTAGE:
		out.numBytes = 2;
        out.value = 1000 * Sensor::getOrZero(SensorType::BatteryVoltage);
		// obdSendValue(_1_MODE, pid, 2, 1000 * Sensor::getOrZero(SensorType::BatteryVoltage), busIndex);
		return ObdStatus::Ok;
	case PID_ETHANOL:
		out.numBytes = 1;
        out.value = (255.0f / 100) * Sensor::getOrZero(SensorType::FuelEthanolPercent);
		// obdSendValue(_1_MODE, pid, 1, (255.0f / 100) * Sensor::getOrZero(SensorType::FuelEthanolPercent), busIndex);
		return ObdStatus::Ok;
	case PID_OIL_TEMPERATURE: 
		out.numBytes = 1;
        out.value = Sensor::getOrZero(SensorType::OilTemperature) + ODB_TEMP_EXTRA;
		// obdSendValue(_1_MODE, pid, 1, Sensor::getOrZero(SensorType::OilTemperature) + ODB_TEMP_EXTRA, busIndex);
		return ObdStatus::Ok;
	default:
		return ObdStatus::UnsupportedPid; // ignore unhandled PIDs
	}
}
