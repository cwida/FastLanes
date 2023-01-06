#include "common/runtime/MemoryPool.hpp"
#include "common/runtime/Memory.hpp"
#include <new>

namespace runtime {

GlobalPool::GlobalPool() {
   current = newChunk(allocSize);
   start = (int8_t*)current + sizeof(Chunk);
   end = start + allocSize;
}

GlobalPool::~GlobalPool() {
   for (auto chunk = current; chunk;) {
      auto c = chunk;
      chunk = chunk->next; // read first, then free
      mem::free_huge(c, c->size + sizeof(Chunk));
   }
   current = nullptr;
}

GlobalPool::Chunk* GlobalPool::newChunk(size_t size) {
   return new (mem::malloc_huge(size + sizeof(Chunk))) Chunk(size);
}

void* GlobalPool::allocate(size_t size) {
   int8_t* start_;
   int8_t* end_;
   int8_t* alloc;
restart:
   do {
      start_ = start.load();
      end_ = end.load();
      if (start_ + size >= end_) {
         {
            std::lock_guard<std::mutex> lock(refill);
            // recheck condition
            start_ = start.load();
            end_ = end.load();
            if (start_ + size >= end_) {
               // set available space to 0 so that no other thread can
               // get memory
               do {
                  end_ = end.load();
               } while (!start.compare_exchange_weak(start_, end_));
               // Add a new chunk if space isn't sufficient
               allocSize = std::max(allocSize * 2, size);
               auto chunk = newChunk(allocSize);
               chunk->next = current;

               start_ = (int8_t*)chunk + sizeof(Chunk);
               end_ = start_ + allocSize;
               // order is important due to above conditions in if
               if (chunk < current) {
                  end = end_;
                  start = start_;
               } else {
                  start = start_;
                  end = end_;
               }
               current = chunk;
            } else
               goto restart;
         }
      }
      alloc = start_;
   } while (!start.compare_exchange_weak(start_, start_ + size));

   return alloc;
}

GlobalPool* Allocator::setSource(GlobalPool* source) {
   auto previousSource = memorySource;
   memorySource = source;
   if (source) {
      start = (uint8_t*)memorySource->allocate(allocSize);
      free = allocSize;
   }
   return previousSource;
}

void ResetableAllocator::setSource(Allocator* source) {
   memorySource = source;
   if (source) {
      auto created =
          (uint8_t*)memorySource->allocate(allocSize + sizeof(Chunk));
      auto chunk = new (created) Chunk();
      chunk->size = allocSize;
      current = chunk;
      first = chunk;
      free = current->size;
      start = reinterpret_cast<uint8_t*>(current) + sizeof(Chunk);
   }
}

} // namespace runtime
