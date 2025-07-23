// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/test/galp_test.cu
// ────────────────────────────────────────────────────────
#include "alp/alp-bindings.cuh"
#include "data/fastlanes_data.hpp"
#include "engine/device-utils.cuh"
#include "engine/kernels.cuh"
#include "flsgpu/alp.cuh"
#include "flsgpu/structs.cuh"
#include "generator/generate_binaries.hpp"
#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>
#include <thrust/device_vector.h>
#include <thrust/execution_policy.h>
#include <thrust/host_vector.h>
#include <thrust/logical.h>
#include <utility> // for std::pair
#include <vector>

template <typename T>
std::vector<T> read_file(const std::string& path) {
	// Open file in binary mode, positioned at end to get its size
	std::ifstream file(path, std::ios::binary | std::ios::ate);
	if (!file) {
		throw std::runtime_error("Could not open file: " + path);
	}

	// Determine file size in bytes
	std::streamsize bytes = file.tellg();
	if (bytes < 0) {
		throw std::runtime_error("Could not determine file size: " + path);
	}

	// Ensure the file contains an integral number of T elements
	if (bytes % sizeof(T) != 0) {
		throw std::runtime_error("File size (" + std::to_string(bytes) + " bytes) is not a multiple of element size (" +
		                         std::to_string(sizeof(T)) + " bytes)");
	}

	// Calculate number of elements
	std::size_t count = static_cast<std::size_t>(bytes / sizeof(T));

	// Seek back to beginning and read all data into a vector
	file.seekg(0, std::ios::beg);
	std::vector<T> data(count);
	if (!file.read(reinterpret_cast<char*>(data.data()), bytes)) {
		throw std::runtime_error("Error reading file: " + path);
	}

	return data;
}

// -----------------------------------------------------------------------------
// CSV loader – light‑weight, header‑only
// -----------------------------------------------------------------------------
template <typename T>
std::vector<T> read_csv(const std::filesystem::path& path) {
	std::ifstream file(path);
	if (!file) {
		throw std::runtime_error("Could not open csv file: " + path.string());
	}

	std::vector<T> data;
	std::string    line;
	while (std::getline(file, line)) {
		std::stringstream ss(line);
		std::string       cell;
		while (std::getline(ss, cell, ',')) {
			if (!cell.empty()) {
				data.push_back(static_cast<T>(std::stod(cell)));
			}
		}
	}
	return data;
}

template <typename T>
bool check_if_device_buffers_are_equal(const T* a, const T* b, const size_t n_values) {
	// Convert to uint8_t as we don't want to compare floats (-nan == -nan =>
	// false)
	thrust::device_ptr<uint8_t> d_a(reinterpret_cast<uint8_t*>(const_cast<T*>(a)));
	thrust::device_ptr<uint8_t> d_b(reinterpret_cast<uint8_t*>(const_cast<T*>(b)));

	return thrust::equal(d_a, d_a + n_values, d_b);
}

template <typename T, unsigned UNPACK_N_VECTORS>
using ALPDecompressor = typename flsgpu::device::ALPDecompressor<
    T,
    UNPACK_N_VECTORS,
    flsgpu::device::
        BitUnpackerStatefulBranchless<T, UNPACK_N_VECTORS, 1, flsgpu::device::ALPFunctor<T, UNPACK_N_VECTORS>>,
    flsgpu::device::StatefulALPExceptionPatcher<T, UNPACK_N_VECTORS, 1>,
    flsgpu::device::ALPColumn<T>>;

template <typename T, unsigned UNPACK_N_VECTORS>
using ALPExtendedDecompressor = typename flsgpu::device::ALPDecompressor<
    T,
    UNPACK_N_VECTORS,
    flsgpu::device::
        BitUnpackerStatefulBranchless<T, UNPACK_N_VECTORS, 1, flsgpu::device::ALPFunctor<T, UNPACK_N_VECTORS>>,
    flsgpu::device::PrefetchAllALPExceptionPatcher<T, UNPACK_N_VECTORS, 1>,
    flsgpu::device::ALPExtendedColumn<T>>;

struct CLIArgs;
template <typename T>
inline void test_alp(const std::filesystem::path& path) {
	auto data_vec = read_file<T>(path);

	flsgpu::host::ALPColumn<T>  column = alp::encode(data_vec.data(), data_vec.size(), true);
	GPUArray<T>                 d_decompression_result(data_vec.size());
	constexpr int32_t           UNPACK_N_VECTORS = 1;
	const ThreadblockMapping<T> mapping(UNPACK_N_VECTORS, column.get_n_vecs());

	flsgpu::device::ALPColumn<T> d_column = column.copy_to_device();
	kernels::device::
	    decompress_column<T, UNPACK_N_VECTORS, 1, ALPDecompressor<T, UNPACK_N_VECTORS>, flsgpu::device::ALPColumn<T>>
	    <<<mapping.n_blocks, mapping.N_THREADS_PER_BLOCK>>>(d_column, d_decompression_result.get());

	CUDA_SAFE_CALL(cudaDeviceSynchronize());
	flsgpu::host::free_column(d_column);

	bool        kernel_successful = false;
	GPUArray<T> d_input(data_vec.size(), data_vec.data());

	kernel_successful =
	    check_if_device_buffers_are_equal<T>(d_decompression_result.get(), d_input.get(), column.get_n_values());

	EXPECT_TRUE(kernel_successful);

	flsgpu::host::free_column(column);
}

struct CLIArgs;
template <typename T>
inline void test_galp(const std::filesystem::path& path) {
	auto data_vec = read_file<T>(path);

	flsgpu::host::ALPColumn<T>           column          = alp::encode(data_vec.data(), data_vec.size(), true);
	flsgpu::host::ALPExtendedColumn<T>   column_extended = column.create_extended_column();
	flsgpu::device::ALPExtendedColumn<T> d_column        = column_extended.copy_to_device();
	GPUArray<T>                          d_decompression_result(data_vec.size());
	constexpr int32_t                    UNPACK_N_VECTORS = 1;
	const ThreadblockMapping<T>          mapping(UNPACK_N_VECTORS, column.get_n_vecs());
	kernels::device::decompress_column<T,
	                                   UNPACK_N_VECTORS,
	                                   1,
	                                   ALPExtendedDecompressor<T, UNPACK_N_VECTORS>,
	                                   flsgpu::device::ALPExtendedColumn<T>>
	    <<<mapping.n_blocks, mapping.N_THREADS_PER_BLOCK>>>(d_column, d_decompression_result.get());

	CUDA_SAFE_CALL(cudaDeviceSynchronize());
	double compression_ratio = column_extended.get_compression_ratio();
	std::cout << "compression_ratio : " << compression_ratio << std::endl;
	flsgpu::host::free_column(column_extended);
	flsgpu::host::free_column(d_column);
}

// -----------------------------------------------------------------------------
// Exact copy of test_galp<…>, but uses read_csv instead of read_file
// -----------------------------------------------------------------------------
template <typename T>
inline void test_galp_csv(const std::filesystem::path& path) {
	auto data_vec = read_csv<T>(path);

	flsgpu::host::ALPColumn<T>           column          = alp::encode(data_vec.data(), data_vec.size(), true);
	flsgpu::host::ALPExtendedColumn<T>   column_extended = column.create_extended_column();
	flsgpu::device::ALPExtendedColumn<T> d_column        = column_extended.copy_to_device();

	GPUArray<T>                 d_decompression_result(data_vec.size());
	constexpr int32_t           UNPACK_N_VECTORS = 1;
	const ThreadblockMapping<T> mapping(UNPACK_N_VECTORS, column.get_n_vecs());

	kernels::device::decompress_column<T,
	                                   UNPACK_N_VECTORS,
	                                   1,
	                                   ALPExtendedDecompressor<T, UNPACK_N_VECTORS>,
	                                   flsgpu::device::ALPExtendedColumn<T>>
	    <<<mapping.n_blocks, mapping.N_THREADS_PER_BLOCK>>>(d_column, d_decompression_result.get());

	CUDA_SAFE_CALL(cudaDeviceSynchronize());
	double compression_ratio = column_extended.get_compression_ratio();
	std::cout << "compression_ratio : " << compression_ratio << std::endl;

	flsgpu::host::free_column(column_extended);
	flsgpu::host::free_column(d_column);
}

TEST(ALP, TEST_ALP) {
	// -------------------------------------------------------------------------
	// (0) Generate new binaries + discover directories
	// -------------------------------------------------------------------------
	const size_t TOTAL = 25'600 * 1'024;
	const size_t HEAD  = 0;

	const std::filesystem::path floats_dir  = FLS_GALP_SOURCE_DIR "/data/floats";
	const std::filesystem::path doubles_dir = FLS_GALP_SOURCE_DIR "/data/doubles";

	bin::GenResult gen = bin::generate_write_and_scan(floats_dir, doubles_dir, TOTAL, HEAD);
	for (const auto& path : gen.float_files) {
		test_alp<float>(path);
	}
}

TEST(GALP, TEST_GALP) {
	// -------------------------------------------------------------------------
	// (0) Generate new binaries + discover directories
	// -------------------------------------------------------------------------
	const size_t TOTAL = 25'600 * 1'024;
	const size_t HEAD  = 0;

	const std::filesystem::path floats_dir  = FLS_GALP_SOURCE_DIR "/data/floats";
	const std::filesystem::path doubles_dir = FLS_GALP_SOURCE_DIR "/data/doubles";

	bin::GenResult gen = bin::generate_write_and_scan(floats_dir, doubles_dir, TOTAL, HEAD);
	for (const auto& path : gen.float_files) {
		test_galp<float>(path);
	}
}

TEST(GALP, TEST_GALP_BY_GALP_DATASET) {
	namespace fs = std::filesystem;

	for (const auto& [name, dir] : fastlanes::galp::dataset) {
		for (const auto& entry : fs::directory_iterator(dir)) {
			if (entry.is_regular_file() && entry.path().extension() == ".csv") {
				std::cout << "Testing file: " << entry.path().string() << std::endl;
				test_galp_csv<float>(entry.path());
			}
		}
	}
}
