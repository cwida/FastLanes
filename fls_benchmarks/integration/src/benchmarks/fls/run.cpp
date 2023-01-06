#include "benchmarks/fls/Queries.hpp"
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
		          << "<number of rep_c> <path to fls dir> [thread_c = all] \n "
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
	thread_c = CFG::T_C;
	std::cout << "*thread_c : " << thread_c << "\n"; // threads

	size_t                          vectorSize  = 1024;
	bool                            clearCaches = false;
	std::unordered_set<std::string> q           = {};

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

	// Execution:
	PerfEvents e;
	Database   fls;

	// load fls data
	importFLS(argv[2], fls);

	// bitpacked
	if (CFG::BITPACK_QUERY) {
		for (uint8_t bw {0}; bw <= 32; bw++) {
			CFG::BW                = bw;
			std::string query_name = "fls " + std::to_string(bw) + "vectorwise";
			e.timeAndProfile(
			    query_name,
			    fls["268435456_10"].tup_c,
			    [&]() {
				    if (clearCaches) clearOsCaches();
				    auto result = fls_q1_vectorwise(fls, thread_c, vectorSize);
				    escape(&result);
			    },
			    rep_c);
		}

	} else {
		e.timeAndProfile(

		    "fls vectorwise ",
		    fls[CFG::NAME].tup_c,
		    [&]() {
			    if (clearCaches) clearOsCaches();
			    auto result = fls_q1_vectorwise(fls, thread_c, vectorSize);
			    escape(&result);
		    },
		    rep_c);
	}

	return 0;
}
