#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <sstream>
#include <thread>
#include <unordered_set>

#include "benchmarks/ssb/Queries.hpp"
#include "common/runtime/Import.hpp"
#include "profile.hpp"
#include "tbb/tbb.h"

using namespace runtime;
using namespace ssb;

static void escape(void* p) { asm volatile("" : : "g"(p) : "memory"); }

size_t nrTuples(Database& db, std::vector<std::string> tables) {
   size_t sum = 0;
   for (auto& table : tables) sum += db[table].tup_c;
   return sum;
}

/// Clears Linux page cache.
/// This function only works on Linux.
void clearOsCaches() {
  if (system("sync; echo 3 > /proc/sys/vm/drop_caches")) {
    throw std::runtime_error("Could not flush system caches: " +
                             std::string(std::strerror(errno)));
  }
}

int main(int argc, char* argv[]) {
   if (argc <= 2) {
      std::cerr
          << "Usage: ./" << argv[0]
          << "<number of repetitions> <path to sbb dir> [nrThreads = all] \n "
             " EnvVars: [vectorSize = 1024] [SIMDhash = 0] [SIMDjoin = 0] "
             "[SIMDsel = 0]";
      exit(1);
   }

   PerfEvents e;
   Database ssb;
   // load ssb data
   importSSB(argv[2], ssb);

   // run queries
   auto repetitions = atoi(argv[1]);
   size_t nrThreads = std::thread::hardware_concurrency();
   size_t vectorSize = 1024;
   bool clearCaches = false;
   if (argc > 3) nrThreads = atoi(argv[3]);


   std::unordered_set<std::string> q = {
       "1.1h", "1.1v", "1.2h", "1.2v", "1.3h", "1.3v", "2.1h", "2.1v", "2.2h",
       "2.2v", "2.3h", "2.3v", "3.1h", "3.1v", "3.2h", "3.2v", "3.3h", "3.3v",
       "3.4h", "3.4v", "4.1h", "4.1v", "4.2h", "4.2v", "4.3h", "4.3v",
   };

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
     copy(istream_iterator<string>(iss), istream_iterator<string>(),
          insert_iterator<decltype(q)>(q, q.begin()));
   }

   tbb::task_scheduler_init scheduler(nrThreads);
   if (q.count("1.1h")) e.timeAndProfile("q1.1 hyper     ", nrTuples(ssb, {"date", "lineorder"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q11_hyper(ssb, nrThreads); escape(&result);}, repetitions);
   if (q.count("1.1v")) e.timeAndProfile("q1.1 vectorwise", nrTuples(ssb, {"date", "lineorder"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q11_vectorwise(ssb, nrThreads, vectorSize); escape(&result);}, repetitions);
   if (q.count("1.2h")) e.timeAndProfile("q1.2 hyper     ", nrTuples(ssb, {"date", "lineorder"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q12_hyper(ssb, nrThreads); escape(&result);}, repetitions);
   if (q.count("1.2v")) e.timeAndProfile("q1.2 vectorwise", nrTuples(ssb, {"date", "lineorder"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q12_vectorwise(ssb, nrThreads, vectorSize); escape(&result);}, repetitions);
   if (q.count("1.3h")) e.timeAndProfile("q1.3 hyper     ", nrTuples(ssb, {"date", "lineorder"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q13_hyper(ssb, nrThreads); escape(&result);}, repetitions);
   if (q.count("1.3v")) e.timeAndProfile("q1.3 vectorwise", nrTuples(ssb, {"date", "lineorder"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q13_vectorwise(ssb, nrThreads, vectorSize); escape(&result);}, repetitions);

   if (q.count("2.1h")) e.timeAndProfile("q2.1 hyper     ", nrTuples(ssb, {"date", "lineorder", "supplier", "part"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q21_hyper(ssb, nrThreads); escape(&result);}, repetitions);
   if (q.count("2.1v")) e.timeAndProfile("q2.1 vectorwise", nrTuples(ssb, {"date", "lineorder", "supplier", "part"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q21_vectorwise(ssb, nrThreads, vectorSize); escape(&result);}, repetitions);
   if (q.count("2.2h")) e.timeAndProfile("q2.2 hyper     ", nrTuples(ssb, {"date", "lineorder", "supplier", "part"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q22_hyper(ssb, nrThreads); escape(&result);}, repetitions);
   if (q.count("2.2v")) e.timeAndProfile("q2.2 vectorwise", nrTuples(ssb, {"date", "lineorder", "supplier", "part"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q22_vectorwise(ssb, nrThreads, vectorSize); escape(&result);}, repetitions);
   if (q.count("2.3h")) e.timeAndProfile("q2.3 hyper     ", nrTuples(ssb, {"date", "lineorder", "supplier", "part"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q23_hyper(ssb, nrThreads); escape(&result);}, repetitions);
   if (q.count("2.3v")) e.timeAndProfile("q2.3 vectorwise", nrTuples(ssb, {"date", "lineorder", "supplier", "part"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q23_vectorwise(ssb, nrThreads, vectorSize); escape(&result);}, repetitions);

   if (q.count("3.1h")) e.timeAndProfile("q3.1 hyper     ", nrTuples(ssb, {"date", "lineorder", "supplier", "customer"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q31_hyper(ssb, nrThreads); escape(&result);}, repetitions);
   if (q.count("3.1v")) e.timeAndProfile("q3.1 vectorwise", nrTuples(ssb, {"date", "lineorder", "supplier", "customer"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q31_vectorwise(ssb, nrThreads, vectorSize); escape(&result);}, repetitions);
   if (q.count("3.2h")) e.timeAndProfile("q3.2 hyper     ", nrTuples(ssb, {"date", "lineorder", "supplier", "customer"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q32_hyper(ssb, nrThreads); escape(&result);}, repetitions);
   if (q.count("3.2v")) e.timeAndProfile("q3.2 vectorwise", nrTuples(ssb, {"date", "lineorder", "supplier", "customer"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q32_vectorwise(ssb, nrThreads, vectorSize); escape(&result);}, repetitions);
   if (q.count("3.3h")) e.timeAndProfile("q3.3 hyper     ", nrTuples(ssb, {"date", "lineorder", "supplier", "customer"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q33_hyper(ssb, nrThreads); escape(&result);}, repetitions);
   if (q.count("3.3v")) e.timeAndProfile("q3.3 vectorwise", nrTuples(ssb, {"date", "lineorder", "supplier", "customer"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q33_vectorwise(ssb, nrThreads, vectorSize); escape(&result);}, repetitions);
   if (q.count("3.3h")) e.timeAndProfile("q3.4 hyper     ", nrTuples(ssb, {"date", "lineorder", "supplier", "customer"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q34_hyper(ssb, nrThreads); escape(&result);}, repetitions);
   if (q.count("3.3v")) e.timeAndProfile("q3.4 vectorwise", nrTuples(ssb, {"date", "lineorder", "supplier", "customer"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q34_vectorwise(ssb, nrThreads, vectorSize); escape(&result);}, repetitions);

   if (q.count("4.1h")) e.timeAndProfile("q4.1 hyper     ", nrTuples(ssb, {"date", "lineorder", "supplier", "customer", "part"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q41_hyper(ssb, nrThreads); escape(&result);}, repetitions);
   if (q.count("4.1v")) e.timeAndProfile("q4.1 vectorwise", nrTuples(ssb, {"date", "lineorder", "supplier", "customer", "part"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q41_vectorwise(ssb, nrThreads, vectorSize); escape(&result);}, repetitions);
   if (q.count("4.2h")) e.timeAndProfile("q4.2 hyper     ", nrTuples(ssb, {"date", "lineorder", "supplier", "customer", "part"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q42_hyper(ssb, nrThreads); escape(&result);}, repetitions);
   if (q.count("4.2v")) e.timeAndProfile("q4.2 vectorwise", nrTuples(ssb, {"date", "lineorder", "supplier", "customer", "part"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q42_vectorwise(ssb, nrThreads, vectorSize); escape(&result);}, repetitions);
   if (q.count("4.3h")) e.timeAndProfile("q4.3 hyper     ", nrTuples(ssb, {"date", "lineorder", "supplier", "customer", "part"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q43_hyper(ssb, nrThreads); escape(&result);}, repetitions);
   if (q.count("4.3v")) e.timeAndProfile("q4.3 vectorwise", nrTuples(ssb, {"date", "lineorder", "supplier", "customer", "part"}), [&]() { if(clearCaches) clearOsCaches(); auto result = q43_vectorwise(ssb, nrThreads, vectorSize); escape(&result);}, repetitions);

   return 0;
}
