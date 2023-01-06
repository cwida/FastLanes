#include "common/runtime/Hash.hpp"
#include "vectorwise/Operations.hpp"
#include "vectorwise/Primitives.hpp"
#include <functional>

using namespace types;
using namespace std;

namespace vectorwise {
namespace primitives {

#define MK_AGGR_STATIC_COL(type, op)                                           \
   F2 aggr_static_##op##_##type##_col = (F2)&aggr_static_col<type, op>;

#define MK_AGGR_STATIC_SEL_COL(type, op)                                       \
   F3 aggr_static_sel_##op##_##type##_col = (F3)&aggr_static_sel_col<type, op>;
#define MK_AGGR_COL(type, op)                                                  \
   FAggr aggr_##op##_##type##_col = (FAggr)&aggr_col<type, op>;
#define MK_AGGR_SEL_COL(type, op)                                              \
   FAggrSel aggr_sel_##op##_##type##_col = (FAggrSel)&aggr_sel_col<type, op>;
#define MK_AGGR_ROW(type, op)                                                  \
   FAggrRow aggr_row_##op##_##type##_col = (FAggrRow)&aggr_row<type, op>;
#define MK_AGGR_INIT(type, op)                                                 \
   FAggrInit aggr_init_##op##_##type##_col = (FAggrInit)&aggr_init<type, op>;

pos_t aggr_static_count_star_(pos_t n, int64_t* RES result)
/// aggregate column
{
   *result += n;
   return n > 0;
}
F1 aggr_static_count_star = (F1)&aggr_static_count_star_;

pos_t aggr_count_star_(pos_t n, int64_t* RES entries[], void* RES /*param1*/,
                       size_t offset)
/// update count aggregates for each entry pointed to by entries
{
   for (uint64_t i = 0; i < n; ++i) {
      auto aggregate = addBytes(entries[i], offset);
      *aggregate += 1;
   }
   return n;
}
FAggr aggr_count_star = (FAggr)&aggr_count_star_;

EACH_ARITH(EACH_TYPE_FULL, MK_AGGR_STATIC_COL)
EACH_ARITH(EACH_TYPE_FULL, MK_AGGR_STATIC_SEL_COL)
EACH_ARITH(EACH_TYPE_FULL, MK_AGGR_COL)
EACH_ARITH(EACH_TYPE_FULL, MK_AGGR_SEL_COL)
EACH_ARITH(EACH_TYPE_FULL, MK_AGGR_ROW)
EACH_ARITH(EACH_TYPE_FULL, MK_AGGR_INIT)
}
}
