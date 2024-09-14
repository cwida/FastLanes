#include "fls/utl/cpu/info.hpp"
#include "fls/utl/cpu/feature.hpp" // for CPUFeature, CPUFeature::FALLBACK
#include <iosfwd>                  // for string
#include <stdint.h>                // for uint32_t
#include <vector>                  // for vector

// clang-format off

namespace fast_lanes {
#if defined(X86_64)
#if defined(_MSC_VER)
static void cpu_getid(int func, int* data) { __cpuid(data, func); }
#else
static void CpuGetid(int func, int* data) {
	__asm__("cpuid" : "=a"(data[0]), "=b"(data[1]), "=c"(data[2]), "=d"(data[3]) : "0"(func), "2"(0));
}
#endif
#elif defined(ARM)
#if (defined(__GNUC__) && ((__GNUC__ > 2) || (__GNUC__ == 2 && __GNUC_MINOR__ >= 16)))
#endif
#endif

#if defined(X86_64)
static unsigned int duckdb_cpuinfo[8 * 4] = {
    0,
};
#elif defined(ARM)
static unsigned long cpuinfo[2] = {
    0,
};
#endif

static void CpuInit() {
#if defined(X86_64)
	int i;
	for (i = 0; i < 8; i++) {
		CpuGetid(i, (int*)&(duckdb_cpuinfo[i * 4]));
	}
#elif defined(ARM)
#endif
}

static int CpuFeatureCheck(enum CPUFeature feature) {
#if defined(X86_64)
	unsigned int i, r, b;
#elif defined(ARM)
	unsigned long b, i;
#endif

#if defined(X86_64)
	if ((feature & CPU_FEATURE_CPU_MASK) != CPU_FEATURE_X86) { return 0; }
#elif defined(ARM)
#else
	return 0;
#endif

	feature = static_cast<CPUFeature>(~static_cast<uint32_t>(CPUFeature::CPU_MASK) & static_cast<uint32_t>(feature));
#if defined(_MSC_VER)
#pragma warning(push)
#pragma warning(disable : 4152)
#endif
#if defined(_MSC_VER)
#pragma warning(pop)
#endif

#if defined(X86_64)
	i = (feature >> 16) & 0xff;
	r = (feature >> 8) & 0xff;
	b = (feature) & 0xff;

	if (i > 7 || r > 3 || b > 31) { return 0; }

	return (duckdb_cpuinfo[(i * 4) + r] >> b) & 1;
#elif defined(ARM)
	b = 1 << ((feature & 0xff) - 1);
	i = cpuinfo[(feature >> 0x08) & 0xff];
	return (cpuinfo[(feature >> 0x08) & 0xff] & b) == b;
#endif
}

CpuInfo::CpuInfo() { Initialize(); }

const std::vector<CPUFeature>& CpuInfo::GetAvailFeatures() const { return avail_features; }
void                           CpuInfo::Initialize() {
    // to make sure CpuFeatureCheck used at least once
    CpuFeatureCheck(CPUFeature::FALLBACK);
    best_feature = CPUFeature::FALLBACK;
    avail_features.push_back(CPUFeature::FALLBACK);

    CpuInit();

#ifdef X86_64
	// Simple rule, the wider better.
	if (CpuFeatureCheck(CPU_FEATURE_X86_AVX2)) {
		best_feature = CPU_FEATURE_X86_AVX2;
		avail_features.push_back(CPU_FEATURE_X86_AVX2);
	}
	if (CpuFeatureCheck(CPU_FEATURE_X86_AVX512F)) {
		best_feature = CPU_FEATURE_X86_AVX512F;
		avail_features.push_back(CPU_FEATURE_X86_AVX512F);
	}
#elif defined(ARM)
#endif
}
CPUFeature CpuInfo::GetBestFeature() const { return best_feature; }

bool CpuInfo::HasFeature(CPUFeature feature) {
	if (feature == CPUFeature::FALLBACK) { return true; }
	return CpuFeatureCheck(feature);
}

bool CpuInfo::HasFeature(const std::string& feature) {
	//	auto feature_s = table.find(feature);
	//	if (feature_s != table.end()) {
	//		return HasFeature(feature_s->second);
	//	} else {
	//		//		throw ParserException("undefined");
	//		throw std::exception();
	//	}
	return false;
}
void CpuInfo::SetBestFeature(CPUFeature a_best_feature) { this->best_feature = a_best_feature; }
void CpuInfo::SetFeature(CPUFeature feature) {
	SetBestFeature(feature);
	switch (feature) {
#if defined(X86_64)
	case CPUFeature::CPU_FEATURE_X86_AVX2:
		break;
	case CPUFeature::CPU_FEATURE_X86_AVX512F:
		break;
#endif
	default:
		break;
	}
}
} // namespace fast_lanes