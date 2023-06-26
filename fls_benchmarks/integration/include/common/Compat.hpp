#pragma once
#include <cstdlib>
#include <fcntl.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

namespace compat {
inline int posix_fallocate(int fd, off_t offset, off_t len) {
#ifdef __APPLE__
   fstore_t store = {F_ALLOCATECONTIG, F_PEOFPOSMODE, offset, len, 0};
   // Try to get a continous chunk of disk space
   int ret = fcntl(fd, F_PREALLOCATE, &store);
   if (-1 == ret) {
      // OK, perhaps we are too fragmented, allocate non-continuous
      store.fst_flags = F_ALLOCATEALL;
      ret = fcntl(fd, F_PREALLOCATE, &store);
      if (-1 == ret) return -1;
   }
   return ftruncate(fd, len);
#else
   return ::posix_fallocate(fd, offset, len);
#endif
}
inline void* aligned_alloc(size_t align, size_t size) {
#ifdef __APPLE__
   align++; // pretend to use the argument
   return std::malloc(size);
#else
   return ::aligned_alloc(align, size);
#endif
}

inline std::string path(std::string p) {
   auto slash = p.find_last_of("/");
   return p.substr(0, slash);
}

#define CLANG 1
#define GCCC 2

#if defined(__clang__)
#define COMPILER CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
#define COMPILER GCCC
#elif defined(_MSC_VER)
#endif

#if COMPILER==GCCC
#define FALLTHROUGH [[gnu::fallthrough]];
#elif  COMPILER==CLANG
#define FALLTHROUGH
#endif

#define STRINGIFY(a) #a

#if COMPILER==CLANG
#define DIAGNOSTIC_PUSH(ARG)                                                   \
   _Pragma("clang diagnostic push")                                            \
       _Pragma(STRINGIFY(clang diagnostic ignored #ARG))
#define DIAGNOSTIC_POP _Pragma("clang diagnostic pop")
#elif COMPILER==GCCC
#define DIAGNOSTIC_PUSH(ARG)                                                   \
   _Pragma("GCC diagnostic push")                                              \
       _Pragma(STRINGIFY(GCC diagnostic ignored #ARG))
#define DIAGNOSTIC_POP _Pragma("GCC diagnostic pop")
#endif

// clang-format off
DIAGNOSTIC_PUSH(-Wunused-parameter)
template <typename... T> void unused(T... x){};
DIAGNOSTIC_POP


#if COMPILER==GCCC
#define DIAGNOSTIC_PUSH_NO_UNKNOWN DIAGNOSTIC_PUSH(-Wpragmas)
#elif  COMPILER==CLANG
#define DIAGNOSTIC_PUSH_NO_UNKNOWN DIAGNOSTIC_PUSH(-Wunknown-warning-option)
#endif

// clang-format on

#if COMPILER==CLANG
#define NOVECTORIZE
#elif COMPILER==GCCC
#define NOVECTORIZE __attribute__((optimize("no-tree-vectorize")))
#endif
} // namespace compat
