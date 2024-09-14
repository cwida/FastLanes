#include <iostream>
#include "benchmark.hpp"
#include "arm64v8_scalar_av_1024_uf1_rut_helper.hpp"
#include <rut/rut.hpp>
static benchmark::BenchmarkReporter::Run bench_0(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 0;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs1_val_arr_ow8, helper::rle_runs1_len_arr_ow8, helper::rle_runs1_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_1(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 1;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs1_val_arr_ow8, helper::rle_runs1_len_arr_ow8, helper::rle_runs1_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_2(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 2;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs1_val_arr_ow16, helper::rle_runs1_len_arr_ow16, helper::rle_runs1_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_3(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 3;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs1_val_arr_ow16, helper::rle_runs1_len_arr_ow16, helper::rle_runs1_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_4(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 4;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs1_val_arr_ow32, helper::rle_runs1_len_arr_ow32, helper::rle_runs1_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_5(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 5;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs1_val_arr_ow32, helper::rle_runs1_len_arr_ow32, helper::rle_runs1_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_6(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 6;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs1_val_arr_ow64, helper::rle_runs1_len_arr_ow64, helper::rle_runs1_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_7(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 7;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs1_val_arr_ow64, helper::rle_runs1_len_arr_ow64, helper::rle_runs1_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_8(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 8;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs2_val_arr_ow8, helper::rle_runs2_len_arr_ow8, helper::rle_runs2_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_9(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 9;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs2_val_arr_ow8, helper::rle_runs2_len_arr_ow8, helper::rle_runs2_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_10(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 10;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs2_val_arr_ow16, helper::rle_runs2_len_arr_ow16, helper::rle_runs2_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_11(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 11;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs2_val_arr_ow16, helper::rle_runs2_len_arr_ow16, helper::rle_runs2_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_12(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 12;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs2_val_arr_ow32, helper::rle_runs2_len_arr_ow32, helper::rle_runs2_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_13(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 13;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs2_val_arr_ow32, helper::rle_runs2_len_arr_ow32, helper::rle_runs2_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_14(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 14;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs2_val_arr_ow64, helper::rle_runs2_len_arr_ow64, helper::rle_runs2_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_15(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 15;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs2_val_arr_ow64, helper::rle_runs2_len_arr_ow64, helper::rle_runs2_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_16(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 16;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs3_val_arr_ow8, helper::rle_runs3_len_arr_ow8, helper::rle_runs3_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_17(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 17;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs3_val_arr_ow8, helper::rle_runs3_len_arr_ow8, helper::rle_runs3_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_18(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 18;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs3_val_arr_ow16, helper::rle_runs3_len_arr_ow16, helper::rle_runs3_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_19(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 19;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs3_val_arr_ow16, helper::rle_runs3_len_arr_ow16, helper::rle_runs3_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_20(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 20;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs3_val_arr_ow32, helper::rle_runs3_len_arr_ow32, helper::rle_runs3_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_21(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 21;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs3_val_arr_ow32, helper::rle_runs3_len_arr_ow32, helper::rle_runs3_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_22(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 22;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs3_val_arr_ow64, helper::rle_runs3_len_arr_ow64, helper::rle_runs3_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_23(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 23;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs3_val_arr_ow64, helper::rle_runs3_len_arr_ow64, helper::rle_runs3_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_24(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 24;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs4_val_arr_ow8, helper::rle_runs4_len_arr_ow8, helper::rle_runs4_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_25(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 25;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs4_val_arr_ow8, helper::rle_runs4_len_arr_ow8, helper::rle_runs4_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_26(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 26;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs4_val_arr_ow16, helper::rle_runs4_len_arr_ow16, helper::rle_runs4_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_27(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 27;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs4_val_arr_ow16, helper::rle_runs4_len_arr_ow16, helper::rle_runs4_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_28(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 28;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs4_val_arr_ow32, helper::rle_runs4_len_arr_ow32, helper::rle_runs4_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_29(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 29;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs4_val_arr_ow32, helper::rle_runs4_len_arr_ow32, helper::rle_runs4_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_30(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 30;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs4_val_arr_ow64, helper::rle_runs4_len_arr_ow64, helper::rle_runs4_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_31(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 31;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs4_val_arr_ow64, helper::rle_runs4_len_arr_ow64, helper::rle_runs4_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_32(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 32;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs5_val_arr_ow8, helper::rle_runs5_len_arr_ow8, helper::rle_runs5_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_33(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 33;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs5_val_arr_ow8, helper::rle_runs5_len_arr_ow8, helper::rle_runs5_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_34(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 34;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs5_val_arr_ow16, helper::rle_runs5_len_arr_ow16, helper::rle_runs5_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_35(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 35;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs5_val_arr_ow16, helper::rle_runs5_len_arr_ow16, helper::rle_runs5_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_36(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 36;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs5_val_arr_ow32, helper::rle_runs5_len_arr_ow32, helper::rle_runs5_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_37(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 37;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs5_val_arr_ow32, helper::rle_runs5_len_arr_ow32, helper::rle_runs5_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_38(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 38;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs5_val_arr_ow64, helper::rle_runs5_len_arr_ow64, helper::rle_runs5_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_39(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 39;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs5_val_arr_ow64, helper::rle_runs5_len_arr_ow64, helper::rle_runs5_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_40(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 40;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs6_val_arr_ow8, helper::rle_runs6_len_arr_ow8, helper::rle_runs6_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_41(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 41;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs6_val_arr_ow8, helper::rle_runs6_len_arr_ow8, helper::rle_runs6_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_42(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 42;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs6_val_arr_ow16, helper::rle_runs6_len_arr_ow16, helper::rle_runs6_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_43(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 43;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs6_val_arr_ow16, helper::rle_runs6_len_arr_ow16, helper::rle_runs6_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_44(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 44;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs6_val_arr_ow32, helper::rle_runs6_len_arr_ow32, helper::rle_runs6_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_45(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 45;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs6_val_arr_ow32, helper::rle_runs6_len_arr_ow32, helper::rle_runs6_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_46(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 46;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs6_val_arr_ow64, helper::rle_runs6_len_arr_ow64, helper::rle_runs6_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_47(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 47;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs6_val_arr_ow64, helper::rle_runs6_len_arr_ow64, helper::rle_runs6_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_48(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 48;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs7_val_arr_ow8, helper::rle_runs7_len_arr_ow8, helper::rle_runs7_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_49(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 49;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs7_val_arr_ow8, helper::rle_runs7_len_arr_ow8, helper::rle_runs7_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_50(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 50;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs7_val_arr_ow16, helper::rle_runs7_len_arr_ow16, helper::rle_runs7_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_51(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 51;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs7_val_arr_ow16, helper::rle_runs7_len_arr_ow16, helper::rle_runs7_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_52(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 52;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs7_val_arr_ow32, helper::rle_runs7_len_arr_ow32, helper::rle_runs7_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_53(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 53;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs7_val_arr_ow32, helper::rle_runs7_len_arr_ow32, helper::rle_runs7_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_54(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 54;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs7_val_arr_ow64, helper::rle_runs7_len_arr_ow64, helper::rle_runs7_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_55(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 55;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs7_val_arr_ow64, helper::rle_runs7_len_arr_ow64, helper::rle_runs7_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_56(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 56;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs8_val_arr_ow8, helper::rle_runs8_len_arr_ow8, helper::rle_runs8_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_57(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 57;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs8_val_arr_ow8, helper::rle_runs8_len_arr_ow8, helper::rle_runs8_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_58(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 58;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs8_val_arr_ow16, helper::rle_runs8_len_arr_ow16, helper::rle_runs8_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_59(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 59;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs8_val_arr_ow16, helper::rle_runs8_len_arr_ow16, helper::rle_runs8_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_60(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 60;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs8_val_arr_ow32, helper::rle_runs8_len_arr_ow32, helper::rle_runs8_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_61(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 61;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs8_val_arr_ow32, helper::rle_runs8_len_arr_ow32, helper::rle_runs8_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_62(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 62;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs8_val_arr_ow64, helper::rle_runs8_len_arr_ow64, helper::rle_runs8_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_63(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 63;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs8_val_arr_ow64, helper::rle_runs8_len_arr_ow64, helper::rle_runs8_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_64(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 64;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs9_val_arr_ow8, helper::rle_runs9_len_arr_ow8, helper::rle_runs9_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_65(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 65;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs9_val_arr_ow8, helper::rle_runs9_len_arr_ow8, helper::rle_runs9_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_66(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 66;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs9_val_arr_ow16, helper::rle_runs9_len_arr_ow16, helper::rle_runs9_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_67(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 67;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs9_val_arr_ow16, helper::rle_runs9_len_arr_ow16, helper::rle_runs9_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_68(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 68;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs9_val_arr_ow32, helper::rle_runs9_len_arr_ow32, helper::rle_runs9_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_69(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 69;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs9_val_arr_ow32, helper::rle_runs9_len_arr_ow32, helper::rle_runs9_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_70(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 70;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs9_val_arr_ow64, helper::rle_runs9_len_arr_ow64, helper::rle_runs9_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_71(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 71;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs9_val_arr_ow64, helper::rle_runs9_len_arr_ow64, helper::rle_runs9_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_72(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 72;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs10_val_arr_ow8, helper::rle_runs10_len_arr_ow8, helper::rle_runs10_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_73(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 73;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs10_val_arr_ow8, helper::rle_runs10_len_arr_ow8, helper::rle_runs10_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_74(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 74;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs10_val_arr_ow16, helper::rle_runs10_len_arr_ow16, helper::rle_runs10_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_75(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 75;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs10_val_arr_ow16, helper::rle_runs10_len_arr_ow16, helper::rle_runs10_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_76(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 76;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs10_val_arr_ow32, helper::rle_runs10_len_arr_ow32, helper::rle_runs10_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_77(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 77;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs10_val_arr_ow32, helper::rle_runs10_len_arr_ow32, helper::rle_runs10_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_78(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 78;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs10_val_arr_ow64, helper::rle_runs10_len_arr_ow64, helper::rle_runs10_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_79(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 79;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs10_val_arr_ow64, helper::rle_runs10_len_arr_ow64, helper::rle_runs10_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_80(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 80;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs11_val_arr_ow8, helper::rle_runs11_len_arr_ow8, helper::rle_runs11_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_81(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 81;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs11_val_arr_ow8, helper::rle_runs11_len_arr_ow8, helper::rle_runs11_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_82(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 82;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs11_val_arr_ow16, helper::rle_runs11_len_arr_ow16, helper::rle_runs11_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_83(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 83;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs11_val_arr_ow16, helper::rle_runs11_len_arr_ow16, helper::rle_runs11_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_84(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 84;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs11_val_arr_ow32, helper::rle_runs11_len_arr_ow32, helper::rle_runs11_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_85(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 85;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs11_val_arr_ow32, helper::rle_runs11_len_arr_ow32, helper::rle_runs11_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_86(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 86;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs11_val_arr_ow64, helper::rle_runs11_len_arr_ow64, helper::rle_runs11_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_87(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 87;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs11_val_arr_ow64, helper::rle_runs11_len_arr_ow64, helper::rle_runs11_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_88(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 88;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs12_val_arr_ow8, helper::rle_runs12_len_arr_ow8, helper::rle_runs12_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_89(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 89;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs12_val_arr_ow8, helper::rle_runs12_len_arr_ow8, helper::rle_runs12_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_90(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 90;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs12_val_arr_ow16, helper::rle_runs12_len_arr_ow16, helper::rle_runs12_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_91(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 91;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs12_val_arr_ow16, helper::rle_runs12_len_arr_ow16, helper::rle_runs12_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_92(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 92;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs12_val_arr_ow32, helper::rle_runs12_len_arr_ow32, helper::rle_runs12_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_93(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 93;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs12_val_arr_ow32, helper::rle_runs12_len_arr_ow32, helper::rle_runs12_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_94(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 94;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs12_val_arr_ow64, helper::rle_runs12_len_arr_ow64, helper::rle_runs12_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_95(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 95;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs12_val_arr_ow64, helper::rle_runs12_len_arr_ow64, helper::rle_runs12_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_96(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 96;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs13_val_arr_ow8, helper::rle_runs13_len_arr_ow8, helper::rle_runs13_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_97(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 97;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs13_val_arr_ow8, helper::rle_runs13_len_arr_ow8, helper::rle_runs13_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_98(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 98;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs13_val_arr_ow16, helper::rle_runs13_len_arr_ow16, helper::rle_runs13_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_99(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 99;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs13_val_arr_ow16, helper::rle_runs13_len_arr_ow16, helper::rle_runs13_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_100(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 100;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs13_val_arr_ow32, helper::rle_runs13_len_arr_ow32, helper::rle_runs13_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_101(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 101;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs13_val_arr_ow32, helper::rle_runs13_len_arr_ow32, helper::rle_runs13_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_102(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 102;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs13_val_arr_ow64, helper::rle_runs13_len_arr_ow64, helper::rle_runs13_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_103(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 103;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs13_val_arr_ow64, helper::rle_runs13_len_arr_ow64, helper::rle_runs13_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_104(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 104;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs14_val_arr_ow8, helper::rle_runs14_len_arr_ow8, helper::rle_runs14_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_105(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 105;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs14_val_arr_ow8, helper::rle_runs14_len_arr_ow8, helper::rle_runs14_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_106(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 106;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs14_val_arr_ow16, helper::rle_runs14_len_arr_ow16, helper::rle_runs14_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_107(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 107;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs14_val_arr_ow16, helper::rle_runs14_len_arr_ow16, helper::rle_runs14_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_108(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 108;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs14_val_arr_ow32, helper::rle_runs14_len_arr_ow32, helper::rle_runs14_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_109(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 109;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs14_val_arr_ow32, helper::rle_runs14_len_arr_ow32, helper::rle_runs14_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_110(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 110;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs14_val_arr_ow64, helper::rle_runs14_len_arr_ow64, helper::rle_runs14_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_111(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 111;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs14_val_arr_ow64, helper::rle_runs14_len_arr_ow64, helper::rle_runs14_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_112(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 112;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs15_val_arr_ow8, helper::rle_runs15_len_arr_ow8, helper::rle_runs15_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_113(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 113;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs15_val_arr_ow8, helper::rle_runs15_len_arr_ow8, helper::rle_runs15_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_114(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 114;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs15_val_arr_ow16, helper::rle_runs15_len_arr_ow16, helper::rle_runs15_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_115(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 115;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs15_val_arr_ow16, helper::rle_runs15_len_arr_ow16, helper::rle_runs15_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_116(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 116;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs15_val_arr_ow32, helper::rle_runs15_len_arr_ow32, helper::rle_runs15_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_117(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 117;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs15_val_arr_ow32, helper::rle_runs15_len_arr_ow32, helper::rle_runs15_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_118(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 118;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs15_val_arr_ow64, helper::rle_runs15_len_arr_ow64, helper::rle_runs15_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_119(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 119;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs15_val_arr_ow64, helper::rle_runs15_len_arr_ow64, helper::rle_runs15_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_120(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 120;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs16_val_arr_ow8, helper::rle_runs16_len_arr_ow8, helper::rle_runs16_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_121(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 121;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs16_val_arr_ow8, helper::rle_runs16_len_arr_ow8, helper::rle_runs16_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_122(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 122;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs16_val_arr_ow16, helper::rle_runs16_len_arr_ow16, helper::rle_runs16_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_123(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 123;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs16_val_arr_ow16, helper::rle_runs16_len_arr_ow16, helper::rle_runs16_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_124(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 124;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs16_val_arr_ow32, helper::rle_runs16_len_arr_ow32, helper::rle_runs16_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_125(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 125;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs16_val_arr_ow32, helper::rle_runs16_len_arr_ow32, helper::rle_runs16_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_126(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 126;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs16_val_arr_ow64, helper::rle_runs16_len_arr_ow64, helper::rle_runs16_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_127(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 127;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs16_val_arr_ow64, helper::rle_runs16_len_arr_ow64, helper::rle_runs16_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_128(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 128;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs17_val_arr_ow8, helper::rle_runs17_len_arr_ow8, helper::rle_runs17_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_129(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 129;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs17_val_arr_ow8, helper::rle_runs17_len_arr_ow8, helper::rle_runs17_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_130(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 130;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs17_val_arr_ow16, helper::rle_runs17_len_arr_ow16, helper::rle_runs17_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_131(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 131;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs17_val_arr_ow16, helper::rle_runs17_len_arr_ow16, helper::rle_runs17_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_132(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 132;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs17_val_arr_ow32, helper::rle_runs17_len_arr_ow32, helper::rle_runs17_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_133(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 133;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs17_val_arr_ow32, helper::rle_runs17_len_arr_ow32, helper::rle_runs17_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_134(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 134;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs17_val_arr_ow64, helper::rle_runs17_len_arr_ow64, helper::rle_runs17_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_135(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 135;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs17_val_arr_ow64, helper::rle_runs17_len_arr_ow64, helper::rle_runs17_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_136(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 136;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs18_val_arr_ow8, helper::rle_runs18_len_arr_ow8, helper::rle_runs18_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_137(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 137;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs18_val_arr_ow8, helper::rle_runs18_len_arr_ow8, helper::rle_runs18_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_138(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 138;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs18_val_arr_ow16, helper::rle_runs18_len_arr_ow16, helper::rle_runs18_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_139(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 139;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs18_val_arr_ow16, helper::rle_runs18_len_arr_ow16, helper::rle_runs18_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_140(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 140;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs18_val_arr_ow32, helper::rle_runs18_len_arr_ow32, helper::rle_runs18_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_141(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 141;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs18_val_arr_ow32, helper::rle_runs18_len_arr_ow32, helper::rle_runs18_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_142(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 142;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs18_val_arr_ow64, helper::rle_runs18_len_arr_ow64, helper::rle_runs18_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_143(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 143;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs18_val_arr_ow64, helper::rle_runs18_len_arr_ow64, helper::rle_runs18_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_144(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 144;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs19_val_arr_ow8, helper::rle_runs19_len_arr_ow8, helper::rle_runs19_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_145(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 145;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs19_val_arr_ow8, helper::rle_runs19_len_arr_ow8, helper::rle_runs19_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_146(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 146;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs19_val_arr_ow16, helper::rle_runs19_len_arr_ow16, helper::rle_runs19_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_147(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 147;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs19_val_arr_ow16, helper::rle_runs19_len_arr_ow16, helper::rle_runs19_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_148(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 148;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs19_val_arr_ow32, helper::rle_runs19_len_arr_ow32, helper::rle_runs19_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_149(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 149;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs19_val_arr_ow32, helper::rle_runs19_len_arr_ow32, helper::rle_runs19_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_150(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 150;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs19_val_arr_ow64, helper::rle_runs19_len_arr_ow64, helper::rle_runs19_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_151(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 151;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs19_val_arr_ow64, helper::rle_runs19_len_arr_ow64, helper::rle_runs19_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_152(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 152;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs20_val_arr_ow8, helper::rle_runs20_len_arr_ow8, helper::rle_runs20_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_153(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 153;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs20_val_arr_ow8, helper::rle_runs20_len_arr_ow8, helper::rle_runs20_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_154(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 154;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs20_val_arr_ow16, helper::rle_runs20_len_arr_ow16, helper::rle_runs20_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_155(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 155;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs20_val_arr_ow16, helper::rle_runs20_len_arr_ow16, helper::rle_runs20_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_156(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 156;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs20_val_arr_ow32, helper::rle_runs20_len_arr_ow32, helper::rle_runs20_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_157(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 157;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs20_val_arr_ow32, helper::rle_runs20_len_arr_ow32, helper::rle_runs20_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_158(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 158;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs20_val_arr_ow64, helper::rle_runs20_len_arr_ow64, helper::rle_runs20_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_159(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 159;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs20_val_arr_ow64, helper::rle_runs20_len_arr_ow64, helper::rle_runs20_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_160(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 160;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs21_val_arr_ow8, helper::rle_runs21_len_arr_ow8, helper::rle_runs21_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_161(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 161;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs21_val_arr_ow8, helper::rle_runs21_len_arr_ow8, helper::rle_runs21_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_162(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 162;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs21_val_arr_ow16, helper::rle_runs21_len_arr_ow16, helper::rle_runs21_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_163(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 163;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs21_val_arr_ow16, helper::rle_runs21_len_arr_ow16, helper::rle_runs21_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_164(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 164;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs21_val_arr_ow32, helper::rle_runs21_len_arr_ow32, helper::rle_runs21_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_165(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 165;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs21_val_arr_ow32, helper::rle_runs21_len_arr_ow32, helper::rle_runs21_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_166(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 166;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs21_val_arr_ow64, helper::rle_runs21_len_arr_ow64, helper::rle_runs21_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_167(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 167;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs21_val_arr_ow64, helper::rle_runs21_len_arr_ow64, helper::rle_runs21_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_168(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 168;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs22_val_arr_ow8, helper::rle_runs22_len_arr_ow8, helper::rle_runs22_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_169(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 169;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs22_val_arr_ow8, helper::rle_runs22_len_arr_ow8, helper::rle_runs22_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_170(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 170;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs22_val_arr_ow16, helper::rle_runs22_len_arr_ow16, helper::rle_runs22_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_171(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 171;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs22_val_arr_ow16, helper::rle_runs22_len_arr_ow16, helper::rle_runs22_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_172(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 172;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs22_val_arr_ow32, helper::rle_runs22_len_arr_ow32, helper::rle_runs22_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_173(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 173;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs22_val_arr_ow32, helper::rle_runs22_len_arr_ow32, helper::rle_runs22_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_174(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 174;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs22_val_arr_ow64, helper::rle_runs22_len_arr_ow64, helper::rle_runs22_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_175(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 175;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs22_val_arr_ow64, helper::rle_runs22_len_arr_ow64, helper::rle_runs22_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_176(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 176;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs23_val_arr_ow8, helper::rle_runs23_len_arr_ow8, helper::rle_runs23_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_177(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 177;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs23_val_arr_ow8, helper::rle_runs23_len_arr_ow8, helper::rle_runs23_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_178(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 178;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs23_val_arr_ow16, helper::rle_runs23_len_arr_ow16, helper::rle_runs23_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_179(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 179;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs23_val_arr_ow16, helper::rle_runs23_len_arr_ow16, helper::rle_runs23_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_180(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 180;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs23_val_arr_ow32, helper::rle_runs23_len_arr_ow32, helper::rle_runs23_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_181(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 181;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs23_val_arr_ow32, helper::rle_runs23_len_arr_ow32, helper::rle_runs23_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_182(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 182;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs23_val_arr_ow64, helper::rle_runs23_len_arr_ow64, helper::rle_runs23_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_183(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 183;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs23_val_arr_ow64, helper::rle_runs23_len_arr_ow64, helper::rle_runs23_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_184(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 184;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs24_val_arr_ow8, helper::rle_runs24_len_arr_ow8, helper::rle_runs24_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_185(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 185;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs24_val_arr_ow8, helper::rle_runs24_len_arr_ow8, helper::rle_runs24_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_186(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 186;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs24_val_arr_ow16, helper::rle_runs24_len_arr_ow16, helper::rle_runs24_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_187(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 187;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs24_val_arr_ow16, helper::rle_runs24_len_arr_ow16, helper::rle_runs24_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_188(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 188;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs24_val_arr_ow32, helper::rle_runs24_len_arr_ow32, helper::rle_runs24_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_189(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 189;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs24_val_arr_ow32, helper::rle_runs24_len_arr_ow32, helper::rle_runs24_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_190(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 190;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs24_val_arr_ow64, helper::rle_runs24_len_arr_ow64, helper::rle_runs24_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_191(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 191;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs24_val_arr_ow64, helper::rle_runs24_len_arr_ow64, helper::rle_runs24_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_192(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 192;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs25_val_arr_ow8, helper::rle_runs25_len_arr_ow8, helper::rle_runs25_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_193(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 193;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs25_val_arr_ow8, helper::rle_runs25_len_arr_ow8, helper::rle_runs25_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_194(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 194;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs25_val_arr_ow16, helper::rle_runs25_len_arr_ow16, helper::rle_runs25_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_195(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 195;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs25_val_arr_ow16, helper::rle_runs25_len_arr_ow16, helper::rle_runs25_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_196(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 196;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs25_val_arr_ow32, helper::rle_runs25_len_arr_ow32, helper::rle_runs25_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_197(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 197;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs25_val_arr_ow32, helper::rle_runs25_len_arr_ow32, helper::rle_runs25_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_198(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 198;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs25_val_arr_ow64, helper::rle_runs25_len_arr_ow64, helper::rle_runs25_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_199(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 199;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs25_val_arr_ow64, helper::rle_runs25_len_arr_ow64, helper::rle_runs25_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_200(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 200;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs26_val_arr_ow8, helper::rle_runs26_len_arr_ow8, helper::rle_runs26_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_201(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 201;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs26_val_arr_ow8, helper::rle_runs26_len_arr_ow8, helper::rle_runs26_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_202(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 202;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs26_val_arr_ow16, helper::rle_runs26_len_arr_ow16, helper::rle_runs26_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_203(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 203;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs26_val_arr_ow16, helper::rle_runs26_len_arr_ow16, helper::rle_runs26_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_204(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 204;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs26_val_arr_ow32, helper::rle_runs26_len_arr_ow32, helper::rle_runs26_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_205(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 205;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs26_val_arr_ow32, helper::rle_runs26_len_arr_ow32, helper::rle_runs26_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_206(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 206;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs26_val_arr_ow64, helper::rle_runs26_len_arr_ow64, helper::rle_runs26_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_207(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 207;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs26_val_arr_ow64, helper::rle_runs26_len_arr_ow64, helper::rle_runs26_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_208(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 208;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs27_val_arr_ow8, helper::rle_runs27_len_arr_ow8, helper::rle_runs27_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_209(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 209;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs27_val_arr_ow8, helper::rle_runs27_len_arr_ow8, helper::rle_runs27_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_210(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 210;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs27_val_arr_ow16, helper::rle_runs27_len_arr_ow16, helper::rle_runs27_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_211(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 211;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs27_val_arr_ow16, helper::rle_runs27_len_arr_ow16, helper::rle_runs27_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_212(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 212;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs27_val_arr_ow32, helper::rle_runs27_len_arr_ow32, helper::rle_runs27_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_213(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 213;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs27_val_arr_ow32, helper::rle_runs27_len_arr_ow32, helper::rle_runs27_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_214(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 214;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs27_val_arr_ow64, helper::rle_runs27_len_arr_ow64, helper::rle_runs27_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_215(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 215;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs27_val_arr_ow64, helper::rle_runs27_len_arr_ow64, helper::rle_runs27_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_216(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 216;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs28_val_arr_ow8, helper::rle_runs28_len_arr_ow8, helper::rle_runs28_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_217(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 217;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs28_val_arr_ow8, helper::rle_runs28_len_arr_ow8, helper::rle_runs28_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_218(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 218;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs28_val_arr_ow16, helper::rle_runs28_len_arr_ow16, helper::rle_runs28_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_219(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 219;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs28_val_arr_ow16, helper::rle_runs28_len_arr_ow16, helper::rle_runs28_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_220(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 220;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs28_val_arr_ow32, helper::rle_runs28_len_arr_ow32, helper::rle_runs28_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_221(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 221;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs28_val_arr_ow32, helper::rle_runs28_len_arr_ow32, helper::rle_runs28_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_222(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 222;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs28_val_arr_ow64, helper::rle_runs28_len_arr_ow64, helper::rle_runs28_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_223(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 223;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs28_val_arr_ow64, helper::rle_runs28_len_arr_ow64, helper::rle_runs28_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_224(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 224;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs29_val_arr_ow8, helper::rle_runs29_len_arr_ow8, helper::rle_runs29_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_225(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 225;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs29_val_arr_ow8, helper::rle_runs29_len_arr_ow8, helper::rle_runs29_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_226(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 226;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs29_val_arr_ow16, helper::rle_runs29_len_arr_ow16, helper::rle_runs29_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_227(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 227;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs29_val_arr_ow16, helper::rle_runs29_len_arr_ow16, helper::rle_runs29_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_228(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 228;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs29_val_arr_ow32, helper::rle_runs29_len_arr_ow32, helper::rle_runs29_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_229(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 229;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs29_val_arr_ow32, helper::rle_runs29_len_arr_ow32, helper::rle_runs29_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_230(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 230;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs29_val_arr_ow64, helper::rle_runs29_len_arr_ow64, helper::rle_runs29_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_231(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 231;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs29_val_arr_ow64, helper::rle_runs29_len_arr_ow64, helper::rle_runs29_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_232(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 232;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs30_val_arr_ow8, helper::rle_runs30_len_arr_ow8, helper::rle_runs30_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_233(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 233;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs30_val_arr_ow8, helper::rle_runs30_len_arr_ow8, helper::rle_runs30_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_234(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 234;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs30_val_arr_ow16, helper::rle_runs30_len_arr_ow16, helper::rle_runs30_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_235(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 235;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs30_val_arr_ow16, helper::rle_runs30_len_arr_ow16, helper::rle_runs30_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_236(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 236;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs30_val_arr_ow32, helper::rle_runs30_len_arr_ow32, helper::rle_runs30_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_237(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 237;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs30_val_arr_ow32, helper::rle_runs30_len_arr_ow32, helper::rle_runs30_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_238(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 238;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs30_val_arr_ow64, helper::rle_runs30_len_arr_ow64, helper::rle_runs30_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_239(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 239;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs30_val_arr_ow64, helper::rle_runs30_len_arr_ow64, helper::rle_runs30_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_240(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 240;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs31_val_arr_ow8, helper::rle_runs31_len_arr_ow8, helper::rle_runs31_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_241(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 241;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs31_val_arr_ow8, helper::rle_runs31_len_arr_ow8, helper::rle_runs31_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_242(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 242;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs31_val_arr_ow16, helper::rle_runs31_len_arr_ow16, helper::rle_runs31_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_243(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 243;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs31_val_arr_ow16, helper::rle_runs31_len_arr_ow16, helper::rle_runs31_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_244(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 244;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs31_val_arr_ow32, helper::rle_runs31_len_arr_ow32, helper::rle_runs31_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_245(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 245;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs31_val_arr_ow32, helper::rle_runs31_len_arr_ow32, helper::rle_runs31_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_246(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 246;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs31_val_arr_ow64, helper::rle_runs31_len_arr_ow64, helper::rle_runs31_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_247(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 247;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs31_val_arr_ow64, helper::rle_runs31_len_arr_ow64, helper::rle_runs31_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_248(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 248;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs32_val_arr_ow8, helper::rle_runs32_len_arr_ow8, helper::rle_runs32_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_249(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 249;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs32_val_arr_ow8, helper::rle_runs32_len_arr_ow8, helper::rle_runs32_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_250(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 250;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs32_val_arr_ow16, helper::rle_runs32_len_arr_ow16, helper::rle_runs32_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_251(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 251;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs32_val_arr_ow16, helper::rle_runs32_len_arr_ow16, helper::rle_runs32_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_252(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 252;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs32_val_arr_ow32, helper::rle_runs32_len_arr_ow32, helper::rle_runs32_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_253(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 253;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs32_val_arr_ow32, helper::rle_runs32_len_arr_ow32, helper::rle_runs32_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_254(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 254;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs32_val_arr_ow64, helper::rle_runs32_len_arr_ow64, helper::rle_runs32_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_255(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 255;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs32_val_arr_ow64, helper::rle_runs32_len_arr_ow64, helper::rle_runs32_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_256(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 256;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs33_val_arr_ow8, helper::rle_runs33_len_arr_ow8, helper::rle_runs33_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_257(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 257;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs33_val_arr_ow8, helper::rle_runs33_len_arr_ow8, helper::rle_runs33_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_258(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 258;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs33_val_arr_ow16, helper::rle_runs33_len_arr_ow16, helper::rle_runs33_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_259(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 259;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs33_val_arr_ow16, helper::rle_runs33_len_arr_ow16, helper::rle_runs33_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_260(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 260;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs33_val_arr_ow32, helper::rle_runs33_len_arr_ow32, helper::rle_runs33_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_261(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 261;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs33_val_arr_ow32, helper::rle_runs33_len_arr_ow32, helper::rle_runs33_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_262(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 262;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs33_val_arr_ow64, helper::rle_runs33_len_arr_ow64, helper::rle_runs33_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_263(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 263;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs33_val_arr_ow64, helper::rle_runs33_len_arr_ow64, helper::rle_runs33_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_264(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 264;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs34_val_arr_ow8, helper::rle_runs34_len_arr_ow8, helper::rle_runs34_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_265(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 265;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs34_val_arr_ow8, helper::rle_runs34_len_arr_ow8, helper::rle_runs34_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_266(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 266;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs34_val_arr_ow16, helper::rle_runs34_len_arr_ow16, helper::rle_runs34_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_267(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 267;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs34_val_arr_ow16, helper::rle_runs34_len_arr_ow16, helper::rle_runs34_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_268(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 268;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs34_val_arr_ow32, helper::rle_runs34_len_arr_ow32, helper::rle_runs34_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_269(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 269;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs34_val_arr_ow32, helper::rle_runs34_len_arr_ow32, helper::rle_runs34_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_270(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 270;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs34_val_arr_ow64, helper::rle_runs34_len_arr_ow64, helper::rle_runs34_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_271(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 271;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs34_val_arr_ow64, helper::rle_runs34_len_arr_ow64, helper::rle_runs34_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_272(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 272;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs35_val_arr_ow8, helper::rle_runs35_len_arr_ow8, helper::rle_runs35_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_273(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 273;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs35_val_arr_ow8, helper::rle_runs35_len_arr_ow8, helper::rle_runs35_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_274(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 274;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs35_val_arr_ow16, helper::rle_runs35_len_arr_ow16, helper::rle_runs35_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_275(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 275;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs35_val_arr_ow16, helper::rle_runs35_len_arr_ow16, helper::rle_runs35_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_276(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 276;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs35_val_arr_ow32, helper::rle_runs35_len_arr_ow32, helper::rle_runs35_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_277(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 277;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs35_val_arr_ow32, helper::rle_runs35_len_arr_ow32, helper::rle_runs35_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_278(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 278;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs35_val_arr_ow64, helper::rle_runs35_len_arr_ow64, helper::rle_runs35_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_279(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 279;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs35_val_arr_ow64, helper::rle_runs35_len_arr_ow64, helper::rle_runs35_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_280(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 280;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs36_val_arr_ow8, helper::rle_runs36_len_arr_ow8, helper::rle_runs36_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_281(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 281;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs36_val_arr_ow8, helper::rle_runs36_len_arr_ow8, helper::rle_runs36_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_282(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 282;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs36_val_arr_ow16, helper::rle_runs36_len_arr_ow16, helper::rle_runs36_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_283(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 283;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs36_val_arr_ow16, helper::rle_runs36_len_arr_ow16, helper::rle_runs36_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_284(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 284;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs36_val_arr_ow32, helper::rle_runs36_len_arr_ow32, helper::rle_runs36_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_285(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 285;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs36_val_arr_ow32, helper::rle_runs36_len_arr_ow32, helper::rle_runs36_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_286(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 286;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs36_val_arr_ow64, helper::rle_runs36_len_arr_ow64, helper::rle_runs36_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_287(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 287;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs36_val_arr_ow64, helper::rle_runs36_len_arr_ow64, helper::rle_runs36_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_288(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 288;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs37_val_arr_ow8, helper::rle_runs37_len_arr_ow8, helper::rle_runs37_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_289(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 289;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs37_val_arr_ow8, helper::rle_runs37_len_arr_ow8, helper::rle_runs37_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_290(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 290;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs37_val_arr_ow16, helper::rle_runs37_len_arr_ow16, helper::rle_runs37_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_291(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 291;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs37_val_arr_ow16, helper::rle_runs37_len_arr_ow16, helper::rle_runs37_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_292(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 292;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs37_val_arr_ow32, helper::rle_runs37_len_arr_ow32, helper::rle_runs37_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_293(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 293;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs37_val_arr_ow32, helper::rle_runs37_len_arr_ow32, helper::rle_runs37_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_294(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 294;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs37_val_arr_ow64, helper::rle_runs37_len_arr_ow64, helper::rle_runs37_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_295(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 295;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs37_val_arr_ow64, helper::rle_runs37_len_arr_ow64, helper::rle_runs37_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_296(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 296;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs38_val_arr_ow8, helper::rle_runs38_len_arr_ow8, helper::rle_runs38_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_297(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 297;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs38_val_arr_ow8, helper::rle_runs38_len_arr_ow8, helper::rle_runs38_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_298(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 298;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs38_val_arr_ow16, helper::rle_runs38_len_arr_ow16, helper::rle_runs38_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_299(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 299;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs38_val_arr_ow16, helper::rle_runs38_len_arr_ow16, helper::rle_runs38_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_300(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 300;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs38_val_arr_ow32, helper::rle_runs38_len_arr_ow32, helper::rle_runs38_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_301(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 301;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs38_val_arr_ow32, helper::rle_runs38_len_arr_ow32, helper::rle_runs38_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_302(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 302;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs38_val_arr_ow64, helper::rle_runs38_len_arr_ow64, helper::rle_runs38_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_303(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 303;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs38_val_arr_ow64, helper::rle_runs38_len_arr_ow64, helper::rle_runs38_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_304(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 304;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs39_val_arr_ow8, helper::rle_runs39_len_arr_ow8, helper::rle_runs39_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_305(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 305;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs39_val_arr_ow8, helper::rle_runs39_len_arr_ow8, helper::rle_runs39_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_306(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 306;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs39_val_arr_ow16, helper::rle_runs39_len_arr_ow16, helper::rle_runs39_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_307(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 307;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs39_val_arr_ow16, helper::rle_runs39_len_arr_ow16, helper::rle_runs39_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_308(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 308;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs39_val_arr_ow32, helper::rle_runs39_len_arr_ow32, helper::rle_runs39_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_309(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 309;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs39_val_arr_ow32, helper::rle_runs39_len_arr_ow32, helper::rle_runs39_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_310(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 310;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs39_val_arr_ow64, helper::rle_runs39_len_arr_ow64, helper::rle_runs39_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_311(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 311;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs39_val_arr_ow64, helper::rle_runs39_len_arr_ow64, helper::rle_runs39_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_312(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 312;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs40_val_arr_ow8, helper::rle_runs40_len_arr_ow8, helper::rle_runs40_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_313(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 313;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs40_val_arr_ow8, helper::rle_runs40_len_arr_ow8, helper::rle_runs40_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_314(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 314;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs40_val_arr_ow16, helper::rle_runs40_len_arr_ow16, helper::rle_runs40_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_315(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 315;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs40_val_arr_ow16, helper::rle_runs40_len_arr_ow16, helper::rle_runs40_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_316(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 316;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs40_val_arr_ow32, helper::rle_runs40_len_arr_ow32, helper::rle_runs40_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_317(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 317;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs40_val_arr_ow32, helper::rle_runs40_len_arr_ow32, helper::rle_runs40_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_318(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 318;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs40_val_arr_ow64, helper::rle_runs40_len_arr_ow64, helper::rle_runs40_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_319(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 319;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs40_val_arr_ow64, helper::rle_runs40_len_arr_ow64, helper::rle_runs40_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_320(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 320;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs41_val_arr_ow8, helper::rle_runs41_len_arr_ow8, helper::rle_runs41_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_321(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 321;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs41_val_arr_ow8, helper::rle_runs41_len_arr_ow8, helper::rle_runs41_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_322(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 322;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs41_val_arr_ow16, helper::rle_runs41_len_arr_ow16, helper::rle_runs41_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_323(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 323;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs41_val_arr_ow16, helper::rle_runs41_len_arr_ow16, helper::rle_runs41_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_324(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 324;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs41_val_arr_ow32, helper::rle_runs41_len_arr_ow32, helper::rle_runs41_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_325(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 325;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs41_val_arr_ow32, helper::rle_runs41_len_arr_ow32, helper::rle_runs41_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_326(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 326;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs41_val_arr_ow64, helper::rle_runs41_len_arr_ow64, helper::rle_runs41_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_327(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 327;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs41_val_arr_ow64, helper::rle_runs41_len_arr_ow64, helper::rle_runs41_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_328(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 328;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs42_val_arr_ow8, helper::rle_runs42_len_arr_ow8, helper::rle_runs42_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_329(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 329;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs42_val_arr_ow8, helper::rle_runs42_len_arr_ow8, helper::rle_runs42_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_330(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 330;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs42_val_arr_ow16, helper::rle_runs42_len_arr_ow16, helper::rle_runs42_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_331(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 331;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs42_val_arr_ow16, helper::rle_runs42_len_arr_ow16, helper::rle_runs42_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_332(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 332;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs42_val_arr_ow32, helper::rle_runs42_len_arr_ow32, helper::rle_runs42_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_333(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 333;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs42_val_arr_ow32, helper::rle_runs42_len_arr_ow32, helper::rle_runs42_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_334(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 334;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs42_val_arr_ow64, helper::rle_runs42_len_arr_ow64, helper::rle_runs42_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_335(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 335;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs42_val_arr_ow64, helper::rle_runs42_len_arr_ow64, helper::rle_runs42_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_336(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 336;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs43_val_arr_ow8, helper::rle_runs43_len_arr_ow8, helper::rle_runs43_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_337(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 337;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs43_val_arr_ow8, helper::rle_runs43_len_arr_ow8, helper::rle_runs43_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_338(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 338;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs43_val_arr_ow16, helper::rle_runs43_len_arr_ow16, helper::rle_runs43_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_339(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 339;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs43_val_arr_ow16, helper::rle_runs43_len_arr_ow16, helper::rle_runs43_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_340(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 340;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs43_val_arr_ow32, helper::rle_runs43_len_arr_ow32, helper::rle_runs43_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_341(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 341;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs43_val_arr_ow32, helper::rle_runs43_len_arr_ow32, helper::rle_runs43_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_342(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 342;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs43_val_arr_ow64, helper::rle_runs43_len_arr_ow64, helper::rle_runs43_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_343(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 343;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs43_val_arr_ow64, helper::rle_runs43_len_arr_ow64, helper::rle_runs43_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_344(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 344;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs44_val_arr_ow8, helper::rle_runs44_len_arr_ow8, helper::rle_runs44_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_345(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 345;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs44_val_arr_ow8, helper::rle_runs44_len_arr_ow8, helper::rle_runs44_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_346(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 346;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs44_val_arr_ow16, helper::rle_runs44_len_arr_ow16, helper::rle_runs44_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_347(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 347;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs44_val_arr_ow16, helper::rle_runs44_len_arr_ow16, helper::rle_runs44_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_348(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 348;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs44_val_arr_ow32, helper::rle_runs44_len_arr_ow32, helper::rle_runs44_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_349(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 349;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs44_val_arr_ow32, helper::rle_runs44_len_arr_ow32, helper::rle_runs44_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_350(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 350;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs44_val_arr_ow64, helper::rle_runs44_len_arr_ow64, helper::rle_runs44_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_351(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 351;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs44_val_arr_ow64, helper::rle_runs44_len_arr_ow64, helper::rle_runs44_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_352(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 352;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs45_val_arr_ow8, helper::rle_runs45_len_arr_ow8, helper::rle_runs45_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_353(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 353;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs45_val_arr_ow8, helper::rle_runs45_len_arr_ow8, helper::rle_runs45_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_354(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 354;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs45_val_arr_ow16, helper::rle_runs45_len_arr_ow16, helper::rle_runs45_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_355(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 355;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs45_val_arr_ow16, helper::rle_runs45_len_arr_ow16, helper::rle_runs45_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_356(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 356;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs45_val_arr_ow32, helper::rle_runs45_len_arr_ow32, helper::rle_runs45_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_357(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 357;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs45_val_arr_ow32, helper::rle_runs45_len_arr_ow32, helper::rle_runs45_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_358(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 358;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs45_val_arr_ow64, helper::rle_runs45_len_arr_ow64, helper::rle_runs45_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_359(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 359;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs45_val_arr_ow64, helper::rle_runs45_len_arr_ow64, helper::rle_runs45_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_360(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 360;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs46_val_arr_ow8, helper::rle_runs46_len_arr_ow8, helper::rle_runs46_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_361(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 361;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs46_val_arr_ow8, helper::rle_runs46_len_arr_ow8, helper::rle_runs46_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_362(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 362;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs46_val_arr_ow16, helper::rle_runs46_len_arr_ow16, helper::rle_runs46_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_363(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 363;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs46_val_arr_ow16, helper::rle_runs46_len_arr_ow16, helper::rle_runs46_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_364(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 364;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs46_val_arr_ow32, helper::rle_runs46_len_arr_ow32, helper::rle_runs46_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_365(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 365;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs46_val_arr_ow32, helper::rle_runs46_len_arr_ow32, helper::rle_runs46_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_366(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 366;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs46_val_arr_ow64, helper::rle_runs46_len_arr_ow64, helper::rle_runs46_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_367(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 367;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs46_val_arr_ow64, helper::rle_runs46_len_arr_ow64, helper::rle_runs46_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_368(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 368;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs47_val_arr_ow8, helper::rle_runs47_len_arr_ow8, helper::rle_runs47_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_369(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 369;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs47_val_arr_ow8, helper::rle_runs47_len_arr_ow8, helper::rle_runs47_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_370(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 370;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs47_val_arr_ow16, helper::rle_runs47_len_arr_ow16, helper::rle_runs47_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_371(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 371;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs47_val_arr_ow16, helper::rle_runs47_len_arr_ow16, helper::rle_runs47_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_372(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 372;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs47_val_arr_ow32, helper::rle_runs47_len_arr_ow32, helper::rle_runs47_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_373(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 373;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs47_val_arr_ow32, helper::rle_runs47_len_arr_ow32, helper::rle_runs47_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_374(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 374;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs47_val_arr_ow64, helper::rle_runs47_len_arr_ow64, helper::rle_runs47_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_375(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 375;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs47_val_arr_ow64, helper::rle_runs47_len_arr_ow64, helper::rle_runs47_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_376(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 376;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs48_val_arr_ow8, helper::rle_runs48_len_arr_ow8, helper::rle_runs48_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_377(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 377;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs48_val_arr_ow8, helper::rle_runs48_len_arr_ow8, helper::rle_runs48_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_378(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 378;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs48_val_arr_ow16, helper::rle_runs48_len_arr_ow16, helper::rle_runs48_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_379(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 379;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs48_val_arr_ow16, helper::rle_runs48_len_arr_ow16, helper::rle_runs48_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_380(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 380;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs48_val_arr_ow32, helper::rle_runs48_len_arr_ow32, helper::rle_runs48_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_381(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 381;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs48_val_arr_ow32, helper::rle_runs48_len_arr_ow32, helper::rle_runs48_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_382(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 382;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs48_val_arr_ow64, helper::rle_runs48_len_arr_ow64, helper::rle_runs48_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_383(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 383;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs48_val_arr_ow64, helper::rle_runs48_len_arr_ow64, helper::rle_runs48_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_384(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 384;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs49_val_arr_ow8, helper::rle_runs49_len_arr_ow8, helper::rle_runs49_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_385(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 385;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs49_val_arr_ow8, helper::rle_runs49_len_arr_ow8, helper::rle_runs49_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_386(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 386;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs49_val_arr_ow16, helper::rle_runs49_len_arr_ow16, helper::rle_runs49_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_387(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 387;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs49_val_arr_ow16, helper::rle_runs49_len_arr_ow16, helper::rle_runs49_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_388(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 388;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs49_val_arr_ow32, helper::rle_runs49_len_arr_ow32, helper::rle_runs49_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_389(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 389;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs49_val_arr_ow32, helper::rle_runs49_len_arr_ow32, helper::rle_runs49_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_390(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 390;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs49_val_arr_ow64, helper::rle_runs49_len_arr_ow64, helper::rle_runs49_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_391(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 391;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs49_val_arr_ow64, helper::rle_runs49_len_arr_ow64, helper::rle_runs49_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_392(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 392;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs50_val_arr_ow8, helper::rle_runs50_len_arr_ow8, helper::rle_runs50_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_393(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 393;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs50_val_arr_ow8, helper::rle_runs50_len_arr_ow8, helper::rle_runs50_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_394(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 394;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs50_val_arr_ow16, helper::rle_runs50_len_arr_ow16, helper::rle_runs50_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_395(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 395;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs50_val_arr_ow16, helper::rle_runs50_len_arr_ow16, helper::rle_runs50_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_396(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 396;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs50_val_arr_ow32, helper::rle_runs50_len_arr_ow32, helper::rle_runs50_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_397(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 397;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs50_val_arr_ow32, helper::rle_runs50_len_arr_ow32, helper::rle_runs50_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_398(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 398;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs50_val_arr_ow64, helper::rle_runs50_len_arr_ow64, helper::rle_runs50_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_399(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 399;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs50_val_arr_ow64, helper::rle_runs50_len_arr_ow64, helper::rle_runs50_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_400(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 400;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs51_val_arr_ow8, helper::rle_runs51_len_arr_ow8, helper::rle_runs51_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_401(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 401;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs51_val_arr_ow8, helper::rle_runs51_len_arr_ow8, helper::rle_runs51_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_402(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 402;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs51_val_arr_ow16, helper::rle_runs51_len_arr_ow16, helper::rle_runs51_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_403(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 403;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs51_val_arr_ow16, helper::rle_runs51_len_arr_ow16, helper::rle_runs51_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_404(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 404;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs51_val_arr_ow32, helper::rle_runs51_len_arr_ow32, helper::rle_runs51_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_405(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 405;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs51_val_arr_ow32, helper::rle_runs51_len_arr_ow32, helper::rle_runs51_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_406(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 406;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs51_val_arr_ow64, helper::rle_runs51_len_arr_ow64, helper::rle_runs51_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_407(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 407;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs51_val_arr_ow64, helper::rle_runs51_len_arr_ow64, helper::rle_runs51_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_408(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 408;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs52_val_arr_ow8, helper::rle_runs52_len_arr_ow8, helper::rle_runs52_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_409(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 409;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs52_val_arr_ow8, helper::rle_runs52_len_arr_ow8, helper::rle_runs52_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_410(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 410;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs52_val_arr_ow16, helper::rle_runs52_len_arr_ow16, helper::rle_runs52_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_411(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 411;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs52_val_arr_ow16, helper::rle_runs52_len_arr_ow16, helper::rle_runs52_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_412(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 412;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs52_val_arr_ow32, helper::rle_runs52_len_arr_ow32, helper::rle_runs52_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_413(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 413;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs52_val_arr_ow32, helper::rle_runs52_len_arr_ow32, helper::rle_runs52_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_414(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 414;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs52_val_arr_ow64, helper::rle_runs52_len_arr_ow64, helper::rle_runs52_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_415(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 415;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs52_val_arr_ow64, helper::rle_runs52_len_arr_ow64, helper::rle_runs52_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_416(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 416;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs53_val_arr_ow8, helper::rle_runs53_len_arr_ow8, helper::rle_runs53_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_417(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 417;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs53_val_arr_ow8, helper::rle_runs53_len_arr_ow8, helper::rle_runs53_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_418(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 418;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs53_val_arr_ow16, helper::rle_runs53_len_arr_ow16, helper::rle_runs53_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_419(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 419;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs53_val_arr_ow16, helper::rle_runs53_len_arr_ow16, helper::rle_runs53_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_420(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 420;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs53_val_arr_ow32, helper::rle_runs53_len_arr_ow32, helper::rle_runs53_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_421(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 421;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs53_val_arr_ow32, helper::rle_runs53_len_arr_ow32, helper::rle_runs53_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_422(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 422;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs53_val_arr_ow64, helper::rle_runs53_len_arr_ow64, helper::rle_runs53_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_423(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 423;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs53_val_arr_ow64, helper::rle_runs53_len_arr_ow64, helper::rle_runs53_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_424(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 424;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs54_val_arr_ow8, helper::rle_runs54_len_arr_ow8, helper::rle_runs54_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_425(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 425;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs54_val_arr_ow8, helper::rle_runs54_len_arr_ow8, helper::rle_runs54_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_426(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 426;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs54_val_arr_ow16, helper::rle_runs54_len_arr_ow16, helper::rle_runs54_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_427(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 427;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs54_val_arr_ow16, helper::rle_runs54_len_arr_ow16, helper::rle_runs54_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_428(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 428;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs54_val_arr_ow32, helper::rle_runs54_len_arr_ow32, helper::rle_runs54_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_429(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 429;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs54_val_arr_ow32, helper::rle_runs54_len_arr_ow32, helper::rle_runs54_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_430(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 430;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs54_val_arr_ow64, helper::rle_runs54_len_arr_ow64, helper::rle_runs54_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_431(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 431;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs54_val_arr_ow64, helper::rle_runs54_len_arr_ow64, helper::rle_runs54_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_432(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 432;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs55_val_arr_ow8, helper::rle_runs55_len_arr_ow8, helper::rle_runs55_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_433(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 433;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs55_val_arr_ow8, helper::rle_runs55_len_arr_ow8, helper::rle_runs55_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_434(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 434;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs55_val_arr_ow16, helper::rle_runs55_len_arr_ow16, helper::rle_runs55_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_435(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 435;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs55_val_arr_ow16, helper::rle_runs55_len_arr_ow16, helper::rle_runs55_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_436(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 436;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs55_val_arr_ow32, helper::rle_runs55_len_arr_ow32, helper::rle_runs55_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_437(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 437;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs55_val_arr_ow32, helper::rle_runs55_len_arr_ow32, helper::rle_runs55_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_438(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 438;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs55_val_arr_ow64, helper::rle_runs55_len_arr_ow64, helper::rle_runs55_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_439(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 439;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs55_val_arr_ow64, helper::rle_runs55_len_arr_ow64, helper::rle_runs55_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_440(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 440;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs56_val_arr_ow8, helper::rle_runs56_len_arr_ow8, helper::rle_runs56_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_441(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 441;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs56_val_arr_ow8, helper::rle_runs56_len_arr_ow8, helper::rle_runs56_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_442(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 442;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs56_val_arr_ow16, helper::rle_runs56_len_arr_ow16, helper::rle_runs56_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_443(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 443;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs56_val_arr_ow16, helper::rle_runs56_len_arr_ow16, helper::rle_runs56_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_444(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 444;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs56_val_arr_ow32, helper::rle_runs56_len_arr_ow32, helper::rle_runs56_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_445(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 445;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs56_val_arr_ow32, helper::rle_runs56_len_arr_ow32, helper::rle_runs56_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_446(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 446;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs56_val_arr_ow64, helper::rle_runs56_len_arr_ow64, helper::rle_runs56_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_447(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 447;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs56_val_arr_ow64, helper::rle_runs56_len_arr_ow64, helper::rle_runs56_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_448(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 448;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs57_val_arr_ow8, helper::rle_runs57_len_arr_ow8, helper::rle_runs57_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_449(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 449;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs57_val_arr_ow8, helper::rle_runs57_len_arr_ow8, helper::rle_runs57_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_450(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 450;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs57_val_arr_ow16, helper::rle_runs57_len_arr_ow16, helper::rle_runs57_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_451(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 451;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs57_val_arr_ow16, helper::rle_runs57_len_arr_ow16, helper::rle_runs57_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_452(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 452;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs57_val_arr_ow32, helper::rle_runs57_len_arr_ow32, helper::rle_runs57_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_453(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 453;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs57_val_arr_ow32, helper::rle_runs57_len_arr_ow32, helper::rle_runs57_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_454(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 454;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs57_val_arr_ow64, helper::rle_runs57_len_arr_ow64, helper::rle_runs57_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_455(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 455;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs57_val_arr_ow64, helper::rle_runs57_len_arr_ow64, helper::rle_runs57_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_456(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 456;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs58_val_arr_ow8, helper::rle_runs58_len_arr_ow8, helper::rle_runs58_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_457(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 457;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs58_val_arr_ow8, helper::rle_runs58_len_arr_ow8, helper::rle_runs58_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_458(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 458;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs58_val_arr_ow16, helper::rle_runs58_len_arr_ow16, helper::rle_runs58_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_459(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 459;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs58_val_arr_ow16, helper::rle_runs58_len_arr_ow16, helper::rle_runs58_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_460(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 460;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs58_val_arr_ow32, helper::rle_runs58_len_arr_ow32, helper::rle_runs58_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_461(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 461;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs58_val_arr_ow32, helper::rle_runs58_len_arr_ow32, helper::rle_runs58_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_462(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 462;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs58_val_arr_ow64, helper::rle_runs58_len_arr_ow64, helper::rle_runs58_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_463(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 463;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs58_val_arr_ow64, helper::rle_runs58_len_arr_ow64, helper::rle_runs58_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_464(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 464;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs59_val_arr_ow8, helper::rle_runs59_len_arr_ow8, helper::rle_runs59_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_465(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 465;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs59_val_arr_ow8, helper::rle_runs59_len_arr_ow8, helper::rle_runs59_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_466(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 466;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs59_val_arr_ow16, helper::rle_runs59_len_arr_ow16, helper::rle_runs59_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_467(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 467;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs59_val_arr_ow16, helper::rle_runs59_len_arr_ow16, helper::rle_runs59_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_468(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 468;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs59_val_arr_ow32, helper::rle_runs59_len_arr_ow32, helper::rle_runs59_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_469(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 469;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs59_val_arr_ow32, helper::rle_runs59_len_arr_ow32, helper::rle_runs59_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_470(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 470;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs59_val_arr_ow64, helper::rle_runs59_len_arr_ow64, helper::rle_runs59_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_471(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 471;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs59_val_arr_ow64, helper::rle_runs59_len_arr_ow64, helper::rle_runs59_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_472(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 472;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs60_val_arr_ow8, helper::rle_runs60_len_arr_ow8, helper::rle_runs60_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_473(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 473;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs60_val_arr_ow8, helper::rle_runs60_len_arr_ow8, helper::rle_runs60_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_474(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 474;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs60_val_arr_ow16, helper::rle_runs60_len_arr_ow16, helper::rle_runs60_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_475(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 475;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs60_val_arr_ow16, helper::rle_runs60_len_arr_ow16, helper::rle_runs60_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_476(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 476;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs60_val_arr_ow32, helper::rle_runs60_len_arr_ow32, helper::rle_runs60_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_477(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 477;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs60_val_arr_ow32, helper::rle_runs60_len_arr_ow32, helper::rle_runs60_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_478(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 478;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs60_val_arr_ow64, helper::rle_runs60_len_arr_ow64, helper::rle_runs60_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_479(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 479;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs60_val_arr_ow64, helper::rle_runs60_len_arr_ow64, helper::rle_runs60_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_480(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 480;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs61_val_arr_ow8, helper::rle_runs61_len_arr_ow8, helper::rle_runs61_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_481(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 481;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs61_val_arr_ow8, helper::rle_runs61_len_arr_ow8, helper::rle_runs61_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_482(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 482;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs61_val_arr_ow16, helper::rle_runs61_len_arr_ow16, helper::rle_runs61_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_483(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 483;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs61_val_arr_ow16, helper::rle_runs61_len_arr_ow16, helper::rle_runs61_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_484(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 484;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs61_val_arr_ow32, helper::rle_runs61_len_arr_ow32, helper::rle_runs61_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_485(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 485;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs61_val_arr_ow32, helper::rle_runs61_len_arr_ow32, helper::rle_runs61_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_486(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 486;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs61_val_arr_ow64, helper::rle_runs61_len_arr_ow64, helper::rle_runs61_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_487(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 487;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs61_val_arr_ow64, helper::rle_runs61_len_arr_ow64, helper::rle_runs61_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_488(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 488;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs62_val_arr_ow8, helper::rle_runs62_len_arr_ow8, helper::rle_runs62_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_489(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 489;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs62_val_arr_ow8, helper::rle_runs62_len_arr_ow8, helper::rle_runs62_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_490(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 490;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs62_val_arr_ow16, helper::rle_runs62_len_arr_ow16, helper::rle_runs62_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_491(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 491;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs62_val_arr_ow16, helper::rle_runs62_len_arr_ow16, helper::rle_runs62_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_492(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 492;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs62_val_arr_ow32, helper::rle_runs62_len_arr_ow32, helper::rle_runs62_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_493(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 493;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs62_val_arr_ow32, helper::rle_runs62_len_arr_ow32, helper::rle_runs62_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_494(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 494;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs62_val_arr_ow64, helper::rle_runs62_len_arr_ow64, helper::rle_runs62_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_495(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 495;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs62_val_arr_ow64, helper::rle_runs62_len_arr_ow64, helper::rle_runs62_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_496(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 496;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs63_val_arr_ow8, helper::rle_runs63_len_arr_ow8, helper::rle_runs63_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_497(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 497;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs63_val_arr_ow8, helper::rle_runs63_len_arr_ow8, helper::rle_runs63_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_498(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 498;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs63_val_arr_ow16, helper::rle_runs63_len_arr_ow16, helper::rle_runs63_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_499(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 499;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs63_val_arr_ow16, helper::rle_runs63_len_arr_ow16, helper::rle_runs63_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_500(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 500;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs63_val_arr_ow32, helper::rle_runs63_len_arr_ow32, helper::rle_runs63_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_501(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 501;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs63_val_arr_ow32, helper::rle_runs63_len_arr_ow32, helper::rle_runs63_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_502(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 502;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs63_val_arr_ow64, helper::rle_runs63_len_arr_ow64, helper::rle_runs63_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_503(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 503;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs63_val_arr_ow64, helper::rle_runs63_len_arr_ow64, helper::rle_runs63_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_504(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 504;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs64_val_arr_ow8, helper::rle_runs64_len_arr_ow8, helper::rle_runs64_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_505(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 505;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs64_val_arr_ow8, helper::rle_runs64_len_arr_ow8, helper::rle_runs64_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_506(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 506;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs64_val_arr_ow16, helper::rle_runs64_len_arr_ow16, helper::rle_runs64_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_507(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 507;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs64_val_arr_ow16, helper::rle_runs64_len_arr_ow16, helper::rle_runs64_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_508(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 508;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs64_val_arr_ow32, helper::rle_runs64_len_arr_ow32, helper::rle_runs64_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_509(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 509;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs64_val_arr_ow32, helper::rle_runs64_len_arr_ow32, helper::rle_runs64_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_510(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 510;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs64_val_arr_ow64, helper::rle_runs64_len_arr_ow64, helper::rle_runs64_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_511(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 511;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs64_val_arr_ow64, helper::rle_runs64_len_arr_ow64, helper::rle_runs64_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_512(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 512;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs65_val_arr_ow8, helper::rle_runs65_len_arr_ow8, helper::rle_runs65_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_513(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 513;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs65_val_arr_ow8, helper::rle_runs65_len_arr_ow8, helper::rle_runs65_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_514(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 514;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs65_val_arr_ow16, helper::rle_runs65_len_arr_ow16, helper::rle_runs65_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_515(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 515;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs65_val_arr_ow16, helper::rle_runs65_len_arr_ow16, helper::rle_runs65_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_516(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 516;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs65_val_arr_ow32, helper::rle_runs65_len_arr_ow32, helper::rle_runs65_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_517(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 517;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs65_val_arr_ow32, helper::rle_runs65_len_arr_ow32, helper::rle_runs65_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_518(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 518;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs65_val_arr_ow64, helper::rle_runs65_len_arr_ow64, helper::rle_runs65_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_519(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 519;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs65_val_arr_ow64, helper::rle_runs65_len_arr_ow64, helper::rle_runs65_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_520(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 520;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs66_val_arr_ow8, helper::rle_runs66_len_arr_ow8, helper::rle_runs66_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_521(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 521;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs66_val_arr_ow8, helper::rle_runs66_len_arr_ow8, helper::rle_runs66_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_522(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 522;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs66_val_arr_ow16, helper::rle_runs66_len_arr_ow16, helper::rle_runs66_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_523(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 523;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs66_val_arr_ow16, helper::rle_runs66_len_arr_ow16, helper::rle_runs66_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_524(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 524;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs66_val_arr_ow32, helper::rle_runs66_len_arr_ow32, helper::rle_runs66_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_525(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 525;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs66_val_arr_ow32, helper::rle_runs66_len_arr_ow32, helper::rle_runs66_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_526(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 526;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs66_val_arr_ow64, helper::rle_runs66_len_arr_ow64, helper::rle_runs66_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_527(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 527;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs66_val_arr_ow64, helper::rle_runs66_len_arr_ow64, helper::rle_runs66_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_528(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 528;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs67_val_arr_ow8, helper::rle_runs67_len_arr_ow8, helper::rle_runs67_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_529(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 529;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs67_val_arr_ow8, helper::rle_runs67_len_arr_ow8, helper::rle_runs67_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_530(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 530;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs67_val_arr_ow16, helper::rle_runs67_len_arr_ow16, helper::rle_runs67_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_531(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 531;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs67_val_arr_ow16, helper::rle_runs67_len_arr_ow16, helper::rle_runs67_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_532(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 532;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs67_val_arr_ow32, helper::rle_runs67_len_arr_ow32, helper::rle_runs67_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_533(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 533;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs67_val_arr_ow32, helper::rle_runs67_len_arr_ow32, helper::rle_runs67_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_534(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 534;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs67_val_arr_ow64, helper::rle_runs67_len_arr_ow64, helper::rle_runs67_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_535(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 535;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs67_val_arr_ow64, helper::rle_runs67_len_arr_ow64, helper::rle_runs67_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_536(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 536;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs68_val_arr_ow8, helper::rle_runs68_len_arr_ow8, helper::rle_runs68_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_537(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 537;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs68_val_arr_ow8, helper::rle_runs68_len_arr_ow8, helper::rle_runs68_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_538(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 538;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs68_val_arr_ow16, helper::rle_runs68_len_arr_ow16, helper::rle_runs68_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_539(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 539;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs68_val_arr_ow16, helper::rle_runs68_len_arr_ow16, helper::rle_runs68_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_540(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 540;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs68_val_arr_ow32, helper::rle_runs68_len_arr_ow32, helper::rle_runs68_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_541(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 541;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs68_val_arr_ow32, helper::rle_runs68_len_arr_ow32, helper::rle_runs68_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_542(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 542;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs68_val_arr_ow64, helper::rle_runs68_len_arr_ow64, helper::rle_runs68_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_543(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 543;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs68_val_arr_ow64, helper::rle_runs68_len_arr_ow64, helper::rle_runs68_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_544(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 544;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs69_val_arr_ow8, helper::rle_runs69_len_arr_ow8, helper::rle_runs69_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_545(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 545;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs69_val_arr_ow8, helper::rle_runs69_len_arr_ow8, helper::rle_runs69_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_546(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 546;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs69_val_arr_ow16, helper::rle_runs69_len_arr_ow16, helper::rle_runs69_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_547(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 547;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs69_val_arr_ow16, helper::rle_runs69_len_arr_ow16, helper::rle_runs69_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_548(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 548;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs69_val_arr_ow32, helper::rle_runs69_len_arr_ow32, helper::rle_runs69_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_549(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 549;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs69_val_arr_ow32, helper::rle_runs69_len_arr_ow32, helper::rle_runs69_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_550(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 550;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs69_val_arr_ow64, helper::rle_runs69_len_arr_ow64, helper::rle_runs69_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_551(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 551;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs69_val_arr_ow64, helper::rle_runs69_len_arr_ow64, helper::rle_runs69_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_552(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 552;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs70_val_arr_ow8, helper::rle_runs70_len_arr_ow8, helper::rle_runs70_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_553(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 553;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs70_val_arr_ow8, helper::rle_runs70_len_arr_ow8, helper::rle_runs70_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_554(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 554;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs70_val_arr_ow16, helper::rle_runs70_len_arr_ow16, helper::rle_runs70_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_555(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 555;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs70_val_arr_ow16, helper::rle_runs70_len_arr_ow16, helper::rle_runs70_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_556(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 556;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs70_val_arr_ow32, helper::rle_runs70_len_arr_ow32, helper::rle_runs70_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_557(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 557;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs70_val_arr_ow32, helper::rle_runs70_len_arr_ow32, helper::rle_runs70_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_558(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 558;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs70_val_arr_ow64, helper::rle_runs70_len_arr_ow64, helper::rle_runs70_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_559(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 559;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs70_val_arr_ow64, helper::rle_runs70_len_arr_ow64, helper::rle_runs70_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_560(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 560;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs71_val_arr_ow8, helper::rle_runs71_len_arr_ow8, helper::rle_runs71_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_561(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 561;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs71_val_arr_ow8, helper::rle_runs71_len_arr_ow8, helper::rle_runs71_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_562(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 562;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs71_val_arr_ow16, helper::rle_runs71_len_arr_ow16, helper::rle_runs71_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_563(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 563;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs71_val_arr_ow16, helper::rle_runs71_len_arr_ow16, helper::rle_runs71_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_564(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 564;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs71_val_arr_ow32, helper::rle_runs71_len_arr_ow32, helper::rle_runs71_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_565(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 565;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs71_val_arr_ow32, helper::rle_runs71_len_arr_ow32, helper::rle_runs71_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_566(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 566;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs71_val_arr_ow64, helper::rle_runs71_len_arr_ow64, helper::rle_runs71_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_567(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 567;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs71_val_arr_ow64, helper::rle_runs71_len_arr_ow64, helper::rle_runs71_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_568(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 568;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs72_val_arr_ow8, helper::rle_runs72_len_arr_ow8, helper::rle_runs72_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_569(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 569;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs72_val_arr_ow8, helper::rle_runs72_len_arr_ow8, helper::rle_runs72_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_570(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 570;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs72_val_arr_ow16, helper::rle_runs72_len_arr_ow16, helper::rle_runs72_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_571(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 571;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs72_val_arr_ow16, helper::rle_runs72_len_arr_ow16, helper::rle_runs72_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_572(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 572;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs72_val_arr_ow32, helper::rle_runs72_len_arr_ow32, helper::rle_runs72_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_573(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 573;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs72_val_arr_ow32, helper::rle_runs72_len_arr_ow32, helper::rle_runs72_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_574(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 574;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs72_val_arr_ow64, helper::rle_runs72_len_arr_ow64, helper::rle_runs72_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_575(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 575;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs72_val_arr_ow64, helper::rle_runs72_len_arr_ow64, helper::rle_runs72_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_576(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 576;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs73_val_arr_ow8, helper::rle_runs73_len_arr_ow8, helper::rle_runs73_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_577(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 577;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs73_val_arr_ow8, helper::rle_runs73_len_arr_ow8, helper::rle_runs73_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_578(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 578;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs73_val_arr_ow16, helper::rle_runs73_len_arr_ow16, helper::rle_runs73_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_579(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 579;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs73_val_arr_ow16, helper::rle_runs73_len_arr_ow16, helper::rle_runs73_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_580(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 580;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs73_val_arr_ow32, helper::rle_runs73_len_arr_ow32, helper::rle_runs73_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_581(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 581;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs73_val_arr_ow32, helper::rle_runs73_len_arr_ow32, helper::rle_runs73_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_582(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 582;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs73_val_arr_ow64, helper::rle_runs73_len_arr_ow64, helper::rle_runs73_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_583(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 583;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs73_val_arr_ow64, helper::rle_runs73_len_arr_ow64, helper::rle_runs73_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_584(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 584;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs74_val_arr_ow8, helper::rle_runs74_len_arr_ow8, helper::rle_runs74_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_585(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 585;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs74_val_arr_ow8, helper::rle_runs74_len_arr_ow8, helper::rle_runs74_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_586(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 586;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs74_val_arr_ow16, helper::rle_runs74_len_arr_ow16, helper::rle_runs74_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_587(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 587;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs74_val_arr_ow16, helper::rle_runs74_len_arr_ow16, helper::rle_runs74_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_588(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 588;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs74_val_arr_ow32, helper::rle_runs74_len_arr_ow32, helper::rle_runs74_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_589(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 589;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs74_val_arr_ow32, helper::rle_runs74_len_arr_ow32, helper::rle_runs74_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_590(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 590;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs74_val_arr_ow64, helper::rle_runs74_len_arr_ow64, helper::rle_runs74_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_591(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 591;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs74_val_arr_ow64, helper::rle_runs74_len_arr_ow64, helper::rle_runs74_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_592(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 592;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs75_val_arr_ow8, helper::rle_runs75_len_arr_ow8, helper::rle_runs75_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_593(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 593;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs75_val_arr_ow8, helper::rle_runs75_len_arr_ow8, helper::rle_runs75_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_594(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 594;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs75_val_arr_ow16, helper::rle_runs75_len_arr_ow16, helper::rle_runs75_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_595(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 595;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs75_val_arr_ow16, helper::rle_runs75_len_arr_ow16, helper::rle_runs75_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_596(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 596;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs75_val_arr_ow32, helper::rle_runs75_len_arr_ow32, helper::rle_runs75_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_597(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 597;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs75_val_arr_ow32, helper::rle_runs75_len_arr_ow32, helper::rle_runs75_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_598(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 598;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs75_val_arr_ow64, helper::rle_runs75_len_arr_ow64, helper::rle_runs75_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_599(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 599;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs75_val_arr_ow64, helper::rle_runs75_len_arr_ow64, helper::rle_runs75_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_600(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 600;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs76_val_arr_ow8, helper::rle_runs76_len_arr_ow8, helper::rle_runs76_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_601(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 601;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs76_val_arr_ow8, helper::rle_runs76_len_arr_ow8, helper::rle_runs76_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_602(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 602;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs76_val_arr_ow16, helper::rle_runs76_len_arr_ow16, helper::rle_runs76_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_603(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 603;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs76_val_arr_ow16, helper::rle_runs76_len_arr_ow16, helper::rle_runs76_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_604(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 604;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs76_val_arr_ow32, helper::rle_runs76_len_arr_ow32, helper::rle_runs76_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_605(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 605;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs76_val_arr_ow32, helper::rle_runs76_len_arr_ow32, helper::rle_runs76_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_606(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 606;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs76_val_arr_ow64, helper::rle_runs76_len_arr_ow64, helper::rle_runs76_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_607(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 607;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs76_val_arr_ow64, helper::rle_runs76_len_arr_ow64, helper::rle_runs76_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_608(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 608;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs77_val_arr_ow8, helper::rle_runs77_len_arr_ow8, helper::rle_runs77_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_609(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 609;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs77_val_arr_ow8, helper::rle_runs77_len_arr_ow8, helper::rle_runs77_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_610(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 610;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs77_val_arr_ow16, helper::rle_runs77_len_arr_ow16, helper::rle_runs77_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_611(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 611;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs77_val_arr_ow16, helper::rle_runs77_len_arr_ow16, helper::rle_runs77_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_612(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 612;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs77_val_arr_ow32, helper::rle_runs77_len_arr_ow32, helper::rle_runs77_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_613(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 613;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs77_val_arr_ow32, helper::rle_runs77_len_arr_ow32, helper::rle_runs77_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_614(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 614;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs77_val_arr_ow64, helper::rle_runs77_len_arr_ow64, helper::rle_runs77_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_615(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 615;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs77_val_arr_ow64, helper::rle_runs77_len_arr_ow64, helper::rle_runs77_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_616(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 616;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs78_val_arr_ow8, helper::rle_runs78_len_arr_ow8, helper::rle_runs78_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_617(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 617;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs78_val_arr_ow8, helper::rle_runs78_len_arr_ow8, helper::rle_runs78_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_618(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 618;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs78_val_arr_ow16, helper::rle_runs78_len_arr_ow16, helper::rle_runs78_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_619(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 619;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs78_val_arr_ow16, helper::rle_runs78_len_arr_ow16, helper::rle_runs78_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_620(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 620;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs78_val_arr_ow32, helper::rle_runs78_len_arr_ow32, helper::rle_runs78_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_621(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 621;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs78_val_arr_ow32, helper::rle_runs78_len_arr_ow32, helper::rle_runs78_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_622(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 622;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs78_val_arr_ow64, helper::rle_runs78_len_arr_ow64, helper::rle_runs78_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_623(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 623;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs78_val_arr_ow64, helper::rle_runs78_len_arr_ow64, helper::rle_runs78_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_624(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 624;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs79_val_arr_ow8, helper::rle_runs79_len_arr_ow8, helper::rle_runs79_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_625(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 625;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs79_val_arr_ow8, helper::rle_runs79_len_arr_ow8, helper::rle_runs79_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_626(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 626;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs79_val_arr_ow16, helper::rle_runs79_len_arr_ow16, helper::rle_runs79_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_627(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 627;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs79_val_arr_ow16, helper::rle_runs79_len_arr_ow16, helper::rle_runs79_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_628(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 628;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs79_val_arr_ow32, helper::rle_runs79_len_arr_ow32, helper::rle_runs79_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_629(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 629;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs79_val_arr_ow32, helper::rle_runs79_len_arr_ow32, helper::rle_runs79_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_630(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 630;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs79_val_arr_ow64, helper::rle_runs79_len_arr_ow64, helper::rle_runs79_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_631(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 631;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs79_val_arr_ow64, helper::rle_runs79_len_arr_ow64, helper::rle_runs79_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_632(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 632;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs80_val_arr_ow8, helper::rle_runs80_len_arr_ow8, helper::rle_runs80_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_633(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 633;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs80_val_arr_ow8, helper::rle_runs80_len_arr_ow8, helper::rle_runs80_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_634(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 634;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs80_val_arr_ow16, helper::rle_runs80_len_arr_ow16, helper::rle_runs80_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_635(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 635;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs80_val_arr_ow16, helper::rle_runs80_len_arr_ow16, helper::rle_runs80_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_636(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 636;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs80_val_arr_ow32, helper::rle_runs80_len_arr_ow32, helper::rle_runs80_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_637(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 637;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs80_val_arr_ow32, helper::rle_runs80_len_arr_ow32, helper::rle_runs80_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_638(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 638;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs80_val_arr_ow64, helper::rle_runs80_len_arr_ow64, helper::rle_runs80_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_639(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 639;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs80_val_arr_ow64, helper::rle_runs80_len_arr_ow64, helper::rle_runs80_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_640(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 640;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs81_val_arr_ow8, helper::rle_runs81_len_arr_ow8, helper::rle_runs81_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_641(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 641;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs81_val_arr_ow8, helper::rle_runs81_len_arr_ow8, helper::rle_runs81_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_642(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 642;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs81_val_arr_ow16, helper::rle_runs81_len_arr_ow16, helper::rle_runs81_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_643(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 643;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs81_val_arr_ow16, helper::rle_runs81_len_arr_ow16, helper::rle_runs81_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_644(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 644;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs81_val_arr_ow32, helper::rle_runs81_len_arr_ow32, helper::rle_runs81_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_645(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 645;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs81_val_arr_ow32, helper::rle_runs81_len_arr_ow32, helper::rle_runs81_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_646(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 646;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs81_val_arr_ow64, helper::rle_runs81_len_arr_ow64, helper::rle_runs81_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_647(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 647;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs81_val_arr_ow64, helper::rle_runs81_len_arr_ow64, helper::rle_runs81_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_648(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 648;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs82_val_arr_ow8, helper::rle_runs82_len_arr_ow8, helper::rle_runs82_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_649(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 649;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs82_val_arr_ow8, helper::rle_runs82_len_arr_ow8, helper::rle_runs82_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_650(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 650;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs82_val_arr_ow16, helper::rle_runs82_len_arr_ow16, helper::rle_runs82_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_651(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 651;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs82_val_arr_ow16, helper::rle_runs82_len_arr_ow16, helper::rle_runs82_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_652(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 652;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs82_val_arr_ow32, helper::rle_runs82_len_arr_ow32, helper::rle_runs82_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_653(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 653;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs82_val_arr_ow32, helper::rle_runs82_len_arr_ow32, helper::rle_runs82_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_654(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 654;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs82_val_arr_ow64, helper::rle_runs82_len_arr_ow64, helper::rle_runs82_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_655(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 655;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs82_val_arr_ow64, helper::rle_runs82_len_arr_ow64, helper::rle_runs82_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_656(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 656;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs83_val_arr_ow8, helper::rle_runs83_len_arr_ow8, helper::rle_runs83_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_657(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 657;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs83_val_arr_ow8, helper::rle_runs83_len_arr_ow8, helper::rle_runs83_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_658(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 658;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs83_val_arr_ow16, helper::rle_runs83_len_arr_ow16, helper::rle_runs83_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_659(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 659;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs83_val_arr_ow16, helper::rle_runs83_len_arr_ow16, helper::rle_runs83_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_660(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 660;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs83_val_arr_ow32, helper::rle_runs83_len_arr_ow32, helper::rle_runs83_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_661(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 661;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs83_val_arr_ow32, helper::rle_runs83_len_arr_ow32, helper::rle_runs83_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_662(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 662;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs83_val_arr_ow64, helper::rle_runs83_len_arr_ow64, helper::rle_runs83_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_663(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 663;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs83_val_arr_ow64, helper::rle_runs83_len_arr_ow64, helper::rle_runs83_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_664(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 664;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs84_val_arr_ow8, helper::rle_runs84_len_arr_ow8, helper::rle_runs84_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_665(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 665;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs84_val_arr_ow8, helper::rle_runs84_len_arr_ow8, helper::rle_runs84_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_666(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 666;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs84_val_arr_ow16, helper::rle_runs84_len_arr_ow16, helper::rle_runs84_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_667(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 667;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs84_val_arr_ow16, helper::rle_runs84_len_arr_ow16, helper::rle_runs84_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_668(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 668;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs84_val_arr_ow32, helper::rle_runs84_len_arr_ow32, helper::rle_runs84_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_669(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 669;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs84_val_arr_ow32, helper::rle_runs84_len_arr_ow32, helper::rle_runs84_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_670(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 670;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs84_val_arr_ow64, helper::rle_runs84_len_arr_ow64, helper::rle_runs84_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_671(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 671;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs84_val_arr_ow64, helper::rle_runs84_len_arr_ow64, helper::rle_runs84_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_672(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 672;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs85_val_arr_ow8, helper::rle_runs85_len_arr_ow8, helper::rle_runs85_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_673(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 673;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs85_val_arr_ow8, helper::rle_runs85_len_arr_ow8, helper::rle_runs85_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_674(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 674;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs85_val_arr_ow16, helper::rle_runs85_len_arr_ow16, helper::rle_runs85_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_675(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 675;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs85_val_arr_ow16, helper::rle_runs85_len_arr_ow16, helper::rle_runs85_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_676(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 676;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs85_val_arr_ow32, helper::rle_runs85_len_arr_ow32, helper::rle_runs85_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_677(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 677;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs85_val_arr_ow32, helper::rle_runs85_len_arr_ow32, helper::rle_runs85_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_678(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 678;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs85_val_arr_ow64, helper::rle_runs85_len_arr_ow64, helper::rle_runs85_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_679(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 679;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs85_val_arr_ow64, helper::rle_runs85_len_arr_ow64, helper::rle_runs85_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_680(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 680;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs86_val_arr_ow8, helper::rle_runs86_len_arr_ow8, helper::rle_runs86_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_681(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 681;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs86_val_arr_ow8, helper::rle_runs86_len_arr_ow8, helper::rle_runs86_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_682(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 682;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs86_val_arr_ow16, helper::rle_runs86_len_arr_ow16, helper::rle_runs86_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_683(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 683;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs86_val_arr_ow16, helper::rle_runs86_len_arr_ow16, helper::rle_runs86_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_684(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 684;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs86_val_arr_ow32, helper::rle_runs86_len_arr_ow32, helper::rle_runs86_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_685(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 685;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs86_val_arr_ow32, helper::rle_runs86_len_arr_ow32, helper::rle_runs86_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_686(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 686;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs86_val_arr_ow64, helper::rle_runs86_len_arr_ow64, helper::rle_runs86_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_687(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 687;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs86_val_arr_ow64, helper::rle_runs86_len_arr_ow64, helper::rle_runs86_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_688(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 688;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs87_val_arr_ow8, helper::rle_runs87_len_arr_ow8, helper::rle_runs87_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_689(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 689;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs87_val_arr_ow8, helper::rle_runs87_len_arr_ow8, helper::rle_runs87_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_690(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 690;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs87_val_arr_ow16, helper::rle_runs87_len_arr_ow16, helper::rle_runs87_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_691(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 691;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs87_val_arr_ow16, helper::rle_runs87_len_arr_ow16, helper::rle_runs87_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_692(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 692;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs87_val_arr_ow32, helper::rle_runs87_len_arr_ow32, helper::rle_runs87_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_693(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 693;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs87_val_arr_ow32, helper::rle_runs87_len_arr_ow32, helper::rle_runs87_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_694(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 694;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs87_val_arr_ow64, helper::rle_runs87_len_arr_ow64, helper::rle_runs87_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_695(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 695;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs87_val_arr_ow64, helper::rle_runs87_len_arr_ow64, helper::rle_runs87_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_696(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 696;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs88_val_arr_ow8, helper::rle_runs88_len_arr_ow8, helper::rle_runs88_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_697(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 697;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs88_val_arr_ow8, helper::rle_runs88_len_arr_ow8, helper::rle_runs88_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_698(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 698;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs88_val_arr_ow16, helper::rle_runs88_len_arr_ow16, helper::rle_runs88_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_699(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 699;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs88_val_arr_ow16, helper::rle_runs88_len_arr_ow16, helper::rle_runs88_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_700(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 700;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs88_val_arr_ow32, helper::rle_runs88_len_arr_ow32, helper::rle_runs88_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_701(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 701;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs88_val_arr_ow32, helper::rle_runs88_len_arr_ow32, helper::rle_runs88_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_702(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 702;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs88_val_arr_ow64, helper::rle_runs88_len_arr_ow64, helper::rle_runs88_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_703(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 703;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs88_val_arr_ow64, helper::rle_runs88_len_arr_ow64, helper::rle_runs88_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_704(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 704;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs89_val_arr_ow8, helper::rle_runs89_len_arr_ow8, helper::rle_runs89_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_705(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 705;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs89_val_arr_ow8, helper::rle_runs89_len_arr_ow8, helper::rle_runs89_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_706(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 706;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs89_val_arr_ow16, helper::rle_runs89_len_arr_ow16, helper::rle_runs89_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_707(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 707;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs89_val_arr_ow16, helper::rle_runs89_len_arr_ow16, helper::rle_runs89_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_708(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 708;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs89_val_arr_ow32, helper::rle_runs89_len_arr_ow32, helper::rle_runs89_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_709(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 709;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs89_val_arr_ow32, helper::rle_runs89_len_arr_ow32, helper::rle_runs89_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_710(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 710;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs89_val_arr_ow64, helper::rle_runs89_len_arr_ow64, helper::rle_runs89_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_711(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 711;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs89_val_arr_ow64, helper::rle_runs89_len_arr_ow64, helper::rle_runs89_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_712(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 712;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs90_val_arr_ow8, helper::rle_runs90_len_arr_ow8, helper::rle_runs90_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_713(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 713;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs90_val_arr_ow8, helper::rle_runs90_len_arr_ow8, helper::rle_runs90_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_714(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 714;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs90_val_arr_ow16, helper::rle_runs90_len_arr_ow16, helper::rle_runs90_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_715(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 715;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs90_val_arr_ow16, helper::rle_runs90_len_arr_ow16, helper::rle_runs90_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_716(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 716;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs90_val_arr_ow32, helper::rle_runs90_len_arr_ow32, helper::rle_runs90_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_717(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 717;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs90_val_arr_ow32, helper::rle_runs90_len_arr_ow32, helper::rle_runs90_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_718(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 718;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs90_val_arr_ow64, helper::rle_runs90_len_arr_ow64, helper::rle_runs90_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_719(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 719;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs90_val_arr_ow64, helper::rle_runs90_len_arr_ow64, helper::rle_runs90_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_720(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 720;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs91_val_arr_ow8, helper::rle_runs91_len_arr_ow8, helper::rle_runs91_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_721(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 721;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs91_val_arr_ow8, helper::rle_runs91_len_arr_ow8, helper::rle_runs91_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_722(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 722;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs91_val_arr_ow16, helper::rle_runs91_len_arr_ow16, helper::rle_runs91_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_723(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 723;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs91_val_arr_ow16, helper::rle_runs91_len_arr_ow16, helper::rle_runs91_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_724(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 724;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs91_val_arr_ow32, helper::rle_runs91_len_arr_ow32, helper::rle_runs91_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_725(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 725;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs91_val_arr_ow32, helper::rle_runs91_len_arr_ow32, helper::rle_runs91_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_726(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 726;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs91_val_arr_ow64, helper::rle_runs91_len_arr_ow64, helper::rle_runs91_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_727(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 727;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs91_val_arr_ow64, helper::rle_runs91_len_arr_ow64, helper::rle_runs91_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_728(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 728;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs92_val_arr_ow8, helper::rle_runs92_len_arr_ow8, helper::rle_runs92_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_729(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 729;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs92_val_arr_ow8, helper::rle_runs92_len_arr_ow8, helper::rle_runs92_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_730(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 730;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs92_val_arr_ow16, helper::rle_runs92_len_arr_ow16, helper::rle_runs92_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_731(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 731;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs92_val_arr_ow16, helper::rle_runs92_len_arr_ow16, helper::rle_runs92_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_732(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 732;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs92_val_arr_ow32, helper::rle_runs92_len_arr_ow32, helper::rle_runs92_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_733(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 733;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs92_val_arr_ow32, helper::rle_runs92_len_arr_ow32, helper::rle_runs92_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_734(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 734;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs92_val_arr_ow64, helper::rle_runs92_len_arr_ow64, helper::rle_runs92_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_735(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 735;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs92_val_arr_ow64, helper::rle_runs92_len_arr_ow64, helper::rle_runs92_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_736(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 736;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs93_val_arr_ow8, helper::rle_runs93_len_arr_ow8, helper::rle_runs93_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_737(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 737;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs93_val_arr_ow8, helper::rle_runs93_len_arr_ow8, helper::rle_runs93_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_738(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 738;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs93_val_arr_ow16, helper::rle_runs93_len_arr_ow16, helper::rle_runs93_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_739(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 739;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs93_val_arr_ow16, helper::rle_runs93_len_arr_ow16, helper::rle_runs93_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_740(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 740;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs93_val_arr_ow32, helper::rle_runs93_len_arr_ow32, helper::rle_runs93_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_741(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 741;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs93_val_arr_ow32, helper::rle_runs93_len_arr_ow32, helper::rle_runs93_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_742(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 742;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs93_val_arr_ow64, helper::rle_runs93_len_arr_ow64, helper::rle_runs93_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_743(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 743;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs93_val_arr_ow64, helper::rle_runs93_len_arr_ow64, helper::rle_runs93_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_744(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 744;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs94_val_arr_ow8, helper::rle_runs94_len_arr_ow8, helper::rle_runs94_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_745(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 745;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs94_val_arr_ow8, helper::rle_runs94_len_arr_ow8, helper::rle_runs94_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_746(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 746;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs94_val_arr_ow16, helper::rle_runs94_len_arr_ow16, helper::rle_runs94_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_747(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 747;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs94_val_arr_ow16, helper::rle_runs94_len_arr_ow16, helper::rle_runs94_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_748(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 748;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs94_val_arr_ow32, helper::rle_runs94_len_arr_ow32, helper::rle_runs94_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_749(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 749;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs94_val_arr_ow32, helper::rle_runs94_len_arr_ow32, helper::rle_runs94_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_750(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 750;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs94_val_arr_ow64, helper::rle_runs94_len_arr_ow64, helper::rle_runs94_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_751(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 751;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs94_val_arr_ow64, helper::rle_runs94_len_arr_ow64, helper::rle_runs94_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_752(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 752;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs95_val_arr_ow8, helper::rle_runs95_len_arr_ow8, helper::rle_runs95_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_753(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 753;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs95_val_arr_ow8, helper::rle_runs95_len_arr_ow8, helper::rle_runs95_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_754(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 754;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs95_val_arr_ow16, helper::rle_runs95_len_arr_ow16, helper::rle_runs95_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_755(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 755;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs95_val_arr_ow16, helper::rle_runs95_len_arr_ow16, helper::rle_runs95_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_756(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 756;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs95_val_arr_ow32, helper::rle_runs95_len_arr_ow32, helper::rle_runs95_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_757(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 757;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs95_val_arr_ow32, helper::rle_runs95_len_arr_ow32, helper::rle_runs95_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_758(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 758;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs95_val_arr_ow64, helper::rle_runs95_len_arr_ow64, helper::rle_runs95_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_759(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 759;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs95_val_arr_ow64, helper::rle_runs95_len_arr_ow64, helper::rle_runs95_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_760(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 760;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs96_val_arr_ow8, helper::rle_runs96_len_arr_ow8, helper::rle_runs96_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_761(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 761;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs96_val_arr_ow8, helper::rle_runs96_len_arr_ow8, helper::rle_runs96_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_762(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 762;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs96_val_arr_ow16, helper::rle_runs96_len_arr_ow16, helper::rle_runs96_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_763(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 763;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs96_val_arr_ow16, helper::rle_runs96_len_arr_ow16, helper::rle_runs96_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_764(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 764;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs96_val_arr_ow32, helper::rle_runs96_len_arr_ow32, helper::rle_runs96_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_765(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 765;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs96_val_arr_ow32, helper::rle_runs96_len_arr_ow32, helper::rle_runs96_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_766(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 766;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs96_val_arr_ow64, helper::rle_runs96_len_arr_ow64, helper::rle_runs96_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_767(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 767;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs96_val_arr_ow64, helper::rle_runs96_len_arr_ow64, helper::rle_runs96_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_768(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 768;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs97_val_arr_ow8, helper::rle_runs97_len_arr_ow8, helper::rle_runs97_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_769(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 769;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs97_val_arr_ow8, helper::rle_runs97_len_arr_ow8, helper::rle_runs97_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_770(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 770;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs97_val_arr_ow16, helper::rle_runs97_len_arr_ow16, helper::rle_runs97_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_771(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 771;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs97_val_arr_ow16, helper::rle_runs97_len_arr_ow16, helper::rle_runs97_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_772(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 772;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs97_val_arr_ow32, helper::rle_runs97_len_arr_ow32, helper::rle_runs97_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_773(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 773;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs97_val_arr_ow32, helper::rle_runs97_len_arr_ow32, helper::rle_runs97_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_774(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 774;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs97_val_arr_ow64, helper::rle_runs97_len_arr_ow64, helper::rle_runs97_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_775(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 775;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs97_val_arr_ow64, helper::rle_runs97_len_arr_ow64, helper::rle_runs97_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_776(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 776;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs98_val_arr_ow8, helper::rle_runs98_len_arr_ow8, helper::rle_runs98_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_777(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 777;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs98_val_arr_ow8, helper::rle_runs98_len_arr_ow8, helper::rle_runs98_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_778(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 778;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs98_val_arr_ow16, helper::rle_runs98_len_arr_ow16, helper::rle_runs98_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_779(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 779;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs98_val_arr_ow16, helper::rle_runs98_len_arr_ow16, helper::rle_runs98_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_780(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 780;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs98_val_arr_ow32, helper::rle_runs98_len_arr_ow32, helper::rle_runs98_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_781(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 781;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs98_val_arr_ow32, helper::rle_runs98_len_arr_ow32, helper::rle_runs98_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_782(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 782;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs98_val_arr_ow64, helper::rle_runs98_len_arr_ow64, helper::rle_runs98_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_783(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 783;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs98_val_arr_ow64, helper::rle_runs98_len_arr_ow64, helper::rle_runs98_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_784(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 784;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs99_val_arr_ow8, helper::rle_runs99_len_arr_ow8, helper::rle_runs99_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_785(int8_t* transposed8, int8_t* untransposed8)
{
	int benchmark_number = 785;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_8";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs99_val_arr_ow8, helper::rle_runs99_len_arr_ow8, helper::rle_runs99_run_count4x256, untransposed8);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_786(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 786;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs99_val_arr_ow16, helper::rle_runs99_len_arr_ow16, helper::rle_runs99_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_787(int16_t* transposed16, int16_t* untransposed16)
{
	int benchmark_number = 787;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_16";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs99_val_arr_ow16, helper::rle_runs99_len_arr_ow16, helper::rle_runs99_run_count4x256, untransposed16);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_788(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 788;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs99_val_arr_ow32, helper::rle_runs99_len_arr_ow32, helper::rle_runs99_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_789(int32_t* transposed32, int32_t* untransposed32)
{
	int benchmark_number = 789;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_32";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs99_val_arr_ow32, helper::rle_runs99_len_arr_ow32, helper::rle_runs99_run_count4x256, untransposed32);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_790(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 790;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::rle(helper::rle_runs99_val_arr_ow64, helper::rle_runs99_len_arr_ow64, helper::rle_runs99_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
static benchmark::BenchmarkReporter::Run bench_791(int64_t* transposed64, int64_t* untransposed64)
{
	int benchmark_number = 791;
	uint64_t iterations = 30000000;
	std::string benchmark_name = "scalar_rle_64";
	
	uint64_t cycles = benchmark::cycleclock::Now();
	for (uint64_t i = 0; i < iterations ; ++i)
	{
		rut::scalar::scalar_rle(helper::rle_runs99_val_arr_ow64, helper::rle_runs99_len_arr_ow64, helper::rle_runs99_run_count4x256, untransposed64);
	}
	
	cycles = benchmark::cycleclock::Now() - cycles;
	
	  return benchmark::BenchmarkReporter::Run(benchmark_number, benchmark_name, iterations,double(cycles) / (double(iterations) * 1024));
}
void benchmark_all(benchmark::Benchmark& benchmark)
{
	auto *transposed8 = new int8_t[1024]();
	auto *transposed16 = new int16_t[1024]();
	auto *transposed32 = new int32_t[1024]();
	auto *transposed64 = new int64_t[1024]();
	auto *untransposed8 = new int8_t[1024]();
	auto *untransposed16 = new int16_t[1024]();
	auto *untransposed32 = new int32_t[1024]();
	auto *untransposed64 = new int64_t[1024]();
	benchmark.Run(bench_0(transposed8, untransposed8));
	benchmark.Run(bench_1(transposed8, untransposed8));
	benchmark.Run(bench_2(transposed16, untransposed16));
	benchmark.Run(bench_3(transposed16, untransposed16));
	benchmark.Run(bench_4(transposed32, untransposed32));
	benchmark.Run(bench_5(transposed32, untransposed32));
	benchmark.Run(bench_6(transposed64, untransposed64));
	benchmark.Run(bench_7(transposed64, untransposed64));
	benchmark.Run(bench_8(transposed8, untransposed8));
	benchmark.Run(bench_9(transposed8, untransposed8));
	benchmark.Run(bench_10(transposed16, untransposed16));
	benchmark.Run(bench_11(transposed16, untransposed16));
	benchmark.Run(bench_12(transposed32, untransposed32));
	benchmark.Run(bench_13(transposed32, untransposed32));
	benchmark.Run(bench_14(transposed64, untransposed64));
	benchmark.Run(bench_15(transposed64, untransposed64));
	benchmark.Run(bench_16(transposed8, untransposed8));
	benchmark.Run(bench_17(transposed8, untransposed8));
	benchmark.Run(bench_18(transposed16, untransposed16));
	benchmark.Run(bench_19(transposed16, untransposed16));
	benchmark.Run(bench_20(transposed32, untransposed32));
	benchmark.Run(bench_21(transposed32, untransposed32));
	benchmark.Run(bench_22(transposed64, untransposed64));
	benchmark.Run(bench_23(transposed64, untransposed64));
	benchmark.Run(bench_24(transposed8, untransposed8));
	benchmark.Run(bench_25(transposed8, untransposed8));
	benchmark.Run(bench_26(transposed16, untransposed16));
	benchmark.Run(bench_27(transposed16, untransposed16));
	benchmark.Run(bench_28(transposed32, untransposed32));
	benchmark.Run(bench_29(transposed32, untransposed32));
	benchmark.Run(bench_30(transposed64, untransposed64));
	benchmark.Run(bench_31(transposed64, untransposed64));
	benchmark.Run(bench_32(transposed8, untransposed8));
	benchmark.Run(bench_33(transposed8, untransposed8));
	benchmark.Run(bench_34(transposed16, untransposed16));
	benchmark.Run(bench_35(transposed16, untransposed16));
	benchmark.Run(bench_36(transposed32, untransposed32));
	benchmark.Run(bench_37(transposed32, untransposed32));
	benchmark.Run(bench_38(transposed64, untransposed64));
	benchmark.Run(bench_39(transposed64, untransposed64));
	benchmark.Run(bench_40(transposed8, untransposed8));
	benchmark.Run(bench_41(transposed8, untransposed8));
	benchmark.Run(bench_42(transposed16, untransposed16));
	benchmark.Run(bench_43(transposed16, untransposed16));
	benchmark.Run(bench_44(transposed32, untransposed32));
	benchmark.Run(bench_45(transposed32, untransposed32));
	benchmark.Run(bench_46(transposed64, untransposed64));
	benchmark.Run(bench_47(transposed64, untransposed64));
	benchmark.Run(bench_48(transposed8, untransposed8));
	benchmark.Run(bench_49(transposed8, untransposed8));
	benchmark.Run(bench_50(transposed16, untransposed16));
	benchmark.Run(bench_51(transposed16, untransposed16));
	benchmark.Run(bench_52(transposed32, untransposed32));
	benchmark.Run(bench_53(transposed32, untransposed32));
	benchmark.Run(bench_54(transposed64, untransposed64));
	benchmark.Run(bench_55(transposed64, untransposed64));
	benchmark.Run(bench_56(transposed8, untransposed8));
	benchmark.Run(bench_57(transposed8, untransposed8));
	benchmark.Run(bench_58(transposed16, untransposed16));
	benchmark.Run(bench_59(transposed16, untransposed16));
	benchmark.Run(bench_60(transposed32, untransposed32));
	benchmark.Run(bench_61(transposed32, untransposed32));
	benchmark.Run(bench_62(transposed64, untransposed64));
	benchmark.Run(bench_63(transposed64, untransposed64));
	benchmark.Run(bench_64(transposed8, untransposed8));
	benchmark.Run(bench_65(transposed8, untransposed8));
	benchmark.Run(bench_66(transposed16, untransposed16));
	benchmark.Run(bench_67(transposed16, untransposed16));
	benchmark.Run(bench_68(transposed32, untransposed32));
	benchmark.Run(bench_69(transposed32, untransposed32));
	benchmark.Run(bench_70(transposed64, untransposed64));
	benchmark.Run(bench_71(transposed64, untransposed64));
	benchmark.Run(bench_72(transposed8, untransposed8));
	benchmark.Run(bench_73(transposed8, untransposed8));
	benchmark.Run(bench_74(transposed16, untransposed16));
	benchmark.Run(bench_75(transposed16, untransposed16));
	benchmark.Run(bench_76(transposed32, untransposed32));
	benchmark.Run(bench_77(transposed32, untransposed32));
	benchmark.Run(bench_78(transposed64, untransposed64));
	benchmark.Run(bench_79(transposed64, untransposed64));
	benchmark.Run(bench_80(transposed8, untransposed8));
	benchmark.Run(bench_81(transposed8, untransposed8));
	benchmark.Run(bench_82(transposed16, untransposed16));
	benchmark.Run(bench_83(transposed16, untransposed16));
	benchmark.Run(bench_84(transposed32, untransposed32));
	benchmark.Run(bench_85(transposed32, untransposed32));
	benchmark.Run(bench_86(transposed64, untransposed64));
	benchmark.Run(bench_87(transposed64, untransposed64));
	benchmark.Run(bench_88(transposed8, untransposed8));
	benchmark.Run(bench_89(transposed8, untransposed8));
	benchmark.Run(bench_90(transposed16, untransposed16));
	benchmark.Run(bench_91(transposed16, untransposed16));
	benchmark.Run(bench_92(transposed32, untransposed32));
	benchmark.Run(bench_93(transposed32, untransposed32));
	benchmark.Run(bench_94(transposed64, untransposed64));
	benchmark.Run(bench_95(transposed64, untransposed64));
	benchmark.Run(bench_96(transposed8, untransposed8));
	benchmark.Run(bench_97(transposed8, untransposed8));
	benchmark.Run(bench_98(transposed16, untransposed16));
	benchmark.Run(bench_99(transposed16, untransposed16));
	benchmark.Run(bench_100(transposed32, untransposed32));
	benchmark.Run(bench_101(transposed32, untransposed32));
	benchmark.Run(bench_102(transposed64, untransposed64));
	benchmark.Run(bench_103(transposed64, untransposed64));
	benchmark.Run(bench_104(transposed8, untransposed8));
	benchmark.Run(bench_105(transposed8, untransposed8));
	benchmark.Run(bench_106(transposed16, untransposed16));
	benchmark.Run(bench_107(transposed16, untransposed16));
	benchmark.Run(bench_108(transposed32, untransposed32));
	benchmark.Run(bench_109(transposed32, untransposed32));
	benchmark.Run(bench_110(transposed64, untransposed64));
	benchmark.Run(bench_111(transposed64, untransposed64));
	benchmark.Run(bench_112(transposed8, untransposed8));
	benchmark.Run(bench_113(transposed8, untransposed8));
	benchmark.Run(bench_114(transposed16, untransposed16));
	benchmark.Run(bench_115(transposed16, untransposed16));
	benchmark.Run(bench_116(transposed32, untransposed32));
	benchmark.Run(bench_117(transposed32, untransposed32));
	benchmark.Run(bench_118(transposed64, untransposed64));
	benchmark.Run(bench_119(transposed64, untransposed64));
	benchmark.Run(bench_120(transposed8, untransposed8));
	benchmark.Run(bench_121(transposed8, untransposed8));
	benchmark.Run(bench_122(transposed16, untransposed16));
	benchmark.Run(bench_123(transposed16, untransposed16));
	benchmark.Run(bench_124(transposed32, untransposed32));
	benchmark.Run(bench_125(transposed32, untransposed32));
	benchmark.Run(bench_126(transposed64, untransposed64));
	benchmark.Run(bench_127(transposed64, untransposed64));
	benchmark.Run(bench_128(transposed8, untransposed8));
	benchmark.Run(bench_129(transposed8, untransposed8));
	benchmark.Run(bench_130(transposed16, untransposed16));
	benchmark.Run(bench_131(transposed16, untransposed16));
	benchmark.Run(bench_132(transposed32, untransposed32));
	benchmark.Run(bench_133(transposed32, untransposed32));
	benchmark.Run(bench_134(transposed64, untransposed64));
	benchmark.Run(bench_135(transposed64, untransposed64));
	benchmark.Run(bench_136(transposed8, untransposed8));
	benchmark.Run(bench_137(transposed8, untransposed8));
	benchmark.Run(bench_138(transposed16, untransposed16));
	benchmark.Run(bench_139(transposed16, untransposed16));
	benchmark.Run(bench_140(transposed32, untransposed32));
	benchmark.Run(bench_141(transposed32, untransposed32));
	benchmark.Run(bench_142(transposed64, untransposed64));
	benchmark.Run(bench_143(transposed64, untransposed64));
	benchmark.Run(bench_144(transposed8, untransposed8));
	benchmark.Run(bench_145(transposed8, untransposed8));
	benchmark.Run(bench_146(transposed16, untransposed16));
	benchmark.Run(bench_147(transposed16, untransposed16));
	benchmark.Run(bench_148(transposed32, untransposed32));
	benchmark.Run(bench_149(transposed32, untransposed32));
	benchmark.Run(bench_150(transposed64, untransposed64));
	benchmark.Run(bench_151(transposed64, untransposed64));
	benchmark.Run(bench_152(transposed8, untransposed8));
	benchmark.Run(bench_153(transposed8, untransposed8));
	benchmark.Run(bench_154(transposed16, untransposed16));
	benchmark.Run(bench_155(transposed16, untransposed16));
	benchmark.Run(bench_156(transposed32, untransposed32));
	benchmark.Run(bench_157(transposed32, untransposed32));
	benchmark.Run(bench_158(transposed64, untransposed64));
	benchmark.Run(bench_159(transposed64, untransposed64));
	benchmark.Run(bench_160(transposed8, untransposed8));
	benchmark.Run(bench_161(transposed8, untransposed8));
	benchmark.Run(bench_162(transposed16, untransposed16));
	benchmark.Run(bench_163(transposed16, untransposed16));
	benchmark.Run(bench_164(transposed32, untransposed32));
	benchmark.Run(bench_165(transposed32, untransposed32));
	benchmark.Run(bench_166(transposed64, untransposed64));
	benchmark.Run(bench_167(transposed64, untransposed64));
	benchmark.Run(bench_168(transposed8, untransposed8));
	benchmark.Run(bench_169(transposed8, untransposed8));
	benchmark.Run(bench_170(transposed16, untransposed16));
	benchmark.Run(bench_171(transposed16, untransposed16));
	benchmark.Run(bench_172(transposed32, untransposed32));
	benchmark.Run(bench_173(transposed32, untransposed32));
	benchmark.Run(bench_174(transposed64, untransposed64));
	benchmark.Run(bench_175(transposed64, untransposed64));
	benchmark.Run(bench_176(transposed8, untransposed8));
	benchmark.Run(bench_177(transposed8, untransposed8));
	benchmark.Run(bench_178(transposed16, untransposed16));
	benchmark.Run(bench_179(transposed16, untransposed16));
	benchmark.Run(bench_180(transposed32, untransposed32));
	benchmark.Run(bench_181(transposed32, untransposed32));
	benchmark.Run(bench_182(transposed64, untransposed64));
	benchmark.Run(bench_183(transposed64, untransposed64));
	benchmark.Run(bench_184(transposed8, untransposed8));
	benchmark.Run(bench_185(transposed8, untransposed8));
	benchmark.Run(bench_186(transposed16, untransposed16));
	benchmark.Run(bench_187(transposed16, untransposed16));
	benchmark.Run(bench_188(transposed32, untransposed32));
	benchmark.Run(bench_189(transposed32, untransposed32));
	benchmark.Run(bench_190(transposed64, untransposed64));
	benchmark.Run(bench_191(transposed64, untransposed64));
	benchmark.Run(bench_192(transposed8, untransposed8));
	benchmark.Run(bench_193(transposed8, untransposed8));
	benchmark.Run(bench_194(transposed16, untransposed16));
	benchmark.Run(bench_195(transposed16, untransposed16));
	benchmark.Run(bench_196(transposed32, untransposed32));
	benchmark.Run(bench_197(transposed32, untransposed32));
	benchmark.Run(bench_198(transposed64, untransposed64));
	benchmark.Run(bench_199(transposed64, untransposed64));
	benchmark.Run(bench_200(transposed8, untransposed8));
	benchmark.Run(bench_201(transposed8, untransposed8));
	benchmark.Run(bench_202(transposed16, untransposed16));
	benchmark.Run(bench_203(transposed16, untransposed16));
	benchmark.Run(bench_204(transposed32, untransposed32));
	benchmark.Run(bench_205(transposed32, untransposed32));
	benchmark.Run(bench_206(transposed64, untransposed64));
	benchmark.Run(bench_207(transposed64, untransposed64));
	benchmark.Run(bench_208(transposed8, untransposed8));
	benchmark.Run(bench_209(transposed8, untransposed8));
	benchmark.Run(bench_210(transposed16, untransposed16));
	benchmark.Run(bench_211(transposed16, untransposed16));
	benchmark.Run(bench_212(transposed32, untransposed32));
	benchmark.Run(bench_213(transposed32, untransposed32));
	benchmark.Run(bench_214(transposed64, untransposed64));
	benchmark.Run(bench_215(transposed64, untransposed64));
	benchmark.Run(bench_216(transposed8, untransposed8));
	benchmark.Run(bench_217(transposed8, untransposed8));
	benchmark.Run(bench_218(transposed16, untransposed16));
	benchmark.Run(bench_219(transposed16, untransposed16));
	benchmark.Run(bench_220(transposed32, untransposed32));
	benchmark.Run(bench_221(transposed32, untransposed32));
	benchmark.Run(bench_222(transposed64, untransposed64));
	benchmark.Run(bench_223(transposed64, untransposed64));
	benchmark.Run(bench_224(transposed8, untransposed8));
	benchmark.Run(bench_225(transposed8, untransposed8));
	benchmark.Run(bench_226(transposed16, untransposed16));
	benchmark.Run(bench_227(transposed16, untransposed16));
	benchmark.Run(bench_228(transposed32, untransposed32));
	benchmark.Run(bench_229(transposed32, untransposed32));
	benchmark.Run(bench_230(transposed64, untransposed64));
	benchmark.Run(bench_231(transposed64, untransposed64));
	benchmark.Run(bench_232(transposed8, untransposed8));
	benchmark.Run(bench_233(transposed8, untransposed8));
	benchmark.Run(bench_234(transposed16, untransposed16));
	benchmark.Run(bench_235(transposed16, untransposed16));
	benchmark.Run(bench_236(transposed32, untransposed32));
	benchmark.Run(bench_237(transposed32, untransposed32));
	benchmark.Run(bench_238(transposed64, untransposed64));
	benchmark.Run(bench_239(transposed64, untransposed64));
	benchmark.Run(bench_240(transposed8, untransposed8));
	benchmark.Run(bench_241(transposed8, untransposed8));
	benchmark.Run(bench_242(transposed16, untransposed16));
	benchmark.Run(bench_243(transposed16, untransposed16));
	benchmark.Run(bench_244(transposed32, untransposed32));
	benchmark.Run(bench_245(transposed32, untransposed32));
	benchmark.Run(bench_246(transposed64, untransposed64));
	benchmark.Run(bench_247(transposed64, untransposed64));
	benchmark.Run(bench_248(transposed8, untransposed8));
	benchmark.Run(bench_249(transposed8, untransposed8));
	benchmark.Run(bench_250(transposed16, untransposed16));
	benchmark.Run(bench_251(transposed16, untransposed16));
	benchmark.Run(bench_252(transposed32, untransposed32));
	benchmark.Run(bench_253(transposed32, untransposed32));
	benchmark.Run(bench_254(transposed64, untransposed64));
	benchmark.Run(bench_255(transposed64, untransposed64));
	benchmark.Run(bench_256(transposed8, untransposed8));
	benchmark.Run(bench_257(transposed8, untransposed8));
	benchmark.Run(bench_258(transposed16, untransposed16));
	benchmark.Run(bench_259(transposed16, untransposed16));
	benchmark.Run(bench_260(transposed32, untransposed32));
	benchmark.Run(bench_261(transposed32, untransposed32));
	benchmark.Run(bench_262(transposed64, untransposed64));
	benchmark.Run(bench_263(transposed64, untransposed64));
	benchmark.Run(bench_264(transposed8, untransposed8));
	benchmark.Run(bench_265(transposed8, untransposed8));
	benchmark.Run(bench_266(transposed16, untransposed16));
	benchmark.Run(bench_267(transposed16, untransposed16));
	benchmark.Run(bench_268(transposed32, untransposed32));
	benchmark.Run(bench_269(transposed32, untransposed32));
	benchmark.Run(bench_270(transposed64, untransposed64));
	benchmark.Run(bench_271(transposed64, untransposed64));
	benchmark.Run(bench_272(transposed8, untransposed8));
	benchmark.Run(bench_273(transposed8, untransposed8));
	benchmark.Run(bench_274(transposed16, untransposed16));
	benchmark.Run(bench_275(transposed16, untransposed16));
	benchmark.Run(bench_276(transposed32, untransposed32));
	benchmark.Run(bench_277(transposed32, untransposed32));
	benchmark.Run(bench_278(transposed64, untransposed64));
	benchmark.Run(bench_279(transposed64, untransposed64));
	benchmark.Run(bench_280(transposed8, untransposed8));
	benchmark.Run(bench_281(transposed8, untransposed8));
	benchmark.Run(bench_282(transposed16, untransposed16));
	benchmark.Run(bench_283(transposed16, untransposed16));
	benchmark.Run(bench_284(transposed32, untransposed32));
	benchmark.Run(bench_285(transposed32, untransposed32));
	benchmark.Run(bench_286(transposed64, untransposed64));
	benchmark.Run(bench_287(transposed64, untransposed64));
	benchmark.Run(bench_288(transposed8, untransposed8));
	benchmark.Run(bench_289(transposed8, untransposed8));
	benchmark.Run(bench_290(transposed16, untransposed16));
	benchmark.Run(bench_291(transposed16, untransposed16));
	benchmark.Run(bench_292(transposed32, untransposed32));
	benchmark.Run(bench_293(transposed32, untransposed32));
	benchmark.Run(bench_294(transposed64, untransposed64));
	benchmark.Run(bench_295(transposed64, untransposed64));
	benchmark.Run(bench_296(transposed8, untransposed8));
	benchmark.Run(bench_297(transposed8, untransposed8));
	benchmark.Run(bench_298(transposed16, untransposed16));
	benchmark.Run(bench_299(transposed16, untransposed16));
	benchmark.Run(bench_300(transposed32, untransposed32));
	benchmark.Run(bench_301(transposed32, untransposed32));
	benchmark.Run(bench_302(transposed64, untransposed64));
	benchmark.Run(bench_303(transposed64, untransposed64));
	benchmark.Run(bench_304(transposed8, untransposed8));
	benchmark.Run(bench_305(transposed8, untransposed8));
	benchmark.Run(bench_306(transposed16, untransposed16));
	benchmark.Run(bench_307(transposed16, untransposed16));
	benchmark.Run(bench_308(transposed32, untransposed32));
	benchmark.Run(bench_309(transposed32, untransposed32));
	benchmark.Run(bench_310(transposed64, untransposed64));
	benchmark.Run(bench_311(transposed64, untransposed64));
	benchmark.Run(bench_312(transposed8, untransposed8));
	benchmark.Run(bench_313(transposed8, untransposed8));
	benchmark.Run(bench_314(transposed16, untransposed16));
	benchmark.Run(bench_315(transposed16, untransposed16));
	benchmark.Run(bench_316(transposed32, untransposed32));
	benchmark.Run(bench_317(transposed32, untransposed32));
	benchmark.Run(bench_318(transposed64, untransposed64));
	benchmark.Run(bench_319(transposed64, untransposed64));
	benchmark.Run(bench_320(transposed8, untransposed8));
	benchmark.Run(bench_321(transposed8, untransposed8));
	benchmark.Run(bench_322(transposed16, untransposed16));
	benchmark.Run(bench_323(transposed16, untransposed16));
	benchmark.Run(bench_324(transposed32, untransposed32));
	benchmark.Run(bench_325(transposed32, untransposed32));
	benchmark.Run(bench_326(transposed64, untransposed64));
	benchmark.Run(bench_327(transposed64, untransposed64));
	benchmark.Run(bench_328(transposed8, untransposed8));
	benchmark.Run(bench_329(transposed8, untransposed8));
	benchmark.Run(bench_330(transposed16, untransposed16));
	benchmark.Run(bench_331(transposed16, untransposed16));
	benchmark.Run(bench_332(transposed32, untransposed32));
	benchmark.Run(bench_333(transposed32, untransposed32));
	benchmark.Run(bench_334(transposed64, untransposed64));
	benchmark.Run(bench_335(transposed64, untransposed64));
	benchmark.Run(bench_336(transposed8, untransposed8));
	benchmark.Run(bench_337(transposed8, untransposed8));
	benchmark.Run(bench_338(transposed16, untransposed16));
	benchmark.Run(bench_339(transposed16, untransposed16));
	benchmark.Run(bench_340(transposed32, untransposed32));
	benchmark.Run(bench_341(transposed32, untransposed32));
	benchmark.Run(bench_342(transposed64, untransposed64));
	benchmark.Run(bench_343(transposed64, untransposed64));
	benchmark.Run(bench_344(transposed8, untransposed8));
	benchmark.Run(bench_345(transposed8, untransposed8));
	benchmark.Run(bench_346(transposed16, untransposed16));
	benchmark.Run(bench_347(transposed16, untransposed16));
	benchmark.Run(bench_348(transposed32, untransposed32));
	benchmark.Run(bench_349(transposed32, untransposed32));
	benchmark.Run(bench_350(transposed64, untransposed64));
	benchmark.Run(bench_351(transposed64, untransposed64));
	benchmark.Run(bench_352(transposed8, untransposed8));
	benchmark.Run(bench_353(transposed8, untransposed8));
	benchmark.Run(bench_354(transposed16, untransposed16));
	benchmark.Run(bench_355(transposed16, untransposed16));
	benchmark.Run(bench_356(transposed32, untransposed32));
	benchmark.Run(bench_357(transposed32, untransposed32));
	benchmark.Run(bench_358(transposed64, untransposed64));
	benchmark.Run(bench_359(transposed64, untransposed64));
	benchmark.Run(bench_360(transposed8, untransposed8));
	benchmark.Run(bench_361(transposed8, untransposed8));
	benchmark.Run(bench_362(transposed16, untransposed16));
	benchmark.Run(bench_363(transposed16, untransposed16));
	benchmark.Run(bench_364(transposed32, untransposed32));
	benchmark.Run(bench_365(transposed32, untransposed32));
	benchmark.Run(bench_366(transposed64, untransposed64));
	benchmark.Run(bench_367(transposed64, untransposed64));
	benchmark.Run(bench_368(transposed8, untransposed8));
	benchmark.Run(bench_369(transposed8, untransposed8));
	benchmark.Run(bench_370(transposed16, untransposed16));
	benchmark.Run(bench_371(transposed16, untransposed16));
	benchmark.Run(bench_372(transposed32, untransposed32));
	benchmark.Run(bench_373(transposed32, untransposed32));
	benchmark.Run(bench_374(transposed64, untransposed64));
	benchmark.Run(bench_375(transposed64, untransposed64));
	benchmark.Run(bench_376(transposed8, untransposed8));
	benchmark.Run(bench_377(transposed8, untransposed8));
	benchmark.Run(bench_378(transposed16, untransposed16));
	benchmark.Run(bench_379(transposed16, untransposed16));
	benchmark.Run(bench_380(transposed32, untransposed32));
	benchmark.Run(bench_381(transposed32, untransposed32));
	benchmark.Run(bench_382(transposed64, untransposed64));
	benchmark.Run(bench_383(transposed64, untransposed64));
	benchmark.Run(bench_384(transposed8, untransposed8));
	benchmark.Run(bench_385(transposed8, untransposed8));
	benchmark.Run(bench_386(transposed16, untransposed16));
	benchmark.Run(bench_387(transposed16, untransposed16));
	benchmark.Run(bench_388(transposed32, untransposed32));
	benchmark.Run(bench_389(transposed32, untransposed32));
	benchmark.Run(bench_390(transposed64, untransposed64));
	benchmark.Run(bench_391(transposed64, untransposed64));
	benchmark.Run(bench_392(transposed8, untransposed8));
	benchmark.Run(bench_393(transposed8, untransposed8));
	benchmark.Run(bench_394(transposed16, untransposed16));
	benchmark.Run(bench_395(transposed16, untransposed16));
	benchmark.Run(bench_396(transposed32, untransposed32));
	benchmark.Run(bench_397(transposed32, untransposed32));
	benchmark.Run(bench_398(transposed64, untransposed64));
	benchmark.Run(bench_399(transposed64, untransposed64));
	benchmark.Run(bench_400(transposed8, untransposed8));
	benchmark.Run(bench_401(transposed8, untransposed8));
	benchmark.Run(bench_402(transposed16, untransposed16));
	benchmark.Run(bench_403(transposed16, untransposed16));
	benchmark.Run(bench_404(transposed32, untransposed32));
	benchmark.Run(bench_405(transposed32, untransposed32));
	benchmark.Run(bench_406(transposed64, untransposed64));
	benchmark.Run(bench_407(transposed64, untransposed64));
	benchmark.Run(bench_408(transposed8, untransposed8));
	benchmark.Run(bench_409(transposed8, untransposed8));
	benchmark.Run(bench_410(transposed16, untransposed16));
	benchmark.Run(bench_411(transposed16, untransposed16));
	benchmark.Run(bench_412(transposed32, untransposed32));
	benchmark.Run(bench_413(transposed32, untransposed32));
	benchmark.Run(bench_414(transposed64, untransposed64));
	benchmark.Run(bench_415(transposed64, untransposed64));
	benchmark.Run(bench_416(transposed8, untransposed8));
	benchmark.Run(bench_417(transposed8, untransposed8));
	benchmark.Run(bench_418(transposed16, untransposed16));
	benchmark.Run(bench_419(transposed16, untransposed16));
	benchmark.Run(bench_420(transposed32, untransposed32));
	benchmark.Run(bench_421(transposed32, untransposed32));
	benchmark.Run(bench_422(transposed64, untransposed64));
	benchmark.Run(bench_423(transposed64, untransposed64));
	benchmark.Run(bench_424(transposed8, untransposed8));
	benchmark.Run(bench_425(transposed8, untransposed8));
	benchmark.Run(bench_426(transposed16, untransposed16));
	benchmark.Run(bench_427(transposed16, untransposed16));
	benchmark.Run(bench_428(transposed32, untransposed32));
	benchmark.Run(bench_429(transposed32, untransposed32));
	benchmark.Run(bench_430(transposed64, untransposed64));
	benchmark.Run(bench_431(transposed64, untransposed64));
	benchmark.Run(bench_432(transposed8, untransposed8));
	benchmark.Run(bench_433(transposed8, untransposed8));
	benchmark.Run(bench_434(transposed16, untransposed16));
	benchmark.Run(bench_435(transposed16, untransposed16));
	benchmark.Run(bench_436(transposed32, untransposed32));
	benchmark.Run(bench_437(transposed32, untransposed32));
	benchmark.Run(bench_438(transposed64, untransposed64));
	benchmark.Run(bench_439(transposed64, untransposed64));
	benchmark.Run(bench_440(transposed8, untransposed8));
	benchmark.Run(bench_441(transposed8, untransposed8));
	benchmark.Run(bench_442(transposed16, untransposed16));
	benchmark.Run(bench_443(transposed16, untransposed16));
	benchmark.Run(bench_444(transposed32, untransposed32));
	benchmark.Run(bench_445(transposed32, untransposed32));
	benchmark.Run(bench_446(transposed64, untransposed64));
	benchmark.Run(bench_447(transposed64, untransposed64));
	benchmark.Run(bench_448(transposed8, untransposed8));
	benchmark.Run(bench_449(transposed8, untransposed8));
	benchmark.Run(bench_450(transposed16, untransposed16));
	benchmark.Run(bench_451(transposed16, untransposed16));
	benchmark.Run(bench_452(transposed32, untransposed32));
	benchmark.Run(bench_453(transposed32, untransposed32));
	benchmark.Run(bench_454(transposed64, untransposed64));
	benchmark.Run(bench_455(transposed64, untransposed64));
	benchmark.Run(bench_456(transposed8, untransposed8));
	benchmark.Run(bench_457(transposed8, untransposed8));
	benchmark.Run(bench_458(transposed16, untransposed16));
	benchmark.Run(bench_459(transposed16, untransposed16));
	benchmark.Run(bench_460(transposed32, untransposed32));
	benchmark.Run(bench_461(transposed32, untransposed32));
	benchmark.Run(bench_462(transposed64, untransposed64));
	benchmark.Run(bench_463(transposed64, untransposed64));
	benchmark.Run(bench_464(transposed8, untransposed8));
	benchmark.Run(bench_465(transposed8, untransposed8));
	benchmark.Run(bench_466(transposed16, untransposed16));
	benchmark.Run(bench_467(transposed16, untransposed16));
	benchmark.Run(bench_468(transposed32, untransposed32));
	benchmark.Run(bench_469(transposed32, untransposed32));
	benchmark.Run(bench_470(transposed64, untransposed64));
	benchmark.Run(bench_471(transposed64, untransposed64));
	benchmark.Run(bench_472(transposed8, untransposed8));
	benchmark.Run(bench_473(transposed8, untransposed8));
	benchmark.Run(bench_474(transposed16, untransposed16));
	benchmark.Run(bench_475(transposed16, untransposed16));
	benchmark.Run(bench_476(transposed32, untransposed32));
	benchmark.Run(bench_477(transposed32, untransposed32));
	benchmark.Run(bench_478(transposed64, untransposed64));
	benchmark.Run(bench_479(transposed64, untransposed64));
	benchmark.Run(bench_480(transposed8, untransposed8));
	benchmark.Run(bench_481(transposed8, untransposed8));
	benchmark.Run(bench_482(transposed16, untransposed16));
	benchmark.Run(bench_483(transposed16, untransposed16));
	benchmark.Run(bench_484(transposed32, untransposed32));
	benchmark.Run(bench_485(transposed32, untransposed32));
	benchmark.Run(bench_486(transposed64, untransposed64));
	benchmark.Run(bench_487(transposed64, untransposed64));
	benchmark.Run(bench_488(transposed8, untransposed8));
	benchmark.Run(bench_489(transposed8, untransposed8));
	benchmark.Run(bench_490(transposed16, untransposed16));
	benchmark.Run(bench_491(transposed16, untransposed16));
	benchmark.Run(bench_492(transposed32, untransposed32));
	benchmark.Run(bench_493(transposed32, untransposed32));
	benchmark.Run(bench_494(transposed64, untransposed64));
	benchmark.Run(bench_495(transposed64, untransposed64));
	benchmark.Run(bench_496(transposed8, untransposed8));
	benchmark.Run(bench_497(transposed8, untransposed8));
	benchmark.Run(bench_498(transposed16, untransposed16));
	benchmark.Run(bench_499(transposed16, untransposed16));
	benchmark.Run(bench_500(transposed32, untransposed32));
	benchmark.Run(bench_501(transposed32, untransposed32));
	benchmark.Run(bench_502(transposed64, untransposed64));
	benchmark.Run(bench_503(transposed64, untransposed64));
	benchmark.Run(bench_504(transposed8, untransposed8));
	benchmark.Run(bench_505(transposed8, untransposed8));
	benchmark.Run(bench_506(transposed16, untransposed16));
	benchmark.Run(bench_507(transposed16, untransposed16));
	benchmark.Run(bench_508(transposed32, untransposed32));
	benchmark.Run(bench_509(transposed32, untransposed32));
	benchmark.Run(bench_510(transposed64, untransposed64));
	benchmark.Run(bench_511(transposed64, untransposed64));
	benchmark.Run(bench_512(transposed8, untransposed8));
	benchmark.Run(bench_513(transposed8, untransposed8));
	benchmark.Run(bench_514(transposed16, untransposed16));
	benchmark.Run(bench_515(transposed16, untransposed16));
	benchmark.Run(bench_516(transposed32, untransposed32));
	benchmark.Run(bench_517(transposed32, untransposed32));
	benchmark.Run(bench_518(transposed64, untransposed64));
	benchmark.Run(bench_519(transposed64, untransposed64));
	benchmark.Run(bench_520(transposed8, untransposed8));
	benchmark.Run(bench_521(transposed8, untransposed8));
	benchmark.Run(bench_522(transposed16, untransposed16));
	benchmark.Run(bench_523(transposed16, untransposed16));
	benchmark.Run(bench_524(transposed32, untransposed32));
	benchmark.Run(bench_525(transposed32, untransposed32));
	benchmark.Run(bench_526(transposed64, untransposed64));
	benchmark.Run(bench_527(transposed64, untransposed64));
	benchmark.Run(bench_528(transposed8, untransposed8));
	benchmark.Run(bench_529(transposed8, untransposed8));
	benchmark.Run(bench_530(transposed16, untransposed16));
	benchmark.Run(bench_531(transposed16, untransposed16));
	benchmark.Run(bench_532(transposed32, untransposed32));
	benchmark.Run(bench_533(transposed32, untransposed32));
	benchmark.Run(bench_534(transposed64, untransposed64));
	benchmark.Run(bench_535(transposed64, untransposed64));
	benchmark.Run(bench_536(transposed8, untransposed8));
	benchmark.Run(bench_537(transposed8, untransposed8));
	benchmark.Run(bench_538(transposed16, untransposed16));
	benchmark.Run(bench_539(transposed16, untransposed16));
	benchmark.Run(bench_540(transposed32, untransposed32));
	benchmark.Run(bench_541(transposed32, untransposed32));
	benchmark.Run(bench_542(transposed64, untransposed64));
	benchmark.Run(bench_543(transposed64, untransposed64));
	benchmark.Run(bench_544(transposed8, untransposed8));
	benchmark.Run(bench_545(transposed8, untransposed8));
	benchmark.Run(bench_546(transposed16, untransposed16));
	benchmark.Run(bench_547(transposed16, untransposed16));
	benchmark.Run(bench_548(transposed32, untransposed32));
	benchmark.Run(bench_549(transposed32, untransposed32));
	benchmark.Run(bench_550(transposed64, untransposed64));
	benchmark.Run(bench_551(transposed64, untransposed64));
	benchmark.Run(bench_552(transposed8, untransposed8));
	benchmark.Run(bench_553(transposed8, untransposed8));
	benchmark.Run(bench_554(transposed16, untransposed16));
	benchmark.Run(bench_555(transposed16, untransposed16));
	benchmark.Run(bench_556(transposed32, untransposed32));
	benchmark.Run(bench_557(transposed32, untransposed32));
	benchmark.Run(bench_558(transposed64, untransposed64));
	benchmark.Run(bench_559(transposed64, untransposed64));
	benchmark.Run(bench_560(transposed8, untransposed8));
	benchmark.Run(bench_561(transposed8, untransposed8));
	benchmark.Run(bench_562(transposed16, untransposed16));
	benchmark.Run(bench_563(transposed16, untransposed16));
	benchmark.Run(bench_564(transposed32, untransposed32));
	benchmark.Run(bench_565(transposed32, untransposed32));
	benchmark.Run(bench_566(transposed64, untransposed64));
	benchmark.Run(bench_567(transposed64, untransposed64));
	benchmark.Run(bench_568(transposed8, untransposed8));
	benchmark.Run(bench_569(transposed8, untransposed8));
	benchmark.Run(bench_570(transposed16, untransposed16));
	benchmark.Run(bench_571(transposed16, untransposed16));
	benchmark.Run(bench_572(transposed32, untransposed32));
	benchmark.Run(bench_573(transposed32, untransposed32));
	benchmark.Run(bench_574(transposed64, untransposed64));
	benchmark.Run(bench_575(transposed64, untransposed64));
	benchmark.Run(bench_576(transposed8, untransposed8));
	benchmark.Run(bench_577(transposed8, untransposed8));
	benchmark.Run(bench_578(transposed16, untransposed16));
	benchmark.Run(bench_579(transposed16, untransposed16));
	benchmark.Run(bench_580(transposed32, untransposed32));
	benchmark.Run(bench_581(transposed32, untransposed32));
	benchmark.Run(bench_582(transposed64, untransposed64));
	benchmark.Run(bench_583(transposed64, untransposed64));
	benchmark.Run(bench_584(transposed8, untransposed8));
	benchmark.Run(bench_585(transposed8, untransposed8));
	benchmark.Run(bench_586(transposed16, untransposed16));
	benchmark.Run(bench_587(transposed16, untransposed16));
	benchmark.Run(bench_588(transposed32, untransposed32));
	benchmark.Run(bench_589(transposed32, untransposed32));
	benchmark.Run(bench_590(transposed64, untransposed64));
	benchmark.Run(bench_591(transposed64, untransposed64));
	benchmark.Run(bench_592(transposed8, untransposed8));
	benchmark.Run(bench_593(transposed8, untransposed8));
	benchmark.Run(bench_594(transposed16, untransposed16));
	benchmark.Run(bench_595(transposed16, untransposed16));
	benchmark.Run(bench_596(transposed32, untransposed32));
	benchmark.Run(bench_597(transposed32, untransposed32));
	benchmark.Run(bench_598(transposed64, untransposed64));
	benchmark.Run(bench_599(transposed64, untransposed64));
	benchmark.Run(bench_600(transposed8, untransposed8));
	benchmark.Run(bench_601(transposed8, untransposed8));
	benchmark.Run(bench_602(transposed16, untransposed16));
	benchmark.Run(bench_603(transposed16, untransposed16));
	benchmark.Run(bench_604(transposed32, untransposed32));
	benchmark.Run(bench_605(transposed32, untransposed32));
	benchmark.Run(bench_606(transposed64, untransposed64));
	benchmark.Run(bench_607(transposed64, untransposed64));
	benchmark.Run(bench_608(transposed8, untransposed8));
	benchmark.Run(bench_609(transposed8, untransposed8));
	benchmark.Run(bench_610(transposed16, untransposed16));
	benchmark.Run(bench_611(transposed16, untransposed16));
	benchmark.Run(bench_612(transposed32, untransposed32));
	benchmark.Run(bench_613(transposed32, untransposed32));
	benchmark.Run(bench_614(transposed64, untransposed64));
	benchmark.Run(bench_615(transposed64, untransposed64));
	benchmark.Run(bench_616(transposed8, untransposed8));
	benchmark.Run(bench_617(transposed8, untransposed8));
	benchmark.Run(bench_618(transposed16, untransposed16));
	benchmark.Run(bench_619(transposed16, untransposed16));
	benchmark.Run(bench_620(transposed32, untransposed32));
	benchmark.Run(bench_621(transposed32, untransposed32));
	benchmark.Run(bench_622(transposed64, untransposed64));
	benchmark.Run(bench_623(transposed64, untransposed64));
	benchmark.Run(bench_624(transposed8, untransposed8));
	benchmark.Run(bench_625(transposed8, untransposed8));
	benchmark.Run(bench_626(transposed16, untransposed16));
	benchmark.Run(bench_627(transposed16, untransposed16));
	benchmark.Run(bench_628(transposed32, untransposed32));
	benchmark.Run(bench_629(transposed32, untransposed32));
	benchmark.Run(bench_630(transposed64, untransposed64));
	benchmark.Run(bench_631(transposed64, untransposed64));
	benchmark.Run(bench_632(transposed8, untransposed8));
	benchmark.Run(bench_633(transposed8, untransposed8));
	benchmark.Run(bench_634(transposed16, untransposed16));
	benchmark.Run(bench_635(transposed16, untransposed16));
	benchmark.Run(bench_636(transposed32, untransposed32));
	benchmark.Run(bench_637(transposed32, untransposed32));
	benchmark.Run(bench_638(transposed64, untransposed64));
	benchmark.Run(bench_639(transposed64, untransposed64));
	benchmark.Run(bench_640(transposed8, untransposed8));
	benchmark.Run(bench_641(transposed8, untransposed8));
	benchmark.Run(bench_642(transposed16, untransposed16));
	benchmark.Run(bench_643(transposed16, untransposed16));
	benchmark.Run(bench_644(transposed32, untransposed32));
	benchmark.Run(bench_645(transposed32, untransposed32));
	benchmark.Run(bench_646(transposed64, untransposed64));
	benchmark.Run(bench_647(transposed64, untransposed64));
	benchmark.Run(bench_648(transposed8, untransposed8));
	benchmark.Run(bench_649(transposed8, untransposed8));
	benchmark.Run(bench_650(transposed16, untransposed16));
	benchmark.Run(bench_651(transposed16, untransposed16));
	benchmark.Run(bench_652(transposed32, untransposed32));
	benchmark.Run(bench_653(transposed32, untransposed32));
	benchmark.Run(bench_654(transposed64, untransposed64));
	benchmark.Run(bench_655(transposed64, untransposed64));
	benchmark.Run(bench_656(transposed8, untransposed8));
	benchmark.Run(bench_657(transposed8, untransposed8));
	benchmark.Run(bench_658(transposed16, untransposed16));
	benchmark.Run(bench_659(transposed16, untransposed16));
	benchmark.Run(bench_660(transposed32, untransposed32));
	benchmark.Run(bench_661(transposed32, untransposed32));
	benchmark.Run(bench_662(transposed64, untransposed64));
	benchmark.Run(bench_663(transposed64, untransposed64));
	benchmark.Run(bench_664(transposed8, untransposed8));
	benchmark.Run(bench_665(transposed8, untransposed8));
	benchmark.Run(bench_666(transposed16, untransposed16));
	benchmark.Run(bench_667(transposed16, untransposed16));
	benchmark.Run(bench_668(transposed32, untransposed32));
	benchmark.Run(bench_669(transposed32, untransposed32));
	benchmark.Run(bench_670(transposed64, untransposed64));
	benchmark.Run(bench_671(transposed64, untransposed64));
	benchmark.Run(bench_672(transposed8, untransposed8));
	benchmark.Run(bench_673(transposed8, untransposed8));
	benchmark.Run(bench_674(transposed16, untransposed16));
	benchmark.Run(bench_675(transposed16, untransposed16));
	benchmark.Run(bench_676(transposed32, untransposed32));
	benchmark.Run(bench_677(transposed32, untransposed32));
	benchmark.Run(bench_678(transposed64, untransposed64));
	benchmark.Run(bench_679(transposed64, untransposed64));
	benchmark.Run(bench_680(transposed8, untransposed8));
	benchmark.Run(bench_681(transposed8, untransposed8));
	benchmark.Run(bench_682(transposed16, untransposed16));
	benchmark.Run(bench_683(transposed16, untransposed16));
	benchmark.Run(bench_684(transposed32, untransposed32));
	benchmark.Run(bench_685(transposed32, untransposed32));
	benchmark.Run(bench_686(transposed64, untransposed64));
	benchmark.Run(bench_687(transposed64, untransposed64));
	benchmark.Run(bench_688(transposed8, untransposed8));
	benchmark.Run(bench_689(transposed8, untransposed8));
	benchmark.Run(bench_690(transposed16, untransposed16));
	benchmark.Run(bench_691(transposed16, untransposed16));
	benchmark.Run(bench_692(transposed32, untransposed32));
	benchmark.Run(bench_693(transposed32, untransposed32));
	benchmark.Run(bench_694(transposed64, untransposed64));
	benchmark.Run(bench_695(transposed64, untransposed64));
	benchmark.Run(bench_696(transposed8, untransposed8));
	benchmark.Run(bench_697(transposed8, untransposed8));
	benchmark.Run(bench_698(transposed16, untransposed16));
	benchmark.Run(bench_699(transposed16, untransposed16));
	benchmark.Run(bench_700(transposed32, untransposed32));
	benchmark.Run(bench_701(transposed32, untransposed32));
	benchmark.Run(bench_702(transposed64, untransposed64));
	benchmark.Run(bench_703(transposed64, untransposed64));
	benchmark.Run(bench_704(transposed8, untransposed8));
	benchmark.Run(bench_705(transposed8, untransposed8));
	benchmark.Run(bench_706(transposed16, untransposed16));
	benchmark.Run(bench_707(transposed16, untransposed16));
	benchmark.Run(bench_708(transposed32, untransposed32));
	benchmark.Run(bench_709(transposed32, untransposed32));
	benchmark.Run(bench_710(transposed64, untransposed64));
	benchmark.Run(bench_711(transposed64, untransposed64));
	benchmark.Run(bench_712(transposed8, untransposed8));
	benchmark.Run(bench_713(transposed8, untransposed8));
	benchmark.Run(bench_714(transposed16, untransposed16));
	benchmark.Run(bench_715(transposed16, untransposed16));
	benchmark.Run(bench_716(transposed32, untransposed32));
	benchmark.Run(bench_717(transposed32, untransposed32));
	benchmark.Run(bench_718(transposed64, untransposed64));
	benchmark.Run(bench_719(transposed64, untransposed64));
	benchmark.Run(bench_720(transposed8, untransposed8));
	benchmark.Run(bench_721(transposed8, untransposed8));
	benchmark.Run(bench_722(transposed16, untransposed16));
	benchmark.Run(bench_723(transposed16, untransposed16));
	benchmark.Run(bench_724(transposed32, untransposed32));
	benchmark.Run(bench_725(transposed32, untransposed32));
	benchmark.Run(bench_726(transposed64, untransposed64));
	benchmark.Run(bench_727(transposed64, untransposed64));
	benchmark.Run(bench_728(transposed8, untransposed8));
	benchmark.Run(bench_729(transposed8, untransposed8));
	benchmark.Run(bench_730(transposed16, untransposed16));
	benchmark.Run(bench_731(transposed16, untransposed16));
	benchmark.Run(bench_732(transposed32, untransposed32));
	benchmark.Run(bench_733(transposed32, untransposed32));
	benchmark.Run(bench_734(transposed64, untransposed64));
	benchmark.Run(bench_735(transposed64, untransposed64));
	benchmark.Run(bench_736(transposed8, untransposed8));
	benchmark.Run(bench_737(transposed8, untransposed8));
	benchmark.Run(bench_738(transposed16, untransposed16));
	benchmark.Run(bench_739(transposed16, untransposed16));
	benchmark.Run(bench_740(transposed32, untransposed32));
	benchmark.Run(bench_741(transposed32, untransposed32));
	benchmark.Run(bench_742(transposed64, untransposed64));
	benchmark.Run(bench_743(transposed64, untransposed64));
	benchmark.Run(bench_744(transposed8, untransposed8));
	benchmark.Run(bench_745(transposed8, untransposed8));
	benchmark.Run(bench_746(transposed16, untransposed16));
	benchmark.Run(bench_747(transposed16, untransposed16));
	benchmark.Run(bench_748(transposed32, untransposed32));
	benchmark.Run(bench_749(transposed32, untransposed32));
	benchmark.Run(bench_750(transposed64, untransposed64));
	benchmark.Run(bench_751(transposed64, untransposed64));
	benchmark.Run(bench_752(transposed8, untransposed8));
	benchmark.Run(bench_753(transposed8, untransposed8));
	benchmark.Run(bench_754(transposed16, untransposed16));
	benchmark.Run(bench_755(transposed16, untransposed16));
	benchmark.Run(bench_756(transposed32, untransposed32));
	benchmark.Run(bench_757(transposed32, untransposed32));
	benchmark.Run(bench_758(transposed64, untransposed64));
	benchmark.Run(bench_759(transposed64, untransposed64));
	benchmark.Run(bench_760(transposed8, untransposed8));
	benchmark.Run(bench_761(transposed8, untransposed8));
	benchmark.Run(bench_762(transposed16, untransposed16));
	benchmark.Run(bench_763(transposed16, untransposed16));
	benchmark.Run(bench_764(transposed32, untransposed32));
	benchmark.Run(bench_765(transposed32, untransposed32));
	benchmark.Run(bench_766(transposed64, untransposed64));
	benchmark.Run(bench_767(transposed64, untransposed64));
	benchmark.Run(bench_768(transposed8, untransposed8));
	benchmark.Run(bench_769(transposed8, untransposed8));
	benchmark.Run(bench_770(transposed16, untransposed16));
	benchmark.Run(bench_771(transposed16, untransposed16));
	benchmark.Run(bench_772(transposed32, untransposed32));
	benchmark.Run(bench_773(transposed32, untransposed32));
	benchmark.Run(bench_774(transposed64, untransposed64));
	benchmark.Run(bench_775(transposed64, untransposed64));
	benchmark.Run(bench_776(transposed8, untransposed8));
	benchmark.Run(bench_777(transposed8, untransposed8));
	benchmark.Run(bench_778(transposed16, untransposed16));
	benchmark.Run(bench_779(transposed16, untransposed16));
	benchmark.Run(bench_780(transposed32, untransposed32));
	benchmark.Run(bench_781(transposed32, untransposed32));
	benchmark.Run(bench_782(transposed64, untransposed64));
	benchmark.Run(bench_783(transposed64, untransposed64));
	benchmark.Run(bench_784(transposed8, untransposed8));
	benchmark.Run(bench_785(transposed8, untransposed8));
	benchmark.Run(bench_786(transposed16, untransposed16));
	benchmark.Run(bench_787(transposed16, untransposed16));
	benchmark.Run(bench_788(transposed32, untransposed32));
	benchmark.Run(bench_789(transposed32, untransposed32));
	benchmark.Run(bench_790(transposed64, untransposed64));
	benchmark.Run(bench_791(transposed64, untransposed64));
}
int main()
{
	benchmark::Benchmark benchmark = benchmark::create("arm64v8_scalar_av_1024_uf1_rut")
                                               .save()
                                               .at(std::string(SOURCE_DIR) + "/results/arm64v8")
                                               .print()
                                               .add_extra_info(benchmark::CmakeInfo::getCmakeInfo());
          benchmark_all(benchmark);
}
