#pragma once
#include <stdexcept>
#include <sys/mman.h>

namespace mem {
inline void* malloc_huge(size_t size) {
   void* p = mmap(nullptr, size, PROT_READ | PROT_WRITE,
                  MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
#ifdef __linux__
   madvise(p, size, MADV_HUGEPAGE);
#endif
   // memset(p, 0, size);
   return p;
}

inline void free_huge(void* p, size_t size) {
   auto r = munmap(p, size);
   if (r) throw std::runtime_error("Memory unmapping failed.");
}
} // namespace mem
