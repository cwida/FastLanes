#include "rsum_bench.hpp"
#include "rsum_helper.hpp"
#include <iostream>

static benchmark::BenchmarkReporter::Run bench_0(uint8_t* out, uint8_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "scalar_delta_08";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		manual::delta::scalar_delta<uint8_t>(in, out, helper::bases_08);
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

	std::string benchmark_name = "scalar_delta_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		manual::delta::scalar_delta<uint16_t>(in16, out16, helper::bases_16);
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

	std::string benchmark_name = "scalar_delta_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		manual::delta::scalar_delta<uint32_t>(in32, out32, helper::bases_32);
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

	std::string benchmark_name = "scalar_delta_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		manual::delta::scalar_delta<uint64_t>(in64, out64, helper::bases_64);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}

static benchmark::BenchmarkReporter::Run bench_4(uint8_t* out8, uint8_t* in8) {
	int benchmark_number = 4;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "d1_128_8";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		manual::delta::lemire_d1_8(in8, out8, helper::bases_08);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}

static benchmark::BenchmarkReporter::Run bench_5(uint16_t* out16, uint16_t* in16) {
	int benchmark_number = 5;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "d1_128_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		manual::delta::lemire_d1_16(in16, out16, helper::bases_16);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}

static benchmark::BenchmarkReporter::Run bench_6(uint32_t* out32, uint32_t* in32) {
	int benchmark_number = 6;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "d1_128_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		manual::delta::lemire_d1_32(in32, out32, helper::bases_32);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}


static benchmark::BenchmarkReporter::Run bench_7(uint64_t* out64, uint64_t* in64) {
	int benchmark_number = 7;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "d1_128_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		manual::delta::lemire_d1_64(in64, out64, helper::bases_64);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}


static benchmark::BenchmarkReporter::Run bench_10(uint32_t* out32, uint32_t* in32) {
	int benchmark_number = 8;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "d1_512_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		manual::delta::avx512_d1_32(in32, out32, helper::bases_32);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}

static benchmark::BenchmarkReporter::Run bench_11(uint64_t* out64, uint64_t* in64) {
	int benchmark_number = 9;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "d1_512_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		manual::delta::avx512_d1_64(in64, out64, helper::bases_64);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}

static benchmark::BenchmarkReporter::Run bench_12(uint8_t* out, uint8_t* in) {
	int benchmark_number = 10;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "four_cursor_delta_08";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		manual::delta::four_cursor_delta<uint8_t>(in, out, helper::bases_08);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}

static benchmark::BenchmarkReporter::Run bench_13(uint16_t* out16, uint16_t* in16) {
	int benchmark_number = 11;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "four_cursor_delta_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		manual::delta::four_cursor_delta<uint16_t>(in16, out16, helper::bases_16);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}

static benchmark::BenchmarkReporter::Run bench_14(uint32_t* out32, uint32_t* in32) {
	int benchmark_number = 12;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "four_cursor_delta_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		manual::delta::four_cursor_delta<uint32_t>(in32, out32, helper::bases_32);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}

static benchmark::BenchmarkReporter::Run bench_15(uint64_t* out64, uint64_t* in64) {
	int benchmark_number = 13;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "four_cursor_delta_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		manual::delta::four_cursor_delta<uint64_t>(in64, out64, helper::bases_64);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}

static benchmark::BenchmarkReporter::Run bench_16(uint32_t* out32, uint32_t* in32) {
	int benchmark_number = 14;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "d1_256_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		manual::delta::my_avx2_d1(in32, out32, helper::bases_32);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 1024));
}

static benchmark::BenchmarkReporter::Run bench_17(uint32_t* out32, uint32_t* in32) {
	int benchmark_number = 15;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "my_d1_256_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		manual::delta::my_avx2_d1(in32, out32, helper::bases_32);
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
	benchmark.Run(bench_4(out08, in08));
	benchmark.Run(bench_5(out16, in16));
	benchmark.Run(bench_6(out32, in32));
	benchmark.Run(bench_7(out64, in64));
	benchmark.Run(bench_10(out32, in32));
	benchmark.Run(bench_11(out64, in64));
	benchmark.Run(bench_12(out08, in08));
	benchmark.Run(bench_13(out16, in16));
	benchmark.Run(bench_14(out32, in32));
	benchmark.Run(bench_15(out64, in64));
	benchmark.Run(bench_16(out32, in32));
	benchmark.Run(bench_17(out32, in32));

}

int main() {
	benchmark::Benchmark benchmark =
	    benchmark::create("x86_64_avx512bw_scalar_delta")
	        .save()
	        .at(std::string(SOURCE_DIR) + "/fls_pub/results/" + benchmark::CmakeInfo::getCmakeToolchainFile())
	        .print()
	        .add_extra_info(benchmark::CmakeInfo::getCmakeInfo());
	benchmark_all(benchmark);
}
