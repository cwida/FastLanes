#include "fls/utl/cpu/arch.hpp"
#include <string>

namespace fast_lanes {
std::string ArchToString(Arch arch) {
	switch (arch) {
	case Arch::FALLBACK:
		return "FALLBACK";
	case Arch::X86:
		return "X86";
	case Arch::X86_64:
		return "X86_64";
	case Arch::ARM:
		return "ARM";
	default:
		return "UNDEFINED";
	}
}
} // namespace fast_lanes