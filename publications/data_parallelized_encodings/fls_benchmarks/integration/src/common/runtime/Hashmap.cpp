// ────────────────────────────────────────────────────────
// |                      FastLanes                       |
// ────────────────────────────────────────────────────────
// publications/data_parallelized_encodings/fls_benchmarks/integration/src/common/runtime/Hashmap.cpp
// ────────────────────────────────────────────────────────
#include "common/runtime/Hashmap.hpp"
#include <assert.h>
#include <iostream>

namespace runtime {

Hashmap::EntryHeader notFound(&notFound, 0);
}
