#ifndef TEST_TESTER_HPP
#define TEST_TESTER_HPP

#include "fls/common/common.hpp"
#include "fls/std/filesystem.hpp"
#include "test/tester.hpp"
#include <fls/std/string.hpp>
#include <gtest/gtest.h>

namespace fastlanes {
class Dir;

class Tester : public ::testing::Test {

public:
	static void Test(const path& dir_path);
	static void Test(const path& dir_path, idx_t col_id);
	static void RealNestTest(const string& table_name);
};

#define FLS_COLOUMN_TEST(DATASET_NAME, TABLE_NAME, ID)                                                                 \
	TEST_F(Tester, DATASET_NAME##_##TABLE_NAME_##ID) {                                                                 \
		Test(DATASET_NAME::TABLE_NAME, ID);                                                                            \
	};

#define FLS_TABLE_TEST(DATASET_NAME, TABLE_NAME)                                                                       \
	TEST_F(Tester, DATASET_NAME##_##TABLE_NAME) {                                                                      \
		Test(DATASET_NAME::TABLE_NAME);                                                                                \
	};

#define FLS_REALNEST_READ_TEST(ID, TABLE_NAME)                                                                         \
	TEST_F(Tester, REALNEST_##ID) {                                                                                    \
		RealNestTest(TABLE_NAME);                                                                                      \
	};

} // namespace fastlanes
#endif // TEST_TESTER_HPP
