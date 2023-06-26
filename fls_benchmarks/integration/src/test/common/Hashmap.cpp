#include "common/runtime/Hashmap.hpp"
#include "common/runtime/Types.hpp"
#include <functional>
#include <gtest/gtest.h>
#include <vector>

using namespace runtime;

struct Entry {
   Hashmap::EntryHeader h;
   uint64_t k;
   uint64_t v;
   Entry() : h(nullptr, 0) {}
};

TEST(Hashtable, insertAndFind) {
   Hashmap ht;
   const auto nrEntries = 5;
   ht.setSize(nrEntries);
   std::vector<Entry> entries;
   entries.reserve(nrEntries);
   for (int i = 0; i < nrEntries; ++i) {
      entries.push_back(Entry());
      auto& e = entries.back();
      e.k = i;
      e.v = i + 50;
      e.h.hash = std::hash<uint64_t>()(e.k);
      ht.insert(&e.h, e.h.hash);
   }

   for (unsigned i = 0; i < nrEntries; ++i) {
      auto hash = std::hash<uint64_t>()(i);
      auto entry = ht.find_chain(hash);
      bool found = false;
      for (; entry != ht.end(); entry = entry->next)
         if (reinterpret_cast<uint64_t*>(entry)[3] == i + 50) found = true;
      ASSERT_EQ(found, true);
   }
}
