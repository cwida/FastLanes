// generated!
// NOLINTBEGIN
#include "fallback_scalar_aav_1024_uf1_untranspose_bench.hpp"
#include "fallback_scalar_aav_1024_uf1_untranspose_helper.hpp"
#include "fls_gen/rsum/rsum.hpp"
#include "fls_gen/rsum_and_untranspose/rsum_and_untranspose.hpp"
#include "fls_gen/transpose/transpose.hpp"
#include "fls_gen/untranspose/untranspose.hpp"
#include <iostream>
static benchmark::BenchmarkReporter::Run bench_0(const uint8_t* transposed8, uint8_t* untransposed8) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "untranspose_i_8";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		generated::untranspose::fallback::scalar::untranspose_i(transposed8, untransposed8);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_1(const uint8_t* transposed8, uint8_t* untransposed8) {
	int benchmark_number = 1;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "untranspose_o_8";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		generated::untranspose::fallback::scalar::untranspose_o(transposed8, untransposed8);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_2(const uint16_t* transposed16, uint16_t* untransposed16) {
	int benchmark_number = 2;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "untranspose_i_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		generated::untranspose::fallback::scalar::untranspose_i(transposed16, untransposed16);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_3(const uint16_t* transposed16, uint16_t* untransposed16) {
	int benchmark_number = 3;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "untranspose_o_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		generated::untranspose::fallback::scalar::untranspose_o(transposed16, untransposed16);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_4(const uint32_t* transposed32, uint32_t* untransposed32) {
	int benchmark_number = 4;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "untranspose_i_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		generated::untranspose::fallback::scalar::untranspose_i(transposed32, untransposed32);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_5(const uint32_t* transposed32, uint32_t* untransposed32) {
	int benchmark_number = 5;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "untranspose_o_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		generated::untranspose::fallback::scalar::untranspose_o(transposed32, untransposed32);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_6(const uint64_t* transposed64, uint64_t* untransposed64) {
	int benchmark_number = 6;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "untranspose_i_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		generated::untranspose::fallback::scalar::untranspose_i(transposed64, untransposed64);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_7(const uint64_t* transposed64, uint64_t* untransposed64) {
	int benchmark_number = 7;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "untranspose_o_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		generated::untranspose::fallback::scalar::untranspose_o(transposed64, untransposed64);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}
void benchmark_all(benchmark::Benchmark& benchmark) {
	const auto* transposed8    = new (std::align_val_t {64}) uint8_t[1024];
	const auto* transposed16   = new (std::align_val_t {64}) uint16_t[1024];
	const auto* transposed32   = new (std::align_val_t {64}) uint32_t[1024];
	const auto* transposed64   = new (std::align_val_t {64}) uint64_t[1024];
	auto*       untransposed8  = new (std::align_val_t {64}) uint8_t[1024];
	auto*       untransposed16 = new (std::align_val_t {64}) uint16_t[1024];
	auto*       untransposed32 = new (std::align_val_t {64}) uint32_t[1024];
	auto*       untransposed64 = new (std::align_val_t {64}) uint64_t[1024];
	benchmark.Run(bench_0(transposed8, untransposed8));
	benchmark.Run(bench_1(transposed8, untransposed8));
	benchmark.Run(bench_2(transposed16, untransposed16));
	benchmark.Run(bench_3(transposed16, untransposed16));
	benchmark.Run(bench_4(transposed32, untransposed32));
	benchmark.Run(bench_5(transposed32, untransposed32));
	benchmark.Run(bench_6(transposed64, untransposed64));
	benchmark.Run(bench_7(transposed64, untransposed64));
}
int main() {
	benchmark::Benchmark benchmark =
	    benchmark::create("fallback_scalar_aav_1024_uf1_untranspose")
	        .save()
	        .at(std::string(SOURCE_DIR) + "/fls_pub/results/" + benchmark::CmakeInfo::getCmakeToolchainFile())
	        .print()
	        .add_extra_info(benchmark::CmakeInfo::getCmakeInfo());
	benchmark_all(benchmark);
}
