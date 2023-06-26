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

//  select c_city, s_city, d_year, sum(lo_revenue) as revenue
//  from customer, lineorder, supplier, "date"
//  where lo_custkey = c_custkey
//  and lo_suppkey = s_suppkey
//  and lo_orderdate = d_datekey
//  and c_nation = 'UNITED STATES'
//  and s_nation = 'UNITED STATES'
//  and d_year >= 1992 and d_year <= 1997
//  group by c_city, s_city, d_year

//                 groupby
//
//                  join
//                  hash
//
// tablescan             join
// date                  hash
//
//           tablescan        join
//           supplier         hash
//
//                     tablescan tablescan
//                     customer  lineorder

NOVECTORIZE std::unique_ptr<runtime::Query> q33_hyper(Database& db,
                                                      size_t nrThreads) {
   // --- aggregates
   auto resources = initQuery(nrThreads);

   // --- constants
   auto city1 = types::Char<10>::castString("UNITED KI1");
   auto city2 = types::Char<10>::castString("UNITED KI5");
   auto year_min = types::Integer(1992);
   auto year_max = types::Integer(1997);

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
      if (year >= year_min && year <= year_max) {
         entries.emplace_back(ht1.hash(datekey), datekey, year);
         found++;
      }
   });
   ht1.setSize(found1);
   parallel_insert(entries1, ht1);

   // --- ht for join supplier-lineorder
   Hashmapx<types::Integer, types::Char<10>, hash> ht2;
   tbb::enumerable_thread_specific<runtime::Stack<decltype(ht2)::Entry>>
       entries2;
   auto& su = db["supplier"];
   auto s_suppkey = su["s_suppkey"].data<types::Integer>();
   auto s_city = su["s_city"].data<types::Char<10>>();
   // do selection on part and put selected elements into ht2
   auto found2 = PARALLEL_SELECT(su.tup_c, entries2, {
      auto& suppkey = s_suppkey[i];
      auto& city = s_city[i];
      if (city == city1 || city == city2) {
         entries.emplace_back(ht2.hash(suppkey), suppkey, city);
         found++;
      }
   });
   ht2.setSize(found2);
   parallel_insert(entries2, ht2);

   // --- ht for join part-lineorder
   Hashmapx<types::Integer, types::Char<10>, hash> ht3;
   tbb::enumerable_thread_specific<runtime::Stack<decltype(ht3)::Entry>>
       entries3;
   auto& c = db["customer"];
   auto c_custkey = c["c_custkey"].data<types::Integer>();
   auto c_city = c["c_city"].data<types::Char<10>>();
   auto found3 = PARALLEL_SELECT(c.tup_c, entries3, {
      auto& custkey = c_custkey[i];
      auto& city = c_city[i];
      if (city == city1 || city == city2) {
         entries.emplace_back(ht3.hash(custkey), custkey, city);
         found++;
      }
   });
   ht3.setSize(found3);
   parallel_insert(entries3, ht3);

   // --- scan and join lineorder
   auto& lo = db["lineorder"];
   auto lo_orderdate = lo["lo_orderdate"].data<types::Integer>();
   auto lo_custkey = lo["lo_custkey"].data<types::Integer>();
   auto lo_suppkey = lo["lo_suppkey"].data<types::Integer>();
   auto lo_revenue = lo["lo_revenue"].data<types::Numeric<18, 2>>();

   const auto zero = types::Numeric<18, 2>::castString("0.00");
   auto groupOp =
       make_GroupBy<tuple<types::Char<10>, types::Char<10>, types::Integer>,
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
             auto& custkey = lo_custkey[i];
             auto& orderdate = lo_orderdate[i];

             auto customer = ht3.findOne(custkey);
             if (customer) {
                auto supplier = ht2.findOne(suppkey);
                if (supplier) {
                   auto date = ht1.findOne(orderdate);
                   if (date) {
                      // --- aggregation
                      groupLocals.consume(
                          make_tuple(*customer, *supplier, *date), revenue);
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
   auto customerCityAttr =
       result->addAttribute("c_city", sizeof(types::Char<10>));
   auto supplierCityAttr =
       result->addAttribute("s_city", sizeof(types::Char<10>));

   groupOp.forallGroups([&](auto& groups) {
      // write aggregates to result
      auto block = result->createBlock(groups.size());
      auto revenue =
          reinterpret_cast<types::Numeric<18, 2>*>(block.data(revenueAttr));
      auto year = reinterpret_cast<types::Integer*>(block.data(yearAttr));
      auto customerCity =
          reinterpret_cast<types::Char<10>*>(block.data(customerCityAttr));
      auto supplierCity =
          reinterpret_cast<types::Char<10>*>(block.data(supplierCityAttr));
      for (auto block : groups)
         for (auto& group : block) {
            *customerCity++ = get<0>(group.k);
            *supplierCity++ = get<1>(group.k);
            *year++ = get<2>(group.k);
            *revenue++ = group.v;
         }
      block.addedElements(groups.size());
   });

   leaveQuery(nrThreads);
   return move(resources.query);
}

// select c_city , s_city , d_year , sum(lo_revenue) as revenue
//   from customer, lineorder, supplier, "date"
//   where lo_custkey = c_custkey
//   and lo_suppkey = s_suppkey
//   and lo_orderdate = d_datekey
//   and (c_city='UNITED KI1'
//        or c_city='UNITED KI5')
//   and (s_city='UNITED KI1'
//        or s_city='UNITED KI5')
//   and d_year >= 1992 and d_year <= 1997
//   group by c_city, s_city, d_year

std::unique_ptr<Q33Builder::Q33> Q33Builder::getQuery() {
   using namespace vectorwise;
   auto result = Result();
   previous = result.resultWriter.shared.result->participate();
   auto r = make_unique<Q33>();

   auto date = Scan("date");
   Select(
       Expression()
           .addOp(BF(primitives::sel_less_equal_int32_t_col_int32_t_val),
                  Buffer(sel_year_max, sizeof(pos_t)), Column(date, "d_year"),
                  Value(&r->year_max))
           .addOp(BF(primitives::selsel_greater_equal_int32_t_col_int32_t_val),
                  Buffer(sel_year_max, sizeof(pos_t)),
                  Buffer(sel_year_min, sizeof(pos_t)), Column(date, "d_year"),
                  Value(&r->year_min)));

   auto supplier = Scan("supplier");
   Select(Expression().addOp(
       primitives::sel_equal_to_Char_10_col_Char_10_val_or_Char_10_val,
       Buffer(sel_supplier, sizeof(pos_t)), Column(supplier, "s_city"),
       Value(&r->city1), Value(&r->city2)));

   auto customer = Scan("customer");
   Select(Expression().addOp(
       primitives::sel_equal_to_Char_10_col_Char_10_val_or_Char_10_val,
       Buffer(sel_customer, sizeof(pos_t)), Column(customer, "c_city"),
       Value(&r->city1), Value(&r->city2)));

   auto lineorder = Scan("lineorder");
   HashJoin(Buffer(lineorder_customer, sizeof(pos_t)), conf.joinAll())
       .addBuildKey(Column(customer, "c_custkey"), Buffer(sel_customer),
                    conf.hash_sel_int32_t_col(),
                    primitives::scatter_sel_int32_t_col)
       .addBuildValue(Column(customer, "c_city"), Buffer(sel_customer),
                      primitives::scatter_sel_Char_10_col,
                      Buffer(c_city, sizeof(types::Char<10>)),
                      primitives::gather_col_Char_10_col)
       .addProbeKey(Column(lineorder, "lo_custkey"), conf.hash_int32_t_col(),
                    primitives::keys_equal_int32_t_col);

   // filter for c_city is lineorder_supplier
   HashJoin(Buffer(lineorder_supplier, sizeof(pos_t)), conf.joinAll())
       .addBuildKey(Column(supplier, "s_suppkey"), Buffer(sel_supplier),
                    conf.hash_sel_int32_t_col(),
                    primitives::scatter_sel_int32_t_col)
       .addBuildValue(Column(supplier, "s_city"), Buffer(sel_supplier),
                      primitives::scatter_sel_Char_10_col,
                      Buffer(s_city, sizeof(types::Char<10>)),
                      primitives::gather_col_Char_10_col)
       .pushProbeSelVector(Buffer(lineorder_customer),
                           Buffer(lineorder_supplier_line, sizeof(pos_t)))
       .addProbeKey(Column(lineorder, "lo_suppkey"), Buffer(lineorder_customer),
                    conf.hash_sel_int32_t_col(),
                    Buffer(lineorder_supplier_line, sizeof(pos_t)),
                    primitives::keys_equal_int32_t_col);

   // filter for s_city is lineorder_date
   HashJoin(Buffer(lineorder_date, sizeof(pos_t)), conf.joinAll())
       .addBuildKey(Column(date, "d_datekey"), Buffer(sel_year_min),
                    conf.hash_sel_int32_t_col(),
                    primitives::scatter_sel_int32_t_col)
       .addBuildValue(Column(date, "d_year"), Buffer(sel_year_min),
                      primitives::scatter_sel_int32_t_col,
                      Buffer(d_year, sizeof(int32_t)),
                      primitives::gather_col_int32_t_col)
       .pushProbeSelVector(Buffer(lineorder_supplier),
                           Buffer(lineorder_date_customer,
                                  sizeof(pos_t))) // c_nation selection vector
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
       .pushKeySelVec(Buffer(lineorder_date_customer),
                      Buffer(lineorder_date_part_grouped, sizeof(pos_t)))
       .addKey(Buffer(c_city, sizeof(types::Char<10>)),
               Buffer(lineorder_date_customer),
               primitives::rehash_sel_Char_10_col,
               primitives::keys_not_equal_sel_Char_10_col,
               primitives::partition_by_key_sel_Char_10_col,
               Buffer(lineorder_date_part_grouped, sizeof(pos_t)),
               primitives::scatter_sel_Char_10_col,
               primitives::keys_not_equal_row_Char_10_col,
               primitives::partition_by_key_row_Char_10_col,
               primitives::scatter_sel_row_Char_10_col,
               primitives::gather_val_Char_10_col,
               Buffer(c_city, sizeof(types::Char<15>)))
       .pushKeySelVec(Buffer(lineorder_date),
                      Buffer(lineorder_date_supplier_grouped, sizeof(pos_t)))
       .addKey(Buffer(s_city, sizeof(types::Char<10>)), Buffer(lineorder_date),
               primitives::rehash_sel_Char_10_col,
               primitives::keys_not_equal_sel_Char_10_col,
               primitives::partition_by_key_sel_Char_10_col,
               Buffer(lineorder_date_supplier_grouped, sizeof(pos_t)),
               primitives::scatter_sel_Char_10_col,
               primitives::keys_not_equal_row_Char_10_col,
               primitives::partition_by_key_row_Char_10_col,
               primitives::scatter_sel_row_Char_10_col,
               primitives::gather_val_Char_10_col,
               Buffer(s_city, sizeof(types::Char<15>)))
       .addValue(Column(lineorder, "lo_revenue"),
                 Buffer(lineorder_supplier_date),
                 primitives::aggr_init_plus_int64_t_col,
                 primitives::aggr_sel_plus_int64_t_col,
                 primitives::aggr_row_plus_int64_t_col,
                 primitives::gather_val_int64_t_col,
                 Buffer(sum_revenue, sizeof(types::Numeric<18, 2>)));

   result.addValue("revenue", Buffer(sum_revenue))
       .addValue("d_year", Buffer(d_year))
       .addValue("c_city", Buffer(c_city))
       .addValue("s_city", Buffer(s_city))
       .finalize();

   r->rootOp = popOperator();
   return r;
}

std::unique_ptr<runtime::Query> q33_vectorwise(Database& db, size_t nrThreads,
                                               size_t vectorSize) {
   using namespace vectorwise;
   WorkerGroup workers(nrThreads);
   vectorwise::SharedStateManager shared;
   std::unique_ptr<runtime::Query> result;
   workers.run([&]() {
      Q33Builder builder(db, shared, vectorSize);
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
