#include "common/runtime/Stack.hpp"
#include <cstdint>
#include <gtest/gtest.h>
#include <tuple>

TEST(Stack, insertAndFind) {
   runtime::Stack<std::tuple<uint64_t, uint16_t>> stack;
   const size_t nrEls = 100000;

   // insert some data
   for (size_t i = 0; i < nrEls; ++i) {
      ASSERT_EQ(stack.size(), i);
      stack.emplace_back(i * 2, i % 256);
   }

   // make sure it is still there
   size_t i = 0;
   for (auto block : stack)
      for (auto& el : block) {
         ASSERT_EQ(el, std::make_tuple(i * 2, i % 256));
         ++i;
      }
   // make sure the right amount of elements was found
   ASSERT_EQ(i, nrEls);
}

TEST(Stack, clear) {
   runtime::Stack<std::tuple<uint64_t, uint16_t>> stack;
   size_t nrEls = 100000;

   // insert some data
   for (size_t i = 0; i < nrEls; ++i) stack.emplace_back(i * 2, i % 256);

   stack.clear();

   // check if stack is empty
   size_t i = 0;
   for (auto block : stack)
      for (auto& el : block) {
         ++i;
         compat::unused(el);
      }
   ASSERT_EQ(i, size_t(0));
   ASSERT_EQ(stack.size(), size_t(0));

   nrEls = 20000;
   // reinsert elements
   for (size_t i = 0; i < nrEls; ++i) stack.emplace_back(i * 2, i % 256);
   // make sure they is still there
   i = 0;
   for (auto block : stack)
      for (auto& el : block) {
         ASSERT_EQ(el, std::make_tuple(i * 2, i % 256));
         ++i;
      }
   // make sure the right amount of elements was found
   ASSERT_EQ(i, nrEls);
}
