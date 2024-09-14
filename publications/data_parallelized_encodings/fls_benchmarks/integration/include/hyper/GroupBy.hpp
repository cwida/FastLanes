#include "common/runtime/Hashmap.hpp"
#include "common/runtime/Stack.hpp"
#include "tbb/tbb.h"

template <typename K, typename V, typename HASH, typename UPDATE>
class GroupBy {
   /// Hashmap for grouping
   tbb::enumerable_thread_specific<runtime::Hashmapx<K, V, HASH, false>> groups;

 public:
   /// type of entry struct in hashmap
   using group_t = typename decltype(groups)::value_type::Entry;

 private:
   /// Memory for materialized entries in hashmap
   tbb::enumerable_thread_specific<runtime::Stack<group_t>> entries;
   /// Memory for spilling hastable entries
   tbb::enumerable_thread_specific<runtime::PartitionedDeque<1024>>
       partitionedDeques;

   UPDATE update;
   V init;

   size_t nrThreads;

 public:
   GroupBy(UPDATE u, V i, size_t nrThreads_)
       : update(u), init(i), nrThreads(nrThreads_) {}

   GroupBy(const GroupBy& g) = delete;
   GroupBy(GroupBy&& g) = default;
   GroupBy& operator=(GroupBy&& g) = default;

   /// Class which manages thread local state in pre-aggregation phase
   class Locals {
      GroupBy& parent;

      runtime::Hashmapx<K, V, HASH, false>& groups;
      runtime::Stack<group_t>& entries;
      runtime::PartitionedDeque<1024>& spillStorage;
      size_t maxFill;

      void spill() {
         for (auto block : entries)
            for (auto& entry : block)
               spillStorage.push_back(&entry, entry.h.hash);
      }

    public:
      Locals(GroupBy& p, runtime::Hashmapx<K, V, HASH, false>& g,
             runtime::Stack<group_t>& e, runtime::PartitionedDeque<1024>& s,
             size_t m)
          : parent(p), groups(g), entries(e), spillStorage(s), maxFill(m) {}

      /// consume key and value
      template <typename KEY, typename VALUE>
      inline void consume(KEY&& key, VALUE&& value) {
         auto group = groups.findOrCreate(key, groups.hash(key), parent.init,
                                          entries, [&]() {
                                             if (groups.size() >= maxFill) {
                                                spill();
                                                groups.clear();
                                                entries.clear();
                                             }
                                          });
         parent.update(*group, std::forward<VALUE>(value));
      }

      template <typename KEY, typename VALUECB>
      inline void consume_callback(KEY&& key, VALUECB cb) {
         auto group = groups.findOrCreate(key, groups.hash(key), parent.init,
                                          entries, [&]() {
                                             if (groups.size() >= maxFill) {
                                                spill();
                                                groups.clear();
                                                entries.clear();
                                             }
                                          });
         cb(*group);
      }

     template<typename KEY>
      inline V& getGroup(KEY&& key) {
       return *groups.findOrCreate(std::forward<KEY>(key), groups.hash(std::forward<KEY>(key)), parent.init,
                                     entries, [&]() {
                                        if (groups.size() >= maxFill) {
                                           spill();
                                           groups.clear();
                                           entries.clear();
                                        }
                                     });
      }
   };

   /// Create thread local state for preaggregation
   Locals preAggLocals() {

      bool exists = false;
      auto& g = groups.local(exists);
      size_t maxFill;
      if (!exists)
         maxFill = g.setSize(1024);
      else
         maxFill = g.capacity * 0.7;
      auto& e = entries.local();

      auto& spillStorage = partitionedDeques.local(exists);
      if (!exists) spillStorage.postConstruct(nrThreads * 4, sizeof(group_t));

      return Locals(*this, g, e, spillStorage, maxFill);
   }
   /// Spill all
   void spillAll() {
      tbb::parallel_for(entries.range(), [&](const auto& e) {

         bool exists;
         auto& deque = partitionedDeques.local(exists);
         if (!exists) deque.postConstruct(nrThreads * 4, sizeof(group_t));
         for (auto& entries : e)
            for (auto block : entries)
               for (auto& entry : block) deque.push_back(&entry, entry.h.hash);
      });
   }

   /// Grow hashtable
   size_t grow(runtime::Hashmapx<K, V, HASH, false>& ht,
               runtime::Stack<group_t>& entries) {
      auto newCapacity = ht.setSize(ht.size() * 2);
      ht.template insertAll<false>(entries);
      return newCapacity;
   }

   /// Iterate over all groups of tuples consumed by Locals::consume
   template <typename C> inline void forallGroups(C consume) {

      spillAll();

      // aggregate from spill partitions
      auto nrPartitions = partitionedDeques.begin()->getPartitions().size();

      tbb::parallel_for(0ul, nrPartitions, [&](auto partitionNr) {
         bool exists = false;
         auto& ht = groups.local(exists);
         size_t maxFill;
         if (!exists)
            maxFill = ht.setSize(1024);
         else
            maxFill = ht.capacity * 0.7;
         auto& localEntries = entries.local();
         ht.clear();
         localEntries.clear();
         // aggregate values from all deques for partitionNr
         for (auto& deque : partitionedDeques) {
            auto& partition = deque.getPartitions()[partitionNr];
            for (auto chunk = partition.first; chunk; chunk = chunk->next) {
               for (auto value = chunk->template data<group_t>(),
                         end = value + partition.size(chunk, sizeof(group_t));
                    value < end; value++) {
                  auto group = ht.findOrCreate(
                      value->k, value->h.hash, init, localEntries, [&]() {
                         if (ht.size() >= maxFill) {
                            maxFill = this->grow(ht, localEntries);
                         }
                      });
                  update(*group, value->v);
               }
            }
         }

         // push aggregated groups into following pipeline
         if (!localEntries.empty()) consume(localEntries);
      });
   }
};

template <typename K, typename V, typename HASH, typename UPDATE>
GroupBy<K, V, HASH, UPDATE> make_GroupBy(UPDATE u, V i,
                                               size_t nrThreads) {
   return std::move(GroupBy<K, V, HASH, UPDATE>(u, i, nrThreads));
}
