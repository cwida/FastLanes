#pragma once
#include "common/runtime/Concurrency.hpp"
#include "vectorwise/defs.hpp"
#include <cstdlib>

#include <deque>

namespace vectorwise {

template <typename T>
class SizeBuffer
/// Buffer which keeps track of how many elements are stored in it
{
   pos_t s = 0;
   T payload[];

 public:
   T& operator[](size_t pos) { return payload[pos]; }
   void push_back(T el) { payload[s++] = el; }
   pos_t size() const { return s; }
   void setSize(pos_t newSize) { s = newSize; }
   void clear() { s = 0; }
   T* data() { return payload; }
};

class VectorAllocator
/// allocator for buffers
{
   size_t vectorSize;

 public:
   /// Get a standard buffer
   inline void* get(size_t elementSize) {
      return runtime::this_worker->allocator.allocate(vectorSize * elementSize);
   }
   inline void* getPlus1(size_t elementSize) {
      return runtime::this_worker->allocator.allocate((vectorSize + 1) *
                                                      elementSize);
   }
   inline SizeBuffer<void*>* getSizeBuffer(size_t elementSize) {
     auto alloc = runtime::this_worker->allocator.allocate(
         vectorSize * elementSize + sizeof(SizeBuffer<void*>));
     new (alloc) SizeBuffer<void*>();
     return reinterpret_cast<SizeBuffer<void*>*>(alloc);
   }
   VectorAllocator(size_t vecSize) : vectorSize(vecSize) {}
   inline size_t getVecSize() { return vectorSize; }
};
}
