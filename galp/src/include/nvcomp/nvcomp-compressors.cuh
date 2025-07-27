// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/src/include/nvcomp/nvcomp-compressors.cuh
// ────────────────────────────────────────────────────────
#include <assert.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <random>
#include <stdexcept>

#ifndef NVCOMP_COMPRESSORS_H
#define NVCOMP_COMPRESSORS_H

#include "engine/enums.cuh"
#include "flsgpu/flsgpu-api.cuh"
#include "nvcomp.h"
#include "nvcomp.hpp"
#include "nvcomp/benchmark-compressors.cuh"
#include "nvcomp/deflate.h"
#include "nvcomp/deflate.hpp"
#include "nvcomp/gdeflate.h"
#include "nvcomp/gdeflate.hpp"
#include "nvcomp/lz4.hpp"
#include "nvcomp/nvcompManager.hpp"
#include "nvcomp/nvcompManagerFactory.hpp"
#include "nvcomp/zstd.h"
#include "nvcomp/zstd.hpp"

namespace hwc {
using nvcompCompressionManager = nvcomp::PimplManager;

nvcompCompressionManager* get_compressor_manager(const enums_nvcomp::CompressionType compression_type,
                                                 const nvcompType_t                  data_type  = NVCOMP_TYPE_CHAR,
                                                 const size_t                        chunk_size = 1 << 16);

struct CompressedBuffer {
	nvcomp::CompressionConfig compression_config;
	uint8_t*                  compressed_buffer;
	size_t                    decompressed_size;
	size_t                    compressed_size;

	CompressedBuffer(nvcomp::CompressionConfig compression_config)
	    : compression_config(compression_config) {

		CUDA_SAFE_CALL(cudaMalloc(&compressed_buffer, compression_config.max_compressed_buffer_size));
	}

	double get_compression_ratio() {
		return static_cast<double>(decompressed_size) / static_cast<double>(compressed_size);
	}

	double get_allocation_compression_ratio() {
		return static_cast<double>(compression_config.max_compressed_buffer_size) /
		       static_cast<double>(compression_config.uncompressed_buffer_size);
	}

	// Manual resource freeing
	void free() {
		CUDA_SAFE_CALL(cudaFree(compressed_buffer));
	}
};

struct Compressor {
	nvcompCompressionManager* manager;

	Compressor(const enums_nvcomp::CompressionType compression_type) {
		manager = get_compressor_manager(compression_type);
	}

	CompressedBuffer compress(uint8_t* input_buffer, const size_t input_buffer_len) {
		CompressedBuffer compressed_buffer(manager->configure_compression(input_buffer_len));
		manager->compress(input_buffer, compressed_buffer.compressed_buffer, compressed_buffer.compression_config);
		compressed_buffer.decompressed_size = input_buffer_len;
		compressed_buffer.compressed_size   = manager->get_compressed_output_size(compressed_buffer.compressed_buffer);
		return compressed_buffer;
	}

	uint8_t* decompress(const CompressedBuffer compressed_buffer, CudaStopwatch& stopwatch) {
		nvcomp::DecompressionConfig decomp_config =
		    manager->configure_decompression(compressed_buffer.compressed_buffer);
		uint8_t* decompressed_buffer;
		CUDA_SAFE_CALL(cudaMalloc(&decompressed_buffer, decomp_config.decomp_data_size));

		stopwatch.start();
		manager->decompress(decompressed_buffer, compressed_buffer.compressed_buffer, decomp_config);
		stopwatch.stop();

		return decompressed_buffer;
	}

	// Manual resource freeing
	void free() {
		delete manager;
	}
};

__global__ void check_buffer_equality(const uint8_t* buffer_a, const uint8_t* buffer_b, const size_t length, bool* out);

bool compare_d_buffers(const uint8_t* buffer_a, const uint8_t* buffer_b, const size_t length);

template <typename T>
struct DummyColumn {
	T*     in;
	size_t n_values;
};

template <typename T>
struct DummyDecompressor : flsgpu::device::DecompressorBase<T> {
	using UINT_T = typename utils::same_width_uint<T>::type;
	flsgpu::device::BitUnpackerDummy<T, 1, 1, flsgpu::device::BPFunctor<T>> unpacker;

	__device__ __forceinline__
	DummyDecompressor(const DummyColumn<T> column, const vi_t vector_index, const lane_t lane)
	    : unpacker(reinterpret_cast<UINT_T*>(column.in + vector_index * consts::VALUES_PER_VECTOR),
	               lane,
	               utils::sizeof_in_bits<T>(),
	               flsgpu::device::BPFunctor<T>()) {
	}

	void __device__ unpack_next_into(T* __restrict out) {
		unpacker.unpack_next_into(out);
	}
};

} // namespace hwc

#endif // NVCOMP_COMPRESSORS_H
