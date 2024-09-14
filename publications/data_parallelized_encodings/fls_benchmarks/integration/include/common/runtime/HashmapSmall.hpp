#pragma once
#include "common/defs.hpp"
#include "vectorwise/defs.hpp"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <limits>
#include <memory>

namespace runtime {
template <typename K, typename V>
class HashmapSmall
/// a hashmap for at most 2^16 elements, using a memory pool for allocations
{
   using ref = vectorwise::pos_t;
   using hash_t = defs::hash_t;
   static const ref empty = std::numeric_limits<ref>::max();
   static constexpr double loadFactor = 0.7;

 public:
   struct Entry {
      ref next;
      hash_t hash;
      K key;
      V value;
   };

 private:
   hash_t mask;
   ref* entries;

   Entry* storage;
   ref storageUsed = 0;
   ref capacity;
   ref capLimit;
   ref maxCapacity;

 public:
   HashmapSmall(size_t size) {
      size_t exp = 64 - __builtin_clzll(size);
      assert(exp < sizeof(hash_t) * 8);
      if (((size_t)1 << exp) < size / loadFactor) exp++;
      maxCapacity = ((size_t)1) << exp;
      capacity = std::min((ref)256, maxCapacity);
      capLimit = capacity * loadFactor;
      mask = capacity - 1;
      entries = new ref[maxCapacity];
      storage = new Entry[size];
      clearByMemset();
   }
   ~HashmapSmall() {
      delete[] entries;
      delete[] storage;
   }
   void clear(hash_t hash) { entries[hash & mask] = empty; }
   void clearByMemset() {
      std::memset(entries, empty, capacity * sizeof(*entries));
   }
   template <typename CLEAR> void clear(CLEAR clearElements) {
      if (storageUsed < capacity * 0.3)
         clearElements(*this);
      else
         clearByMemset();
      storageUsed = 0;
   };

   template <typename COMP> V* findFirst(hash_t& hash, COMP comp) {
      auto cand = entries[hash & mask];
      if (cand == empty) return nullptr;
      for (auto candPtr = &storage[cand]; cand != empty;
           cand = candPtr->next, candPtr = &storage[cand])
         if (comp(candPtr->key)) return &candPtr->value;
      return nullptr;
   }
   void insert(K& key, hash_t& hash, V& value) {
      // calculate spot in directory
      auto& dir = entries[hash & mask];
      auto entryPos = storageUsed++;
      // allocate memory in storage
      auto& entry = storage[entryPos];
      // put new entry to top of chain.
      entry.next = dir;
      // update directory
      dir = entryPos;
      // fill entry
      entry.key = key;
      entry.value = value;
      entry.hash = hash;
      //grow?
      if (storageUsed > capLimit) {
         // increase capacity
         capacity *= 2;
         capLimit = capacity * loadFactor;
         // create new mask
         mask = capacity - 1;
         // clear all entries
         clearByMemset();
         // reinsert all
         for (size_t i = 0; i < storageUsed; i++) {
            auto& entry = storage[i];
            auto& dir = entries[entry.hash & mask];
            // put new entry to top of chain.
            entry.next = dir;
            // update directory
            dir = i;
         }
      }
   }

   Entry* begin() { return storage; }
   Entry* end() { return storage + storageUsed; }
};
}
