#include "add_helper.hpp"
#include "add_bench.hpp"
#include <iostream>

static benchmark::BenchmarkReporter::Run bench_0(uint8_t* out, uint8_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "scalar_add_08";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		manual::add::add<uint8_t>(in, out, helper::bases_08);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}

static benchmark::BenchmarkReporter::Run bench_1(uint16_t* out16, uint16_t* in16) {
	int benchmark_number = 1;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "scalar_add_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		manual::add::add<uint16_t>(in16, out16, helper::bases_16);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}

static benchmark::BenchmarkReporter::Run bench_2(uint32_t* out32, uint32_t* in32) {
	int benchmark_number = 2;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "scalar_add_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		manual::add::add<uint32_t>(in32, out32, helper::bases_32);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}

static benchmark::BenchmarkReporter::Run bench_3(uint64_t* out64, uint64_t* in64) {
	int benchmark_number = 3;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "scalar_add_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		manual::add::add<uint64_t>(in64, out64, helper::bases_64);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}

void benchmark_all(benchmark::Benchmark& benchmark) {
	auto* in08 = new (std::align_val_t {64}) uint8_t[1024];
	auto* in16 = new (std::align_val_t {64}) uint16_t[1024];
	auto* in32 = new (std::align_val_t {64}) uint32_t[1024];
	auto* in64 = new (std::align_val_t {64}) uint64_t[1024];

	auto* out08 = new (std::align_val_t {64}) uint8_t[1024];
	auto* out16 = new (std::align_val_t {64}) uint16_t[1024];
	auto* out32 = new (std::align_val_t {64}) uint32_t[1024];
	auto* out64 = new (std::align_val_t {64}) uint64_t[1024];
	benchmark.Run(bench_0(out08, in08));
	benchmark.Run(bench_1(out16, in16));
	benchmark.Run(bench_2(out32, in32));
	benchmark.Run(bench_3(out64, in64));
}

int main() {
	benchmark::Benchmark benchmark =
	    benchmark::create("x86_64_avx512bw_simd_add")
	        .save()
	        .at(std::string(SOURCE_DIR) + "/fls_pub/results/" + benchmark::CmakeInfo::getCmakeToolchainFile())
	        .print()
	        .add_extra_info(benchmark::CmakeInfo::getCmakeInfo());
	benchmark_all(benchmark);
}
