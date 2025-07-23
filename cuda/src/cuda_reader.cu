// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// cuda/src/cuda_reader.cu
// ────────────────────────────────────────────────────────
#include <cstdio>

// A simple CUDA Hello World example
// This kernel prints a greeting from each thread on the GPU
__global__ void hello_from_gpu() {
	int tid = threadIdx.x;
	printf("Hello World from GPU! Thread %d says hi.\n", tid);
}

int main() {
	// Launch the kernel with 4 threads in one block
	hello_from_gpu<<<1, 4>>>();

	// Wait for GPU to finish before accessing on host
	cudaDeviceSynchronize();

	// And return
	return 0;
}
