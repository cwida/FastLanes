#include "common/runtime/Types.hpp"
#include <map>
#include <tuple>

using map21_t =
    std::map<std::tuple<types::Integer, types::Char<9>>, types::Numeric<18, 2>>;
map21_t& q21_expected();
map21_t& q22_expected();
map21_t& q23_expected();

using map31_t =
    std::map<std::tuple<types::Char<15>, types::Char<15>, types::Integer>,
             types::Numeric<18, 2>>;
using map32_t =
  std::map<std::tuple<types::Char<10>, types::Char<10>, types::Integer>,
           types::Numeric<18, 2>>;
map31_t& q31_expected();
map32_t& q32_expected();
map32_t& q33_expected();
map32_t& q34_expected();

using map41_t =
  std::map<std::tuple<types::Integer, types::Char<15>>,
           types::Numeric<18, 2>>;
using map42_t =
  std::map<std::tuple<types::Integer, types::Char<15>, types::Char<7>>,
           types::Numeric<18, 2>>;
using map43_t =
  std::map<std::tuple<types::Integer, types::Char<10>, types::Char<9>>,
           types::Numeric<18, 2>>;
map41_t& q41_expected();
map42_t& q42_expected();
map43_t& q43_expected();
