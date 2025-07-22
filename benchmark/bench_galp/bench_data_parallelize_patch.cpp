// ─────────────────────────────────────────────────────────────────────────────
//  patch_bench.cpp   –   unified benchmark driver
// ─────────────────────────────────────────────────────────────────────────────
#include "cycle_counter.hpp"
#include "fastlanes.hpp"
#include "fls/cuda/common.hpp"
#include <cstdint>
#include <limits>
#include <new>
#include <random>
#include <string>
#include <type_traits>

// ---------------------------------------------------------------------------
//  Random helpers
// ---------------------------------------------------------------------------
namespace fastlanes::helper {

inline std::mt19937_64& rng() {
	static std::mt19937_64 eng {std::random_device {}()};
	return eng;
}

template <typename PT>
std::enable_if_t<std::is_integral_v<PT>> fill_random_exceptions(PT* dst, std::size_t n) {
	std::uniform_int_distribution<PT> dist(std::numeric_limits<PT>::min(), std::numeric_limits<PT>::max());
	for (std::size_t i = 0; i < n; ++i)
		dst[i] = dist(rng());
}

template <typename PT>
std::enable_if_t<std::is_floating_point_v<PT>> fill_random_exceptions(PT* dst, std::size_t n) {
	std::uniform_real_distribution<PT> dist(PT(-1), PT(1));
	for (std::size_t i = 0; i < n; ++i)
		dst[i] = dist(rng());
}

inline void fill_random_positions(uint16_t* dst, std::size_t n) {
	std::uniform_int_distribution<uint16_t> dist(0, 1023);
	for (std::size_t i = 0; i < n; ++i)
		dst[i] = dist(rng());
}

} // namespace fastlanes::helper

// ---------------------------------------------------------------------------
//  Kernels
// ---------------------------------------------------------------------------
namespace fastlanes {
template <typename PT>
static inline void new_data_parallelizer(const PT*       in_exc_arr,
                                         const uint16_t* in_pos_arr,
                                         n_t             n_exceptions,
                                         PT*             out_exc_arr,
                                         uint16_t*       out_offset,
                                         uint16_t*       out_pos_arr,
                                         uint8_t*        out_count) {
	constexpr n_t N_LANES = cuda::get_n_lanes<PT>();
	constexpr n_t MASK    = N_LANES - 1;
	static_assert((N_LANES & MASK) == 0, "N_LANES must be power-of-two");

	for (n_t l = 0; l < N_LANES; ++l)
		out_count[l] = 0;
	for (n_t i = 0; i < n_exceptions; ++i)
		++out_count[in_pos_arr[i] & MASK];

	uint16_t running = 0;
	for (n_t l = 0; l < N_LANES; ++l) {
		out_offset[l] = running;
		running += out_count[l];
	}

	for (n_t i = 0; i < n_exceptions; ++i) {
		const n_t      lane = in_pos_arr[i] & MASK;
		const uint16_t dst  = out_offset[lane]++;
		out_exc_arr[dst]    = in_exc_arr[i];
		out_pos_arr[dst]    = in_pos_arr[i];
	}
}

template <typename PT>
static inline void old_data_parallelizer(const PT*       in_exc_arr,
                                         const uint16_t* in_pos_arr,
                                         n_t             n_exceptions,
                                         PT*             out_exc_arr,
                                         uint16_t*       out_offset,
                                         uint16_t*       out_pos_arr,
                                         uint8_t*        out_count) {
	constexpr n_t N_LANES         = cuda::get_n_lanes<PT>();
	constexpr n_t VALUES_PER_LANE = cuda::get_values_per_lane<PT>();

	PT       vec_exc[CFG::VEC_SZ];
	PT       vec_pos_proxy[CFG::VEC_SZ];
	uint16_t n_local_exp[N_LANES] {};

	for (n_t exc_idx = 0; exc_idx < n_exceptions; ++exc_idx) {
		PT       exc                                  = in_exc_arr[exc_idx];
		uint16_t position                             = in_pos_arr[exc_idx];
		n_t      lane                                 = position % N_LANES;
		auto&    count                                = n_local_exp[lane];
		vec_exc[lane * VALUES_PER_LANE + count]       = exc;
		vec_pos_proxy[lane * VALUES_PER_LANE + count] = position;
		++count;
	}

	n_t global_idx = 0;
	for (n_t lane = 0; lane < N_LANES; ++lane) {
		out_offset[lane] = static_cast<uint16_t>(global_idx);
		for (n_t k = 0; k < n_local_exp[lane]; ++k) {
			out_exc_arr[global_idx] = vec_exc[lane * VALUES_PER_LANE + k];
			out_pos_arr[global_idx] = static_cast<uint16_t>(vec_pos_proxy[lane * VALUES_PER_LANE + k]);
			++global_idx;
		}
		out_count[lane] = static_cast<uint8_t>(n_local_exp[lane]);
	}
}

// Thin adapter for Patch kernel
template <typename PT>
static inline void try_this_data_parallelizer(const PT*       in_exc,
                                              const uint16_t* in_pos,
                                              n_t             n_exc,
                                              PT*             out_exc,
                                              uint16_t*       out_off,
                                              uint16_t*       out_pos,
                                              uint8_t*        out_cnt) {
	constexpr n_t N_LANES = cuda::get_n_lanes<PT>();
	constexpr n_t MASK    = N_LANES - 1;
	static_assert((N_LANES & MASK) == 0);

	for (n_t lane = 0; lane < N_LANES; ++lane)
		out_cnt[lane] = 0;

	for (n_t i = 0; i < n_exc; ++i)
		++out_cnt[in_pos[i] & MASK];

	uint16_t  prefix = 0;
	PT*       exc_ptr[N_LANES];
	uint16_t* pos_ptr[N_LANES];
#pragma unroll
	for (n_t lane = 0; lane < N_LANES; ++lane) {
		out_off[lane] = prefix;
		exc_ptr[lane] = out_exc + prefix;
		pos_ptr[lane] = out_pos + prefix;
		prefix += out_cnt[lane];
	}

	for (n_t i = 0; i < n_exc; ++i) {
		n_t lane         = in_pos[i] & MASK;
		*exc_ptr[lane]++ = in_exc[i];
		*pos_ptr[lane]++ = in_pos[i];
	}
}

// ---------------------------------------------------------------------------
//  Benchmark plumbing
// ---------------------------------------------------------------------------
template <typename PT, void (*Fn)(const PT*, const uint16_t*, n_t, PT*, uint16_t*, uint16_t*, uint8_t*)>
static benchmark::BenchmarkReporter::Run run_patch_parallelize(int id, std::string name, n_t N_EXC) {
	constexpr std::size_t ALIGN = 64;
#ifdef NDEBUG
	constexpr std::uint64_t ITER = 30'000'000;
#else
	constexpr std::uint64_t ITER = 1;
#endif

	auto in_exc  = static_cast<PT*>(::operator new[](N_EXC * sizeof(PT), std::align_val_t {ALIGN}));
	auto out_exc = static_cast<PT*>(::operator new[](N_EXC * sizeof(PT), std::align_val_t {ALIGN}));
	auto in_pos  = static_cast<uint16_t*>(::operator new[](N_EXC * sizeof(uint16_t), std::align_val_t {ALIGN}));
	auto out_pos = static_cast<uint16_t*>(::operator new[](N_EXC * sizeof(uint16_t), std::align_val_t {ALIGN}));

	constexpr n_t N_LANES = cuda::get_n_lanes<PT>();
	auto out_off = static_cast<uint16_t*>(::operator new[](N_LANES * sizeof(uint16_t), std::align_val_t {ALIGN}));
	auto out_cnt = static_cast<uint8_t*>(::operator new[](N_LANES * sizeof(uint8_t), std::align_val_t {ALIGN}));

	helper::fill_random_exceptions(in_exc, N_EXC);
	helper::fill_random_positions(in_pos, N_EXC);

	const auto start = benchmark::cycleclock::Now();
	for (std::uint64_t i = 0; i < ITER; ++i)
		Fn(in_exc, in_pos, N_EXC, out_exc, out_off, out_pos, out_cnt);
	const auto cycles = benchmark::cycleclock::Now() - start;

	::operator delete[](in_exc, std::align_val_t {ALIGN});
	::operator delete[](out_exc, std::align_val_t {ALIGN});
	::operator delete[](in_pos, std::align_val_t {ALIGN});
	::operator delete[](out_pos, std::align_val_t {ALIGN});
	::operator delete[](out_off, std::align_val_t {ALIGN});
	::operator delete[](out_cnt, std::align_val_t {ALIGN});

	return benchmark::BenchmarkReporter::Run {id, name, ITER, double(cycles) / double(ITER)};
}

// ---------------------------------------------------------------------------
//  Register & run
// ---------------------------------------------------------------------------
static void benchmark_all(benchmark::Benchmark& bench) {
	int idx = 0;
	for (n_t exc = 0; exc <= 20; ++exc) {
		// float kernels
		bench.Run(
		    run_patch_parallelize<float, new_data_parallelizer<float>>(idx++, "new_float" + std::to_string(exc), exc));
		bench.Run(
		    run_patch_parallelize<float, old_data_parallelizer<float>>(idx++, "old_float" + std::to_string(exc), exc));
		bench.Run(
		    run_patch_parallelize<float, try_this_data_parallelizer<float>>(idx++, "try" + std::to_string(exc), exc));

		// double kernels
		bench.Run(
		    run_patch_parallelize<double, new_data_parallelizer<double>>(idx++, "new_dbl" + std::to_string(exc), exc));
		bench.Run(
		    run_patch_parallelize<double, old_data_parallelizer<double>>(idx++, "old_dbl" + std::to_string(exc), exc));
		bench.Run(
		    run_patch_parallelize<double, try_this_data_parallelizer<double>>(idx++, "try" + std::to_string(exc), exc));
	}
}
} // namespace fastlanes
// ---------------------------------------------------------------------------
//  main
// ---------------------------------------------------------------------------
int main() {
	benchmark::Benchmark bench = benchmark::create("patch")
	                                 .save()
	                                 .at(std::string(FLS_CMAKE_SOURCE_DIR) + "/benchmark/result/galp")
	                                 .print()
	                                 .add_extra_info(benchmark::CmakeInfo::getCmakeInfo());

	fastlanes::benchmark_all(bench);
	return 0;
}
