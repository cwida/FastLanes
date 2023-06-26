#include "common/runtime/Query.hpp"
#include <deque>
#include <tbb/tbb.h>

static const size_t morselSize = 10000;

struct ProcessingResources {
   std::vector<runtime::Worker> workers;
   std::unique_ptr<runtime::Query> query;
};

inline ProcessingResources initQuery(size_t nrThreads) {
   ProcessingResources r;
   r.query = std::make_unique<runtime::Query>();
   r.query->result = std::make_unique<runtime::BlockRelation>();
   runtime::Barrier b(nrThreads);
   r.workers.resize(nrThreads);

   tbb::parallel_for(size_t(0), nrThreads, size_t(1), [&](auto i) {
      auto& worker = r.workers[i];
      // save thread local worker pointer
      worker.previousWorker = runtime::this_worker;
      // use this worker resource
      runtime::this_worker = &worker;
      r.query->participate();
      b.wait();
   });
   return r;
}

inline void leaveQuery(size_t nrThreads) {
   runtime::Barrier b(nrThreads);
   tbb::parallel_for(size_t(0), nrThreads, size_t(1), [&](auto) {
      // reset thread local worker pointer
      runtime::this_worker = runtime::this_worker->previousWorker;
      b.wait();
   });
}

#define PARALLEL_SCAN(N, ENTRIES, BLOCK)                                       \
   tbb::parallel_for(tbb::blocked_range<size_t>(0, N, morselSize),             \
                     [&](const tbb::blocked_range<size_t>& r) {                \
                        auto& entries = ENTRIES.local();                       \
                        for (auto i = r.begin(), end = r.end(); i != end; ++i) \
                           BLOCK                                               \
                     })

template <typename E, typename L>
void parallel_scan(size_t n, E& entriesGlobal, L& cb) {
   tbb::parallel_for(tbb::blocked_range<size_t>(0, n, morselSize),
                     [&](const tbb::blocked_range<size_t>& r) {
                        auto& entries = entriesGlobal.local();
                        for (auto i = r.begin(), end = r.end(); i != end; ++i)
                           cb(i, entries);
                     });
}

#define PARALLEL_SELECT(N, ENTRIES, BLOCK)                                     \
   tbb::parallel_reduce(                                                       \
       tbb::blocked_range<size_t>(0, N, morselSize), 0,                        \
       [&](const tbb::blocked_range<size_t>& r, const size_t& f) {             \
          auto& entries = ENTRIES.local();                                     \
          auto found = f;                                                      \
          for (size_t i = r.begin(), end = r.end(); i != end; ++i) BLOCK       \
          return found;                                                        \
       },                                                                      \
       [](const size_t& a, const size_t& b) { return a + b; })

template <typename E, typename HT> void parallel_insert(E& entries, HT& ht) {
   tbb::parallel_for(entries.range(), [&ht](const auto& r) {
      for (auto& entries : r) ht.insertAll(entries);
   });
}
