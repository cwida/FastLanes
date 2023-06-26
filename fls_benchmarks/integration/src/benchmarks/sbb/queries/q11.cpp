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

NOVECTORIZE std::unique_ptr<runtime::Query> q11_hyper(Database& db,
                                                      size_t nrThreads) {
   // --- aggregates

   auto resources = initQuery(nrThreads);

   // --- constants
   const auto relevant_year = types::Integer(1993);
   const auto discount_min = types::Numeric<18, 2>::castString("1.00");
   const auto discount_max = types::Numeric<18, 2>::castString("3.00");
   const auto quantity_max = types::Integer(25);

   using hash = runtime::CRC32Hash;
   const size_t morselSize = 100000;

   // --- ht for join date-lineorder
   Hashset<types::Integer, hash> ht;
   tbb::enumerable_thread_specific<runtime::Stack<decltype(ht)::Entry>>
       entries1;
   auto& d = db["date"];
   auto d_year = d["d_year"].data<types::Integer>();
   auto d_datekey = d["d_datekey"].data<types::Integer>();
   // do selection on part and put selected elements into ht
   auto found = PARALLEL_SELECT(d.tup_c, entries1, {
      auto& year = d_year[i];
      auto& datekey = d_datekey[i];
      if (year == relevant_year) {
         entries.emplace_back(ht.hash(datekey), datekey);
         found++;
      }
   });
   ht.setSize(found);
   parallel_insert(entries1, ht);

   // --- scan lineorder
   auto& lo = db["lineorder"];
   auto lo_orderdate = lo["lo_orderdate"].data<types::Integer>();
   auto lo_quantity = lo["lo_quantity"].data<types::Integer>();
   auto lo_discount = lo["lo_discount"].data<types::Numeric<18, 2>>();
   auto lo_extendedprice = lo["lo_extendedprice"].data<types::Numeric<18, 2>>();

   auto result_revenue = tbb::parallel_reduce(
       tbb::blocked_range<size_t>(0, lo.tup_c), types::Numeric<18, 4>(0),
       [&](const tbb::blocked_range<size_t>& r,
           const types::Numeric<18, 4>& s) {
          auto revenue = s;
          for (size_t i = r.begin(), end = r.end(); i != end; ++i) {
             auto& quantity = lo_quantity[i];
             auto& discount = lo_discount[i];
             auto& extendedprice = lo_extendedprice[i];

             if ((quantity < quantity_max) & (discount >= discount_min) &
                 (discount <= discount_max)) {
                if (ht.contains(lo_orderdate[i])) {
                   // --- aggregation
                   revenue += extendedprice * discount;
                }
             }
          }
          return revenue;
       },
       [](const types::Numeric<18, 4>& x, const types::Numeric<18, 4>& y) {
          return x + y;
       });

   // --- output
   auto& result = resources.query->result;
   auto revAttr =
       result->addAttribute("revenue", sizeof(types::Numeric<18, 4>));
   auto block = result->createBlock(1);
   auto revenue = static_cast<types::Numeric<18, 4>*>(block.data(revAttr));
   *revenue = result_revenue;
   block.addedElements(1);

   leaveQuery(nrThreads);
   return std::move(resources.query);
}

std::unique_ptr<Q11Builder::Q11> Q11Builder::getQuery() {
   using namespace vectorwise;

   auto r = make_unique<Q11>();
   auto date = Scan("date");
   // select d_year = 1993
   Select(Expression().addOp(BF(primitives::sel_equal_to_int32_t_col_int32_t_val),
                             Buffer(sel_year, sizeof(pos_t)),
                             Column(date, "d_year"), Value(&r->year)));

   auto lineorder = Scan("lineorder");
   // select lo_discount between 1 and 3, lo_quantity < 25
   Select(
       Expression()
           .addOp(BF(primitives::sel_less_int32_t_col_int32_t_val),
                  Buffer(sel_qty, sizeof(pos_t)),
                  Column(lineorder, "lo_quantity"), Value(&r->quantity_max))
           .addOp(BF(primitives::selsel_greater_equal_int64_t_col_int64_t_val),
                  Buffer(sel_qty, sizeof(pos_t)),
                  Buffer(sel_discount_low, sizeof(pos_t)),
                  Column(lineorder, "lo_discount"), Value(&r->discount_min))
           .addOp(BF(primitives::selsel_less_equal_int64_t_col_int64_t_val),
                  Buffer(sel_discount_low, sizeof(pos_t)),
                  Buffer(sel_discount_high, sizeof(pos_t)),
                  Column(lineorder, "lo_discount"), Value(&r->discount_max)));

   HashJoin(Buffer(join_result, sizeof(pos_t)), conf.joinAll())
       .setProbeSelVector(Buffer(sel_discount_high), conf.joinSel())
       .addBuildKey(Column(date, "d_datekey"), Buffer(sel_year),
                    conf.hash_sel_int32_t_col(),
                    primitives::scatter_sel_int32_t_col)
       .addProbeKey(Column(lineorder, "lo_orderdate"),
                    Buffer(sel_discount_high), conf.hash_sel_int32_t_col(),
                    primitives::keys_equal_int32_t_col);

   Project().addExpression(Expression().addOp(
       primitives::proj_sel_both_multiplies_int64_t_col_int64_t_col,
       Buffer(join_result), Buffer(result_project, sizeof(int64_t)),
       Column(lineorder, "lo_extendedprice"),
       Column(lineorder, "lo_discount")));

   FixedAggregation(Expression().addOp(primitives::aggr_static_plus_int64_t_col,
                                       Value(&r->aggregator),
                                       Buffer(result_project)));
   r->rootOp = popOperator();
   assert(operatorStack.size() == 0);
   return r;
}

std::unique_ptr<runtime::Query> q11_vectorwise(Database& db, size_t nrThreads,
                                               size_t vectorSize) {
   using namespace vectorwise;

   // runtime::Relation result;
   auto result = std::make_unique<runtime::Query>();
   vectorwise::SharedStateManager shared;
   WorkerGroup workers(nrThreads);
   std::atomic<size_t> n;
   std::atomic<int64_t> aggr;
   aggr = 0;
   n = 0;
   workers.run([&]() {
      Q11Builder b(db, shared, vectorSize);
      b.previous = result->participate();
      auto query = b.getQuery();
      auto n_ = query->rootOp->next();
      if (n_) {
         aggr.fetch_add(query->aggregator);
         n.fetch_add(n_);
      }

      auto leader = barrier();
      if (leader) {
         auto attribute = result->result->addAttribute(
             "revenue", sizeof(types::Numeric<18, 4>));
         if (n.load()) {
            auto block = result->result->createBlock(1);
            int64_t* revenue = static_cast<int64_t*>(block.data(attribute));
            *revenue = aggr.load();
            block.addedElements(1);
         }
      }
   });

   return result;
}

} // namespace ssb
