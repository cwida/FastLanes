// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/test/thrust_memcpy_test.cu
// ────────────────────────────────────────────────────────
// test/test_thrust_memcpy.cu

#include <gtest/gtest.h>
#include <thrust/device_vector.h>
#include <thrust/equal.h>
#include <thrust/host_vector.h>
#include <thrust/sequence.h>

TEST(ThrustMemcpy, HostToDeviceAndBack) {
	constexpr std::size_t N = 1 << 12; // 4096 ints

	// 1) Host data: 0,1,2,…,N-1
	thrust::host_vector<int> h_src(N);
	thrust::sequence(h_src.begin(), h_src.end());

	// 2) Copy to device (H→D constructor)
	thrust::device_vector<int> d_buf = h_src;

	// 3) Copy back to host (D→H constructor)
	thrust::host_vector<int> h_dst = d_buf;

	// 4) Verify equality with a single call
	bool same = thrust::equal(h_src.begin(), h_src.end(), h_dst.begin());
	EXPECT_TRUE(same) << "Data changed after GPU round-trip";
}
