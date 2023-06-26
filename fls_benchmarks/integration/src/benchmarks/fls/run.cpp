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

int main() {
	int t[5] = {0, 1, 2, 4, 8};
	for (size_t j {1}; j <= 5; ++j) {
		auto                            rep_c       = cfg::r_c;
		size_t                          thread_c    = t[j];
		size_t                          vector_c    = cfg::vec_c;
		bool                            clear_cache = false;
		std::unordered_set<std::string> q           = {};

		// Execution:
		PerfEvents e;
		Database   fls;

		std::string name;
		switch (cfg::query_t) {
			// BITPACKED
		case cfg::BITPACKED:
			cfg::is_bitpacked = true;
			// load fls data - dependant on is_bitpacked
			importFLS(std::string(DATADIR) + "/fls/", fls);

			for (uint8_t bw {0}; bw <= 32; bw++) {
				cfg::bw                = bw;
				std::string query_name = "bw" + std::to_string(bw) + "_t" + std::to_string(thread_c);
				e.timeAndProfile(
				    query_name,
				    fls[cfg::name].tup_c,
				    [&]() {
					    if (clear_cache) { clearOsCaches(); }
					    auto result = fls_q(fls, thread_c, vector_c);
					    escape(&result);
				    },
				    rep_c);
			}
			break;

			// NORMAL
		case cfg::NORMAL:
			cfg::is_bitpacked = false;
			// load fls data - dependant on is_bitpacked
			importFLS(std::string(DATADIR) + "/fls/", fls);

			name = "no_bit-packing_" + std::to_string(j);
			e.timeAndProfile(
			    name,
			    fls[cfg::name].tup_c,
			    [&]() {
				    if (clear_cache) { clearOsCaches(); }
				    auto result = fls_q(fls, thread_c, vector_c);
				    escape(&result);
			    },
			    rep_c);

			break;

			// OVERHEAD
		case cfg::QueryT::BITPACKED_OVERHEAD:
			cfg::is_bitpacked = true;
			// load fls data - dependant on is_bitpacked
			importFLS(std::string(DATADIR) + "/fls/", fls);

			for (uint8_t bw {0}; bw <= 0; bw++) {
				cfg::bw                = bw;
				std::string query_name = "bw" + std::to_string(bw) + "_t" + std::to_string(thread_c);
				e.timeAndProfile(
				    query_name,
				    fls[cfg::name].tup_c,
				    [&]() {
					    if (clear_cache) { clearOsCaches(); }
					    auto result = fls_q(fls, thread_c, vector_c);
					    escape(&result);
				    },
				    rep_c);
			};
			break;

		case cfg::NORMAL_OVERHEAD:
			cfg::is_bitpacked = false;
			// load fls data - dependant on is_bitpacked
			importFLS(std::string(DATADIR) + "/fls/", fls);

			name = "no_bit-packing_" + std::to_string(j);
			e.timeAndProfile(
			    name,
			    fls[cfg::name].tup_c,
			    [&]() {
				    if (clear_cache) { clearOsCaches(); }
				    auto result = fls_q(fls, thread_c, vector_c);
				    escape(&result);
			    },
			    rep_c);

			break;

		case cfg::BITPACKED_DEBUG: {
			cfg::is_bitpacked = true;
			// load fls data - dependant on is_bitpacked
			importFLS(std::string(DATADIR) + "/fls/", fls);

			if (clear_cache) { clearOsCaches(); }
			auto res_rel = fls_q(fls, thread_c, vector_c);
			escape(&res_rel);

			auto result = *reinterpret_cast<int32_t*>(res_rel.attributes.at("aggr").data());
			if (result == cfg::answer) {
				std::cout << "\t\t query was successful" << std::endl;
			} else {
				std::cerr << "\t\t query was not successful, cal answer: " << result << std::endl;
				exit(-1);
			};
			break;
		}

			// DEBUG
		case cfg::NORMAL_DEBUG: {
			cfg::is_bitpacked = false;
			// load fls data - dependant on is_bitpacked
			importFLS(std::string(DATADIR) + "/fls/", fls);

			if (clear_cache) { clearOsCaches(); }
			auto res_rel = fls_q(fls, thread_c, vector_c);
			escape(&res_rel);

			auto result = *reinterpret_cast<int32_t*>(res_rel.attributes.at("aggr").data());
			if (result == cfg::answer) {
				std::cout << "\t\t query was successful" << std::endl;
			} else {
				std::cerr << "\t\t query was not successful" << std::endl;
				exit(-1);
			};
			break;
		}
		case cfg::BITPACKED_NORMAL: {
			cfg::is_bitpacked = true;
			// load fls data - dependant on is_bitpacked
			importFLS(std::string(DATADIR) + "/fls/", fls);

			for (uint8_t bw {30}; bw <= 32; bw++) {
				cfg::bw                = bw;
				std::string query_name = "bw" + std::to_string(bw) + "_t" + std::to_string(thread_c);
				e.timeAndProfile(
				    query_name,
				    fls[cfg::name].tup_c,
				    [&]() {
					    if (clear_cache) { clearOsCaches(); }
					    auto result = fls_q(fls, thread_c, vector_c);
					    escape(&result);
				    },
				    rep_c);
			}
			break;
		}
		}
	}
	return 0;
}
