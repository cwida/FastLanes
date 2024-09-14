#include <iostream>
#include "arm64v8_scalar_av_1024_uf1_normal_rsum_bench.hpp"
#include "arm64v8_scalar_av_1024_uf1_normal_rsum_helper.hpp"
#include "fls_gen/normal_rsum/normal_rsum.hpp"
static benchmark::BenchmarkReporter::Run bench_0(int8_t* out8)
{
	int benchmark_number = 0;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	std::string benchmark_name = "rsum_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::normal_rsum::arm64v8::scalar::rsum(helper::delta_arr_ow8, out8, helper::base_arr_ow8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_1(int8_t* out8)
{
	int benchmark_number = 1;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	std::string benchmark_name = "unrolled_rsum_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::normal_rsum::arm64v8::scalar::unrolled_rsum(helper::delta_arr_ow8, out8, helper::base_arr_ow8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_2(int16_t* out16)
{
	int benchmark_number = 2;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	std::string benchmark_name = "rsum_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::normal_rsum::arm64v8::scalar::rsum(helper::delta_arr_ow16, out16, helper::base_arr_ow16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_3(int16_t* out16)
{
	int benchmark_number = 3;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	std::string benchmark_name = "unrolled_rsum_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::normal_rsum::arm64v8::scalar::unrolled_rsum(helper::delta_arr_ow16, out16, helper::base_arr_ow16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_4(int32_t* out32)
{
	int benchmark_number = 4;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	std::string benchmark_name = "rsum_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::normal_rsum::arm64v8::scalar::rsum(helper::delta_arr_ow32, out32, helper::base_arr_ow32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_5(int32_t* out32)
{
	int benchmark_number = 5;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	std::string benchmark_name = "unrolled_rsum_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::normal_rsum::arm64v8::scalar::unrolled_rsum(helper::delta_arr_ow32, out32, helper::base_arr_ow32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_6(int64_t* out64)
{
	int benchmark_number = 6;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	std::string benchmark_name = "rsum_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::normal_rsum::arm64v8::scalar::rsum(helper::delta_arr_ow64, out64, helper::base_arr_ow64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_7(int64_t* out64)
{
	int benchmark_number = 7;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	std::string benchmark_name = "unrolled_rsum_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::normal_rsum::arm64v8::scalar::unrolled_rsum(helper::delta_arr_ow64, out64, helper::base_arr_ow64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
void benchmark_all(benchmark::Benchmark& benchmark)
{
	auto *out8 = new int8_t[1024]();
	auto *out16 = new int16_t[1024]();
	auto *out32 = new int32_t[1024]();
	auto *out64 = new int64_t[1024]();
	benchmark.Run(bench_0(out8));
	benchmark.Run(bench_1(out8));
	benchmark.Run(bench_2(out16));
	benchmark.Run(bench_3(out16));
	benchmark.Run(bench_4(out32));
	benchmark.Run(bench_5(out32));
	benchmark.Run(bench_6(out64));
	benchmark.Run(bench_7(out64));
}
int main()
{
		benchmark::Benchmark benchmark =
	                     benchmark::create("arm64v8_scalar_av_1024_uf1_normal_rsum")
	                    .save()
	                    .at(std::string(SOURCE_DIR) + "/fls_pub/results/" + benchmark::CmakeInfo::getCmakeToolchainFile())
	                    .print()
	                    .add_extra_info(benchmark::CmakeInfo::getCmakeInfo());
	                benchmark_all(benchmark);
}
