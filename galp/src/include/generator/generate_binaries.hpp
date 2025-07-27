// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/src/include/generator/generate_binaries.hpp
// ────────────────────────────────────────────────────────
// =============================================================================
// generate_binaries.hpp  ―  Random-data generator + directory scanner (host-only)
//
// * **Now writes little-endian** (the de-facto standard on x86/ARM).
// * Automatically swaps bytes on big-endian hosts.
// * Produces float32 + float64 binaries and can scan data/floats + data/doubles.
// * Wrapped in host-only guards so NVCC’s device pass never sees <filesystem>.
// =============================================================================
#ifndef GENERATE_BINARIES_HPP
#define GENERATE_BINARIES_HPP

#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <random>
#include <string>
#include <vector>

// ──────────────────────────────────────────────────────────────────────────────
// Host-only implementation (skipped entirely for __CUDA_ARCH__)
// ──────────────────────────────────────────────────────────────────────────────
namespace bin {
namespace detail {

// compile-time endian test (uses compiler macros, no UB in constexpr)
inline constexpr bool is_little_endian =
#if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
    true;
#else
    false;
#endif
;

} // namespace detail

// -----------------------------------------------------------------------------
//  write_little_endian  ―  write POD value in **little-endian** order
// -----------------------------------------------------------------------------
template <typename T>
inline void write_little_endian(std::ostream& os, const T& value) {
	static_assert(std::is_trivially_copyable_v<T>, "write_little_endian requires a trivially-copyable type");
	T tmp = value;
	if constexpr (!detail::is_little_endian) { // host is big-endian
		auto* p = reinterpret_cast<uint8_t*>(&tmp);
		std::reverse(p, p + sizeof(T)); // swap to LE
	}
	os.write(reinterpret_cast<const char*>(&tmp), sizeof(T));
}

// -----------------------------------------------------------------------------
//  generate_and_write  ―  write TOTAL random numbers (0-100, two decimals)
//                         to <out32> (float32 LE) and <out64> (float64 LE)
//                         returns the first HEAD_COUNT values
// -----------------------------------------------------------------------------
inline std::vector<double>
generate_and_write(const std::string& out32, const std::string& out64, size_t total, size_t head_count) {
	std::mt19937_64                        rng(std::random_device {}());
	std::uniform_real_distribution<double> dist(0.0, 100.0);

	std::vector<double> head;
	head.reserve(head_count);

	std::ofstream f32(out32, std::ios::binary);
	std::ofstream f64(out64, std::ios::binary);

	for (size_t i = 0; i < total; ++i) {
		double val = std::round(dist(rng) * 100.0) / 100.0;
		if (head.size() < head_count)
			head.push_back(val);

		write_little_endian(f32, static_cast<float>(val));
		write_little_endian(f64, val);
	}
	return head;
}

// -----------------------------------------------------------------------------
//  generate_write_and_scan  ―  one-stop helper:
//      1) writes <floats_dir>/1.bin + <doubles_dir>/1.bin (little-endian)
//      2) scans both directories for every *.bin
//      3) returns first HEAD_COUNT values + sorted file lists
// -----------------------------------------------------------------------------
struct GenResult {
	std::vector<double>      head;         // first N random values
	std::vector<std::string> float_files;  // *.bin under floats_dir
	std::vector<std::string> double_files; // *.bin under doubles_dir
};

inline GenResult generate_write_and_scan(const std::filesystem::path& floats_dir,
                                         const std::filesystem::path& doubles_dir,
                                         size_t                       total,
                                         size_t                       head_count) {
	GenResult res;

	// (1) produce "1.bin" in each directory
	res.head = generate_and_write(
	    (floats_dir / "random.bin").string(), (doubles_dir / "random.bin").string(), total, head_count);

	// (2) collect existing *.bin files
	auto collect = [](const std::filesystem::path& dir, std::vector<std::string>& out) {
		if (!std::filesystem::exists(dir))
			return;
		for (const auto& e : std::filesystem::directory_iterator(dir))
			if (e.is_regular_file() && e.path().extension() == ".bin")
				out.emplace_back(e.path().string());
		std::sort(out.begin(), out.end());
	};
	collect(floats_dir, res.float_files);
	collect(doubles_dir, res.double_files);

	return res;
}

} // namespace bin
#endif // !__CUDA_ARCH__
