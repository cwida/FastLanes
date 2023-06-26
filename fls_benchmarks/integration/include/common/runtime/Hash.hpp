#pragma once
#include "common/Compat.hpp"
#include "common/Util.hpp"
#include "common/defs.hpp"
#include "common/runtime/SIMD.hpp"
#include "common/runtime/Types.hpp"
#include <x86intrin.h>

namespace runtime {

template <typename CHILD> class Hash {
   const CHILD* impl() const { return static_cast<const CHILD*>(this); }

   // inline uint64_t hashKey(uint8_t k, uint64_t seed) const { }
   // inline uint64_t hashKey(uint16_t k, uint64_t seed) const { }
   // inline uint64_t hashKey(uint32_t k, uint64_t seed) const { }
   // inline uint64_t hashKey(uint64_t k, uint64_t seed) const { }
   // inline uint64_t hashKey(uint64_t k) const { return hashKey(k, 0); }

 public:
   // inline uint64_t hashKey(const void* key, int len, uint64_t seed) const { }

  using hash_t = defs::hash_t;
  /// Integers
  inline hash_t operator()(uint64_t x, hash_t seed) const {
     return impl()->hashKey(x, seed);
  }
  inline hash_t operator()(int64_t x, hash_t seed) const {
     return impl()->hashKey(x, seed);
  }
  inline hash_t operator()(uint32_t x, hash_t seed) const {
     return impl()->hashKey(x, seed);
  }
  inline hash_t operator()(int32_t x, hash_t seed) const {
     return impl()->hashKey(x, seed);
  }
  inline hash_t operator()(int8_t x, hash_t seed) const {
     return impl()->hashKey(x, seed);
  }

  /// Pointers
  inline hash_t operator()(void* ptr, hash_t seed) const {
     return impl()->hashKey(reinterpret_cast<uint64_t>(ptr), seed);
  }

  inline hash_t operator()(types::Integer&& x, hash_t seed) const {
     return impl()->hashKey(x.value, seed);
  }
  inline hash_t operator()(const types::Integer& x, hash_t seed) const {
     return impl()->hashKey(x.value, seed);
  }

  inline hash_t operator()(types::Date&& x, hash_t seed) const {
     return impl()->hashKey(x.value, seed);
  }
  inline hash_t operator()(const types::Date& x, hash_t seed) const {
     return impl()->hashKey(x.value, seed);
  }

  template <unsigned len, unsigned precision>
  inline hash_t operator()(types::Numeric<len, precision>&& x,
                           hash_t seed) const {
     return impl()->hashKey(x.value, seed);
  }
  template <unsigned len, unsigned precision>
  inline hash_t operator()(const types::Numeric<len, precision>& x,
                           hash_t seed) const {
     return impl()->hashKey(x.value, seed);
  }

  template <unsigned l>
  inline hash_t operator()(const types::Char<l>& x, hash_t seed) const;
  template <unsigned l>
  inline hash_t operator()(types::Char<l>&& x, hash_t seed) const;

  template <unsigned l>
  inline hash_t operator()(const types::Varchar<l>& x, hash_t seed) const {
     return impl()->hashKey(&x.value, x.len, seed);
   }
   template <unsigned l>
   inline hash_t operator()(types::Varchar<l>&& x, hash_t seed) const {
      return impl()->hashKey(&x.value, x.len, seed);
   }

   template <typename... T>
   inline hash_t operator()(std::tuple<T...>&& x, hash_t seed) const {
      hash_t hash = seed;
      auto& self = *impl();
      auto f = [&](auto& x) { hash = self(x, hash); };
      for_each_in_tuple(x, f);
      return hash;
   }
   template <typename... T>
   inline hash_t operator()(const std::tuple<T...>& x, hash_t seed) const {
      hash_t hash = seed;
      auto& self = *impl();
      auto f = [&](const auto& x) { hash = self(x, hash); };
      for_each_in_tuple(x, f);
      return hash;
   }
};

#define EXTRAOPS(TYPE)                                                         \
   template <>                                                                 \
   template <>                                                                 \
   inline Hash<TYPE>::hash_t Hash<TYPE>::operator()<1>(                        \
       const types::Char<1>& x, hash_t seed) const {                           \
      return impl()->hashKey((uint8_t)x.value, seed);                          \
   }                                                                           \
   template <>                                                                 \
   template <unsigned l>                                                       \
   inline Hash<TYPE>::hash_t Hash<TYPE>::operator()(const types::Char<l>& x,   \
                                                    hash_t seed) const {       \
      return impl()->hashKey(&x.value, x.len, seed);                           \
   }                                                                           \
   template <>                                                                 \
   template <>                                                                 \
   inline Hash<TYPE>::hash_t Hash<TYPE>::operator()<1>(types::Char<1> && x,    \
                                                       hash_t seed) const {    \
      return impl()->hashKey((uint8_t)x.value, seed);                          \
   }                                                                           \
   template <>                                                                 \
   template <unsigned l>                                                       \
   inline Hash<TYPE>::hash_t Hash<TYPE>::operator()(types::Char<l>&& x,        \
                                                    hash_t seed) const {       \
      return impl()->hashKey(&x.value, x.len, seed);                           \
   }

class StdHash {
 public:
   using hash_t = size_t;
   /// Integers
   inline hash_t operator()(uint64_t x, hash_t seed) const {
      return std::hash<decltype(x)>()(x) ^ (seed << 7) ^ (seed >> 2);
   }
   inline hash_t operator()(int64_t x, hash_t seed) const {
      return std::hash<decltype(x)>()(x) ^ (seed << 7) ^ (seed >> 2);
   }
   inline hash_t operator()(uint32_t x, hash_t seed) const {
      return std::hash<decltype(x)>()(x) ^ (seed << 7) ^ (seed >> 2);
   }
   inline hash_t operator()(int32_t x, hash_t seed) const {
      return std::hash<decltype(x)>()(x) ^ (seed << 7) ^ (seed >> 2);
   }

   /// Pointers
   inline hash_t operator()(void* ptr, hash_t seed) const {
      return std::hash<void*>()(ptr) ^ (seed << 7) ^ (seed >> 2);
   }

   template <typename X>
   inline hash_t operator()(const X& x, hash_t seed) const {
      return std::hash<X>()(x) ^ (seed << 7) ^ (seed >> 2);
   }
};

class MurMurHash : public Hash<MurMurHash> {
 public:

// #ifdef __AVX512F__
//   inline Vec8u operator()(Vec8u& k, Vec8u& seed) const {
//     return ->hashKey(k, seed);
//   }
// #endif
   inline hash_t hashKey(uint64_t k) const { return hashKey(k, 0); }
   inline hash_t hashKey(uint64_t k, hash_t seed) const {
      // MurmurHash64A
      const uint64_t m = 0xc6a4a7935bd1e995;
      const int r = 47;
      uint64_t h = seed ^ 0x8445d61a4e774912 ^ (8 * m);
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

   hash_t hashKey(const void* key, int len, hash_t seed) const {
      // MurmurHash64A
      // MurmurHash2, 64-bit versions, by Austin Appleby
      // https://github.com/aappleby/smhasher/blob/master/src/MurmurHash2.cpp
      // 'm' and 'r' are mixing constants generated offline.
      // They're not really 'magic', they just happen to work well.
      const uint64_t m = 0xc6a4a7935bd1e995;
      const int r = 47;

      uint64_t h = seed ^ (len * m);

      const uint64_t* data = (const uint64_t*)key;
      const uint64_t* end = data + (len / 8);

      while (data != end) {
         uint64_t k = *data++;

         k *= m;
         k ^= k >> r;
         k *= m;

         h ^= k;
         h *= m;
      }

      const unsigned char* data2 = (const unsigned char*)data;

      switch (len & 7) {
      case 7: h ^= uint64_t(data2[6]) << 48;FALLTHROUGH
      case 6: h ^= uint64_t(data2[5]) << 40;FALLTHROUGH
      case 5: h ^= uint64_t(data2[4]) << 32;FALLTHROUGH
      case 4: h ^= uint64_t(data2[3]) << 24;FALLTHROUGH
      case 3: h ^= uint64_t(data2[2]) << 16;FALLTHROUGH
      case 2: h ^= uint64_t(data2[1]) << 8;FALLTHROUGH
      case 1: h ^= uint64_t(data2[0]); h *= m;FALLTHROUGH
      };

      h ^= h >> r;
      h *= m;
      h ^= h >> r;

      return h;
   }

  //#ifdef __AVX512F__
#ifdef __AVX512DQ__
   inline Vec8u hashKey(Vec8u k, Vec8u seed) const {
      // MurmurHash64A
      const Vec8u m(0xc6a4a7935bd1e995);
      const Vec8u r(47);
      Vec8u h = seed ^ Vec8u(0x8445d61a4e774912) ^ (Vec8u(8) * m);
      k = k * m;
      k = k ^ (k >> r);
      k = k * m;
      h = h ^ k;
      h = h * m;
      h = h ^ (h >> r);
      h = h * m;
      h = h ^ (h >> r);
      return h;
   }
#endif

};

EXTRAOPS(MurMurHash)


inline uint32_t rotl32 ( uint32_t x, int8_t r ) {
  return (x << r) | (x >> (32 - r));
}
inline uint64_t rotl64 ( uint64_t x, int8_t r ) {
    return (x << r) | (x >> (64 - r));
}

#define	FORCE_INLINE inline __attribute__((always_inline))
#define	ROTL32(x,y)	rotl32(x,y)
#define ROTL64(x,y) rotl64(x,y)

FORCE_INLINE uint32_t fmix32 ( uint32_t h ) {
    h ^= h >> 16;
    h *= 0x85ebca6b;
    h ^= h >> 13;
    h *= 0xc2b2ae35;
    h ^= h >> 16;
    return h;
}
#ifdef __AVX512F__
FORCE_INLINE Vec16u fmix32 ( Vec16u h ) {
    h = h ^ (h >> 16);
    h = h * Vec16u(0x85ebca6b);
    h = h ^ (h >> 13);
    h = h * Vec16u(0xc2b2ae35);
    h = h ^ (h >> 16);
    return h;
}
#endif
FORCE_INLINE uint32_t getblock32 ( const uint32_t * p, int i ) {
    return p[i];
}

#define IS_INT_LE(bits, t) (sizeof(t)<=(bits/8) &&        \
                          std::is_integral<t>::value)

#define IS_INT_EQ(bits, t) (sizeof(t)==(bits/8) &&      \
                            std::is_integral<t>::value)
// 32-bit hashes
class MurMurHash3 : public Hash<MurMurHash3> {
 public:

// #ifdef __AVX512F__
//   inline Vec8u operator()(Vec8u& k, Vec8u& seed) const {
//     return ->hashKey(k, seed);
//   }
// #endif

  template<class T> inline auto
  hashKey(T k, hash_t seed) const -> typename std::enable_if<IS_INT_LE(32,T), hash_t>::type{
     uint32_t h1 = seed;
     const uint32_t c1 = 0xcc9e2d51;
     const uint32_t c2 = 0x1b873593;

     uint32_t k1 = k;

     k1 *= c1;
     k1 = ROTL32(k1,15);
     k1 *= c2;

     h1 ^= k1;
     h1 = ROTL32(h1,13);
     h1 = h1*5+0xe6546b64;

     return fmix32(h1);
   }
   inline hash_t hashKey(uint64_t k) const { return hashKey(k, 0); }

   template<class T> inline auto
   hashKey(T k, hash_t seed) const -> typename std::enable_if<IS_INT_EQ(64,T), hash_t>::type{
   // inline hash_t hashKey(uint64_t k, hash_t seed) const {
     uint32_t h1 = seed;
     const uint32_t c1 = 0xcc9e2d51;
     const uint32_t c2 = 0x1b873593;

     uint32_t k1 = k;
     uint32_t k2 = k >> 32;

     k1 *= c1;
     k1 = ROTL32(k1,15);
     k1 *= c2;

     h1 ^= k1;
     h1 = ROTL32(h1,13);
     h1 = h1*5+0xe6546b64;

     k2 *= c1;
     k1 = ROTL32(k1,15);
     k2 *= c2;

     h1 ^= k2;
     h1 = ROTL32(h1,13);
     h1 = h1*5+0xe6546b64;

     return fmix32(h1);
   }

   hash_t hashKey(const void* key, int len, hash_t seed) const {
     // from: https://github.com/aappleby/smhasher/blob/master/src/MurmurHash3.cpp
     const uint8_t * data = (const uint8_t*)key;
     const int nblocks = len / 4;

     uint32_t h1 = seed;

     const uint32_t c1 = 0xcc9e2d51;
     const uint32_t c2 = 0x1b873593;

     //----------
     // body

     const uint32_t * blocks = (const uint32_t *)(data + nblocks*4);

     for(int i = -nblocks; i; i++)
       {
         uint32_t k1 = getblock32(blocks,i);

         k1 *= c1;
         k1 = ROTL32(k1,15);
         k1 *= c2;

         h1 ^= k1;
         h1 = ROTL32(h1,13);
         h1 = h1*5+0xe6546b64;
       }

     //----------
     // tail

     const uint8_t * tail = (const uint8_t*)(data + nblocks*4);

     uint32_t k1 = 0;

     switch(len & 3)
       {
       case 3: k1 ^= tail[2] << 16;
       case 2: k1 ^= tail[1] << 8;
       case 1: k1 ^= tail[0];
         k1 *= c1; k1 = ROTL32(k1,15); k1 *= c2; h1 ^= k1;
       };

     //----------
     // finalization

     h1 ^= len;

     h1 = fmix32(h1);

     return h1;
   }

#ifdef __AVX512F__

  //#ifdef __AVX512DQ__
   inline Vec16u hashKey(Vec16u k, Vec16u seed) const {
     auto h1 = seed;
     Vec16u c1(0xcc9e2d51);
     Vec16u c2(0x1b873593);

     auto k1 = k;

     k1 = k1 * c1;
     k1 = _mm512_rol_epi32(k1, 15);
     k1 = k1 * c2;

     h1 = h1 ^ k1;
     h1 = _mm512_rol_epi32(h1, 13);

     h1 = h1*Vec16u(5)+Vec16u(0xe6546b64);

     return fmix32(h1);
   }
#endif

};


EXTRAOPS(MurMurHash3)

class CRC32Hash : public Hash<CRC32Hash> {

 public:

   // template<class T> inline auto
   // hashKey(T k, hash_t seed) const -> typename std::enable_if<IS_INT_LE(32,T), hash_t>::type{
   //   const uint64_t c1= 11400714819323198485ull;
   //   const uint64_t c2= 11500714819323198569ull;
   //   return (__builtin_bswap32(k) * c2) ^ (k * c1) ^ (ROTL64(seed, 15));
   // }

   // template<class T> inline auto
   // hashKey(T k, hash_t seed) const -> typename std::enable_if<IS_INT_LE(32,T), hash_t>::type{
   //    return _mm_crc32_u64(seed, k);
   // }

   template<class T> inline auto
   hashKey(T k, hash_t seed) const -> typename std::enable_if<IS_INT_LE(64,T), hash_t>::type{
   // inline hash_t hashKey(uint64_t k, uint64_t seed) const {
      uint64_t result1 = _mm_crc32_u64(seed, k);
      uint64_t result2 = _mm_crc32_u64(0x04c11db7, k);
      return ((result2 << 32) | result1) * 0x2545F4914F6CDD1Dull;
   }
   inline uint64_t hashKey(uint64_t k) const { return hashKey(k, 0); }

   inline uint64_t hashKey(const void* key, int len, uint64_t seed) const {
      auto data = reinterpret_cast<const uint8_t*>(key);
      uint64_t s = seed;
      while (len >= 8) {
         s = hashKey(*reinterpret_cast<const uint64_t*>(data), s);
         data += 8;
         len -= 8;
      }
      if (len >= 4) {
         s = hashKey((uint32_t) * reinterpret_cast<const uint32_t*>(data), s);
         data += 4;
         len -= 4;
      }
      switch (len) {
      case 3: s ^= ((uint64_t)data[2]) << 16;FALLTHROUGH
      case 2: s ^= ((uint64_t)data[1]) << 8;FALLTHROUGH
      case 1: s ^= data[0];FALLTHROUGH
      }
      return s;
   }
};
EXTRAOPS(CRC32Hash);
} // namespace runtime
