#include "common/runtime/PartitionedDeque.hpp"
#include <functional>
#include <gtest/gtest.h>
#include <unordered_set>
#include <vector>

using namespace runtime;
using namespace std;

TEST(PartitionedDeque, insertAndFind) {
   struct Entry {
      uint64_t hash;
      uint64_t value;
   };
   const size_t n = 10000;
   vector<Entry> data;
   data.reserve(n);
   for (size_t i = 0; i < n; i++) { data.push_back(Entry{i % 2, i}); }
   using deque_t = PartitionedDeque<8>;
   using chunk_t = deque_t::Chunk;
   unordered_set<uint64_t> reference;
   deque_t deque(5, sizeof(Entry::value));
   for (auto& entry : data) {
      deque.push_back(&entry.value, entry.hash);
      reference.insert(entry.value);
   }
   for (auto& partition : deque.getPartitions())
      for (auto chunk = partition.first; chunk; chunk = chunk->next)
         for (auto value = chunk->data<uint64_t>(), end = value + chunk_t::size;
              value < end && value != partition.end; value++)
            ASSERT_EQ(reference.erase(*value), size_t(1));
}
