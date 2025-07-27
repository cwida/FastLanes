#include "fls_tester.hpp"
#include "data/mnist.hpp"

namespace fastlanes {

#define MNIST_TEST(DATASET_VAR)                                                                                     \
	TEST_F(FastLanesReaderTester, mnist_##DATASET_VAR) {                                                            \
		const std::vector<n_t> constant_cols {};                                                                       \
		const std::vector<n_t> equal_cols {};                                                                          \
		const std::vector<n_t> one_to_one_mapped_col_indexes {};                                                       \
		AllTest(mnist::DATASET_VAR, constant_cols, equal_cols, one_to_one_mapped_col_indexes);                      \
	}

	MNIST_TEST(EMNIST_LEFT)
	MNIST_TEST(EMNIST_MID_BAD)
	MNIST_TEST(EMNIST_MID_MIX_RUN)
	MNIST_TEST(EMNIST_MID_NONZERO)
	MNIST_TEST(EMNIST_RIGHT_MIX_RUN)
	MNIST_TEST(EMNIST_RIGHT_NONZERO)
	MNIST_TEST(EMNIST_ORIGINAL)

	MNIST_TEST(FASHION_MNIST_LEFT)
	MNIST_TEST(FASHION_MNIST_MID_BAD)
	MNIST_TEST(FASHION_MNIST_MID_MIX_RUN)
	MNIST_TEST(FASHION_MNIST_MID_NONZERO)
	MNIST_TEST(FASHION_MNIST_RIGHT_MIX_RUN)
	MNIST_TEST(FASHION_MNIST_RIGHT_NONZERO)
	MNIST_TEST(FASHION_MNIST_ORIGINAL)

} // namespace fastlanes