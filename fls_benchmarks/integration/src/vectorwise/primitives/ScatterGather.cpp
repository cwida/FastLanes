
#include "common/runtime/Hash.hpp"
#include "vectorwise/Operations.hpp"
#include "vectorwise/Primitives.hpp"
#include <functional>

using namespace types;
using namespace std;

namespace vectorwise {
namespace primitives {

#define MK_SCATTER(type)                                                       \
   FScatter scatter_##type##_col = (FScatter)&scatter<type>;
#define MK_SCATTER_SEL(type)                                                   \
   FScatterSel scatter_sel_##type##_col = (FScatterSel)&scatter_sel<type>;
#define MK_SCATTER_SEL_ROW(type)                                               \
   FScatterSelRow scatter_sel_row_##type##_col =                               \
       (FScatterSelRow)&scatter_sel_row<type>;

#define MK_GATHER_COL(type)                                                    \
   FGather gather_col_##type##_col = (FGather)&gather_col<type>;
#define MK_GATHER_SEL_COL(type)                                                \
   FGatherSel gather_sel_col_##type##_col = (FGatherSel)&gather_sel_col<type>;
#define MK_GATHER_VAL(type)                                                    \
   FGatherVal gather_val_##type##_col = (FGatherVal)&gather_val<type>;

EACH_TYPE(NIL, MK_SCATTER)
EACH_TYPE(NIL, MK_SCATTER_SEL)
EACH_TYPE(NIL, MK_SCATTER_SEL_ROW)

EACH_TYPE(NIL, MK_GATHER_COL)
EACH_TYPE(NIL, MK_GATHER_SEL_COL)
EACH_TYPE(NIL, MK_GATHER_VAL)
}
}
