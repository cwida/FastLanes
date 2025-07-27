// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// galp/test/thrust_core_test.cu
// ────────────────────────────────────────────────────────
#include <gtest/gtest.h>
#include <thrust/device_vector.h>
#include <thrust/equal.h>
#include <thrust/fill.h>
#include <thrust/functional.h>
#include <thrust/host_vector.h>
#include <thrust/iterator/counting_iterator.h>
#include <thrust/iterator/zip_iterator.h>
#include <thrust/reduce.h>
#include <thrust/scan.h>
#include <thrust/sequence.h>
#include <thrust/set_operations.h>
#include <thrust/sort.h>
#include <thrust/transform.h>
#include <thrust/tuple.h>
#include <thrust/unique.h>

// --------------------------------------------------------------------
// Custom functor for zip transform
// --------------------------------------------------------------------
struct SumTuple {
	__host__ __device__ int operator()(const thrust::tuple<int, int>& t) const {
		return thrust::get<0>(t) + thrust::get<1>(t);
	}
};

// --------------------------------------------------------------------
// 1. Containers & element-wise algorithms
// --------------------------------------------------------------------
TEST(ThrustCore, TransformAdd) {
	const int                  N = 128;
	thrust::device_vector<int> a(N);
	thrust::device_vector<int> b(N);
	thrust::device_vector<int> c(N);

	thrust::sequence(a.begin(), a.end(), 0); // 0..N-1
	thrust::fill(b.begin(), b.end(), 1);     // all 1

	thrust::transform(a.begin(), a.end(), b.begin(), c.begin(), thrust::plus<int>());

	thrust::host_vector<int> h(c);
	for (int i = 0; i < N; ++i)
		EXPECT_EQ(h[i], i + 1);
}

// --------------------------------------------------------------------
// 2. Reductions & scans
// --------------------------------------------------------------------
TEST(ThrustCore, ReduceAndInclusiveScan) {
	const int                  N = 256;
	thrust::device_vector<int> d(N);
	thrust::sequence(d.begin(), d.end(), 1); // 1..N

	int gpu_sum = thrust::reduce(d.begin(), d.end());
	int ref_sum = N * (N + 1) / 2;
	EXPECT_EQ(gpu_sum, ref_sum);

	thrust::inclusive_scan(d.begin(), d.end(), d.begin());

	int last = d.back();
	EXPECT_EQ(last, ref_sum);
}

// --------------------------------------------------------------------
// 3. Sorting & uniquing
// --------------------------------------------------------------------
TEST(ThrustCore, SortAndUnique) {
	std::vector<int>           temp = {5, 1, 4, 4, 3, 2, 1};
	thrust::host_vector<int>   h(temp.begin(), temp.end());
	thrust::device_vector<int> d = h;

	thrust::sort(d.begin(), d.end());
	auto new_end = thrust::unique(d.begin(), d.end());

	EXPECT_EQ(new_end - d.begin(), 5);

	thrust::host_vector<int> out(d.begin(), new_end);
	std::vector<int>         ref = {1, 2, 3, 4, 5};
	EXPECT_TRUE(std::equal(out.begin(), out.end(), ref.begin()));
}

// --------------------------------------------------------------------
// 4. Zip iterator, counting iterator & transform iterator
// --------------------------------------------------------------------
TEST(ThrustCore, CountingAndZipIter) {
	const int N      = 64;
	auto      first  = thrust::make_counting_iterator<int>(0);
	auto      second = thrust::make_counting_iterator<int>(0);

	thrust::device_vector<int> d(N);

	thrust::transform(thrust::make_zip_iterator(thrust::make_tuple(first, second)),
	                  thrust::make_zip_iterator(thrust::make_tuple(first + N, second + N)),
	                  d.begin(),
	                  SumTuple());

	thrust::host_vector<int> h = d;
	for (int i = 0; i < N; ++i)
		EXPECT_EQ(h[i], i + i);
}

// --------------------------------------------------------------------
// 5. Set difference (requires sorted ranges)
// --------------------------------------------------------------------
TEST(ThrustCore, SetDifference) {
	std::vector<int> tempA = {0, 1, 2, 3, 4, 5};
	std::vector<int> tempB = {1, 3, 5};

	thrust::device_vector<int> A(tempA.begin(), tempA.end());
	thrust::device_vector<int> B(tempB.begin(), tempB.end());
	thrust::device_vector<int> diff(A.size());

	auto end = thrust::set_difference(A.begin(), A.end(), B.begin(), B.end(), diff.begin());

	thrust::host_vector<int> h(diff.begin(), end);
	std::vector<int>         ref = {0, 2, 4};
	EXPECT_TRUE(std::equal(h.begin(), h.end(), ref.begin()));
}
