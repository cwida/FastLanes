#include "common/defs.hpp"
#include "common/runtime/Concurrency.hpp"
#include "common/runtime/MemoryPool.hpp"
#include "common/runtime/Util.hpp"
#include <assert.h>
#include <cstdlib>
#include <cstring>
#include <vector>

namespace runtime {

template <size_t chunkSize>
class PartitionedDeque
/// Queue with multiple partitions
/// Used for spilling in parallel operators
{
   using hash_t = defs::hash_t;

 public:
   struct Chunk
   /// Extensible storage for content
   {
      static const size_t size = chunkSize;
      Chunk* next = nullptr;
      template <typename T> T* data();
      Chunk() = default;
      Chunk(const Chunk&) = delete;
      Chunk(Chunk&&) = delete;
   };

   struct Partition
   /// Chunks and metadata for one partition
   {
      Chunk* first = nullptr;
      Chunk* last = nullptr;
      void* current = nullptr;
      void* end = nullptr;
      void push_back(void* element, size_t size);
      size_t size(Chunk* chunk, size_t entrySize) const;

      Partition() = default;
      Partition(const Partition&) = delete;
      Partition(Partition&& o)
          : first(o.first), last(o.last), current(o.current), end(o.end) {
         o.first = nullptr;
         o.last = nullptr;
         o.current = nullptr;
         o.end = nullptr;
      };

    private:
      Chunk* newChunk(size_t entrySize);
   };

   PartitionedDeque(size_t nrPartitions_ = 0, size_t entrySize_ = 0);
   // required so that we are able to cope with the tbb interface for
   // enumerable_thread_specific
   void postConstruct(size_t nrPartitions_ = 0, size_t entrySize_ = 0);
   PartitionedDeque(const PartitionedDeque&) = delete;
   ~PartitionedDeque();

   void push_back(void* element, hash_t hash);

   const std::vector<Partition>& getPartitions();

   /// Size of one entry in bytes
   size_t entrySize;

 private:
   /// Mask to go from hash to partition number
   std::vector<Partition> partitions;
   uint8_t shift;
};

template <size_t chunkSize>
template <typename T>
T* PartitionedDeque<chunkSize>::PartitionedDeque::Chunk::data() {
   return reinterpret_cast<T*>(addBytes(this, sizeof(*this)));
}

template <size_t chunkSize>
PartitionedDeque<chunkSize>::PartitionedDeque(size_t nrPartitions_,
                                              size_t entrySize_)
    : entrySize(entrySize_) {
   if (nrPartitions_ == 0) {
      shift = 0;
      entrySize = 0;
      return;
   }
   assert(nrPartitions_ > 0);
   auto leadingZeros = __builtin_clzll(nrPartitions_);
   shift = leadingZeros;
   auto exp = 64 - leadingZeros;
   auto capacity = ((size_t)1) << exp;
   partitions.resize(capacity);
}

template <size_t chunkSize>
void PartitionedDeque<chunkSize>::postConstruct(size_t nrPartitions_,
                                                size_t entrySize_) {
   entrySize = entrySize_;
   assert(nrPartitions_ > 0);
   auto leadingZeros = __builtin_clzll(nrPartitions_);
   shift = leadingZeros - (64 - sizeof(hash_t) * 8);
   auto exp = 64 /* bultin clzll counts 64 */ - leadingZeros;
   auto capacity = ((size_t)1) << exp;
   partitions.resize(capacity);
}

template <size_t chunkSize> PartitionedDeque<chunkSize>::~PartitionedDeque() {
   // for (auto& partition : partitions)
   //    for (auto chunk = partition.first; chunk;) {
   //       auto nextChunk = chunk->next;
   //       std::free(chunk);
   //       chunk = nextChunk;
   //    }
}

template <size_t chunkSize>
void PartitionedDeque<chunkSize>::push_back(void* element, hash_t hash) {
   // use upper bits of hash
   partitions[hash >> shift].push_back(element, entrySize);
}

template <size_t chunkSize>
void PartitionedDeque<chunkSize>::Partition::push_back(void* element,
                                                       size_t entrySize) {
   if (!first) {
      auto created = newChunk(entrySize);
      first = created;
      last = created;
      current = created->template data<void>();
      end = addBytes(current, entrySize * chunkSize);
   }
   if (current == end) {
      auto created = newChunk(entrySize);
      last->next = created;
      last = created;
      current = created->template data<void>();
      end = addBytes(current, entrySize * chunkSize);
   }
   std::memcpy(current, element, entrySize);
   current = addBytes(current, entrySize);
}

template <size_t chunkSize>
size_t PartitionedDeque<chunkSize>::Partition::size(Chunk* chunk,
                                                    size_t entrySize) const {
#define AsChar(P) reinterpret_cast<char*>(P)
   if (chunk == last)
      return (AsChar(current) - chunk->template data<char>()) / entrySize;
   else
      return chunk->size;
#undef AsChar
}

template <size_t chunkSize>
typename PartitionedDeque<chunkSize>::Chunk*
PartitionedDeque<chunkSize>::Partition::newChunk(size_t entrySize) {

   auto alloc =
       this_worker->allocator.allocate(sizeof(Chunk) + chunkSize * entrySize);
   auto c = reinterpret_cast<Chunk*>(alloc);
   new (c) Chunk();
   return c;
}

template <size_t chunkSize>
const std::vector<typename PartitionedDeque<chunkSize>::Partition>&
PartitionedDeque<chunkSize>::getPartitions() {
   return partitions;
}
} // namespace runtime
