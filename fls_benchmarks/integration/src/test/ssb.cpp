#include "SSB.hpp"
#include "benchmarks/ssb/Queries.hpp"
#include "common/runtime/Import.hpp"
#include "common/runtime/Types.hpp"
#include "ssb_expected.hpp"
#include "tbb/tbb.h"
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

TEST(SSB, q11) {
	Database& tpch    = SSB::getDB();
	auto      threads = getThreads();

	auto checkResult = [&](BlockRelation* result) {
		size_t found   = 0;
		auto   revAttr = result->getAttribute("revenue");
		for (auto& block : *result) {
			auto elementsInBlock = block.size();
			found += elementsInBlock;
			auto rev = reinterpret_cast<int64_t*>(block.data(revAttr));
			ASSERT_NE(rev, nullptr);
			EXPECT_EQ(elementsInBlock, size_t(1));
			for (size_t i = 0; i < elementsInBlock; ++i) {
				EXPECT_EQ(rev[i], 3567186625180000);
			}
		};
		EXPECT_EQ(found, size_t(1));
	};

	{
		auto result = ssb::q11_hyper(tpch, threads);
		checkResult(result->result.get());
	}
	{
		auto result = ssb::q11_vectorwise(tpch, threads, vectorSize);
		checkResult(result->result.get());
	}
}

TEST(SSB, q12) {
	Database& tpch    = SSB::getDB();
	auto      threads = getThreads();

	auto checkResult = [&](BlockRelation* result) {
		size_t found   = 0;
		auto   revAttr = result->getAttribute("revenue");
		for (auto& block : *result) {
			auto elementsInBlock = block.size();
			found += elementsInBlock;
			auto rev = reinterpret_cast<int64_t*>(block.data(revAttr));
			ASSERT_NE(rev, nullptr);
			EXPECT_EQ(elementsInBlock, size_t(1));
			for (size_t i = 0; i < elementsInBlock; ++i) {
				EXPECT_EQ(rev[i], 779718135680000);
			}
		};
		EXPECT_EQ(found, size_t(1));
	};

	{
		auto result = ssb::q12_hyper(tpch, threads);
		checkResult(result->result.get());
	}
	{
		auto result = ssb::q12_vectorwise(tpch, threads, vectorSize);
		checkResult(result->result.get());
	}
}

TEST(SSB, q13) {
	Database& tpch    = SSB::getDB();
	auto      threads = getThreads();

	auto checkResult = [&](BlockRelation* result) {
		size_t found   = 0;
		auto   revAttr = result->getAttribute("revenue");
		for (auto& block : *result) {
			auto elementsInBlock = block.size();
			found += elementsInBlock;
			auto rev = reinterpret_cast<int64_t*>(block.data(revAttr));
			ASSERT_NE(rev, nullptr);
			EXPECT_EQ(elementsInBlock, size_t(1));
			for (size_t i = 0; i < elementsInBlock; ++i) {
				EXPECT_EQ(rev[i], 202559260780000);
			}
		};
		EXPECT_EQ(found, size_t(1));
	};

	{
		auto result = ssb::q13_hyper(tpch, threads);
		checkResult(result->result.get());
	}
	{
		auto result = ssb::q13_vectorwise(tpch, threads, vectorSize);
		checkResult(result->result.get());
	}
}

TEST(SSB, q21) {
	configFromEnv();
	auto& expected = q21_expected();

	auto checkResult = [&](BlockRelation* result) {
		size_t found     = 0;
		auto   yearAttr  = result->getAttribute("d_year");
		auto   brandAttr = result->getAttribute("p_brand1");
		auto   sumAttr   = result->getAttribute("revenue");
		for (auto& block : *result) {
			auto elementsInBlock = block.size();
			auto brand           = reinterpret_cast<types::Char<9>*>(block.data(brandAttr));
			auto year            = reinterpret_cast<types::Integer*>(block.data(yearAttr));
			auto sum             = reinterpret_cast<types::Numeric<18, 2>*>(block.data(sumAttr));
			for (size_t i = 0; i < elementsInBlock; ++i) {
				if (expected.find(make_tuple(year[i], brand[i])) != expected.end()) {
					ASSERT_EQ(sum[i], expected[make_tuple(year[i], brand[i])]);
				}
				found++;
			}
		};
		EXPECT_EQ(found, expected.size());
	};

	Database& tpch    = SSB::getDB();
	auto      threads = getThreads();

	{
		auto result = ssb::q21_hyper(tpch, threads);
		checkResult(result->result.get());
	}
	{
		auto result = ssb::q21_vectorwise(tpch, threads, vectorSize);
		checkResult(result->result.get());
	}
}

TEST(SSB, q22) {
	configFromEnv();
	auto& expected = q22_expected();

	auto checkResult = [&](BlockRelation* result) {
		size_t found     = 0;
		auto   yearAttr  = result->getAttribute("d_year");
		auto   brandAttr = result->getAttribute("p_brand1");
		auto   sumAttr   = result->getAttribute("revenue");
		for (auto& block : *result) {
			auto elementsInBlock = block.size();
			auto brand           = reinterpret_cast<types::Char<9>*>(block.data(brandAttr));
			auto year            = reinterpret_cast<types::Integer*>(block.data(yearAttr));
			auto sum             = reinterpret_cast<types::Numeric<18, 2>*>(block.data(sumAttr));
			for (size_t i = 0; i < elementsInBlock; ++i) {
				if (expected.find(make_tuple(year[i], brand[i])) != expected.end()) {
					ASSERT_EQ(sum[i], expected[make_tuple(year[i], brand[i])]);
				}
				found++;
			}
		};
		EXPECT_EQ(found, expected.size());
	};

	Database& tpch    = SSB::getDB();
	auto      threads = getThreads();

	{
		auto result = ssb::q22_hyper(tpch, threads);
		checkResult(result->result.get());
	}
	{
		auto result = ssb::q22_vectorwise(tpch, threads, vectorSize);
		checkResult(result->result.get());
	}
}

TEST(SSB, q23) {
	configFromEnv();
	auto& expected = q23_expected();

	auto checkResult = [&](BlockRelation* result) {
		size_t found     = 0;
		auto   yearAttr  = result->getAttribute("d_year");
		auto   brandAttr = result->getAttribute("p_brand1");
		auto   sumAttr   = result->getAttribute("revenue");
		for (auto& block : *result) {
			auto elementsInBlock = block.size();
			auto brand           = reinterpret_cast<types::Char<9>*>(block.data(brandAttr));
			auto year            = reinterpret_cast<types::Integer*>(block.data(yearAttr));
			auto sum             = reinterpret_cast<types::Numeric<18, 2>*>(block.data(sumAttr));
			for (size_t i = 0; i < elementsInBlock; ++i) {
				if (expected.find(make_tuple(year[i], brand[i])) != expected.end()) {
					ASSERT_EQ(sum[i], expected[make_tuple(year[i], brand[i])]);
				}
				found++;
			}
		};
		EXPECT_EQ(found, expected.size());
	};

	Database& tpch    = SSB::getDB();
	auto      threads = getThreads();

	{
		auto result = ssb::q23_hyper(tpch, threads);
		checkResult(result->result.get());
	}
	{
		auto result = ssb::q23_vectorwise(tpch, threads, vectorSize);
		checkResult(result->result.get());
	}
}

TEST(SSB, q31) {
	configFromEnv();
	auto& expected = q31_expected();

	auto checkResult = [&](BlockRelation* result) {
		size_t found              = 0;
		auto   yearAttr           = result->getAttribute("d_year");
		auto   supplierNationAttr = result->getAttribute("s_nation");
		auto   customerNationAttr = result->getAttribute("c_nation");
		auto   sumAttr            = result->getAttribute("revenue");
		for (auto& block : *result) {
			auto elementsInBlock = block.size();
			auto c_nation        = reinterpret_cast<types::Char<15>*>(block.data(customerNationAttr));
			auto s_nation        = reinterpret_cast<types::Char<15>*>(block.data(supplierNationAttr));
			auto year            = reinterpret_cast<types::Integer*>(block.data(yearAttr));
			auto sum             = reinterpret_cast<types::Numeric<18, 2>*>(block.data(sumAttr));
			for (size_t i = 0; i < elementsInBlock; ++i) {
				if (expected.find(make_tuple(c_nation[i], s_nation[i], year[i])) != expected.end()) {
					ASSERT_EQ(sum[i], expected[make_tuple(c_nation[i], s_nation[i], year[i])]);
				}
				found++;
			}
		};
		EXPECT_EQ(found, expected.size());
	};

	Database& tpch    = SSB::getDB();
	auto      threads = getThreads();

	{
		auto result = ssb::q31_hyper(tpch, threads);
		checkResult(result->result.get());
	}
	{
		auto result = ssb::q31_vectorwise(tpch, threads, vectorSize);
		checkResult(result->result.get());
	}
}

TEST(SSB, q32) {
	configFromEnv();
	auto& expected = q32_expected();

	auto checkResult = [&](BlockRelation* result) {
		size_t found            = 0;
		auto   yearAttr         = result->getAttribute("d_year");
		auto   supplierCityAttr = result->getAttribute("s_city");
		auto   customerCityAttr = result->getAttribute("c_city");
		auto   sumAttr          = result->getAttribute("revenue");
		for (auto& block : *result) {
			auto elementsInBlock = block.size();
			auto c_city          = reinterpret_cast<types::Char<10>*>(block.data(customerCityAttr));
			auto s_city          = reinterpret_cast<types::Char<10>*>(block.data(supplierCityAttr));
			auto year            = reinterpret_cast<types::Integer*>(block.data(yearAttr));
			auto sum             = reinterpret_cast<types::Numeric<18, 2>*>(block.data(sumAttr));
			for (size_t i = 0; i < elementsInBlock; ++i) {
				if (expected.find(make_tuple(c_city[i], s_city[i], year[i])) != expected.end()) {
					EXPECT_EQ(sum[i], expected[make_tuple(c_city[i], s_city[i], year[i])]);
				}
				found++;
			}
		};
		EXPECT_EQ(found, expected.size());
	};

	Database& tpch    = SSB::getDB();
	auto      threads = getThreads();

	{
		auto result = ssb::q32_hyper(tpch, threads);
		checkResult(result->result.get());
	}
	{
		auto result = ssb::q32_vectorwise(tpch, threads, vectorSize);
		checkResult(result->result.get());
	}
}

TEST(SSB, q33) {
	configFromEnv();
	auto& expected = q33_expected();

	auto checkResult = [&](BlockRelation* result) {
		size_t found            = 0;
		auto   yearAttr         = result->getAttribute("d_year");
		auto   supplierCityAttr = result->getAttribute("s_city");
		auto   customerCityAttr = result->getAttribute("c_city");
		auto   sumAttr          = result->getAttribute("revenue");
		for (auto& block : *result) {
			auto elementsInBlock = block.size();
			auto c_city          = reinterpret_cast<types::Char<10>*>(block.data(customerCityAttr));
			auto s_city          = reinterpret_cast<types::Char<10>*>(block.data(supplierCityAttr));
			auto year            = reinterpret_cast<types::Integer*>(block.data(yearAttr));
			auto sum             = reinterpret_cast<types::Numeric<18, 2>*>(block.data(sumAttr));
			for (size_t i = 0; i < elementsInBlock; ++i) {
				if (expected.find(make_tuple(c_city[i], s_city[i], year[i])) != expected.end()) {
					EXPECT_EQ(sum[i], expected[make_tuple(c_city[i], s_city[i], year[i])]);
				}
				found++;
			}
		};
		EXPECT_EQ(found, expected.size());
	};

	Database& tpch    = SSB::getDB();
	auto      threads = getThreads();

	{
		auto result = ssb::q33_hyper(tpch, threads);
		checkResult(result->result.get());
	}
	{
		auto result = ssb::q33_vectorwise(tpch, threads, vectorSize);
		checkResult(result->result.get());
	}
}

TEST(SSB, q34) {
	configFromEnv();
	auto& expected = q34_expected();

	auto checkResult = [&](BlockRelation* result) {
		size_t found            = 0;
		auto   yearAttr         = result->getAttribute("d_year");
		auto   supplierCityAttr = result->getAttribute("s_city");
		auto   customerCityAttr = result->getAttribute("c_city");
		auto   sumAttr          = result->getAttribute("revenue");
		for (auto& block : *result) {
			auto elementsInBlock = block.size();
			auto c_city          = reinterpret_cast<types::Char<10>*>(block.data(customerCityAttr));
			auto s_city          = reinterpret_cast<types::Char<10>*>(block.data(supplierCityAttr));
			auto year            = reinterpret_cast<types::Integer*>(block.data(yearAttr));
			auto sum             = reinterpret_cast<types::Numeric<18, 2>*>(block.data(sumAttr));
			for (size_t i = 0; i < elementsInBlock; ++i) {
				if (expected.find(make_tuple(c_city[i], s_city[i], year[i])) != expected.end()) {
					EXPECT_EQ(sum[i], expected[make_tuple(c_city[i], s_city[i], year[i])]);
				}
				found++;
			}
		};
		EXPECT_EQ(found, expected.size());
	};

	Database& tpch    = SSB::getDB();
	auto      threads = getThreads();

	{
		auto result = ssb::q34_hyper(tpch, threads);
		checkResult(result->result.get());
	}
	{
		auto result = ssb::q34_vectorwise(tpch, threads, vectorSize);
		checkResult(result->result.get());
	}
}

TEST(SSB, q41) {
	configFromEnv();
	auto& expected = q41_expected();

	auto checkResult = [&](BlockRelation* result) {
		size_t found      = 0;
		auto   yearAttr   = result->getAttribute("d_year");
		auto   nationAttr = result->getAttribute("c_nation");
		auto   profitAttr = result->getAttribute("profit");
		for (auto& block : *result) {
			auto elementsInBlock = block.size();
			auto year            = reinterpret_cast<types::Integer*>(block.data(yearAttr));
			auto c_nation        = reinterpret_cast<types::Char<15>*>(block.data(nationAttr));
			auto profit          = reinterpret_cast<types::Numeric<18, 2>*>(block.data(profitAttr));
			for (size_t i = 0; i < elementsInBlock; ++i) {
				if (expected.find(make_tuple(year[i], c_nation[i])) != expected.end()) {
					EXPECT_EQ(profit[i], expected[make_tuple(year[i], c_nation[i])]);
				}
				found++;
			}
		};
		EXPECT_EQ(found, expected.size());
	};

	Database& tpch    = SSB::getDB();
	auto      threads = getThreads();

	{
		auto result = ssb::q41_hyper(tpch, threads);
		checkResult(result->result.get());
	}
	{
		auto result = ssb::q41_vectorwise(tpch, threads, vectorSize);
		checkResult(result->result.get());
	}
}

TEST(SSB, q42) {
	configFromEnv();
	auto& expected = q42_expected();

	auto checkResult = [&](BlockRelation* result) {
		size_t found        = 0;
		auto   yearAttr     = result->getAttribute("d_year");
		auto   nationAttr   = result->getAttribute("s_nation");
		auto   categoryAttr = result->getAttribute("p_category");
		auto   profitAttr   = result->getAttribute("profit");
		for (auto& block : *result) {
			auto elementsInBlock = block.size();
			auto year            = reinterpret_cast<types::Integer*>(block.data(yearAttr));
			auto c_nation        = reinterpret_cast<types::Char<15>*>(block.data(nationAttr));
			auto p_category      = reinterpret_cast<types::Char<7>*>(block.data(categoryAttr));
			auto profit          = reinterpret_cast<types::Numeric<18, 2>*>(block.data(profitAttr));
			for (size_t i = 0; i < elementsInBlock; ++i) {
				if (expected.find(make_tuple(year[i], c_nation[i], p_category[i])) != expected.end()) {
					EXPECT_EQ(profit[i], expected[make_tuple(year[i], c_nation[i], p_category[i])]);
				}
				found++;
			}
		};
		EXPECT_EQ(found, expected.size());
	};

	Database& tpch    = SSB::getDB();
	auto      threads = getThreads();

	{
		auto result = ssb::q42_hyper(tpch, threads);
		checkResult(result->result.get());
	}
	{
		auto result = ssb::q42_vectorwise(tpch, threads, vectorSize);
		checkResult(result->result.get());
	}
}

TEST(SSB, q43) {
	configFromEnv();
	auto& expected = q43_expected();

	auto checkResult = [&](BlockRelation* result) {
		size_t found      = 0;
		auto   yearAttr   = result->getAttribute("d_year");
		auto   cityAttr   = result->getAttribute("s_city");
		auto   brandAttr  = result->getAttribute("p_brand1");
		auto   profitAttr = result->getAttribute("profit");
		for (auto& block : *result) {
			auto elementsInBlock = block.size();
			auto year            = reinterpret_cast<types::Integer*>(block.data(yearAttr));
			auto s_city          = reinterpret_cast<types::Char<10>*>(block.data(cityAttr));
			auto p_brand1        = reinterpret_cast<types::Char<9>*>(block.data(brandAttr));
			auto profit          = reinterpret_cast<types::Numeric<18, 2>*>(block.data(profitAttr));
			for (size_t i = 0; i < elementsInBlock; ++i) {
				if (expected.find(make_tuple(year[i], s_city[i], p_brand1[i])) != expected.end()) {
					EXPECT_EQ(profit[i], expected[make_tuple(year[i], s_city[i], p_brand1[i])]);
				}
				found++;
			}
		};
		EXPECT_EQ(found, expected.size());
	};

	Database& tpch    = SSB::getDB();
	auto      threads = getThreads();

	{
		auto result = ssb::q43_hyper(tpch, threads);
		checkResult(result->result.get());
	}
	{
		auto result = ssb::q43_vectorwise(tpch, threads, vectorSize);
		checkResult(result->result.get());
	}
}
