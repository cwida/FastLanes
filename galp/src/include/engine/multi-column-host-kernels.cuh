// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/src/include/engine/multi-column-host-kernels.cuh
// ────────────────────────────────────────────────────────
#ifndef MULTI_COLUMN_HOST_KERNELS_CUH
#define MULTI_COLUMN_HOST_KERNELS_CUH

#include "data.cuh"
#include "device-utils.cuh"
#include "generated-bindings/multi-column-device-kernels.cuh"

namespace kernels { namespace host {

template <typename T, unsigned UNPACK_N_VECS, unsigned UNPACK_N_VALUES, typename DecompressorT, typename ColumnT>
__host__ bool query_multi_column(const ColumnT column, const T magic_value, const uint32_t n_samples) {
	using DeviceColumnT          = typename ColumnT::DeviceColumnT;
	constexpr int32_t MAX_N_COLS = 10;
	DeviceColumnT     device_columns[MAX_N_COLS];

	for (int32_t c {0}; c < MAX_N_COLS; ++c) {
		// INFO: Bitwidths are shuffled to ensure that the vectors that
		// are unpacked in the same loop do not have an identical bitwidth,
		// as this might benefit branched unpackers
		data::columns::shuffle_bit_widths(column);
		device_columns[c] = column.copy_to_device();
	}

	bool                        result = false;
	GPUArray<bool>              d_out(1, &result);
	const ThreadblockMapping<T> mapping(UNPACK_N_VECS, column.get_n_vecs());

	for (uint32_t repeat {0}; repeat < n_samples; ++repeat) {
		multi_column::query_multi_column<T, UNPACK_N_VECS, UNPACK_N_VALUES, DecompressorT, DeviceColumnT>
		    <<<mapping.n_blocks, mapping.N_THREADS_PER_BLOCK>>>(device_columns[0], magic_value, d_out.get());
		CUDA_SAFE_CALL(cudaDeviceSynchronize());
	}
	for (uint32_t repeat {0}; repeat < n_samples; ++repeat) {
		multi_column::query_multi_column<T, UNPACK_N_VECS, UNPACK_N_VALUES, DecompressorT, DeviceColumnT>
		    <<<mapping.n_blocks, mapping.N_THREADS_PER_BLOCK>>>(
		        device_columns[0], device_columns[1], magic_value, d_out.get());
		CUDA_SAFE_CALL(cudaDeviceSynchronize());
	}
	for (uint32_t repeat {0}; repeat < n_samples; ++repeat) {
		multi_column::query_multi_column<T, UNPACK_N_VECS, UNPACK_N_VALUES, DecompressorT, DeviceColumnT>
		    <<<mapping.n_blocks, mapping.N_THREADS_PER_BLOCK>>>(
		        device_columns[0], device_columns[1], device_columns[2], magic_value, d_out.get());
		CUDA_SAFE_CALL(cudaDeviceSynchronize());
	}
	for (uint32_t repeat {0}; repeat < n_samples; ++repeat) {
		multi_column::query_multi_column<T, UNPACK_N_VECS, UNPACK_N_VALUES, DecompressorT, DeviceColumnT>
		    <<<mapping.n_blocks, mapping.N_THREADS_PER_BLOCK>>>(
		        device_columns[0], device_columns[1], device_columns[2], device_columns[3], magic_value, d_out.get());
		CUDA_SAFE_CALL(cudaDeviceSynchronize());
	}
	for (uint32_t repeat {0}; repeat < n_samples; ++repeat) {
		multi_column::query_multi_column<T, UNPACK_N_VECS, UNPACK_N_VALUES, DecompressorT, DeviceColumnT>
		    <<<mapping.n_blocks, mapping.N_THREADS_PER_BLOCK>>>(device_columns[0],
		                                                        device_columns[1],
		                                                        device_columns[2],
		                                                        device_columns[3],
		                                                        device_columns[4],
		                                                        magic_value,
		                                                        d_out.get());
		CUDA_SAFE_CALL(cudaDeviceSynchronize());
	}
	for (uint32_t repeat {0}; repeat < n_samples; ++repeat) {
		multi_column::query_multi_column<T, UNPACK_N_VECS, UNPACK_N_VALUES, DecompressorT, DeviceColumnT>
		    <<<mapping.n_blocks, mapping.N_THREADS_PER_BLOCK>>>(device_columns[0],
		                                                        device_columns[1],
		                                                        device_columns[2],
		                                                        device_columns[3],
		                                                        device_columns[4],
		                                                        device_columns[5],
		                                                        magic_value,
		                                                        d_out.get());
		CUDA_SAFE_CALL(cudaDeviceSynchronize());
	}
	for (uint32_t repeat {0}; repeat < n_samples; ++repeat) {
		multi_column::query_multi_column<T, UNPACK_N_VECS, UNPACK_N_VALUES, DecompressorT, DeviceColumnT>
		    <<<mapping.n_blocks, mapping.N_THREADS_PER_BLOCK>>>(device_columns[0],
		                                                        device_columns[1],
		                                                        device_columns[2],
		                                                        device_columns[3],
		                                                        device_columns[4],
		                                                        device_columns[5],
		                                                        device_columns[6],
		                                                        magic_value,
		                                                        d_out.get());
		CUDA_SAFE_CALL(cudaDeviceSynchronize());
	}
	for (uint32_t repeat {0}; repeat < n_samples; ++repeat) {
		multi_column::query_multi_column<T, UNPACK_N_VECS, UNPACK_N_VALUES, DecompressorT, DeviceColumnT>
		    <<<mapping.n_blocks, mapping.N_THREADS_PER_BLOCK>>>(device_columns[0],
		                                                        device_columns[1],
		                                                        device_columns[2],
		                                                        device_columns[3],
		                                                        device_columns[4],
		                                                        device_columns[5],
		                                                        device_columns[6],
		                                                        device_columns[7],
		                                                        magic_value,
		                                                        d_out.get());
		CUDA_SAFE_CALL(cudaDeviceSynchronize());
	}
	for (uint32_t repeat {0}; repeat < n_samples; ++repeat) {
		multi_column::query_multi_column<T, UNPACK_N_VECS, UNPACK_N_VALUES, DecompressorT, DeviceColumnT>
		    <<<mapping.n_blocks, mapping.N_THREADS_PER_BLOCK>>>(device_columns[0],
		                                                        device_columns[1],
		                                                        device_columns[2],
		                                                        device_columns[3],
		                                                        device_columns[4],
		                                                        device_columns[5],
		                                                        device_columns[6],
		                                                        device_columns[7],
		                                                        device_columns[8],
		                                                        magic_value,
		                                                        d_out.get());
		CUDA_SAFE_CALL(cudaDeviceSynchronize());
	}
	for (uint32_t repeat {0}; repeat < n_samples; ++repeat) {
		multi_column::query_multi_column<T, UNPACK_N_VECS, UNPACK_N_VALUES, DecompressorT, DeviceColumnT>
		    <<<mapping.n_blocks, mapping.N_THREADS_PER_BLOCK>>>(device_columns[0],
		                                                        device_columns[1],
		                                                        device_columns[2],
		                                                        device_columns[3],
		                                                        device_columns[4],
		                                                        device_columns[5],
		                                                        device_columns[6],
		                                                        device_columns[7],
		                                                        device_columns[8],
		                                                        device_columns[9],
		                                                        magic_value,
		                                                        d_out.get());
		CUDA_SAFE_CALL(cudaDeviceSynchronize());
	}

	for (int32_t c {0}; c < MAX_N_COLS; ++c) {
		flsgpu::host::free_column(device_columns[c]);
	}

	d_out.copy_to_host(&result);
	return result;
}
}}     // namespace kernels::host
#endif // MULTI_COLUMN_HOST_KERNELS_CUH
