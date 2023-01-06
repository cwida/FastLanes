#pragma once
#include "Database.hpp"
#include <string>

namespace runtime {
   /// imports tpch relations from CSVs in dir into db
   void importTPCH(std::string dir, Database& db);

   /// imports star schema benchmark from CSVs in dir into db
   void importSSB(std::string dir, Database& db);

   /// imports fls benchmark from CSVs in dir into db
   void importFLS(std::string dir, Database& db);
}
