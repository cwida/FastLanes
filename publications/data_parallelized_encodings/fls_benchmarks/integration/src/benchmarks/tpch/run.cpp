#include "benchmarks/tpch/Queries.hpp"
#include "common/runtime/Import.hpp"
#include "profile.hpp"
#include "tbb/tbb.h"
#include <algorithm>
#include <cerrno>
#include <chrono>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <iterator>
#include <sstream>
#include <thread>
#include <unordered_set>

using namespace runtime;

static void escape(void* p) { asm volatile("" : : "g"(p) : "memory"); }

size_t nrTuples(Database& db, std::vector<std::string> tables) {
	size_t sum = 0;
	for (auto& table : tables)
		sum += db[table].tup_c;
	return sum;
}

/// Clears Linux page cache.
/// This function only works on Linux.
void clearOsCaches() {
	if (system("sync; echo 3 > /proc/sys/vm/drop_caches")) {
		throw std::runtime_error("Could not flush system caches: " + std::string(std::strerror(errno)));
	}
}

int main(int argc, char* argv[]) {
	// Arg parsing:
	if (argc <= 2) {
		std::cerr << "Usage: ./" << argv[0]
		          << "<number of rep_c> <path to tpch dir> [thread_c = all] \n "
		             " EnvVars: [vectorSize = 1024] [SIMDhash = 0] [SIMDjoin = 0] "
		             "[SIMDsel = 0]";
		exit(1);
	}

	// Detail:
	std::cout << "========================================== detail =========================================="
	          << "\n";
	auto rep_c = atoi(argv[1]);
	std::cout << "*reptin_c : " << rep_c << "\n"; // repetition

	size_t thread_c = std::thread::hardware_concurrency();
	if (argc > 3) { thread_c = atoi(argv[3]); }
	std::cout << "*thread_c : " << thread_c << "\n"; // threads

	PerfEvents e;
	Database   tpch;
	// load tpch data
	importTPCH(argv[2], tpch);

	size_t vectorSize  = 1024;
	bool   clearCaches = false;

	//	std::unordered_set<std::string> q = {"1h", "1v", "3h", "3v", "5h", "5v", "6h", "6v", "9h", "9v", "18h", "18v"};
	std::unordered_set<std::string> q = {"1v", "3v", "5v", "6v", "9v", "18v"};

	if (auto v = std::getenv("vectorSize")) vectorSize = atoi(v);
	if (auto v = std::getenv("SIMDhash")) conf.useSimdHash = atoi(v);
	if (auto v = std::getenv("SIMDjoin")) conf.useSimdJoin = atoi(v);
	if (auto v = std::getenv("SIMDsel")) conf.useSimdSel = atoi(v);
	if (auto v = std::getenv("SIMDproj")) conf.useSimdProj = atoi(v);
	if (auto v = std::getenv("clearCaches")) clearCaches = atoi(v);
	if (auto v = std::getenv("q")) {
		using namespace std;
		istringstream iss((string(v)));
		q.clear();
		copy(istream_iterator<string>(iss), istream_iterator<string>(), insert_iterator<decltype(q)>(q, q.begin()));
	}

		if (q.count("1h"))
			e.timeAndProfile(
			    "q1 hyper     ",
			    nrTuples(tpch, {"lineitem"}),
			    [&]() {
				    if (clearCaches) clearOsCaches();
				    auto result = q1_hyper(tpch, thread_c);
				    escape(&result);
			    },
			    rep_c);
	if (q.count("1v"))
		e.timeAndProfile(
		    "q1 vectorwise",
		    nrTuples(tpch, {"lineitem"}),
		    [&]() {
			    if (clearCaches) clearOsCaches();
			    auto result = q1_vectorwise(tpch, thread_c, vectorSize);
			    escape(&result);
		    },
		    rep_c);
	if (q.count("3h"))
		e.timeAndProfile(
		    "q3 hyper     ",
		    nrTuples(tpch, {"customer", "orders", "lineitem"}),
		    [&]() {
			    if (clearCaches) clearOsCaches();
			    auto result = q3_hyper(tpch, thread_c);
			    escape(&result);
		    },
		    rep_c);
	if (q.count("3v"))
		e.timeAndProfile(
		    "q3 vectorwise",
		    nrTuples(tpch, {"customer", "orders", "lineitem"}),
		    [&]() {
			    if (clearCaches) clearOsCaches();
			    auto result = q3_vectorwise(tpch, thread_c, vectorSize);
			    escape(&result);
		    },
		    rep_c);
	if (q.count("5h"))
		e.timeAndProfile(
		    "q5 hyper     ",
		    nrTuples(tpch, {"supplier", "region", "nation", "customer", "orders", "lineitem"}),
		    [&]() {
			    if (clearCaches) clearOsCaches();
			    auto result = q5_hyper(tpch, thread_c);
			    escape(&result);
		    },
		    rep_c);
	if (q.count("5v"))
		e.timeAndProfile(
		    "q5 vectorwise",
		    nrTuples(tpch, {"supplier", "region", "nation", "customer", "orders", "lineitem"}),
		    [&]() {
			    if (clearCaches) clearOsCaches();
			    auto result = q5_vectorwise(tpch, thread_c, vectorSize);
			    escape(&result);
		    },
		    rep_c);
	if (q.count("6h"))
		e.timeAndProfile(
		    "q6 hyper     ",
		    tpch["lineitem"].tup_c,
		    [&]() {
			    if (clearCaches) clearOsCaches();
			    auto result = q6_hyper(tpch, thread_c);
			    escape(&result);
		    },
		    rep_c);
	if (q.count("6v")) {
		e.timeAndProfile(
		    "q6 vectorwise",
		    tpch["lineitem"].tup_c,
		    [&]() {
			    if (clearCaches) clearOsCaches();
			    auto result = q6_vectorwise(tpch, thread_c, vectorSize);
			    escape(&result);
		    },
		    rep_c);
	}
	if (q.count("9h"))
		e.timeAndProfile(
		    "q9 hyper     ",
		    nrTuples(tpch, {"nation", "supplier", "part", "partsupp", "lineitem", "orders"}),
		    [&]() {
			    if (clearCaches) clearOsCaches();
			    auto result = q9_hyper(tpch, thread_c);
			    escape(&result);
		    },
		    rep_c);
	if (q.count("9v"))
		e.timeAndProfile(
		    "q9 vectorwise",
		    nrTuples(tpch, {"nation", "supplier", "part", "partsupp", "lineitem", "orders"}),
		    [&]() {
			    if (clearCaches) clearOsCaches();
			    auto result = q9_vectorwise(tpch, thread_c, vectorSize);
			    escape(&result);
		    },
		    rep_c);
	if (q.count("18h"))
		e.timeAndProfile(
		    "q18 hyper     ",
		    nrTuples(tpch, {"customer", "lineitem", "orders", "lineitem"}),
		    [&]() {
			    if (clearCaches) clearOsCaches();
			    auto result = q18_hyper(tpch, thread_c);
			    escape(&result);
		    },
		    rep_c);
	if (q.count("18v"))
		e.timeAndProfile(
		    "q18 vectorwise",
		    nrTuples(tpch, {"customer", "lineitem", "orders", "lineitem"}),
		    [&]() {
			    if (clearCaches) clearOsCaches();
			    auto result = q18_vectorwise(tpch, thread_c, vectorSize);
			    escape(&result);
		    },
		    rep_c);
	return 0;
}
