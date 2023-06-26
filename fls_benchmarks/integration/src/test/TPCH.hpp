#pragma once
#include "gtest/gtest.h"
#include "common/runtime/Import.hpp"

class TPCH : public ::testing::Test {
 public:
   static runtime::Database& getDB() {
      static runtime::Database tpch;
      if (!tpch.hasRelation("lineitem")) {
         importTPCH(std::string(DATADIR) + "/tpch/sf1/", tpch);
      }
      return tpch;
   }
};
