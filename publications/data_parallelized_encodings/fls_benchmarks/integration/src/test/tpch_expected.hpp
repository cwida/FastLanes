#include "common/runtime/Types.hpp"
#include <map>
#include <tuple>

using map3_t = std::map<std::tuple<types::Integer, types::Date, types::Integer>,
                        types::Numeric<12, 4>>;
map3_t& q3_expected();

using map9_t = std::map<std::tuple<types::Char<25>, types::Integer>,
                        types::Numeric<12, 4>>;
map9_t& q9_expected();

using map18_t =
    std::map<std::tuple<types::Char<25>, types::Integer, types::Integer,
                        types::Date, types::Numeric<12, 2>>,
             types::Numeric<12, 2>>;
map18_t& q18_expected();
