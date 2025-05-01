#ifndef FASTLANES_FLS_INFO_HPP
#define FASTLANES_FLS_INFO_HPP

namespace fastlanes {

class Info {
public:
	static constexpr string_view get_version() {
		return version_0_0_2;
	}
	static constexpr string_view get_name() {
		return lib_name;
	}

	static constexpr array<uint8_t, 8> FASTLANES_VERSION_01 = {'S', '|', 'V', '0', '.', '1', '.', '0'};

	/**
	 * MAGIC BYTES FOR FASTLANES FILE FORMAT
	 *
	 * This 64-bit constant encodes the ASCII string "FastLane" directly into an uint64_t value.
	 * It serves as a "magic number" that identifies the file format.
	 *
	 * ASCII bytes of "FastLane":
	 *   'F' -> 0x46
	 *   'a' -> 0x61
	 *   's' -> 0x73
	 *   't' -> 0x74
	 *   'L' -> 0x4C
	 *   'a' -> 0x61
	 *   'n' -> 0x6E
	 *   'e' -> 0x65
	 *
	 * Combined into a 64-bit big-endian value:
	 *   0x46 61 73 74 4C 61 6E 65
	 *   = 0x466173744C616E65
	 *
	 * Big-endian encoding is used here to make the string readable in memory dumps on most systems.
	 *
	 */
	static constexpr uint64_t FASTLANES_MAGIC_BYTES = 0x466173744C616E65;

	/**
	 * Returns the 64-bit magic number for FastLanes file headers.
	 */
	static constexpr uint64_t get_magic_bytes() {
		return FASTLANES_MAGIC_BYTES;
	}

private:
	static constexpr auto lib_name      = string_view("FastLanes");
	static constexpr auto version_0_0_2 = string_view("0.0.2"); // smart entry point
	static constexpr auto version_0_0_1 = string_view("0.0.1"); // starting version
	static constexpr auto version_0_1   = string_view("0.1");   // starting version
};

} // namespace fastlanes

#endif
