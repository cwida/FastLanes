
#include "common/runtime/Hash.hpp"
#include "vectorwise/Operations.hpp"
#include "vectorwise/Primitives.hpp"
#include <functional>

using namespace types;
using namespace std;

namespace vectorwise {
namespace primitives {

#define MK_PARTITION(type)                                                     \
   FPartitionByKey partition_by_key_##type##_col =                             \
       (FPartitionByKey)&partition_by_key<type>;
#define MK_PARTITION_SEL(type)                                                 \
   FPartitionByKeySel partition_by_key_sel_##type##_col =                      \
       (FPartitionByKeySel)&partition_by_key_sel<type>;
#define MK_PARTITION_ROW(type)                                                 \
   FPartitionByKeyRow partition_by_key_row_##type##_col =                      \
       (FPartitionByKeyRow)&partition_by_key_row<type>;

EACH_TYPE(NIL, MK_PARTITION)
EACH_TYPE(NIL, MK_PARTITION_SEL)
EACH_TYPE(NIL, MK_PARTITION_ROW)
}
}
