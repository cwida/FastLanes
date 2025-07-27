// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/src/include/nvcomp/benchmark-compressors.cuh
// ────────────────────────────────────────────────────────
#include "../engine/enums.cuh"
#include "../flsgpu/flsgpu-api.cuh"
#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <memory>
#include <stdexcept>
#include <string>
#include <thrust/device_vector.h>
#include <thrust/execution_policy.h>
#include <thrust/host_vector.h>
#include <thrust/logical.h>

#ifndef BENCHMARK_COMPRESSORS_CUH
#define BENCHMARK_COMPRESSORS_CUH

template <typename T>
bool check_if_device_buffers_are_equal(const T* a, const T* b, const size_t n_values) {
	// Convert to uint8_t as we don't want to compare floats (-nan == -nan =>
	// false)
	thrust::device_ptr<uint8_t> d_a(reinterpret_cast<uint8_t*>(const_cast<T*>(a)));
	thrust::device_ptr<uint8_t> d_b(reinterpret_cast<uint8_t*>(const_cast<T*>(b)));

	return thrust::equal(d_a, d_a + n_values, d_b);
}

class CudaStopwatch {
private:
	cudaEvent_t  startEvent, stopEvent;
	cudaStream_t stream;
	float        milliseconds = 0.0f;

public:
	CudaStopwatch(cudaStream_t stream = 0)
	    : stream(stream) {
		CUDA_SAFE_CALL(cudaEventCreate(&startEvent));
		CUDA_SAFE_CALL(cudaEventCreate(&stopEvent));
	}

	~CudaStopwatch() {
		CUDA_SAFE_CALL(cudaEventDestroy(startEvent));
		CUDA_SAFE_CALL(cudaEventDestroy(stopEvent));
	}

	void start() {
		CUDA_SAFE_CALL(cudaDeviceSynchronize());
		CUDA_SAFE_CALL(cudaEventRecord(startEvent, stream));
	}

	double stop() {
		CUDA_SAFE_CALL(cudaEventRecord(stopEvent, stream));
		CUDA_SAFE_CALL(cudaEventSynchronize(stopEvent));
		CUDA_SAFE_CALL(cudaDeviceSynchronize());

		CUDA_SAFE_CALL(cudaEventElapsedTime(&milliseconds, startEvent, stopEvent));
		return milliseconds;
	}

	double get_result() {
		return milliseconds;
	}
};

struct BenchmarkResult {
	bool   results_match;
	double execution_time_ms;
	double compression_ratio;

	void log_result(const enums_nvcomp::ComparisonType  comparison_type,
	                const enums_nvcomp::CompressionType compression_type,
	                const size_t                        n_bytes,
	                const std::string                   data_name) const {

		const char* is_valid = results_match ? "valid" : "wrong";

		printf("%s,%s,%s,%s,%lu,%f,%f\n",
		       enums_nvcomp::comparison_type_to_string(comparison_type).c_str(),
		       enums_nvcomp::compression_type_to_string(compression_type).c_str(),
		       data_name.c_str(),
		       is_valid,
		       n_bytes,
		       execution_time_ms,
		       compression_ratio);
	}
};

template <typename T>
struct is_equal_to {
	T value;
	is_equal_to(T value)
	    : value(value) {
	}
	__host__ __device__ bool operator()(T x) {
		return x == value;
	}
};

template <typename T>
BenchmarkResult benchmark_thrust(const T* input, const size_t value_count, const T value_to_search_for);

template <typename T>
BenchmarkResult benchmark_alp(const enums_nvcomp::ComparisonType  comparison_type,
                              const enums_nvcomp::CompressionType decompressor_enum,
                              const T*                            input,
                              const size_t                        value_count,
                              const T                             value_to_search_for);

template <typename T>
BenchmarkResult benchmark_hwc(const enums_nvcomp::ComparisonType  comparison_type,
                              const enums_nvcomp::CompressionType compression_type,
                              const T*                            input,
                              const size_t                        value_count,
                              const T                             value_to_search_for);

BenchmarkResult benchmark_thrust(const float* input, const size_t value_count, const float value_to_search_for);
BenchmarkResult benchmark_alp(const enums_nvcomp::ComparisonType  comparison_type,
                              const enums_nvcomp::CompressionType decompressor_enum,
                              const float*                        input,
                              const size_t                        value_count,
                              const float                         value_to_search_for);
BenchmarkResult benchmark_hwc(const enums_nvcomp::ComparisonType  comparison_type,
                              const enums_nvcomp::CompressionType compression_type,
                              const float*                        input,
                              const size_t                        value_count,
                              const float                         value_to_search_for);

BenchmarkResult benchmark_thrust(const double* input, const size_t value_count, const double value_to_search_for);
BenchmarkResult benchmark_alp(const enums_nvcomp::ComparisonType  comparison_type,
                              const enums_nvcomp::CompressionType decompressor_enum,
                              const double*                       input,
                              const size_t                        value_count,
                              const double                        value_to_search_for);
BenchmarkResult benchmark_hwc(const enums_nvcomp::ComparisonType  comparison_type,
                              const enums_nvcomp::CompressionType compression_type,
                              const double*                       input,
                              const size_t                        value_count,
                              const double                        value_to_search_for);

#endif // BENCHMARK_COMPRESSORS_CUH
