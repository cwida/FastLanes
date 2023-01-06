#include "tpch_expected.hpp"
#include "common/Compat.hpp"
#include <fstream>
#include <iostream>

struct Attribute {
   const char* ptr = nullptr;
   int64_t len;
};
static bool getattribute(std::string& line, Attribute& attr) {
   attr.ptr += attr.len + 1;
   auto pos = attr.ptr - line.data();
   auto separatorPos = line.find_first_of(",", pos);
   if (separatorPos == std::string::npos) separatorPos = line.size();
   attr.len = separatorPos - pos;
   return true;
}

/*
  select
  l_orderkey || ',' ||
  o_orderdate|| ',' ||
  o_shippriority|| ',' ||
  sum(l_extendedprice * (1 - l_discount))
  from
  customer,
  orders,
  lineitem
  where
  c_mktsegment = 'BUILDING'
  and c_custkey = o_custkey
  and l_orderkey = o_orderkey
  and o_orderdate < date '1995-03-15'
  and l_shipdate > date '1995-03-15'
  group by
  l_orderkey,
  o_orderdate,
  o_shippriority
  order by
  l_orderkey,
  o_orderdate,
  o_shippriority;
*/
map3_t& q3_expected() {
   static map3_t expected;
   if (!expected.size()) {
      std::ifstream input(compat::path(__FILE__) + "/q3_expected.csv");
      Attribute value;
      for (std::string line; std::getline(input, line);) {
         value.ptr = line.data();
         value.len = -1;
         getattribute(line, value);
         auto l_orderkey = types::Integer::castString(value.ptr, value.len);
         getattribute(line, value);
         auto o_orderdate = types::Date::castString(value.ptr, value.len);
         getattribute(line, value);
         auto o_shippriority = types::Integer::castString(value.ptr, value.len);
         getattribute(line, value);
         auto sum = types::Numeric<12, 4>::castString(value.ptr, value.len);
         expected.emplace(
             std::make_tuple(l_orderkey, o_orderdate, o_shippriority), sum);
      }
   }
   return expected;
}

/*
  select
  nation || ',' ||
  o_year || ',' ||
  sum(amount)
  from
  (
  select
  n_name as nation,
  extract(year from o_orderdate) as o_year,
  l_extendedprice * (1 - l_discount) - ps_supplycost * l_quantity as amount
  from
  part,
  supplier,
  lineitem,
  partsupp,
  orders,
  nation
  where
  s_suppkey = l_suppkey
  and ps_suppkey = l_suppkey
  and ps_partkey = l_partkey
  and p_partkey = l_partkey
  and o_orderkey = l_orderkey
  and s_nationkey = n_nationkey
  and p_name like '%green%'
  ) as profit
  group by
  nation,
  o_year
 */

map9_t& q9_expected() {
  static map9_t expected;
  if (!expected.size()) {
    std::ifstream input(compat::path(__FILE__) + "/q9_expected.csv");
    Attribute value;
    for (std::string line; std::getline(input, line);) {
       value.ptr = line.data();
       value.len = -1;
       getattribute(line, value);
       auto nation = types::Char<25>::castString(value.ptr, value.len);
       getattribute(line, value);
       auto o_year = types::Integer::castString(value.ptr, value.len);
       getattribute(line, value);
       auto sum = types::Numeric<12, 4>::castString(value.ptr, value.len);
       expected.emplace(std::make_tuple(nation, o_year), sum);
    }
  }
  return expected;
}

/*
  select
  c_name|| ',' ||
  c_custkey|| ',' ||
  o_orderkey|| ',' ||
  o_orderdate|| ',' ||
  o_totalprice|| ',' ||
  sum(l_quantity)
  from
  customer,
  orders,
  lineitem
  where
  o_orderkey in (
  select
  l_orderkey
  from
  lineitem
  group by
  l_orderkey having
  sum(l_quantity) > 300
  )
  and c_custkey = o_custkey
  and o_orderkey = l_orderkey
  group by
  c_name,
  c_custkey,
  o_orderkey,
  o_orderdate,
  o_totalprice
 */

map18_t& q18_expected() {
   static map18_t expected;
   if (!expected.size()) {
      std::ifstream input(compat::path(__FILE__) + "/q18_expected.csv");
      Attribute value;
      for (std::string line; std::getline(input, line);) {
         value.ptr = line.data();
         value.len = -1;
         getattribute(line, value);
         auto name = types::Char<25>::castString(value.ptr, value.len);
         getattribute(line, value);
         auto c_custkey = types::Integer::castString(value.ptr, value.len);
         getattribute(line, value);
         auto o_orderkey = types::Integer::castString(value.ptr, value.len);
         getattribute(line, value);
         auto o_orderdate = types::Date::castString(value.ptr, value.len);
         getattribute(line, value);
         auto o_totalprice =
             types::Numeric<12, 2>::castString(value.ptr, value.len);
         getattribute(line, value);
         auto sum = types::Numeric<12, 2>::castString(value.ptr, value.len);
         expected.emplace(std::make_tuple(name, c_custkey, o_orderkey,
                                          o_orderdate, o_totalprice),
                          sum);
      }
   }
   return expected;
}
