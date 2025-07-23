// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/src/include/flsgpu/device-types.cuh
// ────────────────────────────────────────────────────────
#ifndef GPU_DEVICE_TYPES_CUH
#define GPU_DEVICE_TYPES_CUH

#include <cstdint>

using vbw_t  = uint8_t;
using lane_t = uint16_t;
using si_t   = uint32_t; // si = start index (of value within vector)
using vi_t   = uint32_t; // vi = Vector Index

#endif // GPU_DEVICE_TYPES_CUH
