#include "rle_bench.hpp"
#include "generator.hpp"
#include "rle_helper.hpp"

__attribute__((noinline)) static benchmark::BenchmarkReporter::Run
bench_1(uint16_t* val_16, uint16_t* len_16, uint16_t* out_16, size_t benchmark_number) {
#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "rle_scalar";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		manual::rle::scalar_rle_decompress(val_16, len_16, out_16);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}

__attribute__((noinline)) static benchmark::BenchmarkReporter::Run
bench_2(uint16_t* val_16, uint16_t* len_16, uint16_t* out_16, size_t benchmark_number) {
#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "rle_simd";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		manual::rle::simd_rle_avx512_16(val_16, len_16, out_16);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}

__attribute__((noinline)) void benchmark_all(benchmark::Benchmark& benchmark) {
	auto* in08 = new (std::align_val_t {64}) uint8_t[1024];
	auto* in16 = new (std::align_val_t {64}) uint16_t[1024];
	auto* in32 = new (std::align_val_t {64}) uint32_t[1024];
	auto* in64 = new (std::align_val_t {64}) uint64_t[1024];

	auto* out08 = new (std::align_val_t {64}) uint8_t[1024];
	auto* out16 = new (std::align_val_t {64}) uint16_t[1024];
	auto* out32 = new (std::align_val_t {64}) uint32_t[1024];
	auto* out64 = new (std::align_val_t {64}) uint64_t[1024];

	auto* val_32 = new uint32_t[1024];
	auto* len_32 = new uint32_t[1024];
	auto* out_32 = new uint32_t[1024];

	auto* val_16 = new uint16_t[1024];
	auto* len_16 = new uint16_t[1024];
	auto* out_16 = new uint16_t[1024];


	for (size_t n {1}; n < 250; ++n) {
		generator::generate_rle_data(n, val_16, len_16);

		benchmark.Run(bench_1(val_16, len_16, out_16, n));
		benchmark.Run(bench_2(val_16, len_16, out_16, n));
	}
}

int main() {
	benchmark::Benchmark benchmark =
	    benchmark::create("x86_64_avx512bw_rle")
	        .save()
	        .at(std::string(SOURCE_DIR) + "/fls_pub/results/" + benchmark::CmakeInfo::getCmakeToolchainFile())
	        .print()
	        .add_extra_info(benchmark::CmakeInfo::getCmakeInfo());
	benchmark_all(benchmark);
}
