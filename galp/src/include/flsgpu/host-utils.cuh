// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/src/include/flsgpu/host-utils.cuh
// ────────────────────────────────────────────────────────
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <cuda.h>
#include <cuda_runtime.h>
#include <iostream>
#include <stdio.h>

#ifndef GPU_UTILS_H
#define GPU_UTILS_H

#define CUDA_SAFE_CALL(call)                                                                                           \
	do {                                                                                                               \
		cudaError_t err = call;                                                                                        \
		if (cudaSuccess != err) {                                                                                      \
			fprintf(stderr, "Cuda error in file '%s' in line %i : %s.", __FILE__, __LINE__, cudaGetErrorString(err));  \
			exit(EXIT_FAILURE);                                                                                        \
		}                                                                                                              \
	} while (0)

#define CUDA_SAFE_CALL_TRACED(call)                                                                                    \
	do {                                                                                                               \
		fprintf(stderr, "Start CUDA_CALL ['%s': line %i\n", __FILE__, __LINE__);                                       \
		cudaError_t err = call;                                                                                        \
		fprintf(stderr, "End CUDA_CALL ['%s': line %i\n", __FILE__, __LINE__);                                         \
		if (cudaSuccess != err) {                                                                                      \
			fprintf(stderr, "Cuda error in file '%s' in line %i : %s.", __FILE__, __LINE__, cudaGetErrorString(err));  \
			exit(EXIT_FAILURE);                                                                                        \
		}                                                                                                              \
	} while (0)

template <typename T>
void free_device_pointer(T*& device_ptr) {
	if (device_ptr != nullptr) {
		CUDA_SAFE_CALL(cudaFree(device_ptr));
	}
	device_ptr = nullptr;
}

template <typename T>
class GPUArray {
private:
	size_t allocation_size;
	size_t memory_size;
	T*     device_ptr = nullptr;

	void allocate() {
		CUDA_SAFE_CALL(cudaMalloc(reinterpret_cast<void**>(&device_ptr), allocation_size));
	}

public:
	GPUArray(const size_t count) {
		memory_size     = count * sizeof(T);
		allocation_size = memory_size;
		allocate();
	}

	GPUArray(const size_t count, const T* host_p) {
		memory_size     = count * sizeof(T);
		allocation_size = memory_size;
		allocate();
		CUDA_SAFE_CALL(cudaMemcpy(device_ptr, host_p, memory_size, cudaMemcpyHostToDevice));
	}

	GPUArray(const size_t count, const size_t buffer, const T* host_p) {
		memory_size     = count * sizeof(T);
		allocation_size = memory_size + buffer * sizeof(T);
		allocate();

		CUDA_SAFE_CALL(cudaMemcpy(device_ptr, host_p, memory_size, cudaMemcpyHostToDevice));
	}

	// Copy constructor
	GPUArray(const GPUArray&) = delete;
	// Assignment operator deleted
	GPUArray& operator=(const GPUArray&) = delete;

	// Move constructor
	GPUArray(GPUArray&& other) noexcept
	    : device_ptr(other.device_ptr) {
		other.device_ptr = nullptr;
	}

	// Assignment operator
	GPUArray& operator=(GPUArray&& other) noexcept {
		if (this != &other) {
			free_device_pointer(device_ptr);
			device_ptr       = other.device_ptr;
			other.device_ptr = nullptr;
		}
		return *this;
	}

	~GPUArray() {
		free_device_pointer(device_ptr);
	}

	void copy_to_host(T* host_p) {
		CUDA_SAFE_CALL(cudaMemcpy(host_p, device_ptr, memory_size, cudaMemcpyDeviceToHost));
	}

	T* get() {
		return device_ptr;
	}

	T* release() {
		auto temp  = device_ptr;
		device_ptr = nullptr;
		return temp;
	}
};

#endif // GPU_UTILS_H
