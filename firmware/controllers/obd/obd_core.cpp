#include "obd_core.h"

#include "obd2.h"               // PID definitions, mode constants
#include "sensor.h"             // Sensor::getOrZero()
#include "engine_math.h"        // efiRound(), etc (if needed)

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

static ObdStatus obdHandleMode01(uint8_t pid, ObdResponse& out) {
    switch (pid) {

        case PID_RPM:
            // PID 0C – Engine RPM
            // Formula: (A * 256 + B) / 4
            out.numBytes = 2;
            out.value =
                Sensor::getOrZero(SensorType::Rpm) * ODB_RPM_MULT;
            return ObdStatus::Ok;

        default:
            return ObdStatus::UnsupportedPid;
    }
}