// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// src/include/fls/utl/cpu/arch.hpp
// ────────────────────────────────────────────────────────
#ifndef FLS_UTL_CPU_ARCH_HPP
#define FLS_UTL_CPU_ARCH_HPP

#include <cstdint>
#include <string>

namespace fastlanes {
enum class Arch : uint8_t {
	FALLBACK = 0, //
	X86      = 1, //
	X86_64   = 2, //
	ARM      = 4  //
};

std::string ArchitectureToString(Arch arch);
} // namespace fastlanes
#endif // FLS_UTL_CPU_ARCH_HPP
