#include "TPCH.hpp"
#include "benchmarks/tpch/Queries.hpp"
#include "common/runtime/Import.hpp"
#include "common/runtime/Types.hpp"
#include "tbb/tbb.h"
#include "tpch_expected.hpp"
#include <algorithm>
#include <gtest/gtest.h>
#include <map>
#include <string>
#include <unordered_set>

using namespace runtime;
using namespace std;

static size_t vectorSize = 1024;

static size_t getThreads() {
	static size_t threads = 0;
	if (threads == 0) {
		if (auto v = std::getenv("threads"))
			threads = atoi(v);
		else
			threads = thread::hardware_concurrency();
	}
	return threads;
}

static void configFromEnv() {
	if (auto v = std::getenv("vectorSize")) vectorSize = atoi(v);
	if (auto v = std::getenv("SIMDhash")) conf.useSimdHash = atoi(v);
	if (auto v = std::getenv("SIMDjoin")) conf.useSimdJoin = atoi(v);
	if (auto v = std::getenv("SIMDsel")) conf.useSimdSel = atoi(v);
	if (auto v = std::getenv("SIMDproj")) conf.useSimdProj = atoi(v);
}


TEST(FLS, q1) {
	configFromEnv();
	Database& tpch    = TPCH::getDB();
	auto      threads = getThreads();

	auto expected = types::Numeric<12, 4>::castString("123141078.2283");

	{
		auto result = fls_q1_vectorwise(tpch, threads, vectorSize);
		EXPECT_EQ(result.tup_c, size_t(1));
		auto& revenue = result["revenue"].typedAccess<types::Numeric<12, 4>>();
		ASSERT_EQ(size_t(1), revenue.size());
		ASSERT_EQ(revenue[0], expected);
	}
}

