#include "common/runtime/Mmap.hpp"
#include <gtest/gtest.h>

using namespace runtime;

using namespace std;
TEST(Mmap, rwCycle) {
   vector<string> v = {"abc", "a", "fsdjkljkldfkl"};
   Vector<string>::writeBinary("/tmp/stringx", v);

   Vector<string> v2("/tmp/stringx");
   for (unsigned i = 0; i < v2.size(); i++)
      ASSERT_EQ(v2[i], v[i]);

   vector<int> v3 = {1, 2, 3, 4, 5};
   Vector<int>::writeBinary("/tmp/intx", v3);

   Vector<int> v4("/tmp/intx");
   for (unsigned i = 0; i < v4.size(); i++)
      ASSERT_EQ(v4[i], v3[i]);

   unordered_map<int, vector<uint64_t>> m;
   for (size_t i = 0; i < 1000000; i++)
      m.insert({i, {i}});
   HashTable<int, uint64_t>::writeBinary("/tmp/mapx", m);

   HashTable<int, uint64_t> h("/tmp/mapx");
   for (int i = 0; i < 1000000; i++) {
      const HashTable<int, uint64_t>::HashTableVector& x = h[i];
      ASSERT_EQ(x.size(), size_t(1));
      ASSERT_EQ(x.key, i);
      ASSERT_EQ(x[0], size_t(i));
   }
   for (int i = 1000000; i < 2000000; i++) {
      auto& x = h[i];
      ASSERT_EQ(x.size(), size_t(0));
   }
}
