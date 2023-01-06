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

// select sum(lo_revenue), d_year, p_brand1
// from lineorder, "date", part, supplier
// where lo_orderdate = d_datekey
// and lo_partkey = p_partkey
// and lo_suppkey = s_suppkey
// and p_category = 'MFGR#12'
// and s_region = 'AMERICA'
// group by d_year, p_brand1

//                 sort
//
//                groupby
//
//                 join
//                 hash
//
// tablescan             join
// date                  hash
//
//          tablescan        join
//          supplier         hash
//
//                    tablescan tablescan
//                    part      lineorder

NOVECTORIZE std::unique_ptr<runtime::Query> q21_hyper(Database& db,
                                                      size_t nrThreads) {
   // --- aggregates
   auto resources = initQuery(nrThreads);

   // --- constants
   auto relevant_category = types::Char<7>::castString("MFGR#12");
   auto relevant_region = types::Char<12>::castString("AMERICA");

   using hash = runtime::CRC32Hash;
   const size_t morselSize = 100000;

   // --- ht for join date-lineorder
   Hashmapx<types::Integer, types::Integer, hash> ht1;
   tbb::enumerable_thread_specific<runtime::Stack<decltype(ht1)::Entry>>
       entries1;
   auto& d = db["date"];
   auto d_year = d["d_year"].data<types::Integer>();
   auto d_datekey = d["d_datekey"].data<types::Integer>();
   PARALLEL_SCAN(d.tup_c, entries1, {
      auto& year = d_year[i];
      auto& datekey = d_datekey[i];
      entries.emplace_back(ht1.hash(datekey), datekey, year);
   });
   ht1.setSize(d.tup_c);
   parallel_insert(entries1, ht1);

   // --- ht for join supplier-lineorder
   Hashset<types::Integer, hash> ht2;
   tbb::enumerable_thread_specific<runtime::Stack<decltype(ht2)::Entry>>
       entries2;
   auto& su = db["supplier"];
   auto s_suppkey = su["s_suppkey"].data<types::Integer>();
   auto s_region = su["s_region"].data<types::Char<12>>();
   // do selection on part and put selected elements into ht2
   auto found2 = PARALLEL_SELECT(su.tup_c, entries2, {
      auto& suppkey = s_suppkey[i];
      auto& region = s_region[i];
      if (region == relevant_region) {
         entries.emplace_back(ht2.hash(suppkey), suppkey);
         found++;
      }
   });
   ht2.setSize(found2);
   parallel_insert(entries2, ht2);

   // --- ht for join part-lineorder
   Hashmapx<types::Integer, types::Char<9>, hash> ht3;
   tbb::enumerable_thread_specific<runtime::Stack<decltype(ht3)::Entry>>
       entries3;
   auto& p = db["part"];
   auto p_partkey = p["p_partkey"].data<types::Integer>();
   auto p_category = p["p_category"].data<types::Char<7>>();
   auto p_brand1 = p["p_brand1"].data<types::Char<9>>();
   auto found3 = PARALLEL_SELECT(p.tup_c, entries3, {
      auto& partkey = p_partkey[i];
      auto& category = p_category[i];
      auto& brand1 = p_brand1[i];
      if (category == relevant_category) {
         entries.emplace_back(ht3.hash(partkey), partkey, brand1);
         found++;
      }
   });
   ht3.setSize(found3);
   parallel_insert(entries3, ht3);

   // --- scan and join lineorder
   auto& lo = db["lineorder"];
   auto lo_orderdate = lo["lo_orderdate"].data<types::Integer>();
   auto lo_partkey = lo["lo_partkey"].data<types::Integer>();
   auto lo_suppkey = lo["lo_suppkey"].data<types::Integer>();
   auto lo_revenue = lo["lo_revenue"].data<types::Numeric<18, 2>>();

   const auto zero = types::Numeric<18, 2>::castString("0.00");
   auto groupOp = make_GroupBy<tuple<types::Char<9>, types::Integer>,
                               types::Numeric<18, 2>, hash>(
       [](auto& acc, auto&& value) { acc += value; }, zero, nrThreads);

   // preaggregation
   tbb::parallel_for(
       tbb::blocked_range<size_t>(0, lo.tup_c, morselSize),
       [&](const tbb::blocked_range<size_t>& r) {
          auto groupLocals = groupOp.preAggLocals();
          for (size_t i = r.begin(), end = r.end(); i != end; ++i) {
             auto& revenue = lo_revenue[i];
             auto& suppkey = lo_suppkey[i];
             auto& partkey = lo_partkey[i];
             auto& orderdate = lo_orderdate[i];

             auto part = ht3.findOne(partkey);
             if (part) {
                if (ht2.contains(suppkey)) {
                   auto date = ht1.findOne(orderdate);
                   if (date) {
                      // --- aggregation
                      groupLocals.consume(make_tuple(*part, *date), revenue);
                   }
                }
             }
          }
       });
   // --- output
   auto& result = resources.query->result;
   auto revenueAttr =
       result->addAttribute("revenue", sizeof(types::Numeric<18, 2>));
   auto yearAttr = result->addAttribute("d_year", sizeof(types::Integer));
   auto brandAttr = result->addAttribute("p_brand1", sizeof(types::Char<9>));

   groupOp.forallGroups([&](auto& groups) {
      // write aggregates to result
      auto block = result->createBlock(groups.size());
      auto revenue =
          reinterpret_cast<types::Numeric<18, 2>*>(block.data(revenueAttr));
      auto year = reinterpret_cast<types::Integer*>(block.data(yearAttr));
      auto brand = reinterpret_cast<types::Char<9>*>(block.data(brandAttr));
      for (auto block : groups)
         for (auto& group : block) {
            *brand++ = get<0>(group.k);
            *year++ = get<1>(group.k);
            *revenue++ = group.v;
         }
      block.addedElements(groups.size());
   });

   leaveQuery(nrThreads);
   return move(resources.query);
}

std::unique_ptr<Q21Builder::Q21> Q21Builder::getQuery() {
   using namespace vectorwise;
   auto result = Result();
   previous = result.resultWriter.shared.result->participate();
   auto r = make_unique<Q21>();

   auto date = Scan("date");

   auto supplier = Scan("supplier");
   Select(
       Expression().addOp(BF(primitives::sel_equal_to_Char_12_col_Char_12_val),
                          Buffer(sel_supplier, sizeof(pos_t)),
                          Column(supplier, "s_region"), Value(&r->region)));

   auto part = Scan("part");
   Select(Expression().addOp(BF(primitives::sel_equal_to_Char_7_col_Char_7_val),
                             Buffer(sel_part, sizeof(pos_t)),
                             Column(part, "p_category"), Value(&r->category)));

   auto lineorder = Scan("lineorder");
   HashJoin(Buffer(lineorder_part, sizeof(pos_t)), conf.joinAll())
       .addBuildKey(Column(part, "p_partkey"), Buffer(sel_part),
                    conf.hash_sel_int32_t_col(),
                    primitives::scatter_sel_int32_t_col)
       .addBuildValue(Column(part, "p_brand1"), Buffer(sel_part),
                      primitives::scatter_sel_Char_9_col,
                      Buffer(p_brand1, sizeof(types::Char<9>)),
                      primitives::gather_col_Char_9_col)
       .addProbeKey(Column(lineorder, "lo_partkey"), conf.hash_int32_t_col(),
                    primitives::keys_equal_int32_t_col);

   // filter for p_brand1 is lineorder_supplier
   HashJoin(Buffer(lineorder_supplier, sizeof(pos_t)), conf.joinAll())
       .addBuildKey(Column(supplier, "s_suppkey"), Buffer(sel_supplier),
                    conf.hash_sel_int32_t_col(),
                    primitives::scatter_sel_int32_t_col)
       .pushProbeSelVector(Buffer(lineorder_part),
                           Buffer(lineorder_supplier_line, sizeof(pos_t)))
       .addProbeKey(Column(lineorder, "lo_suppkey"), Buffer(lineorder_part),
                    conf.hash_sel_int32_t_col(),
                    Buffer(lineorder_supplier_line, sizeof(pos_t)),
                    primitives::keys_equal_int32_t_col);

   HashJoin(Buffer(lineorder_date, sizeof(pos_t)), conf.joinAll())
       .addBuildKey(Column(date, "d_datekey"), conf.hash_int32_t_col(),
                    primitives::scatter_int32_t_col)
       .addBuildValue(Column(date, "d_year"), primitives::scatter_int32_t_col,
                      Buffer(d_year, sizeof(int32_t)),
                      primitives::gather_col_int32_t_col)
       .pushProbeSelVector(Buffer(lineorder_supplier),
                           Buffer(lineorder_date_part,
                                  sizeof(pos_t))) // brand1 selection vector
       .pushProbeSelVector(Buffer(lineorder_supplier_line),
                           Buffer(lineorder_supplier_date,
                                  sizeof(pos_t))) // lineorder selection vector
       .addProbeKey(Column(lineorder, "lo_orderdate"),
                    Buffer(lineorder_supplier_line),
                    conf.hash_sel_int32_t_col(),
                    Buffer(lineorder_supplier_date, sizeof(pos_t)),
                    primitives::keys_equal_int32_t_col);

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
       .pushKeySelVec(Buffer(lineorder_date_part),
                      Buffer(lineorder_date_part_grouped, sizeof(pos_t)))
       .addKey(Buffer(p_brand1), Buffer(lineorder_date_part),
               primitives::rehash_sel_Char_9_col,
               primitives::keys_not_equal_sel_Char_9_col,
               primitives::partition_by_key_sel_Char_9_col,
               Buffer(lineorder_date_part_grouped, sizeof(pos_t)),
               primitives::scatter_sel_Char_9_col,
               primitives::keys_not_equal_row_Char_9_col,
               primitives::partition_by_key_row_Char_9_col,
               primitives::scatter_sel_row_Char_9_col,
               primitives::gather_val_Char_9_col,
               Buffer(p_brand1, sizeof(types::Char<9>)))
       .addValue(Column(lineorder, "lo_revenue"),
                 Buffer(lineorder_supplier_date),
                 primitives::aggr_init_plus_int64_t_col,
                 primitives::aggr_sel_plus_int64_t_col,
                 primitives::aggr_row_plus_int64_t_col,
                 primitives::gather_val_int64_t_col,
                 Buffer(sum_revenue, sizeof(types::Numeric<18, 2>)));

   result.addValue("revenue", Buffer(sum_revenue))
       .addValue("d_year", Buffer(d_year))
       .addValue("p_brand1", Buffer(p_brand1))
       .finalize();

   r->rootOp = popOperator();
   return r;
}

std::unique_ptr<runtime::Query> q21_vectorwise(Database& db, size_t nrThreads,
                                               size_t vectorSize) {
   using namespace vectorwise;

   using namespace vectorwise;
   WorkerGroup workers(nrThreads);
   vectorwise::SharedStateManager shared;
   std::unique_ptr<runtime::Query> result;
   workers.run([&]() {
      Q21Builder builder(db, shared, vectorSize);
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
