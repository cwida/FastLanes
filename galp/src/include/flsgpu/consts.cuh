// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/src/include/flsgpu/consts.cuh
// ────────────────────────────────────────────────────────
#ifndef CONSTS_H
#define CONSTS_H

#include <cstdint>

namespace consts {

constexpr int32_t  REGISTER_WIDTH    = 1024;
constexpr int32_t  VALUES_PER_VECTOR = 1024;
constexpr int32_t  THREADS_PER_WARP  = 32;
constexpr unsigned MAX_UNPACK_N_VECS = 4;

template <class T>
struct as {
	static inline constexpr T MAGIC_NUMBER = 1;
};

template <>
struct as<float> {
	static inline constexpr float   MAGIC_NUMBER   = 0.3214f;
	static inline constexpr int32_t FACT_ARR_COUNT = 10;
	static inline constexpr int32_t FRAC_ARR_COUNT = 11;
};

template <>
struct as<double> {
	static inline constexpr double  MAGIC_NUMBER   = 0.3214;
	static inline constexpr int32_t FACT_ARR_COUNT = 19;
	static inline constexpr int32_t FRAC_ARR_COUNT = 21;
};
} // namespace consts

#endif // CONSTS_H
