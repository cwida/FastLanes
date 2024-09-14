#include "common/runtime/Hashmap.hpp"
#include <assert.h>
#include <iostream>

namespace runtime {

Hashmap::EntryHeader notFound(&notFound, 0);
}
