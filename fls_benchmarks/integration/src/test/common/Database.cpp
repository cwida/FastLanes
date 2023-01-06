#include "common/runtime/Database.hpp"
#include <gtest/gtest.h>

using namespace runtime;

TEST(BlockRelation, insertAndRead) {

   // create relation
   BlockRelation rel;
   size_t n = 80;
   // add two attributes
   auto attr1 = rel.addAttribute("a", sizeof(int64_t));
   auto attr2 = rel.addAttribute("b", sizeof(int32_t));
   // add block to relation
   auto block = rel.createBlock(n);

   // write data for both attributes
   {
      int64_t* a = reinterpret_cast<int64_t*>(block.data(attr1));
      int32_t* b = reinterpret_cast<int32_t*>(block.data(attr2));
      for (size_t i = 0; i < n; ++i, a++, b++) {
         *a = 7 * i;
         *b = i;
      }
      block.addedElements(n);
   }

   // read data for both attributes
   {
      auto elementsInBlock = block.size();
      int64_t* a = reinterpret_cast<int64_t*>(block.data(attr1));
      int32_t* b = reinterpret_cast<int32_t*>(block.data(attr2));
      ASSERT_EQ(elementsInBlock, n);
      for (int64_t i = 0; size_t(i) < elementsInBlock; ++i, a++, b++) {
         ASSERT_EQ(*a, 7 * i);
         ASSERT_EQ(*b, i);
      }
   }
}
