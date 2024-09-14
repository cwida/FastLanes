#include "lemire_bitunpack_bench.hpp"
#include "lemire_bitunpack_helper.hpp"
#include <iostream>

static benchmark::BenchmarkReporter::Run bench_0(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_0";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 0);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_1(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_1";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 1);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}
static benchmark::BenchmarkReporter::Run bench_2(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_2";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 2);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_3(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_3";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 3);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_4(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_4";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 4);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_5(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_5";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 5);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_6(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_6";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 6);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_7(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_7";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 7);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_8(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_8";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 8);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_9(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_9";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 9);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_10(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_10";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 10);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_11(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_11";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 11);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_12(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_12";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 12);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_13(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_13";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 13);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_14(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_14";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 14);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_15(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_15";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 15);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_16(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 16);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_17(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_17";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 17);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_18(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_18";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 18);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_19(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_19";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 19);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_20(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_20";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 20);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_21(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_21";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 21);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_22(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_22";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 22);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_23(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_23";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 23);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_24(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_24";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 24);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_25(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_25";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 25);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_26(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_26";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 26);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_27(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_27";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 27);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_28(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_28";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 28);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_29(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_29";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 29);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_30(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_30";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 30);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_31(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_31";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 31);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
}

static benchmark::BenchmarkReporter::Run bench_32(uint32_t* out, uint32_t* in) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 3000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "4way_bitunpack_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		FastPForLib::SIMD_fastunpack_32(reinterpret_cast<const __m128i*>(in), out, 32);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 128));
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
	benchmark.Run(bench_0(out32, in32));
	benchmark.Run(bench_1(out32, in32));
	benchmark.Run(bench_2(out32, in32));
	benchmark.Run(bench_3(out32, in32));
	benchmark.Run(bench_4(out32, in32));
	benchmark.Run(bench_5(out32, in32));
	benchmark.Run(bench_6(out32, in32));
	benchmark.Run(bench_7(out32, in32));
	benchmark.Run(bench_8(out32, in32));
	benchmark.Run(bench_9(out32, in32));
	benchmark.Run(bench_10(out32, in32));
	benchmark.Run(bench_11(out32, in32));
	benchmark.Run(bench_12(out32, in32));
	benchmark.Run(bench_13(out32, in32));
	benchmark.Run(bench_14(out32, in32));
	benchmark.Run(bench_15(out32, in32));
	benchmark.Run(bench_16(out32, in32));
	benchmark.Run(bench_17(out32, in32));
	benchmark.Run(bench_18(out32, in32));
	benchmark.Run(bench_19(out32, in32));
	benchmark.Run(bench_20(out32, in32));
	benchmark.Run(bench_21(out32, in32));
	benchmark.Run(bench_22(out32, in32));
	benchmark.Run(bench_23(out32, in32));
	benchmark.Run(bench_24(out32, in32));
	benchmark.Run(bench_25(out32, in32));
	benchmark.Run(bench_26(out32, in32));
	benchmark.Run(bench_27(out32, in32));
	benchmark.Run(bench_28(out32, in32));
	benchmark.Run(bench_29(out32, in32));
	benchmark.Run(bench_30(out32, in32));
	benchmark.Run(bench_31(out32, in32));
	benchmark.Run(bench_32(out32, in32));
}

int main() {
	benchmark::Benchmark benchmark =
	    benchmark::create("x86_64_avx512bw_4way")
	        .save()
	        .at(std::string(SOURCE_DIR) + "/fls_pub/results/" + benchmark::CmakeInfo::getCmakeToolchainFile())
	        .print()
	        .add_extra_info(benchmark::CmakeInfo::getCmakeInfo());
	benchmark_all(benchmark);
}
