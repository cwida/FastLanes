#include <iostream>
#include "fallback_scalar_aav_1024_uf1_unpack_bench.hpp"
#include "fallback_scalar_aav_1024_uf1_unpack_helper.hpp"
#include "fls_gen/unpack/unpack.hpp"
#include "fls_gen/pack/pack.hpp"
static benchmark::BenchmarkReporter::Run bench0_unpack_0bw_8ow_8crw_1uf(const uint8_t* packed8, uint8_t* unpacked8)
{
	int benchmark_number = 0;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint8_t base8[1] = {1};
	std::string benchmark_name =  "bench0_unpack_0bw_8ow_8crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_0_b0_w8_arr, const_cast<uint8_t*>(packed8), 0);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed8, const_cast<uint8_t*>(unpacked8), 0);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench1_unpack_1bw_8ow_8crw_1uf(const uint8_t* packed8, uint8_t* unpacked8)
{
	int benchmark_number = 1;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint8_t base8[1] = {1};
	std::string benchmark_name =  "bench1_unpack_1bw_8ow_8crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_1_b1_w8_arr, const_cast<uint8_t*>(packed8), 1);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed8, const_cast<uint8_t*>(unpacked8), 1);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench2_unpack_2bw_8ow_8crw_1uf(const uint8_t* packed8, uint8_t* unpacked8)
{
	int benchmark_number = 2;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint8_t base8[1] = {1};
	std::string benchmark_name =  "bench2_unpack_2bw_8ow_8crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_2_b2_w8_arr, const_cast<uint8_t*>(packed8), 2);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed8, const_cast<uint8_t*>(unpacked8), 2);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench3_unpack_3bw_8ow_8crw_1uf(const uint8_t* packed8, uint8_t* unpacked8)
{
	int benchmark_number = 3;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint8_t base8[1] = {1};
	std::string benchmark_name =  "bench3_unpack_3bw_8ow_8crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_3_b3_w8_arr, const_cast<uint8_t*>(packed8), 3);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed8, const_cast<uint8_t*>(unpacked8), 3);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench4_unpack_4bw_8ow_8crw_1uf(const uint8_t* packed8, uint8_t* unpacked8)
{
	int benchmark_number = 4;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint8_t base8[1] = {1};
	std::string benchmark_name =  "bench4_unpack_4bw_8ow_8crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_4_b4_w8_arr, const_cast<uint8_t*>(packed8), 4);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed8, const_cast<uint8_t*>(unpacked8), 4);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench5_unpack_5bw_8ow_8crw_1uf(const uint8_t* packed8, uint8_t* unpacked8)
{
	int benchmark_number = 5;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint8_t base8[1] = {1};
	std::string benchmark_name =  "bench5_unpack_5bw_8ow_8crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_5_b5_w8_arr, const_cast<uint8_t*>(packed8), 5);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed8, const_cast<uint8_t*>(unpacked8), 5);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench6_unpack_6bw_8ow_8crw_1uf(const uint8_t* packed8, uint8_t* unpacked8)
{
	int benchmark_number = 6;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint8_t base8[1] = {1};
	std::string benchmark_name =  "bench6_unpack_6bw_8ow_8crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_6_b6_w8_arr, const_cast<uint8_t*>(packed8), 6);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed8, const_cast<uint8_t*>(unpacked8), 6);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench7_unpack_7bw_8ow_8crw_1uf(const uint8_t* packed8, uint8_t* unpacked8)
{
	int benchmark_number = 7;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint8_t base8[1] = {1};
	std::string benchmark_name =  "bench7_unpack_7bw_8ow_8crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_7_b7_w8_arr, const_cast<uint8_t*>(packed8), 7);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed8, const_cast<uint8_t*>(unpacked8), 7);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench8_unpack_8bw_8ow_8crw_1uf(const uint8_t* packed8, uint8_t* unpacked8)
{
	int benchmark_number = 8;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint8_t base8[1] = {1};
	std::string benchmark_name =  "bench8_unpack_8bw_8ow_8crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_8_b8_w8_arr, const_cast<uint8_t*>(packed8), 8);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed8, const_cast<uint8_t*>(unpacked8), 8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench9_unpack_0bw_16ow_16crw_1uf(const uint16_t* packed16, uint16_t* unpacked16)
{
	int benchmark_number = 9;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint16_t base16[1] = {1};
	std::string benchmark_name =  "bench9_unpack_0bw_16ow_16crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_9_b0_w16_arr, const_cast<uint16_t*>(packed16), 0);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 0);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench10_unpack_1bw_16ow_16crw_1uf(const uint16_t* packed16, uint16_t* unpacked16)
{
	int benchmark_number = 10;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint16_t base16[1] = {1};
	std::string benchmark_name =  "bench10_unpack_1bw_16ow_16crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_10_b1_w16_arr, const_cast<uint16_t*>(packed16), 1);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 1);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench11_unpack_2bw_16ow_16crw_1uf(const uint16_t* packed16, uint16_t* unpacked16)
{
	int benchmark_number = 11;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint16_t base16[1] = {1};
	std::string benchmark_name =  "bench11_unpack_2bw_16ow_16crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_11_b2_w16_arr, const_cast<uint16_t*>(packed16), 2);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 2);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench12_unpack_3bw_16ow_16crw_1uf(const uint16_t* packed16, uint16_t* unpacked16)
{
	int benchmark_number = 12;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint16_t base16[1] = {1};
	std::string benchmark_name =  "bench12_unpack_3bw_16ow_16crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_12_b3_w16_arr, const_cast<uint16_t*>(packed16), 3);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 3);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench13_unpack_4bw_16ow_16crw_1uf(const uint16_t* packed16, uint16_t* unpacked16)
{
	int benchmark_number = 13;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint16_t base16[1] = {1};
	std::string benchmark_name =  "bench13_unpack_4bw_16ow_16crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_13_b4_w16_arr, const_cast<uint16_t*>(packed16), 4);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 4);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench14_unpack_5bw_16ow_16crw_1uf(const uint16_t* packed16, uint16_t* unpacked16)
{
	int benchmark_number = 14;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint16_t base16[1] = {1};
	std::string benchmark_name =  "bench14_unpack_5bw_16ow_16crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_14_b5_w16_arr, const_cast<uint16_t*>(packed16), 5);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 5);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench15_unpack_6bw_16ow_16crw_1uf(const uint16_t* packed16, uint16_t* unpacked16)
{
	int benchmark_number = 15;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint16_t base16[1] = {1};
	std::string benchmark_name =  "bench15_unpack_6bw_16ow_16crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_15_b6_w16_arr, const_cast<uint16_t*>(packed16), 6);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 6);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench16_unpack_7bw_16ow_16crw_1uf(const uint16_t* packed16, uint16_t* unpacked16)
{
	int benchmark_number = 16;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint16_t base16[1] = {1};
	std::string benchmark_name =  "bench16_unpack_7bw_16ow_16crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_16_b7_w16_arr, const_cast<uint16_t*>(packed16), 7);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 7);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench17_unpack_8bw_16ow_16crw_1uf(const uint16_t* packed16, uint16_t* unpacked16)
{
	int benchmark_number = 17;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint16_t base16[1] = {1};
	std::string benchmark_name =  "bench17_unpack_8bw_16ow_16crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_17_b8_w16_arr, const_cast<uint16_t*>(packed16), 8);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench18_unpack_9bw_16ow_16crw_1uf(const uint16_t* packed16, uint16_t* unpacked16)
{
	int benchmark_number = 18;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint16_t base16[1] = {1};
	std::string benchmark_name =  "bench18_unpack_9bw_16ow_16crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_18_b9_w16_arr, const_cast<uint16_t*>(packed16), 9);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 9);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench19_unpack_10bw_16ow_16crw_1uf(const uint16_t* packed16, uint16_t* unpacked16)
{
	int benchmark_number = 19;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint16_t base16[1] = {1};
	std::string benchmark_name =  "bench19_unpack_10bw_16ow_16crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_19_b10_w16_arr, const_cast<uint16_t*>(packed16), 10);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 10);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench20_unpack_11bw_16ow_16crw_1uf(const uint16_t* packed16, uint16_t* unpacked16)
{
	int benchmark_number = 20;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint16_t base16[1] = {1};
	std::string benchmark_name =  "bench20_unpack_11bw_16ow_16crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_20_b11_w16_arr, const_cast<uint16_t*>(packed16), 11);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 11);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench21_unpack_12bw_16ow_16crw_1uf(const uint16_t* packed16, uint16_t* unpacked16)
{
	int benchmark_number = 21;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint16_t base16[1] = {1};
	std::string benchmark_name =  "bench21_unpack_12bw_16ow_16crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_21_b12_w16_arr, const_cast<uint16_t*>(packed16), 12);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 12);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench22_unpack_13bw_16ow_16crw_1uf(const uint16_t* packed16, uint16_t* unpacked16)
{
	int benchmark_number = 22;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint16_t base16[1] = {1};
	std::string benchmark_name =  "bench22_unpack_13bw_16ow_16crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_22_b13_w16_arr, const_cast<uint16_t*>(packed16), 13);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 13);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench23_unpack_14bw_16ow_16crw_1uf(const uint16_t* packed16, uint16_t* unpacked16)
{
	int benchmark_number = 23;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint16_t base16[1] = {1};
	std::string benchmark_name =  "bench23_unpack_14bw_16ow_16crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_23_b14_w16_arr, const_cast<uint16_t*>(packed16), 14);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 14);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench24_unpack_15bw_16ow_16crw_1uf(const uint16_t* packed16, uint16_t* unpacked16)
{
	int benchmark_number = 24;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint16_t base16[1] = {1};
	std::string benchmark_name =  "bench24_unpack_15bw_16ow_16crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_24_b15_w16_arr, const_cast<uint16_t*>(packed16), 15);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 15);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench25_unpack_16bw_16ow_16crw_1uf(const uint16_t* packed16, uint16_t* unpacked16)
{
	int benchmark_number = 25;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint16_t base16[1] = {1};
	std::string benchmark_name =  "bench25_unpack_16bw_16ow_16crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_25_b16_w16_arr, const_cast<uint16_t*>(packed16), 16);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed16, const_cast<uint16_t*>(unpacked16), 16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench26_unpack_0bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 26;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench26_unpack_0bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_26_b0_w32_arr, const_cast<uint32_t*>(packed32), 0);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 0);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench27_unpack_1bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 27;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench27_unpack_1bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_27_b1_w32_arr, const_cast<uint32_t*>(packed32), 1);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 1);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench28_unpack_2bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 28;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench28_unpack_2bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_28_b2_w32_arr, const_cast<uint32_t*>(packed32), 2);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 2);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench29_unpack_3bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 29;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench29_unpack_3bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_29_b3_w32_arr, const_cast<uint32_t*>(packed32), 3);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 3);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench30_unpack_4bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 30;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench30_unpack_4bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_30_b4_w32_arr, const_cast<uint32_t*>(packed32), 4);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 4);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench31_unpack_5bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 31;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench31_unpack_5bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_31_b5_w32_arr, const_cast<uint32_t*>(packed32), 5);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 5);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench32_unpack_6bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 32;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench32_unpack_6bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_32_b6_w32_arr, const_cast<uint32_t*>(packed32), 6);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 6);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench33_unpack_7bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 33;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench33_unpack_7bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_33_b7_w32_arr, const_cast<uint32_t*>(packed32), 7);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 7);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench34_unpack_8bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 34;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench34_unpack_8bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_34_b8_w32_arr, const_cast<uint32_t*>(packed32), 8);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench35_unpack_9bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 35;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench35_unpack_9bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_35_b9_w32_arr, const_cast<uint32_t*>(packed32), 9);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 9);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench36_unpack_10bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 36;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench36_unpack_10bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_36_b10_w32_arr, const_cast<uint32_t*>(packed32), 10);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 10);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench37_unpack_11bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 37;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench37_unpack_11bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_37_b11_w32_arr, const_cast<uint32_t*>(packed32), 11);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 11);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench38_unpack_12bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 38;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench38_unpack_12bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_38_b12_w32_arr, const_cast<uint32_t*>(packed32), 12);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 12);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench39_unpack_13bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 39;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench39_unpack_13bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_39_b13_w32_arr, const_cast<uint32_t*>(packed32), 13);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 13);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench40_unpack_14bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 40;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench40_unpack_14bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_40_b14_w32_arr, const_cast<uint32_t*>(packed32), 14);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 14);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench41_unpack_15bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 41;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench41_unpack_15bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_41_b15_w32_arr, const_cast<uint32_t*>(packed32), 15);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 15);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench42_unpack_16bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 42;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench42_unpack_16bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_42_b16_w32_arr, const_cast<uint32_t*>(packed32), 16);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench43_unpack_17bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 43;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench43_unpack_17bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_43_b17_w32_arr, const_cast<uint32_t*>(packed32), 17);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 17);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench44_unpack_18bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 44;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench44_unpack_18bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_44_b18_w32_arr, const_cast<uint32_t*>(packed32), 18);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 18);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench45_unpack_19bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 45;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench45_unpack_19bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_45_b19_w32_arr, const_cast<uint32_t*>(packed32), 19);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 19);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench46_unpack_20bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 46;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench46_unpack_20bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_46_b20_w32_arr, const_cast<uint32_t*>(packed32), 20);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 20);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench47_unpack_21bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 47;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench47_unpack_21bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_47_b21_w32_arr, const_cast<uint32_t*>(packed32), 21);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 21);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench48_unpack_22bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 48;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench48_unpack_22bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_48_b22_w32_arr, const_cast<uint32_t*>(packed32), 22);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 22);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench49_unpack_23bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 49;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench49_unpack_23bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_49_b23_w32_arr, const_cast<uint32_t*>(packed32), 23);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 23);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench50_unpack_24bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 50;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench50_unpack_24bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_50_b24_w32_arr, const_cast<uint32_t*>(packed32), 24);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 24);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench51_unpack_25bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 51;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench51_unpack_25bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_51_b25_w32_arr, const_cast<uint32_t*>(packed32), 25);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 25);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench52_unpack_26bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 52;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench52_unpack_26bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_52_b26_w32_arr, const_cast<uint32_t*>(packed32), 26);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 26);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench53_unpack_27bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 53;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench53_unpack_27bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_53_b27_w32_arr, const_cast<uint32_t*>(packed32), 27);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 27);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench54_unpack_28bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 54;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench54_unpack_28bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_54_b28_w32_arr, const_cast<uint32_t*>(packed32), 28);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 28);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench55_unpack_29bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 55;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench55_unpack_29bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_55_b29_w32_arr, const_cast<uint32_t*>(packed32), 29);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 29);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench56_unpack_30bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 56;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench56_unpack_30bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_56_b30_w32_arr, const_cast<uint32_t*>(packed32), 30);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 30);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench57_unpack_31bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 57;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench57_unpack_31bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_57_b31_w32_arr, const_cast<uint32_t*>(packed32), 31);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 31);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench58_unpack_32bw_32ow_32crw_1uf(const uint32_t* packed32, uint32_t* unpacked32)
{
	int benchmark_number = 58;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint32_t base32[1] = {1};
	std::string benchmark_name =  "bench58_unpack_32bw_32ow_32crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_58_b32_w32_arr, const_cast<uint32_t*>(packed32), 32);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed32, const_cast<uint32_t*>(unpacked32), 32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench59_unpack_0bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 59;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench59_unpack_0bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_59_b0_w64_arr, const_cast<uint64_t*>(packed64), 0);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 0);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench60_unpack_1bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 60;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench60_unpack_1bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_60_b1_w64_arr, const_cast<uint64_t*>(packed64), 1);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 1);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench61_unpack_2bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 61;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench61_unpack_2bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_61_b2_w64_arr, const_cast<uint64_t*>(packed64), 2);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 2);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench62_unpack_3bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 62;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench62_unpack_3bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_62_b3_w64_arr, const_cast<uint64_t*>(packed64), 3);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 3);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench63_unpack_4bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 63;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench63_unpack_4bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_63_b4_w64_arr, const_cast<uint64_t*>(packed64), 4);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 4);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench64_unpack_5bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 64;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench64_unpack_5bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_64_b5_w64_arr, const_cast<uint64_t*>(packed64), 5);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 5);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench65_unpack_6bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 65;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench65_unpack_6bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_65_b6_w64_arr, const_cast<uint64_t*>(packed64), 6);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 6);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench66_unpack_7bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 66;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench66_unpack_7bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_66_b7_w64_arr, const_cast<uint64_t*>(packed64), 7);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 7);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench67_unpack_8bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 67;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench67_unpack_8bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_67_b8_w64_arr, const_cast<uint64_t*>(packed64), 8);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench68_unpack_9bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 68;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench68_unpack_9bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_68_b9_w64_arr, const_cast<uint64_t*>(packed64), 9);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 9);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench69_unpack_10bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 69;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench69_unpack_10bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_69_b10_w64_arr, const_cast<uint64_t*>(packed64), 10);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 10);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench70_unpack_11bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 70;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench70_unpack_11bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_70_b11_w64_arr, const_cast<uint64_t*>(packed64), 11);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 11);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench71_unpack_12bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 71;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench71_unpack_12bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_71_b12_w64_arr, const_cast<uint64_t*>(packed64), 12);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 12);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench72_unpack_13bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 72;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench72_unpack_13bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_72_b13_w64_arr, const_cast<uint64_t*>(packed64), 13);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 13);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench73_unpack_14bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 73;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench73_unpack_14bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_73_b14_w64_arr, const_cast<uint64_t*>(packed64), 14);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 14);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench74_unpack_15bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 74;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench74_unpack_15bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_74_b15_w64_arr, const_cast<uint64_t*>(packed64), 15);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 15);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench75_unpack_16bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 75;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench75_unpack_16bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_75_b16_w64_arr, const_cast<uint64_t*>(packed64), 16);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench76_unpack_17bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 76;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench76_unpack_17bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_76_b17_w64_arr, const_cast<uint64_t*>(packed64), 17);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 17);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench77_unpack_18bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 77;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench77_unpack_18bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_77_b18_w64_arr, const_cast<uint64_t*>(packed64), 18);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 18);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench78_unpack_19bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 78;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench78_unpack_19bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_78_b19_w64_arr, const_cast<uint64_t*>(packed64), 19);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 19);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench79_unpack_20bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 79;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench79_unpack_20bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_79_b20_w64_arr, const_cast<uint64_t*>(packed64), 20);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 20);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench80_unpack_21bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 80;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench80_unpack_21bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_80_b21_w64_arr, const_cast<uint64_t*>(packed64), 21);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 21);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench81_unpack_22bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 81;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench81_unpack_22bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_81_b22_w64_arr, const_cast<uint64_t*>(packed64), 22);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 22);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench82_unpack_23bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 82;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench82_unpack_23bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_82_b23_w64_arr, const_cast<uint64_t*>(packed64), 23);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 23);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench83_unpack_24bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 83;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench83_unpack_24bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_83_b24_w64_arr, const_cast<uint64_t*>(packed64), 24);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 24);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench84_unpack_25bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 84;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench84_unpack_25bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_84_b25_w64_arr, const_cast<uint64_t*>(packed64), 25);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 25);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench85_unpack_26bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 85;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench85_unpack_26bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_85_b26_w64_arr, const_cast<uint64_t*>(packed64), 26);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 26);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench86_unpack_27bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 86;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench86_unpack_27bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_86_b27_w64_arr, const_cast<uint64_t*>(packed64), 27);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 27);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench87_unpack_28bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 87;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench87_unpack_28bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_87_b28_w64_arr, const_cast<uint64_t*>(packed64), 28);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 28);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench88_unpack_29bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 88;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench88_unpack_29bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_88_b29_w64_arr, const_cast<uint64_t*>(packed64), 29);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 29);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench89_unpack_30bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 89;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench89_unpack_30bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_89_b30_w64_arr, const_cast<uint64_t*>(packed64), 30);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 30);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench90_unpack_31bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 90;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench90_unpack_31bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_90_b31_w64_arr, const_cast<uint64_t*>(packed64), 31);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 31);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench91_unpack_32bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 91;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench91_unpack_32bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_91_b32_w64_arr, const_cast<uint64_t*>(packed64), 32);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench92_unpack_33bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 92;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench92_unpack_33bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_92_b33_w64_arr, const_cast<uint64_t*>(packed64), 33);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 33);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench93_unpack_34bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 93;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench93_unpack_34bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_93_b34_w64_arr, const_cast<uint64_t*>(packed64), 34);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 34);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench94_unpack_35bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 94;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench94_unpack_35bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_94_b35_w64_arr, const_cast<uint64_t*>(packed64), 35);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 35);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench95_unpack_36bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 95;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench95_unpack_36bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_95_b36_w64_arr, const_cast<uint64_t*>(packed64), 36);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 36);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench96_unpack_37bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 96;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench96_unpack_37bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_96_b37_w64_arr, const_cast<uint64_t*>(packed64), 37);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 37);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench97_unpack_38bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 97;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench97_unpack_38bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_97_b38_w64_arr, const_cast<uint64_t*>(packed64), 38);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 38);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench98_unpack_39bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 98;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench98_unpack_39bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_98_b39_w64_arr, const_cast<uint64_t*>(packed64), 39);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 39);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench99_unpack_40bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 99;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench99_unpack_40bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_99_b40_w64_arr, const_cast<uint64_t*>(packed64), 40);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 40);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench100_unpack_41bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 100;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench100_unpack_41bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_100_b41_w64_arr, const_cast<uint64_t*>(packed64), 41);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 41);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench101_unpack_42bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 101;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench101_unpack_42bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_101_b42_w64_arr, const_cast<uint64_t*>(packed64), 42);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 42);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench102_unpack_43bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 102;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench102_unpack_43bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_102_b43_w64_arr, const_cast<uint64_t*>(packed64), 43);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 43);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench103_unpack_44bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 103;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench103_unpack_44bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_103_b44_w64_arr, const_cast<uint64_t*>(packed64), 44);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 44);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench104_unpack_45bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 104;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench104_unpack_45bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_104_b45_w64_arr, const_cast<uint64_t*>(packed64), 45);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 45);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench105_unpack_46bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 105;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench105_unpack_46bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_105_b46_w64_arr, const_cast<uint64_t*>(packed64), 46);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 46);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench106_unpack_47bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 106;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench106_unpack_47bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_106_b47_w64_arr, const_cast<uint64_t*>(packed64), 47);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 47);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench107_unpack_48bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 107;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench107_unpack_48bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_107_b48_w64_arr, const_cast<uint64_t*>(packed64), 48);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 48);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench108_unpack_49bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 108;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench108_unpack_49bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_108_b49_w64_arr, const_cast<uint64_t*>(packed64), 49);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 49);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench109_unpack_50bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 109;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench109_unpack_50bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_109_b50_w64_arr, const_cast<uint64_t*>(packed64), 50);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 50);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench110_unpack_51bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 110;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench110_unpack_51bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_110_b51_w64_arr, const_cast<uint64_t*>(packed64), 51);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 51);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench111_unpack_52bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 111;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench111_unpack_52bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_111_b52_w64_arr, const_cast<uint64_t*>(packed64), 52);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 52);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench112_unpack_53bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 112;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench112_unpack_53bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_112_b53_w64_arr, const_cast<uint64_t*>(packed64), 53);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 53);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench113_unpack_54bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 113;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench113_unpack_54bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_113_b54_w64_arr, const_cast<uint64_t*>(packed64), 54);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 54);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench114_unpack_55bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 114;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench114_unpack_55bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_114_b55_w64_arr, const_cast<uint64_t*>(packed64), 55);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 55);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench115_unpack_56bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 115;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench115_unpack_56bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_115_b56_w64_arr, const_cast<uint64_t*>(packed64), 56);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 56);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench116_unpack_57bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 116;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench116_unpack_57bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_116_b57_w64_arr, const_cast<uint64_t*>(packed64), 57);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 57);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench117_unpack_58bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 117;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench117_unpack_58bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_117_b58_w64_arr, const_cast<uint64_t*>(packed64), 58);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 58);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench118_unpack_59bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 118;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench118_unpack_59bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_118_b59_w64_arr, const_cast<uint64_t*>(packed64), 59);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 59);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench119_unpack_60bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 119;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench119_unpack_60bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_119_b60_w64_arr, const_cast<uint64_t*>(packed64), 60);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 60);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench120_unpack_61bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 120;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench120_unpack_61bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_120_b61_w64_arr, const_cast<uint64_t*>(packed64), 61);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 61);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench121_unpack_62bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 121;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench121_unpack_62bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_121_b62_w64_arr, const_cast<uint64_t*>(packed64), 62);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 62);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench122_unpack_63bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 122;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench122_unpack_63bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_122_b63_w64_arr, const_cast<uint64_t*>(packed64), 63);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 63);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench123_unpack_64bw_64ow_64crw_1uf(const uint64_t* packed64, uint64_t* unpacked64)
{
	int benchmark_number = 123;
	
    #ifdef NDEBUG
    uint64_t iterations = 3000000;
    #else 
    uint64_t iterations = 1;
    #endif
                
	[[maybe_unused]] const uint64_t base64[1] = {1};
	std::string benchmark_name =  "bench123_unpack_64bw_64ow_64crw_1uf";
	
	generated::pack::helper::scalar::pack(helper::rand_arr_123_b64_w64_arr, const_cast<uint64_t*>(packed64), 64);
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		generated::unpack::fallback::scalar::unpack(packed64, const_cast<uint64_t*>(unpacked64), 64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	
	return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
void benchmark_all(benchmark::Benchmark& benchmark)
{
	const auto packed8 = new (std::align_val_t {64}) uint8_t[1024];
	const auto packed16 = new (std::align_val_t {64}) uint16_t[1024];
	const auto packed32 = new (std::align_val_t {64}) uint32_t[1024];
	const auto packed64 = new (std::align_val_t {64}) uint64_t[1024];
	auto unpacked8 = new (std::align_val_t {64}) uint8_t[1024];
	auto unpacked16 = new (std::align_val_t {64}) uint16_t[1024];
	auto unpacked32 = new (std::align_val_t {64}) uint32_t[1024];
	auto unpacked64 = new (std::align_val_t {64}) uint64_t[1024];
	benchmark.Run(bench0_unpack_0bw_8ow_8crw_1uf(packed8, unpacked8));
	benchmark.Run(bench1_unpack_1bw_8ow_8crw_1uf(packed8, unpacked8));
	benchmark.Run(bench2_unpack_2bw_8ow_8crw_1uf(packed8, unpacked8));
	benchmark.Run(bench3_unpack_3bw_8ow_8crw_1uf(packed8, unpacked8));
	benchmark.Run(bench4_unpack_4bw_8ow_8crw_1uf(packed8, unpacked8));
	benchmark.Run(bench5_unpack_5bw_8ow_8crw_1uf(packed8, unpacked8));
	benchmark.Run(bench6_unpack_6bw_8ow_8crw_1uf(packed8, unpacked8));
	benchmark.Run(bench7_unpack_7bw_8ow_8crw_1uf(packed8, unpacked8));
	benchmark.Run(bench8_unpack_8bw_8ow_8crw_1uf(packed8, unpacked8));
	benchmark.Run(bench9_unpack_0bw_16ow_16crw_1uf(packed16, unpacked16));
	benchmark.Run(bench10_unpack_1bw_16ow_16crw_1uf(packed16, unpacked16));
	benchmark.Run(bench11_unpack_2bw_16ow_16crw_1uf(packed16, unpacked16));
	benchmark.Run(bench12_unpack_3bw_16ow_16crw_1uf(packed16, unpacked16));
	benchmark.Run(bench13_unpack_4bw_16ow_16crw_1uf(packed16, unpacked16));
	benchmark.Run(bench14_unpack_5bw_16ow_16crw_1uf(packed16, unpacked16));
	benchmark.Run(bench15_unpack_6bw_16ow_16crw_1uf(packed16, unpacked16));
	benchmark.Run(bench16_unpack_7bw_16ow_16crw_1uf(packed16, unpacked16));
	benchmark.Run(bench17_unpack_8bw_16ow_16crw_1uf(packed16, unpacked16));
	benchmark.Run(bench18_unpack_9bw_16ow_16crw_1uf(packed16, unpacked16));
	benchmark.Run(bench19_unpack_10bw_16ow_16crw_1uf(packed16, unpacked16));
	benchmark.Run(bench20_unpack_11bw_16ow_16crw_1uf(packed16, unpacked16));
	benchmark.Run(bench21_unpack_12bw_16ow_16crw_1uf(packed16, unpacked16));
	benchmark.Run(bench22_unpack_13bw_16ow_16crw_1uf(packed16, unpacked16));
	benchmark.Run(bench23_unpack_14bw_16ow_16crw_1uf(packed16, unpacked16));
	benchmark.Run(bench24_unpack_15bw_16ow_16crw_1uf(packed16, unpacked16));
	benchmark.Run(bench25_unpack_16bw_16ow_16crw_1uf(packed16, unpacked16));
	benchmark.Run(bench26_unpack_0bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench27_unpack_1bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench28_unpack_2bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench29_unpack_3bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench30_unpack_4bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench31_unpack_5bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench32_unpack_6bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench33_unpack_7bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench34_unpack_8bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench35_unpack_9bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench36_unpack_10bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench37_unpack_11bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench38_unpack_12bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench39_unpack_13bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench40_unpack_14bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench41_unpack_15bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench42_unpack_16bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench43_unpack_17bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench44_unpack_18bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench45_unpack_19bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench46_unpack_20bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench47_unpack_21bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench48_unpack_22bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench49_unpack_23bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench50_unpack_24bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench51_unpack_25bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench52_unpack_26bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench53_unpack_27bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench54_unpack_28bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench55_unpack_29bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench56_unpack_30bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench57_unpack_31bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench58_unpack_32bw_32ow_32crw_1uf(packed32, unpacked32));
	benchmark.Run(bench59_unpack_0bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench60_unpack_1bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench61_unpack_2bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench62_unpack_3bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench63_unpack_4bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench64_unpack_5bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench65_unpack_6bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench66_unpack_7bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench67_unpack_8bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench68_unpack_9bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench69_unpack_10bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench70_unpack_11bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench71_unpack_12bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench72_unpack_13bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench73_unpack_14bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench74_unpack_15bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench75_unpack_16bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench76_unpack_17bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench77_unpack_18bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench78_unpack_19bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench79_unpack_20bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench80_unpack_21bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench81_unpack_22bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench82_unpack_23bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench83_unpack_24bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench84_unpack_25bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench85_unpack_26bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench86_unpack_27bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench87_unpack_28bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench88_unpack_29bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench89_unpack_30bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench90_unpack_31bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench91_unpack_32bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench92_unpack_33bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench93_unpack_34bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench94_unpack_35bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench95_unpack_36bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench96_unpack_37bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench97_unpack_38bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench98_unpack_39bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench99_unpack_40bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench100_unpack_41bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench101_unpack_42bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench102_unpack_43bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench103_unpack_44bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench104_unpack_45bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench105_unpack_46bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench106_unpack_47bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench107_unpack_48bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench108_unpack_49bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench109_unpack_50bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench110_unpack_51bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench111_unpack_52bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench112_unpack_53bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench113_unpack_54bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench114_unpack_55bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench115_unpack_56bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench116_unpack_57bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench117_unpack_58bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench118_unpack_59bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench119_unpack_60bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench120_unpack_61bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench121_unpack_62bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench122_unpack_63bw_64ow_64crw_1uf(packed64, unpacked64));
	benchmark.Run(bench123_unpack_64bw_64ow_64crw_1uf(packed64, unpacked64));
}
int main()
{
		benchmark::Benchmark benchmark =
	                     benchmark::create("fallback_scalar_aav_1024_uf1_unpack")
	                    .save()
	                    .at(std::string(SOURCE_DIR) + "/fls_pub/results/" + benchmark::CmakeInfo::getCmakeToolchainFile())
	                    .print()
	                    .add_extra_info(benchmark::CmakeInfo::getCmakeInfo());
	                benchmark_all(benchmark);
}
