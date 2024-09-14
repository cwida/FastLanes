#include "vectorwise/Operations.hpp"
#include "vectorwise/Primitives.hpp"
#include <functional>

using namespace types;
using namespace std;

namespace vectorwise {
namespace primitives {

#define MK_KEYS_EQUAL(type)                                                    \
   EQCheck keys_equal_##type##_col = (EQCheck)&keys_equal<type, equal_to>;
#define MK_KEYS_NOT_EQUAL(type)                                                \
   NEQCheck keys_not_equal_##type##_col = (NEQCheck)&keys_not_equal<type>;
#define MK_KEYS_NOT_EQUAL_SEL(type)                                            \
   NEQCheckSel keys_not_equal_sel_##type##_col =                               \
       (NEQCheckSel)&keys_not_equal_sel<type>;
#define MK_KEYS_NOT_EQUAL_ROW(type)                                            \
   NEQCheckRow keys_not_equal_row_##type##_col =                               \
       (NEQCheckRow)&keys_not_equal_row<type>;

EACH_TYPE(NIL, MK_KEYS_EQUAL)
EACH_TYPE(NIL, MK_KEYS_NOT_EQUAL)
EACH_TYPE(NIL, MK_KEYS_NOT_EQUAL_SEL)
EACH_TYPE(NIL, MK_KEYS_NOT_EQUAL_ROW)
}
}
