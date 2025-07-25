// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/utl/cpu/ftr.cpp
// ────────────────────────────────────────────────────────
#include "fls/utl/cpu/feature.hpp" // for CPUFeature, CPUFeature::FALLBACK
#include <string>                  // for basic_string

namespace fastlanes {
std::string CPUFeatureToString(CPUFeature feature) {
	switch (feature) {
	case CPUFeature::FALLBACK:
		return "FALLBACK";
	case CPUFeature::X86_AVX2:
		return "X86_AVX2";
	case CPUFeature::X86_AVX512F:
		return "X86_AVX512F";
	default:
		return "UNDEFINED";
	}
}
} // namespace fastlanes
