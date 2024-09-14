#include "bitpackinghelpers.hpp"
#include "lemire_scalar_bitunpack_bench.hpp"

static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_0(const uint8_t* in, uint8_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_0_8";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 0);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_1(const uint8_t* in, uint8_t* out) {
	int benchmark_number = 1;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_1_8";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 1);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_2(const uint8_t* in, uint8_t* out) {
	int benchmark_number = 2;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_2_8";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 2);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_3(const uint8_t* in, uint8_t* out) {
	int benchmark_number = 3;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_3_8";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 3);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_4(const uint8_t* in, uint8_t* out) {
	int benchmark_number = 4;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_4_8";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 4);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_5(const uint8_t* in, uint8_t* out) {
	int benchmark_number = 5;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_5_8";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 5);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_6(const uint8_t* in, uint8_t* out) {
	int benchmark_number = 6;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_6_8";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 6);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_7(const uint8_t* in, uint8_t* out) {
	int benchmark_number = 7;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_7_8";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 7);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_8(const uint8_t* in, uint8_t* out) {
	int benchmark_number = 8;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_8_8";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 8);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}

static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_9(const uint16_t* in, uint16_t* out) {
	int benchmark_number = 9;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_0_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 0);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_10(const uint16_t* in, uint16_t* out) {
	int benchmark_number = 10;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_1_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 1);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_11(const uint16_t* in, uint16_t* out) {
	int benchmark_number = 11;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_2_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 2);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_12(const uint16_t* in, uint16_t* out) {
	int benchmark_number = 12;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_3_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 3);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_13(const uint16_t* in, uint16_t* out) {
	int benchmark_number = 13;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_4_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 4);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_14(const uint16_t* in, uint16_t* out) {
	int benchmark_number = 14;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_5_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 5);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_15(const uint16_t* in, uint16_t* out) {
	int benchmark_number = 15;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_6_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 6);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_16(const uint16_t* in, uint16_t* out) {
	int benchmark_number = 16;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_7_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 7);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_17(const uint16_t* in, uint16_t* out) {
	int benchmark_number = 17;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_8_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 8);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_18(const uint16_t* in, uint16_t* out) {
	int benchmark_number = 18;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_9_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 9);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_19(const uint16_t* in, uint16_t* out) {
	int benchmark_number = 19;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_10_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 10);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_20(const uint16_t* in, uint16_t* out) {
	int benchmark_number = 20;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_11_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 11);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_21(const uint16_t* in, uint16_t* out) {
	int benchmark_number = 21;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_12_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 12);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_22(const uint16_t* in, uint16_t* out) {
	int benchmark_number = 22;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_13_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 13);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_23(const uint16_t* in, uint16_t* out) {
	int benchmark_number = 23;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_14_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 14);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_24(const uint16_t* in, uint16_t* out) {
	int benchmark_number = 24;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_15_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 15);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_25(const uint16_t* in, uint16_t* out) {
	int benchmark_number = 25;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_16_16";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 16);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}

static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_26(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 26;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_0_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 0);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_27(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 27;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_1_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 1);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_28(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 28;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_2_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 2);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_29(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 29;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_3_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 3);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_30(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 30;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_4_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 4);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_31(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 31;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_5_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 5);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_32(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 32;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_6_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 6);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_33(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 33;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_7_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 7);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_34(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 34;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_8_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 8);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_35(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_9_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 9);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_36(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_10_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 10);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_37(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_11_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 11);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_38(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_12_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 12);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_39(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_13_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 13);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_40(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_14_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 14);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_41(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_15_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 15);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_42(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_16_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 16);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_43(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_17_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 17);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_44(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_18_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 18);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_45(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_19_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 19);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_46(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_20_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 20);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_47(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_21_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 21);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_48(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_22_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 22);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_49(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_23_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 23);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_50(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_24_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 24);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_51(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_25_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 25);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_52(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_26_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 26);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_53(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_27_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 27);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_54(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_28_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 28);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_55(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_29_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 29);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_56(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_30_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 30);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_57(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_31_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 31);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_58(const uint32_t* in, uint32_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_32_32";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 32);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}

static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_59(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_0_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 0);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_60(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_1_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 1);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_61(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_2_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 2);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_62(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_3_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 3);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_63(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_4_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 4);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_64(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_5_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 5);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_65(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_6_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 6);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_66(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_7_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 7);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_67(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_8_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 8);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_68(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_9_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 9);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_69(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_10_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 10);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_70(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_11_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 11);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_71(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_12_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 12);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_72(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_13_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 13);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_73(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_14_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 14);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_74(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_15_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 15);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_75(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_16_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 16);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_76(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_17_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 17);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_77(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_18_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 18);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_78(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_19_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 19);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_79(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_20_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 20);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_80(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_21_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 21);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_81(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_22_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 22);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_82(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_23_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 23);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_83(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_24_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 24);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_84(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_25_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 25);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_85(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_26_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 26);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_86(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_27_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 27);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_87(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_28_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 28);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_88(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_29_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 29);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_89(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_30_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 30);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_90(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_31_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 31);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_91(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_32_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 32);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_92(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_33_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 33);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_93(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_34_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 34);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_94(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_35_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 35);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_95(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_36_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 36);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_96(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_37_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 37);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_97(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_38_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 38);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_98(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_39_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 39);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_99(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_40_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 40);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_100(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_41_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 41);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_101(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_42_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 42);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_102(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_43_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 43);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_103(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_44_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 44);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_104(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_45_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 45);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_105(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_46_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 46);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_106(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_47_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 47);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_107(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_48_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 48);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_108(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_49_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 49);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_109(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_50_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 50);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_110(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_51_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 51);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_111(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_52_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 52);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_112(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_53_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 53);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_113(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_54_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 54);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_114(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_55_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 55);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_115(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_56_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 56);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_116(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_57_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 57);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_117(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_58_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 58);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_118(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_59_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 59);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_119(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_60_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 60);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_120(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_61_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 61);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_121(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_62_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 62);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_122(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_63_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack((in), out, 63);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
}
static __attribute__ ((noinline)) benchmark::BenchmarkReporter::Run bench_123(const uint32_t* in, uint64_t* out) {
	int benchmark_number = 0;

#ifdef NDEBUG
	uint64_t iterations = 30000000;
#else
	uint64_t iterations = 1;
#endif

	std::string benchmark_name = "bitunpack_64_64";

	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations; ++i) {
		duckdb_fastpforlib::fastunpack(in, out, 64);
	}

	cycles = benchmark::cycleclock::Now() - cycles;

	return benchmark::BenchmarkReporter::Run(
	    benchmark_number, benchmark_name, iterations, double(cycles) / (double(iterations) * 32));
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
	benchmark.Run(bench_0(in08, out08));
	benchmark.Run(bench_1(in08, out08));
	benchmark.Run(bench_2(in08, out08));
	benchmark.Run(bench_3(in08, out08));
	benchmark.Run(bench_4(in08, out08));
	benchmark.Run(bench_5(in08, out08));
	benchmark.Run(bench_6(in08, out08));
	benchmark.Run(bench_7(in08, out08));
	benchmark.Run(bench_8(in08, out08));
	benchmark.Run(bench_9(in16, out16));
	benchmark.Run(bench_10(in16, out16));
	benchmark.Run(bench_11(in16, out16));
	benchmark.Run(bench_12(in16, out16));
	benchmark.Run(bench_13(in16, out16));
	benchmark.Run(bench_14(in16, out16));
	benchmark.Run(bench_15(in16, out16));
	benchmark.Run(bench_16(in16, out16));
	benchmark.Run(bench_17(in16, out16));
	benchmark.Run(bench_18(in16, out16));
	benchmark.Run(bench_19(in16, out16));
	benchmark.Run(bench_20(in16, out16));
	benchmark.Run(bench_21(in16, out16));
	benchmark.Run(bench_22(in16, out16));
	benchmark.Run(bench_23(in16, out16));
	benchmark.Run(bench_24(in16, out16));
	benchmark.Run(bench_25(in16, out16));
	benchmark.Run(bench_26(in32, out32));
	benchmark.Run(bench_27(in32, out32));
	benchmark.Run(bench_28(in32, out32));
	benchmark.Run(bench_29(in32, out32));
	benchmark.Run(bench_30(in32, out32));
	benchmark.Run(bench_31(in32, out32));
	benchmark.Run(bench_32(in32, out32));
	benchmark.Run(bench_33(in32, out32));
	benchmark.Run(bench_34(in32, out32));
	benchmark.Run(bench_35(in32, out32));
	benchmark.Run(bench_36(in32, out32));
	benchmark.Run(bench_37(in32, out32));
	benchmark.Run(bench_38(in32, out32));
	benchmark.Run(bench_39(in32, out32));
	benchmark.Run(bench_40(in32, out32));
	benchmark.Run(bench_41(in32, out32));
	benchmark.Run(bench_42(in32, out32));
	benchmark.Run(bench_43(in32, out32));
	benchmark.Run(bench_44(in32, out32));
	benchmark.Run(bench_45(in32, out32));
	benchmark.Run(bench_46(in32, out32));
	benchmark.Run(bench_47(in32, out32));
	benchmark.Run(bench_48(in32, out32));
	benchmark.Run(bench_49(in32, out32));
	benchmark.Run(bench_50(in32, out32));
	benchmark.Run(bench_51(in32, out32));
	benchmark.Run(bench_52(in32, out32));
	benchmark.Run(bench_53(in32, out32));
	benchmark.Run(bench_54(in32, out32));
	benchmark.Run(bench_55(in32, out32));
	benchmark.Run(bench_56(in32, out32));
	benchmark.Run(bench_57(in32, out32));
	benchmark.Run(bench_58(in32, out32));
	benchmark.Run(bench_59(in32, out64));
	benchmark.Run(bench_60(in32, out64));
	benchmark.Run(bench_61(in32, out64));
	benchmark.Run(bench_62(in32, out64));
	benchmark.Run(bench_63(in32, out64));
	benchmark.Run(bench_64(in32, out64));
	benchmark.Run(bench_65(in32, out64));
	benchmark.Run(bench_66(in32, out64));
	benchmark.Run(bench_67(in32, out64));
	benchmark.Run(bench_68(in32, out64));
	benchmark.Run(bench_69(in32, out64));
	benchmark.Run(bench_70(in32, out64));
	benchmark.Run(bench_71(in32, out64));
	benchmark.Run(bench_72(in32, out64));
	benchmark.Run(bench_73(in32, out64));
	benchmark.Run(bench_74(in32, out64));
	benchmark.Run(bench_75(in32, out64));
	benchmark.Run(bench_76(in32, out64));
	benchmark.Run(bench_77(in32, out64));
	benchmark.Run(bench_78(in32, out64));
	benchmark.Run(bench_79(in32, out64));
	benchmark.Run(bench_80(in32, out64));
	benchmark.Run(bench_81(in32, out64));
	benchmark.Run(bench_82(in32, out64));
	benchmark.Run(bench_83(in32, out64));
	benchmark.Run(bench_84(in32, out64));
	benchmark.Run(bench_85(in32, out64));
	benchmark.Run(bench_86(in32, out64));
	benchmark.Run(bench_87(in32, out64));
	benchmark.Run(bench_88(in32, out64));
	benchmark.Run(bench_89(in32, out64));
	benchmark.Run(bench_90(in32, out64));
	benchmark.Run(bench_91(in32, out64));
	benchmark.Run(bench_92(in32, out64));
	benchmark.Run(bench_93(in32, out64));
	benchmark.Run(bench_94(in32, out64));
	benchmark.Run(bench_95(in32, out64));
	benchmark.Run(bench_96(in32, out64));
	benchmark.Run(bench_97(in32, out64));
	benchmark.Run(bench_98(in32, out64));
	benchmark.Run(bench_99(in32, out64));
	benchmark.Run(bench_100(in32, out64));
	benchmark.Run(bench_101(in32, out64));
	benchmark.Run(bench_102(in32, out64));
	benchmark.Run(bench_103(in32, out64));
	benchmark.Run(bench_104(in32, out64));
	benchmark.Run(bench_105(in32, out64));
	benchmark.Run(bench_106(in32, out64));
	benchmark.Run(bench_107(in32, out64));
	benchmark.Run(bench_108(in32, out64));
	benchmark.Run(bench_109(in32, out64));
	benchmark.Run(bench_110(in32, out64));
	benchmark.Run(bench_111(in32, out64));
	benchmark.Run(bench_112(in32, out64));
	benchmark.Run(bench_113(in32, out64));
	benchmark.Run(bench_114(in32, out64));
	benchmark.Run(bench_115(in32, out64));
	benchmark.Run(bench_116(in32, out64));
	benchmark.Run(bench_117(in32, out64));
	benchmark.Run(bench_118(in32, out64));
	benchmark.Run(bench_119(in32, out64));
	benchmark.Run(bench_120(in32, out64));
	benchmark.Run(bench_121(in32, out64));
	benchmark.Run(bench_122(in32, out64));
	benchmark.Run(bench_123(in32, out64));
}

int main() {
	benchmark::Benchmark benchmark =
	    benchmark::create("x86_64_scalar")
	        .save()
	        .at(std::string(SOURCE_DIR) + "/fls_pub/results/" + benchmark::CmakeInfo::getCmakeToolchainFile())
	        .print()
	        .add_extra_info(benchmark::CmakeInfo::getCmakeInfo());
	benchmark_all(benchmark);
}
