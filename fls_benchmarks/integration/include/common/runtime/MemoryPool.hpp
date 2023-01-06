#pragma once
#include <algorithm>
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <mutex>
#include <new>


#define DEBUG_ALLOC 0

namespace runtime {

class GlobalPool {
   struct Chunk {
      Chunk* next = nullptr;
      size_t size;
      Chunk(size_t s) : size(s) {}
   };

   std::atomic<int8_t*> start;
   std::atomic<int8_t*> end;

   std::mutex refill;
   // guarded by refill mutex
   Chunk* current = nullptr;
   size_t allocSize = 128 * 1024 * 1024;

 public:
   GlobalPool();
   ~GlobalPool();
   GlobalPool(GlobalPool&&) = delete;
   GlobalPool(const GlobalPool&) = delete;

   Chunk* newChunk(size_t size);
   void* allocate(size_t size);
};

class Allocator {
   size_t allocSize =
       1024 * 1024 * 2; // start with a multiple of the huge page size
   uint8_t* start = nullptr;
   size_t free = 0;

 public:
   GlobalPool* memorySource = nullptr;
   Allocator() = default;
   Allocator(Allocator&&) = default;
   Allocator(const Allocator&) = delete;
   GlobalPool* setSource(GlobalPool* s);
   inline void* allocate(size_t size);
};

inline void* Allocator::allocate(size_t size) {
#if DEBUG_ALLOC
  return malloc(size);
#else
   auto aligndiff = 64 - ((uintptr_t)start % 64);
   size += aligndiff;
   if (free < size) {
      allocSize = std::max(allocSize * 2, size + 64);
      start = (uint8_t*)memorySource->allocate(allocSize);

      aligndiff = 64 - ((uintptr_t)start % 64);
      size += aligndiff;
      free = allocSize;
   }
   auto alloc = start + aligndiff;
   start += size;
   free -= size;
   return alloc;
#endif
}

class ResetableAllocator {
   size_t allocSize =
       1024 * 1024 * 2; // start with a multiple of the huge page size
   uint8_t* start = nullptr;
   size_t free = 0;

   struct Chunk {
      Chunk* next = nullptr;
      size_t size = 0;
   };

   Chunk* first;
   Chunk* current;
   Allocator* memorySource = nullptr;

 public:
   ResetableAllocator() = default;
   ResetableAllocator(ResetableAllocator&&) = default;
   ResetableAllocator(const ResetableAllocator&) = delete;
   void setSource(Allocator* s);
   inline void* allocate(size_t size);
   inline void reset();
};
inline void* ResetableAllocator::allocate(size_t size) {
#if DEBUG_ALLOC
  return malloc(size);
#else
   auto aligndiff = 64 - ((uintptr_t)start % 64);
   size += aligndiff;
   if (free < size) {
      // skip chunks that are too small
      for (; current->next && current->next->size < size; current = current->next) {}
      // in case no chunk with enough space was found: allocate new one
      if(!current->next){
         allocSize = std::max(allocSize * 2, size);
         auto created = (uint8_t*)memorySource->allocate(allocSize + sizeof(Chunk));
         auto chunk = new (created) Chunk();
         chunk->size = allocSize;
         current->next = chunk;
         current = chunk;
      }else{
        current = current->next;
      }
      free = current->size;
      start = reinterpret_cast<uint8_t*>(current) + sizeof(Chunk);

      aligndiff = 64 - ((uintptr_t)start % 64);
      size += aligndiff;
   }
   auto alloc = start + aligndiff;
   start += size;
   free -= size;
   if((uintptr_t)alloc % 64) throw;
   return alloc;
#endif
}

inline void ResetableAllocator::reset() {
   current = first;
   start = reinterpret_cast<uint8_t*>(current) + sizeof(Chunk);
   free = current->size;
}

} // namespace runtime
