#pragma once
#include "common/runtime/Concurrency.hpp"
#include "common/runtime/Util.hpp"
#include <cstddef>
#include <new>

namespace runtime {

template <typename T> class Stack {
 private:
   struct Chunk;

 public:
   static const size_t initialSize = 1024;
   Stack();
   Stack(const Stack&) = delete;
   Stack(Stack&&) = default;
   /// construct element at top of stack
   template <typename... C> void emplace_back(C&&...);
   class ChunkIter;
   /// iterates of all chunks in the stack
   struct StackIter {
      StackIter(const Stack<T>& parent);
      StackIter(const Stack<T>& parent, Chunk* c);
      const Stack<T>& data;
      size_t chunkSize = initialSize;
      Chunk* current = nullptr;
      void operator++();
      ChunkIter operator*() const;
      bool operator!=(const StackIter& other) const;
   };
   /// iterates all elements in one chunk
   class ChunkIter {
    public:
      ChunkIter(T* f, T* l);
      T* begin() const;
      T* end() const;
      size_t size() const;

    private:
      T* first;
      T* last;
   };

   StackIter begin() const;
   StackIter end() const;
   T& back();
   void clear();
   bool empty() const;
   size_t size() const;

 private:
   struct Chunk {
      Chunk* next = nullptr;
      T* data();
   };
   size_t chunkSize = initialSize;
   size_t fill = 0;
   size_t nrElements = 0;
   Chunk* first;
   Chunk* last;
   void newChunk();
};

template <typename T> Stack<T>::Stack() {
   auto alloc =
       this_worker->allocator.allocate(sizeof(Chunk) + chunkSize * sizeof(T));
   first = new (alloc) Chunk;
   last = first;
}

template <typename T> typename Stack<T>::StackIter Stack<T>::begin() const {
   return StackIter(*this, this->first);
}
template <typename T> typename Stack<T>::StackIter Stack<T>::end() const {
   return StackIter(*this, this->last->next); // iteration is over when it
                                              // reaches whatever comes after
                                              // last
}

template <typename T> T& Stack<T>::back() {
   return *((last->data() + fill) - 1);
}
template <typename T> void Stack<T>::clear() {
   // reset all values, but keep memory in chunk chain
   last = first;
   chunkSize = initialSize;
   fill = 0;
   nrElements = 0;
}

template <typename T> bool Stack<T>::empty() const {
   return (first == last) & (fill == 0);
}
template <typename T> size_t Stack<T>::size() const {
   return nrElements + fill;
}

template <typename T>
template <typename... C>
void Stack<T>::emplace_back(C&&... args) {
   if (fill == chunkSize) newChunk();
   auto loc = last->data() + fill;
   new (loc) T(std::forward<C>(args)...);
   fill++;
};

template <typename T> void Stack<T>::newChunk() {
   chunkSize *= 2;
   void* alloc;
   if (last->next)
      last = last->next; // reuse memory
   else {
      auto prev = last;
      alloc = this_worker->allocator.allocate(sizeof(Chunk) +
                                              chunkSize * sizeof(T));
      last = new (alloc) Chunk;
      prev->next = last;
   }
   nrElements += fill;
   fill = 0;
}

template <typename T> T* Stack<T>::Chunk::data() {
   return reinterpret_cast<T*>(addBytes(this, sizeof(Chunk)));
}

template <typename T>
Stack<T>::StackIter::StackIter(const Stack<T>& p) : data(p) {}
template <typename T>
Stack<T>::StackIter::StackIter(const Stack<T>& p, Chunk* c)
    : data(p), current(c) {}

template <typename T> void Stack<T>::StackIter::operator++() {
   current = current->next;
   chunkSize *= 2;
}

template <typename T>
typename Stack<T>::ChunkIter Stack<T>::StackIter::operator*() const {
   auto d = current->data();
   if (current == data.last)
      return Stack<T>::ChunkIter(d, d + data.fill);
   else
      return Stack<T>::ChunkIter(d, d + chunkSize);
}

template <typename T>
bool Stack<T>::StackIter::operator!=(const StackIter& other) const {
   return current != other.current;
}

template <typename T>
Stack<T>::ChunkIter::ChunkIter(T* f, T* l) : first(f), last(l) {}
template <typename T> T* Stack<T>::ChunkIter::begin() const { return first; }
template <typename T> T* Stack<T>::ChunkIter::end() const { return last; }
template <typename T> size_t Stack<T>::ChunkIter::size() const {
   return last - first;
}

} // namespace runtime
