#pragma once
#include "common/runtime/MemoryPool.hpp"
#include <memory>

namespace runtime {

class Query {
 public:
   GlobalPool pool;
   std::unique_ptr<BlockRelation> result;
   Query() { result = std::make_unique<BlockRelation>(); }
   GlobalPool* participate() { return this_worker->allocator.setSource(&pool); }
   void leave(GlobalPool* prev) { this_worker->allocator.setSource(prev); }
};

} // namespace runtime
