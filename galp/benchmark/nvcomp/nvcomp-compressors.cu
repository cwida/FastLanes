// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/benchmark/nvcomp/nvcomp-compressors.cu
// ────────────────────────────────────────────────────────
#include "nvcomp/nvcomp-compressors.cuh"
#include <assert.h>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <stdexcept>

namespace hwc {
nvcompCompressionManager* get_compressor_manager(const enums_nvcomp::CompressionType compression_type,
                                                 const nvcompType_t                  data_type,
                                                 const size_t                        chunk_size) {
	switch (compression_type) {
	case enums_nvcomp::CompressionType::BITCOMP: {
		nvcompBatchedBitcompOpts_t format_opts {0, data_type};
		return new nvcomp::BitcompManager {chunk_size, format_opts};
	} break;
	case enums_nvcomp::CompressionType::BITCOMP_SPARSE: {
		nvcompBatchedBitcompOpts_t format_opts {1, data_type};
		return new nvcomp::BitcompManager {chunk_size, format_opts};
	} break;
	case enums_nvcomp::CompressionType::LZ4: {
		nvcompBatchedLZ4Opts_t format_opts {data_type};
		return new nvcomp::LZ4Manager {chunk_size, format_opts};
	} break;
	case enums_nvcomp::CompressionType::ZSTD: {
		nvcompBatchedZstdOpts_t format_opts {data_type};
		return new nvcomp::ZstdManager {chunk_size, format_opts};
	} break;
	case enums_nvcomp::CompressionType::DEFLATE: {
		nvcompBatchedDeflateOpts_t format_opts {data_type};
		return new nvcomp::DeflateManager {chunk_size, format_opts};
	} break;
	case enums_nvcomp::CompressionType::GDEFLATE: {
		nvcompBatchedGdeflateOpts_t format_opts {data_type};
		return new nvcomp::GdeflateManager {chunk_size, format_opts};
	} break;
	case enums_nvcomp::CompressionType::SNAPPY: {
		nvcompBatchedSnappyOpts_t format_opts {data_type};
		return new nvcomp::SnappyManager {chunk_size, format_opts};
	} break;
	default:
		throw std::invalid_argument("Compression type is not supported");
	}
}

__global__ void
check_buffer_equality(const uint8_t* buffer_a, const uint8_t* buffer_b, const size_t length, bool* out) {
	constexpr int32_t N_ELEMENTS_PER_THREAD = 4 * 32;
	size_t            index                 = N_ELEMENTS_PER_THREAD * (threadIdx.x + blockIdx.x * blockDim.x);

	bool buffers_are_equal = true;

#pragma unroll
	for (int32_t i {0}; i < N_ELEMENTS_PER_THREAD; ++i) {
		if (index + i < length) {
			buffers_are_equal &= buffer_a[index + i] == buffer_b[index + i];
		}
	}

	if (!buffers_are_equal) {
		*out = false;
	}
}

bool compare_d_buffers(const uint8_t* buffer_a, const uint8_t* buffer_b, const size_t length) {
	bool  result = true;
	bool* d_result;
	CUDA_SAFE_CALL(cudaMalloc(&d_result, sizeof(bool) * 1));
	CUDA_SAFE_CALL(cudaMemcpy(d_result, &result, sizeof(bool) * 1, cudaMemcpyHostToDevice));

	const int n_blocks = (length + (1024 * 128) - 1) / (1024 * 128);
	check_buffer_equality<<<n_blocks, 1024>>>(buffer_a, buffer_b, length, d_result);

	CUDA_SAFE_CALL(cudaMemcpy(&result, d_result, sizeof(bool) * 1, cudaMemcpyDeviceToHost));
	CUDA_SAFE_CALL(cudaFree(d_result));

	return result;
}

} // namespace hwc
