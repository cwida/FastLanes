#ifndef FLS_UTL_CPU_ARCH_HPP
#define FLS_UTL_CPU_ARCH_HPP

#include <cstdint>
#include <string>

namespace fast_lanes {
enum class Arch : uint8_t {
	FALLBACK = 0, //
	X86      = 1, //
	X86_64   = 2, //
	ARM      = 4  //
};

std::string ArchitectureToString(Arch arch);
} // namespace fast_lanes
#endif // FLS_UTL_CPU_ARCH_HPP
