#ifndef FASTLANES_FLS_INFO_HPP
#define FASTLANES_FLS_INFO_HPP

#include <cstdint>
#include <string_view>

namespace fastlanes {

using std::string_view;

class Info {
public:
	static constexpr string_view get_version() {
		return current_version;
	}
	static constexpr string_view get_name() {
		return lib_name;
	}

	// ──────────────────────────────────────────────────────────────
	// MAGIC BYTES  (little-endian encoding of "FastLane")
	//
	// ASCII          :  F   a   s   t   L   a   n   e
	// byte values    : 46  61  73  74  4C  61  6E  65
	// little-endian  : least-significant byte first ⇒ integer
	//                  0x65 6E 61 4C 74 73 61 46
	//                  = 0x656E614C74736146
	//
	static constexpr uint64_t FASTLANES_MAGIC_BYTES = 0x656E614C74736146ULL;

	static constexpr uint64_t get_magic_bytes() {
		return FASTLANES_MAGIC_BYTES;
	}

	// ──────────────────────────────────────────────────────────────
	// VERSION TAG  (little-endian encoding of "S|V0.1.0")
	//
	// ASCII          :  S   |   V   0   .   1   .   0
	// byte values    : 53  7C  56  30  2E  31  2E  30
	// little-endian  : 0x30 2E 31 2E 30 56 7C 53
	//                  = 0x302E312E30567C53
	//
	static constexpr uint64_t FASTLANES_VERSION_01 = 0x302E312E30567C53ULL;

	static constexpr uint64_t get_version_bytes() {
		return FASTLANES_VERSION_01;
	}

private:
	static constexpr auto lib_name        = string_view("FastLanes");
	static constexpr auto version_0_0_2   = string_view("0.0.2");       // smart entry point
	static constexpr auto version_0_0_1   = string_view("0.0.1");       // starting version
	static constexpr auto version_0_1     = string_view("0.1");         // starting version
	static constexpr auto current_version = string_view("0.1.3.post1"); // smart entry point
};

} // namespace fastlanes

#endif // FASTLANES_FLS_INFO_HPP
