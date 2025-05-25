#include "fls/utl/cpu/feature.hpp" // for CPUFeature, CPUFeature::FALLBACK
#include <iosfwd>                  // for string
#include <string>                  // for basic_string

namespace fast_lanes {
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
} // namespace fast_lanes