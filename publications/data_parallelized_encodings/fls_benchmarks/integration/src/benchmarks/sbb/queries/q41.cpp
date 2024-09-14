#include <deque>
#include <iostream>

#include "benchmarks/ssb/Queries.hpp"
#include "common/runtime/Hash.hpp"
#include "common/runtime/Types.hpp"
#include "hyper/GroupBy.hpp"
#include "hyper/ParallelHelper.hpp"
#include "tbb/tbb.h"
#include "vectorwise/Operations.hpp"
#include "vectorwise/Operators.hpp"
#include "vectorwise/Primitives.hpp"
#include "vectorwise/QueryBuilder.hpp"
#include "vectorwise/VectorAllocator.hpp"

using namespace runtime;
using namespace std;

namespace ssb {

// select d_year, c_nation, sum(lo_revenue - lo_supplycost) as profit
// from "date", customer, supplier, part, lineorder
// where lo_custkey = c_custkey
// and lo_suppkey = s_suppkey
// and lo_partkey = p_partkey
// and lo_orderdate = d_datekey
// and c_region = 'AMERICA'
// and s_region = 'AMERICA'
// and (p_mfgr = 'MFGR#1' or p_mfgr = 'MFGR#2')
// group by d_year, c_nation

//                      groupby
//
//                       join
//                       hash
//
// tablescan                  join
// date                       hash
//
//           tablescan             join
//           part                  hash
//
//                     tablescan        join
//                     customer         hash
//
//                               tablescan tablescan
//                               supplier  lineorder

NOVECTORIZE std::unique_ptr<runtime::Query> q41_hyper(Database& db,
                                                      size_t nrThreads) {
   // --- aggregates
   auto resources = initQuery(nrThreads);

   // --- constants
   auto relevant_region = types::Char<12>::castString("AMERICA");
   auto mfgr1 = types::Char<6>::castString("MFGR#1");
   auto mfgr2 = types::Char<6>::castString("MFGR#2");

   using hash = runtime::CRC32Hash;
   const size_t morselSize = 100000;

   // --- ht for join date-lineorder
   Hashmapx<types::Integer, types::Integer, hash> ht1;
   tbb::enumerable_thread_specific<runtime::Stack<decltype(ht1)::Entry>>
       entries1;
   auto& d = db["date"];
   auto d_year = d["d_year"].data<types::Integer>();
   auto d_datekey = d["d_datekey"].data<types::Integer>();
   auto found1 = PARALLEL_SELECT(d.tup_c, entries1, {
      auto& year = d_year[i];
      auto& datekey = d_datekey[i];
      entries.emplace_back(ht1.hash(datekey), datekey, year);
      found++;
   });
   ht1.setSize(found1);
   parallel_insert(entries1, ht1);

   // --- ht for join part-lineorder
   Hashset<types::Integer, hash> ht2;
   tbb::enumerable_thread_specific<runtime::Stack<decltype(ht2)::Entry>>
       entries2;
   auto& p = db["part"];
   auto p_partkey = p["p_partkey"].data<types::Integer>();
   auto p_mfgr = p["p_mfgr"].data<types::Char<6>>();
   auto found2 = PARALLEL_SELECT(p.tup_c, entries2, {
      auto& partkey = p_partkey[i];
      auto& mfgr = p_mfgr[i];
      if (mfgr == mfgr1 || mfgr == mfgr2) {
         entries.emplace_back(ht2.hash(partkey), partkey);
         found++;
      }
   });
   ht2.setSize(found2);
   parallel_insert(entries2, ht2);

   // --- ht for join customer-lineorder
   Hashmapx<types::Integer, types::Char<15>, hash> ht3;
   tbb::enumerable_thread_specific<runtime::Stack<decltype(ht3)::Entry>>
       entries3;
   auto& c = db["customer"];
   auto c_custkey = c["c_custkey"].data<types::Integer>();
   auto c_nation = c["c_nation"].data<types::Char<15>>();
   auto c_region = c["c_region"].data<types::Char<12>>();
   auto found3 = PARALLEL_SELECT(c.tup_c, entries3, {
      auto& custkey = c_custkey[i];
      auto& nation = c_nation[i];
      auto& region = c_region[i];
      if (region == relevant_region) {
         entries.emplace_back(ht3.hash(custkey), custkey, nation);
         found++;
      }
   });
   ht3.setSize(found3);
   parallel_insert(entries3, ht3);

   // --- ht for join supplier-lineorder
   Hashset<types::Integer, hash> ht4;
   tbb::enumerable_thread_specific<runtime::Stack<decltype(ht4)::Entry>>
       entries4;
   auto& su = db["supplier"];
   auto s_suppkey = su["s_suppkey"].data<types::Integer>();
   auto s_region = su["s_region"].data<types::Char<12>>();
   auto found4 = PARALLEL_SELECT(su.tup_c, entries4, {
      auto& suppkey = s_suppkey[i];
      auto& region = s_region[i];
      if (region == relevant_region) {
         entries.emplace_back(ht4.hash(suppkey), suppkey);
         found++;
      }
   });
   ht4.setSize(found4);
   parallel_insert(entries4, ht4);

   // --- scan and join lineorder
   auto& lo = db["lineorder"];
   auto lo_orderdate = lo["lo_orderdate"].data<types::Integer>();
   auto lo_custkey = lo["lo_custkey"].data<types::Integer>();
   auto lo_suppkey = lo["lo_suppkey"].data<types::Integer>();
   auto lo_partkey = lo["lo_partkey"].data<types::Integer>();
   auto lo_revenue = lo["lo_revenue"].data<types::Numeric<18, 2>>();
   auto lo_supplycost = lo["lo_supplycost"].data<types::Numeric<18, 2>>();

   const auto zero = types::Numeric<18, 2>::castString("0.00");
   auto groupOp = make_GroupBy<tuple<types::Integer, types::Char<15>>,
                               types::Numeric<18, 2>, hash>(
       [](auto& acc, auto&& value) { acc += value; }, zero, nrThreads);

   // preaggregation
   tbb::parallel_for(
       tbb::blocked_range<size_t>(0, lo.tup_c, morselSize),
       [&](const tbb::blocked_range<size_t>& r) {
          auto groupLocals = groupOp.preAggLocals();
          for (size_t i = r.begin(), end = r.end(); i != end; ++i) {
             auto& revenue = lo_revenue[i];
             auto& supplycost = lo_supplycost[i];
             auto& suppkey = lo_suppkey[i];
             auto& partkey = lo_partkey[i];
             auto& custkey = lo_custkey[i];
             auto& orderdate = lo_orderdate[i];

             if (ht4.contains(suppkey)) {
                auto customer = ht3.findOne(custkey);
                if (customer) {
                   if (ht2.contains(partkey)) {
                      auto date = ht1.findOne(orderdate);
                      if (date) {
                         // --- aggregation
                         groupLocals.consume(make_tuple(*date, *customer),
                                             revenue - supplycost);
                      }
                   }
                }
             }
          }
       });
   // --- output
   auto& result = resources.query->result;
   auto revenueAttr =
       result->addAttribute("profit", sizeof(types::Numeric<18, 2>));
   auto yearAttr = result->addAttribute("d_year", sizeof(types::Integer));
   auto customerNationAttr =
       result->addAttribute("c_nation", sizeof(types::Char<15>));

   groupOp.forallGroups([&](auto& groups) {
      // write aggregates to result
      auto block = result->createBlock(groups.size());
      auto revenue =
          reinterpret_cast<types::Numeric<18, 2>*>(block.data(revenueAttr));
      auto year = reinterpret_cast<types::Integer*>(block.data(yearAttr));
      auto customerNation =
          reinterpret_cast<types::Char<15>*>(block.data(customerNationAttr));
      for (auto block : groups)
         for (auto& group : block) {
            *year++ = get<0>(group.k);
            *customerNation++ = get<1>(group.k);
            *revenue++ = group.v;
         }
      block.addedElements(groups.size());
   });

   leaveQuery(nrThreads);
   return move(resources.query);
}

std::unique_ptr<Q41Builder::Q41> Q41Builder::getQuery() {
   using namespace vectorwise;
   auto result = Result();
   previous = result.resultWriter.shared.result->participate();
   auto r = make_unique<Q41>();

   auto date = Scan("date");

   auto part = Scan("part");
   Select(Expression().addOp(
       primitives::sel_equal_to_Char_6_col_Char_6_val_or_Char_6_val,
       Buffer(sel_part, sizeof(pos_t)), Column(part, "p_mfgr"),
       Value(&r->mfgr1), Value(&r->mfgr2)));

   auto customer = Scan("customer");
   Select(Expression().addOp(primitives::sel_equal_to_Char_12_col_Char_12_val,
                             Buffer(sel_customer, sizeof(pos_t)),
                             Column(customer, "c_region"), Value(&r->region)));

   auto supplier = Scan("supplier");
   Select(
       Expression().addOp(BF(primitives::sel_equal_to_Char_12_col_Char_12_val),
                          Buffer(sel_supplier, sizeof(pos_t)),
                          Column(supplier, "s_region"), Value(&r->region)));

   auto lineorder = Scan("lineorder");

   // filter for lineorder is lineorder_supplier
   HashJoin(Buffer(lineorder_supplier, sizeof(pos_t)), conf.joinAll())
       .addBuildKey(Column(supplier, "s_suppkey"), Buffer(sel_supplier),
                    conf.hash_sel_int32_t_col(),
                    primitives::scatter_sel_int32_t_col)
       .addProbeKey(Column(lineorder, "lo_suppkey"), conf.hash_int32_t_col(),
                    primitives::keys_equal_int32_t_col);

   // filter for lineorder is lineorder_customer
   HashJoin(Buffer(lineorder_customer, sizeof(pos_t)), conf.joinAll())
       .addBuildKey(Column(customer, "c_custkey"), Buffer(sel_customer),
                    conf.hash_sel_int32_t_col(),
                    primitives::scatter_sel_int32_t_col)
       .addBuildValue(Column(customer, "c_nation"), Buffer(sel_customer),
                      primitives::scatter_sel_Char_15_col,
                      Buffer(c_nation, sizeof(types::Char<15>)),
                      primitives::gather_col_Char_15_col)
       .setProbeSelVector(Buffer(lineorder_supplier), conf.joinSel())
       .addProbeKey(Column(lineorder, "lo_custkey"), Buffer(lineorder_supplier),
                    conf.hash_sel_int32_t_col(),
                    primitives::keys_equal_int32_t_col);

   // filter for c_nation is lineorder_part
   HashJoin(Buffer(lineorder_part, sizeof(pos_t)), conf.joinAll())
       .addBuildKey(Column(part, "p_partkey"), Buffer(sel_part),
                    conf.hash_sel_int32_t_col(),
                    primitives::scatter_sel_int32_t_col)
       .pushProbeSelVector(Buffer(lineorder_customer),
                           Buffer(lineorder_customer_part,
                                  sizeof(pos_t))) // filter for lineorder
       .addProbeKey(Column(lineorder, "lo_partkey"), Buffer(lineorder_customer),
                    conf.hash_sel_int32_t_col(),
                    Buffer(lineorder_customer_part),
                    primitives::keys_equal_int32_t_col);

   HashJoin(Buffer(lineorder_date, sizeof(pos_t)), conf.joinAll())
       .addBuildKey(Column(date, "d_datekey"), conf.hash_int32_t_col(),
                    primitives::scatter_int32_t_col)
       .addBuildValue(Column(date, "d_year"), primitives::scatter_int32_t_col,
                      Buffer(d_year, sizeof(int32_t)),
                      primitives::gather_col_int32_t_col)
       .pushProbeSelVector(Buffer(lineorder_part),
                           Buffer(lineorder_part_date,
                                  sizeof(pos_t))) // c_nation selection vector
       .pushProbeSelVector(Buffer(lineorder_customer_part),
                           Buffer(lineorder_customer_part_date,
                                  sizeof(pos_t))) // lineorder selection vector
       .addProbeKey(Column(lineorder, "lo_orderdate"),
                    Buffer(lineorder_customer_part),
                    conf.hash_sel_int32_t_col(),
                    Buffer(lineorder_customer_part_date, sizeof(pos_t)),
                    primitives::keys_equal_int32_t_col);

   Project().addExpression(
       Expression() //
           .addOp(primitives::proj_sel_both_minus_int64_t_col_int64_t_col,
                  Buffer(lineorder_customer_part_date), //
                  Buffer(result_proj_minus, sizeof(int64_t)),
                  Column(lineorder, "lo_revenue"),
                  Column(lineorder, "lo_supplycost")));
   HashGroup()
       .addKey(Buffer(d_year),          //
               conf.hash_int32_t_col(), //
               primitives::keys_not_equal_int32_t_col,
               primitives::partition_by_key_int32_t_col,
               primitives::scatter_sel_int32_t_col,
               primitives::keys_not_equal_row_int32_t_col,
               primitives::partition_by_key_row_int32_t_col,
               primitives::scatter_sel_row_int32_t_col,
               primitives::gather_val_int32_t_col, Buffer(d_year))
       .pushKeySelVec(Buffer(lineorder_part_date),
                      Buffer(lineorder_part_date_grouped, sizeof(pos_t)))
       .addKey(Buffer(c_nation, sizeof(types::Char<15>)),
               Buffer(lineorder_part_date), primitives::rehash_sel_Char_15_col,
               primitives::keys_not_equal_sel_Char_15_col,
               primitives::partition_by_key_sel_Char_15_col,
               Buffer(lineorder_part_date_grouped, sizeof(pos_t)),
               primitives::scatter_sel_Char_15_col,
               primitives::keys_not_equal_row_Char_15_col,
               primitives::partition_by_key_row_Char_15_col,
               primitives::scatter_sel_row_Char_15_col,
               primitives::gather_val_Char_15_col,
               Buffer(c_nation, sizeof(types::Char<15>)))
       .addValue(Buffer(result_proj_minus),
                 primitives::aggr_init_plus_int64_t_col,
                 primitives::aggr_plus_int64_t_col,
                 primitives::aggr_row_plus_int64_t_col,
                 primitives::gather_val_int64_t_col,
                 Buffer(profit, sizeof(types::Numeric<18, 2>)));

   result.addValue("profit", Buffer(profit))
       .addValue("d_year", Buffer(d_year))
       .addValue("c_nation", Buffer(c_nation))
       .finalize();

   r->rootOp = popOperator();
   return r;
}

std::unique_ptr<runtime::Query> q41_vectorwise(Database& db, size_t nrThreads,
                                               size_t vectorSize) {
   using namespace vectorwise;

   using namespace vectorwise;
   WorkerGroup workers(nrThreads);
   vectorwise::SharedStateManager shared;
   std::unique_ptr<runtime::Query> result;
   workers.run([&]() {
      Q41Builder builder(db, shared, vectorSize);
      auto query = builder.getQuery();
      /* auto found = */ query->rootOp->next();
      auto leader = barrier();
      if (leader)
         result = move(
             dynamic_cast<ResultWriter*>(query->rootOp.get())->shared.result);
   });

   return result;
}

} // namespace ssb
