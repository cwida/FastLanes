#include <iostream>
#include <cassert>
#include <algorithm>
#include <ostream>
#include <vector>
#include <cstring>
#include <sys/mman.h>
#include <immintrin.h>
#include <cassert>

// #include "/opt/iaca-lin64/include/iacaMarks.h"
#include "profile.hpp"

using namespace std;

void* malloc_huge(size_t size) {
   void* p = mmap(NULL, size, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
#ifdef __linux__
   madvise(p, size, MADV_HUGEPAGE);
#endif
   memset(p, 0, size);
   return p;
}

struct Vec8u {
   union {
      __m512i reg;
      uint64_t entry[8];
   };

   // constructor
   Vec8u(uint64_t x) { reg = _mm512_set1_epi64(x); };
   Vec8u(void* p) { reg = _mm512_loadu_si512(p); };
   Vec8u(__m512i x) { reg = x; };
   Vec8u(uint64_t x0, uint64_t x1, uint64_t x2, uint64_t x3, uint64_t x4, uint64_t x5, uint64_t x6, uint64_t x7) { reg = _mm512_set_epi64(x0, x1, x2, x3, x4, x5, x6, x7); };

   // implicit conversion to register
   operator __m512i() { return reg; }

   // print vector (for debugging)
   friend std::ostream& operator<< (std::ostream& stream, const Vec8u& v) {
      for (auto& e : v.entry)
         stream << e << " ";
      return stream;
   }
};

inline Vec8u operator+ (const Vec8u& a, const Vec8u& b) { return _mm512_add_epi64(a.reg, b.reg); }
inline Vec8u operator- (const Vec8u& a, const Vec8u& b) { return _mm512_sub_epi64(a.reg, b.reg); }
inline Vec8u operator* (const Vec8u& a, const Vec8u& b) { return _mm512_mullo_epi64(a.reg, b.reg); }
inline Vec8u operator^ (const Vec8u& a, const Vec8u& b) { return _mm512_xor_epi64(a.reg, b.reg); }
inline Vec8u operator>> (const Vec8u& a, const unsigned shift) { return _mm512_srli_epi64(a.reg, shift); }
inline Vec8u operator<< (const Vec8u& a, const unsigned shift) { return _mm512_slli_epi64(a.reg, shift); }
inline Vec8u operator& (const Vec8u& a, const Vec8u& b) { return _mm512_and_epi64(a.reg, b.reg); }
inline __mmask16 operator== (const Vec8u& a, const Vec8u& b) { return _mm512_cmpeq_epi64_mask(a.reg, b.reg); }
inline __mmask16 operator!= (const Vec8u& a, const Vec8u& b) { return _mm512_cmpneq_epi64_mask(a.reg, b.reg); }

//int countLoops = 0;

struct Hashtable {
   struct Entry {
      uint64_t key;
      Entry* next;
      uint64_t value;
      //uint64_t value2;

      Entry(uint64_t key,uint64_t value) : key(key) , value(value) {}
   };
   uint64_t mask;
   Entry** entries;

   Hashtable(uint64_t sizeInBits) {
      uint64_t size = (1ull<<sizeInBits);
      mask = size-1;
      entries = (Entry**)malloc_huge(size*sizeof(Entry*));
   }

   uint64_t hashKey(uint64_t k) {
      //MurmurHash64A
      const uint64_t m = 0xc6a4a7935bd1e995ull;
      const int r = 47;
      uint64_t h = 0x8445d61a4e774912ull ^ (8*m);
      k *= m;
      k ^= k >> r;
      k *= m;
      h ^= k;
      h *= m;
      h ^= h >> r;
      h *= m;
      h ^= h >> r;
      return h;
   }

   void insert(uint64_t key, uint64_t value) {
      auto e = new Entry(key,value);
      uint64_t pos = hashKey(key) & mask;
      e->next = entries[pos];
      entries[pos] = e;
   }

   Entry* lookup(uint64_t key) {
      uint64_t pos = hashKey(key) & mask;
      auto e = entries[pos];
      while (e) {
         if (e->key == key)
            return e;
         e = e->next;
      }
      return nullptr;
   }

   Entry* lookup2(uint64_t key) {
      uint64_t pos = hashKey(key) & mask;
      auto e = entries[pos];
      Entry* result = nullptr;
      while (e) {
         if (e->key == key)
            result = e;
         e = e->next;
      }
      return result;
   }

   void lookups(uint64_t* keys, uint64_t count, uint64_t* resultIndexes, Entry** resultEntry) {
      for (uint64_t i=0; i<count; i++) {
         uint64_t key = keys[i];
         uint64_t pos = hashKey(key) & mask;
         auto e = entries[pos];
         uint64_t outPos = 0;
         while (e) {
            if (e->key == key) {
               resultEntry[outPos] = e;
               resultIndexes[outPos] = i;
               outPos++;
            }
            e = e->next;
         }
      }
   }

//#pragma clang loop vectorize(disable)
//IACA_START
//IACA_END

   void initVectors(uint64_t* keys, uint64_t count, uint64_t* initialKeyIndexes, uint64_t* initialKeyPtrs) {
      Vec8u maskV = mask;
      Vec8u m = 0xc6a4a7935bd1e995ull;
      const int r = 47;
      Vec8u initH = 0x8445d61a4e774912ull ^ (8*m);

      Vec8u eight = 8;
      Vec8u keyIndexes(0,1,2,3,4,5,6,7);

      for (uint64_t i=0; i<count; i+=8) {
         Vec8u key = keys + i;
         Vec8u h = initH;
         Vec8u k = key;
         k = k * m;
         k = k ^ (k >> r);
         k = k * m;
         h = h ^ k;
         h = h * m;
         h = h ^ (h >> r);
         h = h * m;
         h = h ^ (h >> r);
         Vec8u pos = h & maskV;
         Vec8u e = _mm512_i64gather_epi64(pos, reinterpret_cast<const long long int*>(entries), 8);
         _mm512_storeu_si512(initialKeyPtrs + i, e);
         _mm512_storeu_si512(initialKeyIndexes + i, keyIndexes);
         keyIndexes = keyIndexes + eight;
      }
   }

   void lookups3(uint64_t* keys, uint64_t count, uint64_t* resultIndexes, Entry** resultEntry) {
      /*
        if !null
          gather
          if key matches
            store matches
          cycle to next
        else
          refill
       */

      uint64_t initialKeyIndexes[count];
      uint64_t initialKeyPtrs[count];
      initVectors(keys, count, initialKeyIndexes, initialKeyPtrs);

      Vec8u eight = 8;
      Vec8u nulls(_mm512_set1_epi64(0));

      Vec8u key(keys); // uint64_t
      Vec8u keyIndexes(initialKeyIndexes); // uint64_t
      Vec8u ptr(initialKeyPtrs); // Entry*

      unsigned inPos = 8; // # keys read
      unsigned outPos = 0; // # results written

      while (true) {
         //IACA_START
         // not null: gather
         __mmask8 isNotNull = (ptr != nulls);
         Vec8u candidateKeys = _mm512_mask_i64gather_epi64(ptr, isNotNull, ptr, nullptr, 1);

         // not null + match: store result
         __mmask8 isMatch = _mm512_mask_cmpeq_epi64_mask(isNotNull, key, candidateKeys);
         _mm512_mask_compressstoreu_epi64(resultEntry + outPos, isMatch, ptr);
         _mm512_mask_compressstoreu_epi64(resultIndexes + outPos, isMatch, keyIndexes);
         outPos += __builtin_popcount(isMatch);

         // not null: cycle to next
         Vec8u nextAddr = _mm512_mask_add_epi64(ptr, isNotNull, ptr, eight);
         ptr = _mm512_mask_i64gather_epi64(nextAddr, isNotNull, nextAddr, nullptr, 1);

         // null: refill
         __mmask8 isNull = _mm512_knot(isNotNull);
         key = _mm512_mask_expandloadu_epi64(key, isNull, keys + inPos);
         ptr = _mm512_mask_expandloadu_epi64(ptr, isNull, initialKeyPtrs + inPos);
         keyIndexes = _mm512_mask_expandloadu_epi64(keyIndexes, isNull, initialKeyIndexes + inPos);
         inPos += __builtin_popcount(isNull);

         if (inPos > count-8)
            break;
         if (outPos > count-8)
            break;
      }
      //IACA_END
   }


   void lookups2(uint64_t* keys, uint64_t count, Entry** result) {
      Vec8u m = 0xc6a4a7935bd1e995ull;
      const int r = 47;
      Vec8u initH = 0x8445d61a4e774912ull ^ (8*m);
      Vec8u maskV = mask;
      Vec8u nulls(_mm512_set1_epi64(0));
      Vec8u eight = 8;

      for (uint64_t i=0; i<count; i+=8) {
         Vec8u key = keys + i;
         Vec8u h = initH;
         Vec8u k = key;

         k = k * m;
         k = k ^ (k >> r);
         k = k * m;
         h = h ^ k;
         h = h * m;
         h = h ^ (h >> r);
         h = h * m;
         h = h ^ (h >> r);

         Vec8u pos = h & maskV;
         Vec8u e = _mm512_i64gather_epi64(pos, reinterpret_cast<const long long int*>(entries), 8);
         Vec8u results = nulls;
         __mmask16 notnullMask = (e != nulls);

         while (notnullMask) {
            //countLoops++;
            Vec8u keysEntry = _mm512_mask_i64gather_epi64(e, notnullMask, e, nullptr, 1);
            __mmask8 matches = _mm512_mask_cmpeq_epi64_mask(notnullMask, key, keysEntry);
            results = _mm512_mask_blend_epi64(matches, results, e);
            Vec8u next = e + eight;
            e = _mm512_mask_i64gather_epi64(next, notnullMask, next, nullptr, 1);
            notnullMask = _mm512_mask_cmpneq_epi64_mask(notnullMask, e, nulls);
         }
         _mm512_store_epi64(result + i, results);
      }
   }



};

int main() {
   uint64_t nBits = 18;
   uint64_t n = 1ull << nBits;
   unsigned repeat = 10;

   auto keys = reinterpret_cast<uint64_t*>(malloc_huge(n*sizeof(uint64_t)));
   auto resultIndexes = reinterpret_cast<uint64_t*>(malloc_huge(n*sizeof(uint64_t)));
   auto result1 = reinterpret_cast<Hashtable::Entry**>(malloc_huge(n*sizeof(Hashtable::Entry*)));
   auto result2 = reinterpret_cast<Hashtable::Entry**>(malloc_huge(n*sizeof(Hashtable::Entry*)));

   for (uint64_t i=0; i<n; i++)
      keys[i] = (((uint64_t)random())<<(nBits+1)) | i;

   PerfEvents e;
   Hashtable ht(nBits+1);

   for (uint64_t i=0; i<n; i++)
      ht.insert(keys[i], i);

   //for (uint64_t i=0; i<n; i++)
   //if (random()%100 < 95)
   //  keys[i] = 457867;

   e.timeAndProfile("seq",n,[&](){
         ht.lookups(keys, n, resultIndexes, result1);
      }, repeat);

   e.timeAndProfile("simd",n,[&](){
         ht.lookups2(keys, n, result2);
      }, repeat);

   e.timeAndProfile("simd refill",n,[&](){
         for (unsigned i=0; i<n; i+=2048)
            ht.lookups3(keys+i, 2048, resultIndexes+i, result1+i);
      }, repeat);


   //assert(memcmp(result1,result2,n*sizeof(Hashtable::Entry*))==0);

   //cout << countLoops << endl;

   //for (unsigned i=0; i<n; i++)
   //assert(result[i]->key == keys[i] && result[i]->value == i);

   return 0;
}
