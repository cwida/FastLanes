#include "vectorwise/Primitives.hpp"
#include "common/runtime/Hash.hpp"
#include "common/runtime/Hashmap.hpp"
#include "common/runtime/Types.hpp"
#include <gtest/gtest.h>

using types::Date;
using namespace std;
using namespace vectorwise;

TEST(GTEQ, Date) {
   vector<Date> dates;
   dates.push_back(Date::castString("2017-01-01"));
   dates.push_back(Date::castString("2017-01-04"));
   dates.push_back(Date::castString("2017-01-02"));
   dates.push_back(Date::castString("2017-01-03"));
   dates.push_back(Date::castString("2017-01-04"));
   auto c = types::Date::castString("2017-01-03");

   vector<pos_t> result;
   result.assign(5, 0);
   pos_t n = primitives::sel_greater_equal_Date_col_Date_val(5, result.data(),
                                                             dates.data(), &c);

   ASSERT_EQ(pos_t(3), n);
   vector<pos_t> expected = {1, 3, 4};
   for (pos_t i = 0; i < n; ++i) ASSERT_EQ(expected[i], result[i]);
}

struct TestData {
   uint64_t a;
   uint8_t b;
};

TEST(Scatter, Continuous) {
   vector<uint64_t> a;
   vector<uint8_t> b;
   const auto n = 10;
   for (size_t i = 0; i < n; ++i) {
      a.emplace_back(i + 2);
      b.emplace_back(i * 2);
   }
   vector<TestData> res;
   res.assign(n, {0, 0});
   size_t step = sizeof(TestData);
   void* scatterStart = res.data();
   // --- run scatter functions
   primitives::scatter_int64_t_col(n, a.data(), &scatterStart, &step, 0);
   primitives::scatter_int8_t_col(n, b.data(), &scatterStart, &step,
                                  sizeof(int64_t));

   // --- check if results arrived correctly
   for (size_t i = 0; i < n; ++i) {
      ASSERT_EQ(res[i].a, i + 2);
      ASSERT_EQ(res[i].b, i * 2);
   }
}

TEST(Scatter, Selected) {
   vector<uint64_t> a;
   vector<uint8_t> b;
   const auto els = 10;
   for (size_t i = 0; i < els; ++i) {
      a.emplace_back(i + 2);
      b.emplace_back(i * 2);
   }
   vector<TestData> res;
   res.assign(els, {0, 0});
   size_t step = sizeof(TestData);

   const auto n = 3;
   vector<pos_t> selection = {2, 3, 4};
   void* scatterStart = res.data();
   // --- run scatter functions
   primitives::scatter_sel_int64_t_col(n, selection.data(), a.data(),
                                       &scatterStart, &step, 0);
   primitives::scatter_sel_int8_t_col(n, selection.data(), b.data(),
                                      &scatterStart, &step, sizeof(int64_t));

   // --- check if results arrived correctly
   for (size_t i = 0; i < n; ++i) {
      auto idx = selection[i];
      ASSERT_EQ(res[i].a, uint64_t(idx) + 2);
      ASSERT_EQ(res[i].b, uint64_t(idx) * 2);
   }
   // --- check if rest is untouched
   for (size_t i = n + 1; i < els; ++i) {
      ASSERT_EQ(res[i].a, 0ull);
      ASSERT_EQ(res[i].b, uint8_t(0));
   }
}

TEST(Partition, uint64_t) {
   const auto vecSize = 15;
   using key_t = int64_t;
   vector<key_t> keys = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 9};
   vector<pos_t> sel = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
   vector<runtime::Hashmap::hash_t> hashes;
   for (auto& key : keys) hashes.push_back(key);
   vector<pos_t> partitionBounds = {12};
   vector<pos_t> selOut;
   selOut.resize(vecSize);
   vector<pos_t> partitionBoundsOut;
   partitionBoundsOut.resize(vecSize);
   runtime::HashmapSmall<pos_t, pos_t> groupHt(vecSize);
   auto foundPartitions = primitives::partition_by_key_int64_t_col(
       partitionBounds.size(), sel.data(), keys.data(), hashes.data(),
       partitionBounds.data(), selOut.data(), partitionBoundsOut.data(),
       &groupHt);
   ASSERT_EQ(foundPartitions, size_t(7));
   unordered_map<key_t, size_t> expectedGroupCounts = {
       {1, 2}, {2, 2}, {3, 2}, {4, 2}, {5, 2}, {6, 1}, {9, 1}};
   size_t pStart = 0;
   for (size_t p = 0; p < foundPartitions; ++p) {
      key_t partitionValue = keys[selOut[pStart]];
      for (size_t i = pStart; i < partitionBoundsOut[p]; ++i) {
         key_t rowValue = keys[selOut[i]];
         // all values in one partition should be equal
         ASSERT_EQ(rowValue, partitionValue);
         expectedGroupCounts[rowValue]--;
      }
      pStart = partitionBoundsOut[p];
   }
   for (auto& e : expectedGroupCounts) { ASSERT_EQ(e.second, size_t(0)); }
}

#ifdef __AVX512F__
using hash_t = defs::hash_t;
TEST(Hash, SIMD32bits){
   // checks if scalar and simd variants generate the same hashes
   using runtime::MurMurHash3;
   vector<int32_t> keys = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
   vector<uint32_t> scalarHashes;
   vector<uint32_t> simdHashes(16);

   for(auto& k : keys) scalarHashes.push_back(MurMurHash3{}(k, (uint32_t)vectorwise::primitives::seed));

   auto simdHash = MurMurHash3{}.hashKey(Vec16u(keys.data()), Vec16u((uint32_t)vectorwise::primitives::seed));
   _mm512_mask_storeu_epi64(simdHashes.data(), ~0, simdHash);

   size_t i = 0;
   for(auto& scalarHash : scalarHashes){
     ASSERT_EQ(scalarHash, simdHashes[i++]);
   }

}
#endif
