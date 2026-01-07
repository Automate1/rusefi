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