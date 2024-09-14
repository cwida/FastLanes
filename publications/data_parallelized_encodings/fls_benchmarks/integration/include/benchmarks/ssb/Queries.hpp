#pragma once

#include <memory>

#include "benchmarks/Config.hpp"
#include "common/runtime/Concurrency.hpp"
#include "common/runtime/Database.hpp"
#include "common/runtime/Types.hpp"
#include "vectorwise/Operators.hpp"
#include "vectorwise/Query.hpp"
#include "vectorwise/QueryBuilder.hpp"

namespace ssb {

struct Q11Builder : public vectorwise::QueryBuilder {
   enum {
      sel_year,
      sel_qty,
      sel_discount_low,
      sel_discount_high,
      join_result,
      result_project
   };
   struct Q11 {
      types::Integer year = types::Integer(1993);
      types::Numeric<18, 2> discount_min =
          types::Numeric<18, 2>::castString("1.00");
      types::Numeric<18, 2> discount_max =
          types::Numeric<18, 2>::castString("3.00");
      types::Integer quantity_max = types::Integer(25);
      int64_t aggregator = 0;
      std::unique_ptr<vectorwise::Operator> rootOp;
   };
   Q11Builder(runtime::Database& db, vectorwise::SharedStateManager& shared,
              size_t size = 1024)
       : QueryBuilder(db, shared, size) {}
   std::unique_ptr<Q11> getQuery();
};

std::unique_ptr<runtime::Query>
q11_hyper(runtime::Database& db,
          size_t nrThreads = std::thread::hardware_concurrency());
std::unique_ptr<runtime::Query>
q11_vectorwise(runtime::Database& db,
               size_t nrThreads = std::thread::hardware_concurrency(),
               size_t vectorSize = 1024);

struct Q12Builder : public vectorwise::QueryBuilder {
   enum {
      sel_year,
      sel_qty_high,
      sel_qty_low,
      sel_discount_low,
      sel_discount_high,
      join_result,
      result_project
   };
   struct Q12 {
      types::Integer yearmonthnum = types::Integer(199401);
      types::Numeric<18, 2> discount_min =
          types::Numeric<18, 2>::castString("4.00");
      types::Numeric<18, 2> discount_max =
          types::Numeric<18, 2>::castString("6.00");
      types::Integer quantity_max = types::Integer(35);
      types::Integer quantity_min = types::Integer(26);
      int64_t aggregator = 0;
      std::unique_ptr<vectorwise::Operator> rootOp;
   };
   Q12Builder(runtime::Database& db, vectorwise::SharedStateManager& shared,
              size_t size = 1024)
       : QueryBuilder(db, shared, size) {}
   std::unique_ptr<Q12> getQuery();
};

std::unique_ptr<runtime::Query>
q12_hyper(runtime::Database& db,
          size_t nrThreads = std::thread::hardware_concurrency());
std::unique_ptr<runtime::Query>
q12_vectorwise(runtime::Database& db,
               size_t nrThreads = std::thread::hardware_concurrency(),
               size_t vectorSize = 1024);

struct Q13Builder : public vectorwise::QueryBuilder {
   enum {
      sel_year,
      sel_week,
      sel_qty_high,
      sel_qty_low,
      sel_discount_low,
      sel_discount_high,
      join_result,
      result_project
   };
   struct Q13 {
      types::Integer year = types::Integer(1994);
      types::Integer weeknuminyear = types::Integer(6);
      types::Numeric<18, 2> discount_min =
          types::Numeric<18, 2>::castString("5.00");
      types::Numeric<18, 2> discount_max =
          types::Numeric<18, 2>::castString("7.00");
      types::Integer quantity_max = types::Integer(35);
      types::Integer quantity_min = types::Integer(26);
      int64_t aggregator = 0;
      std::unique_ptr<vectorwise::Operator> rootOp;
   };
   Q13Builder(runtime::Database& db, vectorwise::SharedStateManager& shared,
              size_t size = 1024)
       : QueryBuilder(db, shared, size) {}
   std::unique_ptr<Q13> getQuery();
};

std::unique_ptr<runtime::Query>
q13_hyper(runtime::Database& db,
          size_t nrThreads = std::thread::hardware_concurrency());
std::unique_ptr<runtime::Query>
q13_vectorwise(runtime::Database& db,
               size_t nrThreads = std::thread::hardware_concurrency(),
               size_t vectorSize = 1024);

struct Q21Builder : public vectorwise::QueryBuilder {
   enum {
      sel_part,
      sel_supplier,
      lineorder_part,
      lineorder_supplier,
      lineorder_supplier_line,
      lineorder_date_part,
      lineorder_date_part_grouped,
      lineorder_supplier_date,
      lineorder_date,
      p_brand1,
      sum_revenue,
      d_year
   };
   struct Q21 {
      types::Char<7> category = types::Char<7>::castString("MFGR#12");
      types::Char<12> region = types::Char<12>::castString("AMERICA");

      std::unique_ptr<vectorwise::Operator> rootOp;
   };
   Q21Builder(runtime::Database& db, vectorwise::SharedStateManager& shared,
              size_t size = 1024)
       : QueryBuilder(db, shared, size) {}
   std::unique_ptr<Q21> getQuery();
};

std::unique_ptr<runtime::Query>
q21_hyper(runtime::Database& db,
          size_t nrThreads = std::thread::hardware_concurrency());
std::unique_ptr<runtime::Query>
q21_vectorwise(runtime::Database& db,
               size_t nrThreads = std::thread::hardware_concurrency(),
               size_t vectorSize = 1024);

struct Q22Builder : public vectorwise::QueryBuilder {
   enum {
      sel_part_min,
      sel_part_max,
      sel_supplier,
      lineorder_part,
      lineorder_supplier,
      lineorder_supplier_line,
      lineorder_date_part,
      lineorder_date_part_grouped,
      lineorder_supplier_date,
      lineorder_date,
      p_brand1,
      sum_revenue,
      d_year
   };
   struct Q22 {
      types::Char<9> brand_min = types::Char<9>::castString("MFGR#2221");
      types::Char<9> brand_max = types::Char<9>::castString("MFGR#2228");
      types::Char<12> region = types::Char<12>::castString("ASIA");

      std::unique_ptr<vectorwise::Operator> rootOp;
   };
   Q22Builder(runtime::Database& db, vectorwise::SharedStateManager& shared,
              size_t size = 1024)
       : QueryBuilder(db, shared, size) {}
   std::unique_ptr<Q22> getQuery();
};

std::unique_ptr<runtime::Query>
q22_hyper(runtime::Database& db,
          size_t nrThreads = std::thread::hardware_concurrency());
std::unique_ptr<runtime::Query>
q22_vectorwise(runtime::Database& db,
               size_t nrThreads = std::thread::hardware_concurrency(),
               size_t vectorSize = 1024);

struct Q23Builder : public vectorwise::QueryBuilder {
   enum {
      sel_part,
      sel_supplier,
      lineorder_part,
      lineorder_supplier,
      lineorder_supplier_line,
      lineorder_date_part,
      lineorder_date_part_grouped,
      lineorder_supplier_date,
      lineorder_date,
      p_brand1,
      sum_revenue,
      d_year
   };
   struct Q23 {
      types::Char<9> brand = types::Char<9>::castString("MFGR#2221");
      types::Char<12> region = types::Char<12>::castString("EUROPE");

      std::unique_ptr<vectorwise::Operator> rootOp;
   };
   Q23Builder(runtime::Database& db, vectorwise::SharedStateManager& shared,
              size_t size = 1024)
       : QueryBuilder(db, shared, size) {}
   std::unique_ptr<Q23> getQuery();
};

std::unique_ptr<runtime::Query>
q23_hyper(runtime::Database& db,
          size_t nrThreads = std::thread::hardware_concurrency());
std::unique_ptr<runtime::Query>
q23_vectorwise(runtime::Database& db,
               size_t nrThreads = std::thread::hardware_concurrency(),
               size_t vectorSize = 1024);

struct Q31Builder : public vectorwise::QueryBuilder {
   enum {
      sel_customer,
      sel_supplier,
      sel_year_min,
      sel_year_max,
      lineorder_customer,
      lineorder_supplier,
      lineorder_supplier_line,
      lineorder_date_customer,
      lineorder_date_supplier_grouped,
      lineorder_date_part_grouped,
      lineorder_supplier_date,
      lineorder_supplier_date_grouped,
      lineorder_date,
      c_nation,
      s_nation,
      sum_revenue,
      d_year
   };
   struct Q31 {
      types::Char<12> region = types::Char<12>::castString("ASIA");
      types::Integer year_min = types::Integer(1992);
      types::Integer year_max = types::Integer(1997);
      std::unique_ptr<vectorwise::Operator> rootOp;
   };
   Q31Builder(runtime::Database& db, vectorwise::SharedStateManager& shared,
              size_t size = 1024)
       : QueryBuilder(db, shared, size) {}
   std::unique_ptr<Q31> getQuery();
};

std::unique_ptr<runtime::Query>
q31_hyper(runtime::Database& db,
          size_t nrThreads = std::thread::hardware_concurrency());
std::unique_ptr<runtime::Query>
q31_vectorwise(runtime::Database& db,
               size_t nrThreads = std::thread::hardware_concurrency(),
               size_t vectorSize = 1024);

struct Q32Builder : public vectorwise::QueryBuilder {
   enum {
      sel_customer,
      sel_supplier,
      sel_year_min,
      sel_year_max,
      lineorder_customer,
      lineorder_supplier,
      lineorder_supplier_line,
      lineorder_date_customer,
      lineorder_date_supplier_grouped,
      lineorder_date_part_grouped,
      lineorder_supplier_date,
      lineorder_supplier_date_grouped,
      lineorder_date,
      c_city,
      s_city,
      sum_revenue,
      d_year
   };
   struct Q32 {
      types::Char<15> nation = types::Char<15>::castString("UNITED STATES");
      types::Integer year_min = types::Integer(1992);
      types::Integer year_max = types::Integer(1997);
      std::unique_ptr<vectorwise::Operator> rootOp;
   };
   Q32Builder(runtime::Database& db, vectorwise::SharedStateManager& shared,
              size_t size = 1024)
       : QueryBuilder(db, shared, size) {}
   std::unique_ptr<Q32> getQuery();
};

std::unique_ptr<runtime::Query>
q32_hyper(runtime::Database& db,
          size_t nrThreads = std::thread::hardware_concurrency());
std::unique_ptr<runtime::Query>
q32_vectorwise(runtime::Database& db,
               size_t nrThreads = std::thread::hardware_concurrency(),
               size_t vectorSize = 1024);

struct Q33Builder : public vectorwise::QueryBuilder {
   enum {
      sel_customer,
      sel_supplier,
      sel_year_min,
      sel_year_max,
      lineorder_customer,
      lineorder_supplier,
      lineorder_supplier_line,
      lineorder_date_customer,
      lineorder_date_supplier_grouped,
      lineorder_date_part_grouped,
      lineorder_supplier_date,
      lineorder_supplier_date_grouped,
      lineorder_date,
      c_city,
      s_city,
      sum_revenue,
      d_year
   };
   struct Q33 {
      types::Char<10> city1 = types::Char<10>::castString("UNITED KI1");
      types::Char<10> city2 = types::Char<10>::castString("UNITED KI5");
      types::Integer year_min = types::Integer(1992);
      types::Integer year_max = types::Integer(1997);
      std::unique_ptr<vectorwise::Operator> rootOp;
   };
   Q33Builder(runtime::Database& db, vectorwise::SharedStateManager& shared,
              size_t size = 1024)
       : QueryBuilder(db, shared, size) {}
   std::unique_ptr<Q33> getQuery();
};

std::unique_ptr<runtime::Query>
q33_hyper(runtime::Database& db,
          size_t nrThreads = std::thread::hardware_concurrency());
std::unique_ptr<runtime::Query>
q33_vectorwise(runtime::Database& db,
               size_t nrThreads = std::thread::hardware_concurrency(),
               size_t vectorSize = 1024);

struct Q34Builder : public vectorwise::QueryBuilder {
   enum {
      sel_customer,
      sel_supplier,
      sel_year,
      lineorder_customer,
      lineorder_supplier,
      lineorder_supplier_line,
      lineorder_date_customer,
      lineorder_date_supplier_grouped,
      lineorder_date_part_grouped,
      lineorder_supplier_date,
      lineorder_supplier_date_grouped,
      lineorder_date,
      c_city,
      s_city,
      sum_revenue,
      d_year
   };
   struct Q34 {
      types::Char<10> city1 = types::Char<10>::castString("UNITED KI1");
      types::Char<10> city2 = types::Char<10>::castString("UNITED KI5");
      types::Char<7> yearmonth = types::Char<7>::castString("Dec1997");
      std::unique_ptr<vectorwise::Operator> rootOp;
   };
   Q34Builder(runtime::Database& db, vectorwise::SharedStateManager& shared,
              size_t size = 1024)
       : QueryBuilder(db, shared, size) {}
   std::unique_ptr<Q34> getQuery();
};

std::unique_ptr<runtime::Query>
q34_hyper(runtime::Database& db,
          size_t nrThreads = std::thread::hardware_concurrency());
std::unique_ptr<runtime::Query>
q34_vectorwise(runtime::Database& db,
               size_t nrThreads = std::thread::hardware_concurrency(),
               size_t vectorSize = 1024);

struct Q41Builder : public vectorwise::QueryBuilder {
   enum {
      sel_customer,
      sel_supplier,
      sel_year_min,
      sel_year_max,
      sel_part,
      lineorder_customer,
      lineorder_supplier,
      lineorder_supplier_line,
      lineorder_date_customer,
      lineorder_date_supplier_grouped,
      lineorder_date_part_grouped,
      lineorder_supplier_date,
      lineorder_supplier_date_grouped,
      lineorder_date,
      lineorder_part,
      lineorder_customer_part,
      lineorder_part_date,
      lineorder_part_date_grouped,
      lineorder_customer_part_date,
      result_proj_minus,
      lineorder_date_customer_grouped,
      c_nation,
      s_nation,
      profit,
      d_year
   };
   struct Q41 {
      types::Char<12> region = types::Char<12>::castString("AMERICA");
      types::Char<6> mfgr1 = types::Char<6>::castString("MFGR#1");
      types::Char<6> mfgr2 = types::Char<6>::castString("MFGR#2");
      std::unique_ptr<vectorwise::Operator> rootOp;
   };
   Q41Builder(runtime::Database& db, vectorwise::SharedStateManager& shared,
              size_t size = 1024)
       : QueryBuilder(db, shared, size) {}
   std::unique_ptr<Q41> getQuery();
};
std::unique_ptr<runtime::Query>
q41_hyper(runtime::Database& db,
          size_t nrThreads = std::thread::hardware_concurrency());
std::unique_ptr<runtime::Query>
q41_vectorwise(runtime::Database& db,
               size_t nrThreads = std::thread::hardware_concurrency(),
               size_t vectorSize = 1024);

struct Q42Builder : public vectorwise::QueryBuilder {
   enum {
      sel_customer,
      sel_supplier,
      sel_year_min,
      sel_year_max,
      sel_part,
      sel_date,
      lineorder_customer,
      lineorder_supplier,
      lineorder_supplier_customer,
      lineorder_customer_part2,
      lineorder_customer_part2_date,
      lineorder_supplier_line,
      lineorder_date_grouped,
      lineorder_date_customer,
      lineorder_date_supplier_grouped,
      lineorder_date_part_grouped,
      lineorder_supplier_date,
      lineorder_supplier_date_grouped,
      lineorder_date,
      lineorder_part,
      lineorder_customer_part,
      lineorder_part_date,
      lineorder_part_date_grouped,
      lineorder_customer_part_date,
      result_proj_minus,
      lineorder_date_customer_grouped,
      c_nation,
      s_nation,
      profit,
      d_year,
      p_category
   };
   struct Q42 {
      types::Char<12> region = types::Char<12>::castString("AMERICA");
      types::Char<6> mfgr1 = types::Char<6>::castString("MFGR#1");
      types::Char<6> mfgr2 = types::Char<6>::castString("MFGR#2");
      types::Integer year1 = types::Integer(1997);
      types::Integer year2 = types::Integer(1998);
      std::unique_ptr<vectorwise::Operator> rootOp;
   };
   Q42Builder(runtime::Database& db, vectorwise::SharedStateManager& shared,
              size_t size = 1024)
       : QueryBuilder(db, shared, size) {}
   std::unique_ptr<Q42> getQuery();
};
std::unique_ptr<runtime::Query>
q42_hyper(runtime::Database& db,
          size_t nrThreads = std::thread::hardware_concurrency());
std::unique_ptr<runtime::Query>
q42_vectorwise(runtime::Database& db,
               size_t nrThreads = std::thread::hardware_concurrency(),
               size_t vectorSize = 1024);

struct Q43Builder : public vectorwise::QueryBuilder {
   enum {
      sel_customer,
      sel_supplier,
      sel_year_min,
      sel_year_max,
      sel_part,
      sel_date,
      lineorder_customer,
      lineorder_supplier,
      lineorder_supplier_customer,
      lineorder_customer_part2,
      lineorder_customer_part2_date,
      lineorder_supplier_line,
      lineorder_date_grouped,
      lineorder_date_customer,
      lineorder_date_supplier_grouped,
      lineorder_date_part_grouped,
      lineorder_supplier_date,
      lineorder_supplier_date_grouped,
      lineorder_date,
      lineorder_part,
      lineorder_customer_part,
      lineorder_part_date,
      lineorder_part_date_grouped,
      lineorder_customer_part_date,
      result_proj_minus,
      lineorder_date_customer_grouped,
      c_nation,
      s_nation,
      profit,
      d_year,
      p_category,
      s_city,
      p_brand1,
   };
   struct Q43 {
      types::Char<12> region = types::Char<12>::castString("AMERICA");
      types::Char<15> nation = types::Char<15>::castString("UNITED STATES");
      types::Char<7> category = types::Char<7>::castString("MFGR#14");
      types::Integer year1 = types::Integer(1997);
      types::Integer year2 = types::Integer(1998);
      std::unique_ptr<vectorwise::Operator> rootOp;
   };
   Q43Builder(runtime::Database& db, vectorwise::SharedStateManager& shared,
              size_t size = 1024)
       : QueryBuilder(db, shared, size) {}
   std::unique_ptr<Q43> getQuery();
};
std::unique_ptr<runtime::Query>
q43_hyper(runtime::Database& db,
          size_t nrThreads = std::thread::hardware_concurrency());
std::unique_ptr<runtime::Query>
q43_vectorwise(runtime::Database& db,
               size_t nrThreads = std::thread::hardware_concurrency(),
               size_t vectorSize = 1024);
} // namespace ssb
