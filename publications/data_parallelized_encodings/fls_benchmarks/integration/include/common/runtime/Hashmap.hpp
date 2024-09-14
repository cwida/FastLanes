#pragma once
#include "common/defs.hpp"
#include "common/runtime/Memory.hpp"
#include "common/runtime/SIMD.hpp"
#include "common/runtime/Stack.hpp"
#include <assert.h>
#include <atomic>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <memory>
#include <vector>

namespace runtime {

class Hashmap {

 public:
   using hash_t = defs::hash_t;
   size_t capacity = 0;
   class EntryHeader
   /// Header for hashtable entries
   {
    public:
      EntryHeader* next;
      hash_t hash;
      EntryHeader(EntryHeader* n, hash_t h) : next(n), hash(h) {}
      // payload data follows this header
   };
   /// Returns the first entry of the chain for the given hash
   inline EntryHeader* find_chain(hash_t hash);
   /// Returns the first entry of the chain for the given hash
   /// Uses pointer tagging as a filter to quickly determine whether hash is
   /// contained
   inline EntryHeader* find_chain_tagged(hash_t hash);
   inline Vec8uM find_chain_tagged(Vec8u hashes);
   /// Insert entry into chain for the given hash
   template <bool concurrentInsert = true>
   inline void insert(EntryHeader* entry, hash_t hash);
   /// Insert entry into chain for the given hash
   /// Updates tag
   template <bool concurrentInsert = true>
   inline void insert_tagged(EntryHeader* entry, hash_t hash);
   /// Insert n entries starting from first, always looking for the next entry
   /// step bytes after the previous
   template <bool concurrentInsert = true>
   inline void insertAll(EntryHeader* first, size_t n, size_t step);
   template <bool concurrentInsert = true>
   inline void insertAll_tagged(EntryHeader* first, size_t n, size_t step);
   /// Set size (no resize functionality)
   inline size_t setSize(size_t nrEntries);
   /// Removes all elements from the hashtable
   inline void clear();

   std::atomic<EntryHeader*>* entries = nullptr;

   hash_t mask;
   using ptr_t = uint64_t;
   const ptr_t maskPointer = (~(ptr_t)0) >> (16);
   const ptr_t maskTag = (~(ptr_t)0) << (sizeof(ptr_t) * 8 - 16);

   inline static EntryHeader* end();
   Hashmap() = default;
   Hashmap(const Hashmap&) = delete;
   inline ~Hashmap();

 private:
   inline Hashmap::EntryHeader* ptr(Hashmap::EntryHeader* p);
   inline ptr_t tag(hash_t p);
   inline Vec8u tag(Vec8u p);
   inline Hashmap::EntryHeader* update(Hashmap::EntryHeader* old,
                                       Hashmap::EntryHeader* p, hash_t hash);
};

extern Hashmap::EntryHeader notFound;

inline Hashmap::EntryHeader* Hashmap::end() { return nullptr; }

inline Hashmap::~Hashmap() {
  if (entries)
     mem::free_huge(entries, capacity * sizeof(std::atomic<EntryHeader*>));
}

inline Hashmap::ptr_t Hashmap::tag(Hashmap::hash_t hash) {
   auto tagPos = hash >> (sizeof(hash_t) * 8 - 4);
   return ((size_t)1) << (tagPos + (sizeof(ptr_t) * 8 - 16));
}

inline Vec8u Hashmap::tag(Vec8u hashes) {
   auto tagPos = hashes >> (sizeof(hash_t) * 8 - 4);
   return Vec8u(1) << (tagPos + Vec8u(sizeof(ptr_t) * 8 - 16));
}

inline Hashmap::EntryHeader* Hashmap::ptr(Hashmap::EntryHeader* p) {
   return (EntryHeader*)((ptr_t)p & maskPointer);
}

inline Hashmap::EntryHeader* Hashmap::update(Hashmap::EntryHeader* old,
                                             Hashmap::EntryHeader* p,
                                             Hashmap::hash_t hash) {
   return reinterpret_cast<EntryHeader*>((size_t)p | ((size_t)old & maskTag) |
                                         tag(hash));
}

inline Hashmap::EntryHeader* Hashmap::find_chain(hash_t hash) {
   auto pos = hash & mask;
   return entries[pos].load(std::memory_order_relaxed);
}

template <bool concurrentInsert>
void inline Hashmap::insert(EntryHeader* entry, hash_t hash) {
   const size_t pos = hash & mask;
   assert(pos <= mask);
   assert(pos < capacity);
   if (concurrentInsert) {

      auto locPtr = &entries[pos];
      EntryHeader* loc = locPtr->load();
      EntryHeader* newLoc;
      do {
         entry->next = loc;
         newLoc = entry;
      } while (!locPtr->compare_exchange_weak(loc, newLoc));
   } else {
      auto& loc = entries[pos];
      auto oldValue = loc.load(std::memory_order_relaxed);
      entry->next = oldValue;
      loc.store(entry, std::memory_order_relaxed);
   }
}

inline Hashmap::EntryHeader* Hashmap::find_chain_tagged(hash_t hash) {
  //static_assert(sizeof(hash_t) == 8, "Hashtype not supported");
   auto pos = hash & mask;
   auto candidate = entries[pos].load(std::memory_order_relaxed);
   auto filterMatch = (size_t)candidate & tag(hash);
   if (filterMatch)
      return ptr(candidate);
   else
      return end();
}

inline Vec8uM Hashmap::find_chain_tagged(Vec8u hashes) {
   auto pos = hashes & Vec8u(mask);
   Vec8u candidates = _mm512_i64gather_epi64(pos, (const long long int*)entries, 8);
   Vec8u filterMatch = candidates & tag(hashes);
   __mmask8 matches = filterMatch != Vec8u(uint64_t(0));
   candidates = candidates & Vec8u(maskPointer);
   return {candidates, matches};
}

template <bool concurrentInsert>
void inline Hashmap::insert_tagged(EntryHeader* entry, hash_t hash) {
   const size_t pos = hash & mask;
   assert(pos <= mask);
   assert(pos < capacity);
   if (concurrentInsert) {
      auto locPtr = &entries[pos];
      EntryHeader* loc = locPtr->load();
      EntryHeader* newLoc;
      do {
         entry->next = ptr(loc);
         newLoc = update(loc, entry, hash);
      } while (!locPtr->compare_exchange_weak(loc, newLoc));
   } else {
      auto& loc = entries[pos];
      auto oldValue = loc.load(std::memory_order_relaxed);
      entry->next = ptr(oldValue);
      loc.store(update(loc, entry, hash), std::memory_order_relaxed);
   }
}

template <bool concurrentInsert>
void inline Hashmap::insertAll(EntryHeader* first, size_t n, size_t step) {
   EntryHeader* e = first;
   for (size_t i = 0; i < n; ++i) {
      insert<concurrentInsert>(e, e->hash);
      e = reinterpret_cast<EntryHeader*>(reinterpret_cast<uint8_t*>(e) + step);
   }
}

template <bool concurrentInsert>
void inline Hashmap::insertAll_tagged(EntryHeader* first, size_t n,
                                      size_t step) {
   EntryHeader* e = first;
   for (size_t i = 0; i < n; ++i) {
      insert_tagged<concurrentInsert>(e, e->hash);
      e = reinterpret_cast<EntryHeader*>(reinterpret_cast<uint8_t*>(e) + step);
   }
}

size_t inline Hashmap::setSize(size_t nrEntries) {
   assert(nrEntries != 0);
   if (entries)
      mem::free_huge(entries, capacity * sizeof(std::atomic<EntryHeader*>));

   const auto loadFactor = 0.7;
   size_t exp = 64 - __builtin_clzll(nrEntries);
   assert(exp < sizeof(hash_t) * 8);
   if (((size_t)1 << exp) < nrEntries / loadFactor) exp++;
   capacity = ((size_t)1) << exp;
   mask = capacity - 1;
   entries = static_cast<std::atomic<EntryHeader*>*>(
       mem::malloc_huge(capacity * sizeof(std::atomic<EntryHeader*>)));
   //clear();
   return capacity * loadFactor;
}

void inline Hashmap::clear() {
   for (size_t i = 0; i < capacity; i++) {
      entries[i].store(end(), std::memory_order_relaxed);
   }
}

template <typename K, typename V, typename H, bool useTags = true>
class Hashmapx : public Hashmap {
   H hasher;
   size_t nrEntries = 0;

 public:
   using key_type = K;
   using value_type = V;
   static const uint64_t seed = 902850234;
   struct Entry {
      EntryHeader h;
      K k;
      V v;
      Entry(hash_t h_, K k_, V v_) : h(nullptr, h_), k(k_), v(v_) {}
   };
   template <bool concurrentInsert = true> void insert(Entry& entry);
   template <bool concurrentInsert = true>
   void insertAll(Entry* first, size_t n);
   template <bool concurrentInsert = true>
   void insertAll(std::deque<Entry>& entries);
   template <bool concurrentInsert = true>
   void insertAll(runtime::Stack<Entry>& entries);
   Entry* findOneEntry(const K& key, hash_t hash);
   V* findOne(const K& key);
   V* findOne(const K& key, hash_t hash);
   /// Find or create entry
   /// Not thread safe
   template <typename T>
   V* findOrCreate(K& key, hash_t hash, V& defaultValue, T& entryCollection);
   template <typename T, typename CB, typename KEY>
   V* findOrCreate(KEY&& key, hash_t hash, V& defaultValue, T& entryCollection,
                   CB onGroup);
   hash_t hash(const K& k);
   hash_t hash(const K& k, hash_t seed);
   inline static Entry* end() { return nullptr; }
   size_t size() { return nrEntries; }
   size_t inline setSize(size_t nrEntries);
   void clear();
   Hashmapx() = default;
   Hashmapx(Hashmapx&&) = default;
};

template <typename K, typename V, typename H, bool useTags>
size_t inline Hashmapx<K, V, H, useTags>::setSize(size_t newSize) {
   nrEntries = 0;
   return Hashmap::setSize(newSize);
}

template <typename K, typename V, typename H, bool useTags>
template <bool concurrentInsert>
void Hashmapx<K, V, H, useTags>::insert(Entry& entry) {
   if (useTags)
      insert_tagged<concurrentInsert>(&entry.h, entry.h.hash);
   else
      Hashmap::insert<concurrentInsert>(&entry.h, entry.h.hash);

   nrEntries++;
}

template <typename K, typename V, typename H, bool useTags>
void Hashmapx<K, V, H, useTags>::clear() {
   nrEntries = 0;
   Hashmap::clear();
}

template <typename K, typename V, typename H, bool useTags>
template <bool concurrentInsert>
void Hashmapx<K, V, H, useTags>::insertAll(Entry* first, size_t n) {
   if (useTags)
      insertAll_tagged<concurrentInsert>(first, n, sizeof(Entry));
   else
      insertAll<concurrentInsert>(first, n, sizeof(Entry));
   nrEntries += n;
}

template <typename K, typename V, typename H, bool useTags>
template <bool concurrentInsert>
void Hashmapx<K, V, H, useTags>::insertAll(std::deque<Entry>& entries) {
   if (useTags)
      for (auto& e : entries) insert_tagged<concurrentInsert>(&e.h, e.h.hash);
   else
      for (auto& e : entries) Hashmap::insert<concurrentInsert>(&e.h, e.h.hash);

   nrEntries += entries.size();
}

template <typename K, typename V, typename H, bool useTags>
template <bool concurrentInsert>
void Hashmapx<K, V, H, useTags>::insertAll(runtime::Stack<Entry>& entries) {
   size_t n = 0;
   if (useTags)
      for (auto block : entries) {
         for (auto& e : block) insert_tagged<concurrentInsert>(&e.h, e.h.hash);
         n += block.size();
      }
   else
      for (auto block : entries) {
         for (auto& e : block)
            Hashmap::insert<concurrentInsert>(&e.h, e.h.hash);
         n += block.size();
      }

   nrEntries += n;
}

template <typename K, typename V, typename H, bool useTags>
inline typename Hashmapx<K, V, H, useTags>::Entry*
Hashmapx<K, V, H, useTags>::findOneEntry(const K& key, hash_t h) {
   Entry* entry;
   if (useTags)
      entry = reinterpret_cast<Entry*>(find_chain_tagged(h));
    else
      entry = reinterpret_cast<Entry*>(find_chain(h));
    if (entry == end()) return nullptr;
    for (; entry != end(); entry = reinterpret_cast<Entry*>(entry->h.next))
       if (entry->h.hash == h && entry->k == key) return entry;
    return nullptr;
  }

template <typename K, typename V, typename H, bool useTags>
inline V* Hashmapx<K, V, H, useTags>::findOne(const K& key) {
   auto h = hash(key, seed);
   Entry* entry;
   if (useTags)
      entry = reinterpret_cast<Entry*>(find_chain_tagged(h));
   else
      entry = reinterpret_cast<Entry*>(find_chain(h));
   if (entry == end()) return nullptr;
   for (; entry != end(); entry = reinterpret_cast<Entry*>(entry->h.next))
      if (entry->h.hash == h && entry->k == key) return &entry->v;
   return nullptr;
}

template <typename K, typename V, typename H, bool useTags>
inline V* Hashmapx<K, V, H, useTags>::findOne(const K& key, hash_t h) {
   Entry* entry;
   if (useTags)
      entry = reinterpret_cast<Entry*>(find_chain_tagged(h));
   else
      entry = reinterpret_cast<Entry*>(find_chain(h));
   if (entry == end()) return nullptr;
   for (; entry != end(); entry = reinterpret_cast<Entry*>(entry->h.next))
      if (entry->h.hash == h && entry->k == key) return &entry->v;
   return nullptr;
}

template <typename K, typename V, typename H, bool useTags>
template <typename T>
inline V* Hashmapx<K, V, H, useTags>::findOrCreate(K& key, hash_t hash,
                                                   V& defaultValue,
                                                   T& entryCollection) {
   return findOrCreate(key, hash, defaultValue, entryCollection, []() {});
}

template <typename K, typename V, typename H, bool useTags>
template <typename T, typename CB, typename KEY>
inline V*
Hashmapx<K, V, H, useTags>::findOrCreate(KEY&& key, hash_t hash, V& defaultValue,
                                         T& entryCollection, CB onGroup) {
   V* group = findOne(key, hash);
   if (!group) {
      onGroup();
      entryCollection.emplace_back(hash, key, defaultValue);
      auto& g = entryCollection.back();
      insert<false>(g);
      group = &g.v;
   }
   return group;
}

template <typename K, typename V, typename H, bool useTags>
Hashmap::hash_t Hashmapx<K, V, H, useTags>::hash(const K& key) {
   return hash(key, seed);
}

template <typename K, typename V, typename H, bool useTags>
Hashmap::hash_t Hashmapx<K, V, H, useTags>::hash(const K& key, hash_t seed) {
   return hasher(key, seed);
}

template <typename K, typename H, bool useTags = true>
class Hashset : public Hashmap {
   H hasher;
   static const uint64_t seed = 902850234;

 public:
   struct Entry {
      EntryHeader h;
      K k;
      Entry(hash_t h, K k);
   };
   void insertAll(Entry* first, size_t n);
   void insertAll(std::deque<Entry>& entries);
   void insertAll(runtime::Stack<Entry>& entries);
   bool contains(const K& key);
   hash_t hash(const K& k);
   hash_t hash(const K& k, hash_t seed);
   inline static Entry* end() { return nullptr; }
};

template <typename K, typename H, bool useTags>
Hashset<K, H, useTags>::Entry::Entry(hash_t h, K key) : h{nullptr, h}, k(key) {}

template <typename K, typename H, bool useTags>
void Hashset<K, H, useTags>::insertAll(Entry* first, size_t n) {
   if (useTags)
      Hashmap::insertAll_tagged(&first->h, n, sizeof(Entry));
   else
      Hashmap::insertAll(&first->h, n, sizeof(Entry));
}

template <typename K, typename H, bool useTags>
void Hashset<K, H, useTags>::insertAll(std::deque<Entry>& entries) {
   if (useTags)
      for (auto& e : entries) insert_tagged(&e.h, e.h.hash);
   else
      for (auto& e : entries) insert(&e.h, e.h.hash);
}

template <typename K, typename H, bool useTags>
void Hashset<K, H, useTags>::insertAll(runtime::Stack<Entry>& entries) {
   if (useTags)
      for (auto block : entries)
         for (auto& e : block) insert_tagged(&e.h, e.h.hash);
   else
      for (auto block : entries)
         for (auto& e : block) insert(&e.h, e.h.hash);
}

template <typename K, typename H, bool useTags>
inline bool Hashset<K, H, useTags>::contains(const K& key) {
   auto h = hash(key, seed);
   Entry* entry;
   if (useTags)
      entry = reinterpret_cast<Entry*>(find_chain_tagged(h));
   else
      entry = reinterpret_cast<Entry*>(find_chain(h));
   if (entry == end()) return false;
   for (; entry != end(); entry = reinterpret_cast<Entry*>(entry->h.next))
      if (entry->h.hash == h && entry->k == key) return true;
   return false;
}

template <typename K, typename H, bool useTags>
Hashmap::hash_t Hashset<K, H, useTags>::hash(const K& key) {
   return hash(key, seed);
}

template <typename K, typename H, bool useTags>
Hashmap::hash_t Hashset<K, H, useTags>::hash(const K& key, hash_t seed) {
   return hasher(key, seed);
}
} // namespace runtime
