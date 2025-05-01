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

	/**
	 * FASTLANES_VERSION_01
	 *
	 * This 64-bit constant encodes the ASCII string "S|V0.1.0" directly into a binary value,
	 * and serves as a *magic version tag* for identifying FastLanes file format version 0.1.0.
	 *
	 * ─────────────────────────────────────────────────────────────────────────────
	 * Encoding Strategy:
	 * ------------------
	 * Each character in the string "S|V0.1.0" is stored in a byte of the 64-bit word.
	 * The characters are:
	 *     'S'  → 0x53
	 *     '|'  → 0x7C
	 *     'V'  → 0x56
	 *     '0'  → 0x30
	 *     '.'  → 0x2E
	 *     '1'  → 0x31
	 *     '.'  → 0x2E
	 *     '0'  → 0x30
	 *
	 * The resulting 64-bit value (big-endian byte order) is:
	 *     0x53 7C 56 30 2E 31 2E 30
	 *     => 0x537C56302E312E30
	 *
	 * ─────────────────────────────────────────────────────────────────────────────
	 */
	static constexpr uint64_t FASTLANES_VERSION_01 = 0x537C56302E312E30;

	/**
	 * Returns the 64-bit encoded version tag for FastLanes files.
	 *
	 * This value corresponds to the ASCII string "S|V0.1.0", encoded into a
	 * single 64-bit word for compact storage and fast format validation.
	 *
	 * Use this method to retrieve the version identifier when writing headers,
	 * validating file input, or debugging format compatibility issues.
	 *
	 * Equivalent string representation (ASCII): "S|V0.1.0"
	 * Raw 64-bit value (hex): 0x537C56302E312E30
	 *
	 * @return The encoded 64-bit version tag.
	 */
	static constexpr uint64_t get_version_bytes() {
		return FASTLANES_VERSION_01;
	}

private:
	static constexpr auto lib_name      = string_view("FastLanes");
	static constexpr auto version_0_0_2 = string_view("0.0.2"); // smart entry point
	static constexpr auto version_0_0_1 = string_view("0.0.1"); // starting version
	static constexpr auto version_0_1   = string_view("0.1");   // starting version
};

} // namespace fastlanes

#endif
