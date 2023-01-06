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

TEST(TPCH, q1) {
	configFromEnv();
	using namespace types;
	std::map<tuple<Char<1>, Char<1>>, tuple<Numeric<12, 2>, Numeric<12, 2>, Numeric<12, 4>, Numeric<12, 6>, int64_t>>
	    expected = {{make_tuple(Char<1>::castString("A"), Char<1>::castString("F")),
	                 make_tuple(Numeric<12, 2>::castString("37734107.00"),
	                            Numeric<12, 2>::castString("56586554400.73"),
	                            Numeric<12, 4>::castString("53758257134.8700"),
	                            Numeric<12, 6>::castString("55909065222.827692"),
	                            1478493)},

	                {make_tuple(Char<1>::castString("N"), Char<1>::castString("F")),
	                 make_tuple(Numeric<12, 2>::castString("991417.00"),
	                            Numeric<12, 2>::castString("1487504710.38"),
	                            Numeric<12, 4>::castString("1413082168.0541"),
	                            Numeric<12, 6>::castString("1469649223.194375"),
	                            38854)},

	                {make_tuple(Char<1>::castString("N"), Char<1>::castString("O")),
	                 make_tuple(Numeric<12, 2>::castString("74476040.00"),
	                            Numeric<12, 2>::castString("111701729697.74"),
	                            Numeric<12, 4>::castString("106118230307.6056"),
	                            Numeric<12, 6>::castString("110367043872.497010"),
	                            2920374)},

	                {make_tuple(Char<1>::castString("R"), Char<1>::castString("F")),
	                 make_tuple(Numeric<12, 2>::castString("37719753.00"),
	                            Numeric<12, 2>::castString("56568041380.90"),
	                            Numeric<12, 4>::castString("53741292684.6040"),
	                            Numeric<12, 6>::castString("55889619119.831932"),
	                            1478870)}};

	auto checkResult = [&](BlockRelation* result) {
		size_t found           = 0;
		auto   retAttr         = result->getAttribute("l_returnflag");
		auto   statusAttr      = result->getAttribute("l_linestatus");
		auto   qtyAttr         = result->getAttribute("sum_qty");
		auto   base_priceAttr  = result->getAttribute("sum_base_price");
		auto   disc_priceAttr  = result->getAttribute("sum_disc_price");
		auto   chargeAttr      = result->getAttribute("sum_charge");
		auto   count_orderAttr = result->getAttribute("count_order");
		for (auto& block : *result) {
			auto elementsInBlock = block.size();
			found += elementsInBlock;
			auto ret         = reinterpret_cast<Char<1>*>(block.data(retAttr));
			auto status      = reinterpret_cast<Char<1>*>(block.data(statusAttr));
			auto qty         = reinterpret_cast<Numeric<12, 2>*>(block.data(qtyAttr));
			auto base_price  = reinterpret_cast<Numeric<12, 2>*>(block.data(base_priceAttr));
			auto disc_price  = reinterpret_cast<Numeric<12, 4>*>(block.data(disc_priceAttr));
			auto charge      = reinterpret_cast<Numeric<12, 6>*>(block.data(chargeAttr));
			auto count_order = reinterpret_cast<int64_t*>(block.data(count_orderAttr));
			for (size_t i = 0; i < elementsInBlock; ++i) {
				auto& exValues = expected[make_tuple(ret[i], status[i])];
				ASSERT_EQ(qty[i], get<0>(exValues));
				ASSERT_EQ(base_price[i], get<1>(exValues));
				ASSERT_EQ(disc_price[i], get<2>(exValues));
				ASSERT_EQ(charge[i], get<3>(exValues));
				ASSERT_EQ(count_order[i], get<4>(exValues));
			}
		};
		EXPECT_EQ(found, expected.size());
	};

	Database& tpch    = TPCH::getDB();
	auto      threads = getThreads();

	{
		// run queries
		auto result = q1_hyper(tpch, threads);
		checkResult(result->result.get());
	}
	{
		auto result = q1_vectorwise(tpch, threads, vectorSize);
		checkResult(result->result.get());
	}
}

TEST(TPCH, q3) {
	configFromEnv();
	using rev_t    = types::Numeric<12, 4>;
	auto& expected = q3_expected();

	auto checkResult = [&](BlockRelation* result) {
		size_t found       = 0;
		auto   keyAttr     = result->getAttribute("l_orderkey");
		auto   dateAttr    = result->getAttribute("o_orderdate");
		auto   prioAttr    = result->getAttribute("o_shippriority");
		auto   revenueAttr = result->getAttribute("revenue");
		for (auto& block : *result) {
			auto elementsInBlock = block.size();
			found += elementsInBlock;
			auto key     = reinterpret_cast<types::Integer*>(block.data(keyAttr));
			auto date    = reinterpret_cast<types::Date*>(block.data(dateAttr));
			auto prio    = reinterpret_cast<types::Integer*>(block.data(prioAttr));
			auto revenue = reinterpret_cast<rev_t*>(block.data(revenueAttr));
			for (size_t i = 0; i < elementsInBlock; ++i) {
				ASSERT_EQ(revenue[i], expected[make_tuple(key[i], date[i], prio[i])]);
			}
		};
		EXPECT_EQ(found, expected.size());
	};
	Database& tpch    = TPCH::getDB();
	auto      threads = getThreads();

	{
		// run queries
		auto result = q3_hyper(tpch, threads);
		checkResult(result->result.get());
	}
	{
		auto result = q3_vectorwise(tpch, threads, vectorSize);
		checkResult(result->result.get());
	}
}

TEST(TPCH, q5) {
	configFromEnv();
	using Char25 = vectorwise::primitives::Char_25;
	using rev_t  = types::Numeric<12, 4>;

	std::unordered_map<vectorwise::primitives::Char_25, types::Numeric<12, 4>> expected = {
	    {types::Char<25>::castString("INDONESIA"), types::Numeric<12, 4>::castString("55502041.1697")},
	    {types::Char<25>::castString("VIETNAM"), types::Numeric<12, 4>::castString("55295086.9967")},
	    {types::Char<25>::castString("CHINA"), types::Numeric<12, 4>::castString("53724494.2566")},
	    {types::Char<25>::castString("INDIA"), types::Numeric<12, 4>::castString("52035512.0002")},
	    {types::Char<25>::castString("JAPAN"), types::Numeric<12, 4>::castString("45410175.6954")}};

	Database& tpch    = TPCH::getDB();
	auto      threads = getThreads();

	auto checkResult = [&](BlockRelation* result) {
		size_t found       = 0;
		auto   nameAttr    = result->getAttribute("n_name");
		auto   revenueAttr = result->getAttribute("revenue");
		for (auto& block : *result) {
			auto elementsInBlock = block.size();
			found += elementsInBlock;
			auto name    = reinterpret_cast<Char25*>(block.data(nameAttr));
			auto revenue = reinterpret_cast<rev_t*>(block.data(revenueAttr));
			for (size_t i = 0; i < elementsInBlock; ++i) {
				ASSERT_GT(name[i].len, 0);
				ASSERT_LE(name[i].len, 25);
				ASSERT_EQ(revenue[i], expected[name[i]]);
			}
		};
		EXPECT_EQ(found, size_t(5));
	};
	// run queries
	{
		auto result = q5_hyper(tpch, threads);
		checkResult(result->result.get());
	}
	{
		auto result = q5_vectorwise(tpch, threads, vectorSize);
		checkResult(result->result.get());
	}
}

TEST(TPCH, q6) {
	configFromEnv();
	Database& tpch    = TPCH::getDB();
	auto      threads = getThreads();

	auto expected = types::Numeric<12, 4>::castString("123141078.2283");
	{
		// run queries
		auto result = q6_hyper(tpch, threads);
		EXPECT_EQ(result.tup_c, size_t(1));
		auto& revenue = result["revenue"].typedAccess<types::Numeric<12, 4>>();
		ASSERT_EQ(size_t(1), revenue.size());
		ASSERT_EQ(expected, revenue[0]);
	}

	{
		auto result = q6_vectorwise(tpch, threads, vectorSize);
		EXPECT_EQ(result.tup_c, size_t(1));
		auto& revenue = result["revenue"].typedAccess<types::Numeric<12, 4>>();
		ASSERT_EQ(size_t(1), revenue.size());
		ASSERT_EQ(revenue[0], expected);
	}
}

TEST(TPCH, q9) {
	configFromEnv();
	auto& expected = q9_expected();

	auto checkResult = [&](BlockRelation* result) {
		size_t found          = 0;
		auto   nationAttr     = result->getAttribute("nation");
		auto   o_yearAttr     = result->getAttribute("o_year");
		auto   sum_profitAttr = result->getAttribute("sum_profit");
		for (auto& block : *result) {
			auto elementsInBlock = block.size();
			found += elementsInBlock;
			auto nation     = reinterpret_cast<types::Char<25>*>(block.data(nationAttr));
			auto o_year     = reinterpret_cast<types::Integer*>(block.data(o_yearAttr));
			auto sum_profit = reinterpret_cast<types::Numeric<12, 4>*>(block.data(sum_profitAttr));
			for (size_t i = 0; i < elementsInBlock; ++i) {
				auto exp = expected.find(make_tuple(nation[i], o_year[i]));
				if (exp == expected.end()) {
					cerr << "Not found: " << nation[i] << "" << o_year[i];
					ASSERT_NE(exp, expected.end());
				}
				ASSERT_EQ(sum_profit[i], exp->second);
			}
		};
		EXPECT_EQ(found, expected.size());
	};
	Database& tpch    = TPCH::getDB();
	auto      threads = getThreads();

	{
		// run queries
		auto result = q9_hyper(tpch, threads);
		checkResult(result->result.get());
	}
	{
		auto result = q9_vectorwise(tpch, threads, vectorSize);
		checkResult(result->result.get());
	}
}

TEST(TPCH, q18) {
	configFromEnv();
	auto& expected = q18_expected();

	auto checkResult = [&](BlockRelation* result) {
		size_t found          = 0;
		auto   nameAttr       = result->getAttribute("c_name");
		auto   custkeyAttr    = result->getAttribute("c_custkey");
		auto   orderkeyAttr   = result->getAttribute("o_orderkey");
		auto   orderdateAttr  = result->getAttribute("o_orderdate");
		auto   totalpriceAttr = result->getAttribute("o_totalprice");
		auto   sumAttr        = result->getAttribute("sum");
		for (auto& block : *result) {
			auto elementsInBlock = block.size();
			// found += elementsInBlock;
			auto name       = reinterpret_cast<types::Char<25>*>(block.data(nameAttr));
			auto custkey    = reinterpret_cast<types::Integer*>(block.data(custkeyAttr));
			auto orderkey   = reinterpret_cast<types::Integer*>(block.data(orderkeyAttr));
			auto orderdate  = reinterpret_cast<types::Date*>(block.data(orderdateAttr));
			auto totalprice = reinterpret_cast<types::Numeric<12, 2>*>(block.data(totalpriceAttr));
			auto sum        = reinterpret_cast<types::Numeric<12, 2>*>(block.data(sumAttr));
			for (size_t i = 0; i < elementsInBlock; ++i) {
				if (expected.find(make_tuple(name[i], custkey[i], orderkey[i], orderdate[i], totalprice[i])) !=
				    expected.end()) {
					ASSERT_EQ(sum[i],
					          expected[make_tuple(name[i], custkey[i], orderkey[i], orderdate[i], totalprice[i])]);
				}
				found++;
			}
		};
		EXPECT_EQ(found, expected.size());
	};

	auto printResult = [&](BlockRelation* result) {
		size_t found    = 0;
		auto   nameAttr = result->getAttribute("l_orderkey");
		auto   sumAttr  = result->getAttribute("sum");
		for (auto& block : *result) {
			auto elementsInBlock = block.size();
			found += elementsInBlock;
			auto name = reinterpret_cast<int32_t*>(block.data(nameAttr));
			auto sum  = reinterpret_cast<types::Numeric<12, 2>*>(block.data(sumAttr));
			for (size_t i = 0; i < elementsInBlock; ++i) {
				cout << name[i] << "\t" << sum[i] << endl;
				// ASSERT_EQ(sum[i],
				//           expected[make_tuple(name[i], custkey[i], orderkey[i],
				//                               orderdate[i], totalprice[i])]);
			}
		}
		cout << found << endl;
	};

	Database& tpch    = TPCH::getDB();
	auto      threads = getThreads();

	// {
	//   auto result = q18group_vectorwise(tpch, threads, vectorSize);
	//   printResult(result->result.get());
	// }
	{
		auto result = q18_hyper(tpch, threads);
		checkResult(result->result.get());
		// run queries
	}
	{
		auto result = q18_vectorwise(tpch, threads, vectorSize);
		checkResult(result->result.get());
	}
}
