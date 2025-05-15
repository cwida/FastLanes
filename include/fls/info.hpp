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

	// ──────────────────────────────────────────────────────────────
	// VERSION TAG  (little-endian encoding of "0.1.3.P2")
	//
	// ASCII          :  0   .   1   .   3   .   P   2
	// byte values    : 0x30 0x2E 0x31 0x2E 0x33 0x2E 0x50 0x32
	// little-endian  : 0x32 0x50 0x2E 0x33 0x2E 0x31 0x2E 0x30
	//                  = 0x32502E332E312E30
	//
	static constexpr uint64_t FASTLANES_VERSION_0_1_3_POST2 = 0x32502E332E312E30ULL;

	static constexpr uint64_t get_version_bytes() {
		return FASTLANES_VERSION_0_1_3_POST2;
	}

private:
	static constexpr auto lib_name        = string_view("FastLanes");
	static constexpr auto current_version = string_view("0.1.3.post2"); // smart entry point
};

} // namespace fastlanes

#endif // FASTLANES_FLS_INFO_HPP
