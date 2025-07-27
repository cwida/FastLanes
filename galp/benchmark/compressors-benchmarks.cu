// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/benchmark/compressors-benchmarks.cu
// ────────────────────────────────────────────────────────
// =============================================================================
// benchmark_runner.cpp  —  single-file driver that mirrors test-scripts/run.sh
//
// * Builds with any C++17+ host compiler + NVCC.
// * Host-only code (filesystem, main, etc.) is hidden from the device pass
//   via `#if !defined(__CUDA_ARCH__)` guards, so NVCC no longer chokes.
//
// Compile example:
//   g++ -std=c++17 benchmark_runner.cpp -o compressors-benchmarks $(CUDA_LIBS) ...
// =============================================================================
#include "engine/enums.cuh"
#include "flsgpu/consts.cuh"
#include "generator/generate_binaries.hpp"
#include "nvcomp/benchmark-compressors.cuh"
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#if !defined(__CUDA_ARCH__)
#include <filesystem> // host-only
#endif
#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

// -----------------------------------------------------------------------------
// Utility helpers (shared by host + device passes)
// -----------------------------------------------------------------------------
inline std::string extract_filename(const std::string& path) {
	const std::size_t pos = path.find_last_of('/');
	std::string       fn  = (pos == std::string::npos) ? path : path.substr(pos + 1);
	const std::size_t ext = fn.find_last_of('.');
	return (ext == std::string::npos) ? fn : fn.substr(0, ext);
}

struct CLIArgs {
	enums::DataType               data_type;
	enums_nvcomp::ComparisonType  comparison_type;
	enums_nvcomp::CompressionType decompressor_enum;
	std::string                   file_path;
	int                           n_values;
};

inline CLIArgs parse_cli_args(int argc, char* argv[]) {
	if (argc != 6) {
		std::cerr << "Usage: " << argv[0]
		          << " <data_type> <comparison_enum:string> <decompressor_enum:string> "
		             "<data_path> <vector_count>\n";
		throw std::invalid_argument("Incorrect CLI argument count");
	}

	int     idx = 0;
	CLIArgs args;
	args.data_type         = enums::string_to_data_type(argv[++idx]);
	args.comparison_type   = enums_nvcomp::string_to_comparison_type(argv[++idx]);
	args.decompressor_enum = enums_nvcomp::string_to_compression_type(argv[++idx]);
	args.file_path         = argv[++idx];
	args.n_values          = std::atoi(argv[++idx]) * consts::VALUES_PER_VECTOR;
	return args;
}

namespace data::arrays {
template <typename T>
std::pair<T*, size_t> read_file_as(const std::string path, const size_t input_count) {
	// Open file
	std::ifstream inputFile(path, std::ios::binary | std::ios::ate);
	if (!inputFile) {
		throw std::invalid_argument("Could not open the specified file.");
	}
	// Get file size
	const std::streamsize file_size = inputFile.tellg();
	inputFile.seekg(0, std::ios::beg);

	// Check file size to contain right type of data
	bool file_size_is_multiple_of_T_size = static_cast<size_t>(file_size) % static_cast<size_t>(sizeof(T)) != 0;
	if (file_size_is_multiple_of_T_size) {
		throw std::invalid_argument("File size is incorrect, it is not a multiple of the type's size.");
	}

	const size_t values_in_file = static_cast<size_t>(file_size) / sizeof(T);
	size_t       count          = input_count == 0 ? values_in_file : input_count;
	count                       = count - (count % consts::VALUES_PER_VECTOR);
	auto column                 = new T[count];

	// Read either the file size, or the total number of values needed,
	// whichever is smaller
	const std::streamsize read_size = std::min(file_size, static_cast<std::streamsize>((count * sizeof(T))));
	if (!inputFile.read(reinterpret_cast<char*>(column), read_size)) {
		throw std::invalid_argument("Failed to read file into column");
	}

	inputFile.close();

	// Copy paste the values in file until the column is filled
	if (values_in_file < count) {
		size_t n_filled_values       = values_in_file;
		size_t n_empty_values_column = count - n_filled_values;
		while (n_empty_values_column != 0) {
			size_t n_values_to_copy = std::min(n_empty_values_column, values_in_file);
			std::memcpy(column + n_filled_values, column, n_values_to_copy * sizeof(T));
			n_filled_values += n_values_to_copy;
			n_empty_values_column -= n_values_to_copy;
		}
	}

	return std::make_pair(column, count);
}
} // namespace data::arrays

// Template benchmark launcher (host-only code but harmless for device pass)
template <typename T>
inline void execute_benchmark(const CLIArgs& args) {
	auto [data, count] = data::arrays::read_file_as<T>(args.file_path, args.n_values);

	uint32_t u                   = 0x4100f9db; // deterministic test value
	const T  value_to_search_for = *reinterpret_cast<T*>(&u);

	BenchmarkResult result;
	for (int i = 0; i < 2; ++i) {
		if (args.comparison_type == enums_nvcomp::ComparisonType::DECOMPRESSION_QUERY &&
		    args.decompressor_enum == enums_nvcomp::THRUST) {
			result = benchmark_thrust<T>(data, count, value_to_search_for);
		} else if (args.decompressor_enum == enums_nvcomp::ALP || args.decompressor_enum == enums_nvcomp::GALP) {
			result = benchmark_alp<T>(args.comparison_type, args.decompressor_enum, data, count, value_to_search_for);
		} else {
			result = benchmark_hwc<T>(args.comparison_type, args.decompressor_enum, data, count, value_to_search_for);
		}
	}

	result.log_result(
	    args.comparison_type, args.decompressor_enum, count * sizeof(T), extract_filename(args.file_path));

	delete data;
}

// -----------------------------------------------------------------------------
// Main driver  (host-only; skipped entirely for the device pass)
// -----------------------------------------------------------------------------
#if !defined(__CUDA_ARCH__)
int main(int argc, char* argv[]) {
	constexpr int VECTOR_COUNT = 25'600; // matches shell-script constant

	// -------------------------------------------------------------------------
	// Single-case CLI fallback (exactly 5 user args)
	// -------------------------------------------------------------------------
	if (argc == 6) {
		CLIArgs args = parse_cli_args(argc, argv);
		if (args.data_type == enums::DataType::F32)
			execute_benchmark<float>(args);
		else if (args.data_type == enums::DataType::F64)
			execute_benchmark<double>(args);
		else
			throw std::invalid_argument("Unsupported data type");
		return 0;
	}

	// -------------------------------------------------------------------------
	// (0) Generate new binaries + discover directories
	// -------------------------------------------------------------------------
	const size_t TOTAL = 25'600 * 1'024;
	const size_t HEAD  = 0;

	const std::filesystem::path floats_dir  = FLS_GALP_SOURCE_DIR "/data/floats";
	const std::filesystem::path doubles_dir = FLS_GALP_SOURCE_DIR "/data/doubles";

	bin::GenResult gen = bin::generate_write_and_scan(floats_dir, doubles_dir, TOTAL, HEAD);

	std::cout << "First " << HEAD << " values:\n";
	for (double v : gen.head)
		std::cout << v << '\n';

	if (gen.float_files.empty() && gen.double_files.empty()) {
		std::cerr << "No .bin test files found. Populate data/floats and data/doubles.\n";
		return 1;
	}

	// -------------------------------------------------------------------------
	// Benchmark matrix settings (mirrors test-scripts/run.sh)
	// -------------------------------------------------------------------------
	const std::vector<enums_nvcomp::ComparisonType> COMPARISONS = {enums_nvcomp::ComparisonType::DECOMPRESSION,
	                                                               enums_nvcomp::ComparisonType::DECOMPRESSION_QUERY};

	const std::vector<enums_nvcomp::CompressionType> COMPRESSORS = {
	    //
	    // enums_nvcomp::ALP,
	    enums_nvcomp::GALP,
	    enums_nvcomp::BITCOMP,
	    enums_nvcomp::BITCOMP_SPARSE,
	    enums_nvcomp::LZ4,
	    enums_nvcomp::ZSTD,
	    enums_nvcomp::DEFLATE,
	    enums_nvcomp::GDEFLATE,
	    enums_nvcomp::SNAPPY
	    //
	};

	// CSV header
	std::printf("comparison_type,compression_type,data_name,found_value,"
	            "n_bytes,execution_time_ms,compression_ratio\n");

	// -------------------------------------------------------------------------
	// (1) Full matrix — Floats (F32)
	// -------------------------------------------------------------------------
	for (auto cmp : COMPARISONS)
		for (auto decomp : COMPRESSORS)
			for (const auto& path : gen.float_files) {
				CLIArgs args {enums::DataType::F32, cmp, decomp, path, VECTOR_COUNT * consts::VALUES_PER_VECTOR};
				execute_benchmark<float>(args);
			}

	// -------------------------------------------------------------------------
	// (2) Full matrix — Doubles (F64)
	// -------------------------------------------------------------------------
	for (auto cmp : COMPARISONS)
		for (auto decomp : COMPRESSORS)
			for (const auto& path : gen.double_files) {
				CLIArgs args {enums::DataType::F64, cmp, decomp, path, VECTOR_COUNT * consts::VALUES_PER_VECTOR};
				execute_benchmark<double>(args);
			}

	// -------------------------------------------------------------------------
	// (3) Thrust path — only DECOMPRESSION_QUERY
	// -------------------------------------------------------------------------
	auto run_thrust = [&](enums::DataType dtype, const std::vector<std::string>& files) {
		for (const auto& path : files) {
			CLIArgs args;
			args.data_type         = dtype;
			args.comparison_type   = enums_nvcomp::ComparisonType::DECOMPRESSION_QUERY;
			args.decompressor_enum = enums_nvcomp::THRUST;
			args.file_path         = path;
			args.n_values          = VECTOR_COUNT * consts::VALUES_PER_VECTOR;

			if (dtype == enums::DataType::F32)
				execute_benchmark<float>(args);
			else
				execute_benchmark<double>(args);
		}
	};

	run_thrust(enums::DataType::F32, gen.float_files);
	run_thrust(enums::DataType::F64, gen.double_files);

	return 0;
}
#endif // !__CUDA_ARCH__
