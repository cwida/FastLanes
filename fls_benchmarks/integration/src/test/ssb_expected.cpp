#include "ssb_expected.hpp"
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

static void q2_expected(std::string file, map21_t& expected) {
  if (!expected.size()) {
    std::ifstream input(compat::path(__FILE__) + "/" + file);
    Attribute value;
    for (std::string line; std::getline(input, line);) {
      value.ptr = line.data();
      value.len = -1;
      getattribute(line, value);
      auto d_year = types::Integer::castString(value.ptr, value.len);
      getattribute(line, value);
      auto p_brand1 = types::Char<9>::castString(value.ptr, value.len);
      getattribute(line, value);
      auto sum = types::Numeric<18, 2>::castString(value.ptr, value.len);
      expected.emplace(std::make_tuple(d_year, p_brand1), sum);
    }
  }
}

/*
  select
  d_year || ',' ||
  p_brand1|| ',' ||
  sum(lo_revenue)
  from lineorder, "date", part, supplier
  where lo_orderdate = d_datekey
  and lo_partkey = p_partkey
  and lo_suppkey = s_suppkey
  and p_category = 'MFGR#12'
  and s_region = 'AMERICA'
  group by d_year, p_brand1
*/
map21_t& q21_expected() {
  static map21_t expected;
  q2_expected("q21_ssb_expected.csv", expected);
  return expected;
}
map21_t& q22_expected() {
  static map21_t expected;
  q2_expected("q22_ssb_expected.csv", expected);
  return expected;
}
map21_t& q23_expected() {
  static map21_t expected;
  q2_expected("q23_ssb_expected.csv", expected);
  return expected;
}

static void q3_expected(std::string file, map31_t& expected) {
  if (!expected.size()) {
    std::ifstream input(compat::path(__FILE__) + "/" + file);
    Attribute value;
    for (std::string line; std::getline(input, line);) {
      value.ptr = line.data();
      value.len = -1;
      getattribute(line, value);
      auto c_nation = types::Char<15>::castString(value.ptr, value.len);
      getattribute(line, value);
      auto s_nation = types::Char<15>::castString(value.ptr, value.len);
      getattribute(line, value);
      auto d_year = types::Integer::castString(value.ptr, value.len);
      getattribute(line, value);
      auto sum = types::Numeric<18, 2>::castString(value.ptr, value.len);
      expected.emplace(std::make_tuple(c_nation, s_nation, d_year), sum);
    }
  }
}

static void q32_expected(std::string file, map32_t& expected) {
  if (!expected.size()) {
    std::ifstream input(compat::path(__FILE__) + "/" + file);
    Attribute value;
    for (std::string line; std::getline(input, line);) {
      value.ptr = line.data();
      value.len = -1;
      getattribute(line, value);
      auto c_city = types::Char<10>::castString(value.ptr, value.len);
      getattribute(line, value);
      auto s_city = types::Char<10>::castString(value.ptr, value.len);
      getattribute(line, value);
      auto d_year = types::Integer::castString(value.ptr, value.len);
      getattribute(line, value);
      auto sum = types::Numeric<18, 2>::castString(value.ptr, value.len);
      expected.emplace(std::make_tuple(c_city, s_city, d_year), sum);
    }
  }
}
map31_t& q31_expected() {
  static map31_t expected;
  q3_expected("q31_ssb_expected.csv", expected);
  return expected;
}
map32_t& q32_expected() {
  static map32_t expected;
  q32_expected("q32_ssb_expected.csv", expected);
  return expected;
}
map32_t& q33_expected() {
  static map32_t expected;
  q32_expected("q33_ssb_expected.csv", expected);
  return expected;
}
map32_t& q34_expected() {
  static map32_t expected;
  q32_expected("q34_ssb_expected.csv", expected);
  return expected;
}

map41_t& q41_expected() {
  static map41_t expected;
  if (!expected.size()) {
    std::ifstream input(compat::path(__FILE__) + "/q41_ssb_expected.csv");
    Attribute value;
    for (std::string line; std::getline(input, line);) {
      value.ptr = line.data();
      value.len = -1;
      getattribute(line, value);
      auto d_year = types::Integer::castString(value.ptr, value.len);
      getattribute(line, value);
      auto c_nation = types::Char<15>::castString(value.ptr, value.len);
      getattribute(line, value);
      auto profit = types::Numeric<18, 2>::castString(value.ptr, value.len);
      expected.emplace(std::make_tuple(d_year, c_nation), profit);
    }
  }
  return expected;
}
map42_t& q42_expected() {
  static map42_t expected;
  if (!expected.size()) {
    std::ifstream input(compat::path(__FILE__) + "/q42_ssb_expected.csv");
    Attribute value;
    for (std::string line; std::getline(input, line);) {
      value.ptr = line.data();
      value.len = -1;
      getattribute(line, value);
      auto d_year = types::Integer::castString(value.ptr, value.len);
      getattribute(line, value);
      auto s_nation = types::Char<15>::castString(value.ptr, value.len);
      getattribute(line, value);
      auto p_category = types::Char<7>::castString(value.ptr, value.len);
      getattribute(line, value);
      auto profit = types::Numeric<18, 2>::castString(value.ptr, value.len);
      expected.emplace(std::make_tuple(d_year, s_nation, p_category), profit);
    }
  }
  return expected;
}
map43_t& q43_expected() {
  static map43_t expected;
  if (!expected.size()) {
    std::ifstream input(compat::path(__FILE__) + "/q43_ssb_expected.csv");
    Attribute value;
    for (std::string line; std::getline(input, line);) {
      value.ptr = line.data();
      value.len = -1;
      getattribute(line, value);
      auto d_year = types::Integer::castString(value.ptr, value.len);
      getattribute(line, value);
      auto s_city = types::Char<10>::castString(value.ptr, value.len);
      getattribute(line, value);
      auto p_brand1 = types::Char<9>::castString(value.ptr, value.len);
      getattribute(line, value);
      auto profit = types::Numeric<18, 2>::castString(value.ptr, value.len);
      expected.emplace(std::make_tuple(d_year, s_city, p_brand1), profit);
    }
  }
  return expected;
}
