#include "benchmarks/Primitives.hpp"
#include "vectorwise/Operators.hpp"
#include "common/runtime/Hashmap.hpp"
#include "common/runtime/Hash.hpp"
#include "immintrin.h"
#include <algorithm>

using namespace std;
using vectorwise::pos_t;
using namespace vectorwise::primitives;

void gather_int32_t_avx512(pos_t n, pos_t* sel, int32_t* data, int32_t* out){
  size_t rest = n % 16;
  for (uint64_t i = 0; i < n - rest; i += 16) {
    auto idxs = _mm512_loadu_si512((const __m512i *)(sel + i));
    auto in = _mm512_i32gather_epi32(idxs, (const long long int *)data, 4);
    _mm512_store_epi64(out + i, in);
  }
  for (uint64_t i = n - rest; i < n; i++)
    out[i] = data[sel[i]];
}

__attribute__((optimize("unroll-loops")))
// #pragma GCC push_options
// #pragma GCC optimize ("unroll-loops")
void gather_int32_t(pos_t n, pos_t* sel, int32_t* data, int32_t* out){

#pragma unroll 16
  for (uint64_t i = 0; i < n; i++)
    out[i] = data[sel[i]];
}
// #pragma GCC pop_options

template<typename T> T* alloc(size_t els){return static_cast<T*>(compat::aligned_alloc(64, els * sizeof(T)));}

void measureHash(size_t minSize, size_t vecSize, PerfEvents& e) {
   auto* input = static_cast<int64_t*>(compat::aligned_alloc(64, vecSize * sizeof(int64_t)));
   auto* output = static_cast<int64_t*>(compat::aligned_alloc(64, vecSize * sizeof(int64_t)));
   putRandom(input, vecSize, 0, ~0ull);


   for (size_t n = minSize; n <= vecSize; n *= 2) {
     cout << "workingSet: " << n << "\n";

     cout << "typeSize: 4" << "\n";
     e.timeAndProfile("hash", n, [&]() { hash_int32_t_col(n, output, input); }, std::max<uint64_t>(1, 100000*1024ull/n));
     e.timeAndProfile("hash simd", n, [&]() { hash4_int32_t_col(n, output, input); }, std::max<uint64_t>(1, 100000*1024ull/n));

     cout << "typeSize: 8" << "\n";
     e.timeAndProfile("hash", n, [&]() { hash_int64_t_col(n, output, input); }, std::max<uint64_t>(1, 100000*1024ull/n));
     e.timeAndProfile("hash simd", n, [&]() { hash8_int64_t_col(n, output, input); }, std::max<uint64_t>(1, 100000*1024ull/n));
   }

}

void measureSelHash(size_t minSize, size_t maxSize, PerfEvents& e) {
  auto* input = static_cast<int64_t*>(compat::aligned_alloc(64, maxSize * sizeof(int64_t)));
  auto* output = static_cast<int64_t*>(compat::aligned_alloc(64, maxSize * sizeof(int64_t)));
  auto* sel = static_cast<pos_t*>(compat::aligned_alloc(64, maxSize * sizeof(pos_t)));
  putRandom(input, maxSize, 0, ~0ull);
  size_t lookups = 1024 * 1024;


  for (size_t n = minSize; n <= maxSize; n *= 2) {
    cout << "workingSet: " << n << "\n";
    putRandom(sel, maxSize, 0, n);

    cout << "typeSize: 4" << "\n";
    e.timeAndProfile("hash sel", lookups, [&]() { hash_sel_int32_t_col(lookups, sel, output, input); }, std::max<uint64_t>(1, 1000));
    e.timeAndProfile("hash sel simd", lookups, [&]() { hash4_sel_int32_t_col(lookups, sel, output, input); }, std::max<uint64_t>(1, 1000));

    // cout << "typeSize: 8" << "\n";
    // e.timeAndProfile("hash sel", n, [&]() { hash_sel_int64_t_col(n, sel, output, input); }, std::max<uint64_t>(1, 100000*1024ull/n));
    // e.timeAndProfile("hash sel simd", n, [&]() { hash8_sel_int64_t_col(n, sel, output, input); }, std::max<uint64_t>(1, 100000*1024ull/n));
  }

}

void measureGather(size_t minSize, size_t maxSize, size_t lookups, PerfEvents& e){
  auto* input = static_cast<int64_t*>(compat::aligned_alloc(64, maxSize * sizeof(int64_t)));
  auto* output = static_cast<int64_t*>(compat::aligned_alloc(64, maxSize * sizeof(int64_t)));
  auto* sel = static_cast<pos_t*>(compat::aligned_alloc(64, maxSize * sizeof(pos_t)));
  putRandom(input, maxSize, 0, ~0ull);

  cout << "typeSize: 4" << "\n";
  for (size_t n = minSize; n <= maxSize; n *= 2) {
    cout << "workingSet: " << n << "\n";
    putRandom(sel, maxSize, 0, n);
    e.timeAndProfile("gather", lookups, [&]() { gather_int32_t(lookups, sel, (int32_t*)input,(int32_t*) output); }, 1000);
    e.timeAndProfile("gather simd", lookups, [&]() { gather_int32_t_avx512(lookups, sel,(int32_t*) input,(int32_t*) output); }, 1000);
  }
}

void measureJoin(size_t minSize, size_t maxSize, PerfEvents& e){
  using vectorwise::Hashjoin;

  auto vecSize = maxSize;


  Hashjoin::Shared shared;
  // set hashtable size
  // reserve space for entries
  auto entries = alloc<runtime::Hashmap::EntryHeader>(maxSize);

  Hashjoin join(shared);
  join.followupIds = alloc<pos_t>(vecSize + 1);
  join.followupEntries = alloc<runtime::Hashmap::EntryHeader*>(vecSize + 1);
  join.followupBufferSize = 1; // don't follow chains
  // join.join = Hashjoin::joinSelParallel;
  join.batchSize = vecSize;
  join.probeHashes = alloc<runtime::Hashmap::hash_t>(vecSize);
  // result is written into these
  join.buildMatches = alloc<runtime::Hashmap::EntryHeader*>(vecSize);
  join.probeMatches = alloc<pos_t>(vecSize);

  runtime::MurMurHash hash;

  std::mt19937 mersenne_engine(293457);
  std::uniform_int_distribution<runtime::Hashmap::hash_t> dist(0, ~0ull);
  auto gen = std::bind(dist, mersenne_engine);

  for (size_t n = minSize; n <= maxSize; n *= 2) {
    cout << "workingSet: " << n << "\n";
    shared.ht.clear(); shared.ht.setSize(n);
    for(size_t i = 0; i < n; i++){
      auto val = hash(gen(), 1337);
      entries[i].hash = val;
      join.probeHashes[i] = val;
    }
    shared.ht.insertAll_tagged<false>(entries, n, sizeof(runtime::Hashmap::EntryHeader *));

    auto lookups = std::min<size_t>(n, 1024 * 1024);
    join.cont.numProbes = lookups;
    e.timeAndProfile("htLookup", lookups, [&]() { join.joinAllParallel(); }, std::max<uint64_t>(1000, 2*1024ull*1024*1024/lookups));
    e.timeAndProfile("htLookup SIMD", lookups, [&]() { join.joinAllSIMD(); }, std::max<uint64_t>(1000, 2*1024ull*1024*1024/lookups));
  }
}

int main() {
  PerfEvents e;
  
  // measureHash(256, 1024 * 1024 * 256, e);
  measureSelHash(256, 1024 * 1024 * 256, e);
  // measureGather(256, 1024 * 1024 * 256, 1024 * 1024, e);
//  measureJoin(256, 1024 * 1024 * 256, e);

  return 0;
}
