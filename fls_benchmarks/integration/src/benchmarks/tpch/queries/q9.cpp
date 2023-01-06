#include "benchmarks/tpch/Queries.hpp"
#include "common/runtime/Concurrency.hpp"
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
#include <iostream>

using namespace runtime;
using namespace std;
using vectorwise::primitives::Char_10;
using vectorwise::primitives::Char_25;
using vectorwise::primitives::hash_t;
/*

select
nation,
  o_year,
  sum(amount) as sum_profit
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

std::unique_ptr<runtime::Query> q9_hyper(runtime::Database& db,
                                         size_t nrThreads) {

   // --- aggregates
   auto resources = initQuery(nrThreads);
   using hash = runtime::CRC32Hash;

   // --- constants
   auto contains = types::Varchar<55>::castString("green");

   auto& na = db["nation"];
   auto& supp = db["supplier"];

   // --- build ht for nation
   auto n_nationkey = na["n_nationkey"].data<types::Integer>();
   auto n_name = na["n_name"].data<types::Char<25>>();
   Hashmapx<types::Integer, types::Char<25>, hash> ht1;
   tbb::enumerable_thread_specific<runtime::Stack<decltype(ht1)::Entry>>
       entries1;
   PARALLEL_SCAN(na.tup_c, entries1, {
      auto& key = n_nationkey[i];
      entries.emplace_back(ht1.hash(key), key, n_name[i]);
   });
   ht1.setSize(na.tup_c);
   parallel_insert(entries1, ht1);


   // --- ht for bushy join
   Hashmapx<types::Integer, types::Char<25>, hash> ht2;
   tbb::enumerable_thread_specific<runtime::Stack<decltype(ht2)::Entry>>
     entries2;
   auto s_suppkey = supp["s_suppkey"].data<types::Integer>();
   auto s_nationkey = supp["s_nationkey"].data<types::Integer>();
   // do join nation-supplier and put result into bushy ht
   auto found2 = PARALLEL_SELECT(supp.tup_c, entries2, {
      auto& suppkey = s_suppkey[i];
      auto& nationkey = s_nationkey[i];
      auto name = ht1.findOne(nationkey);
      if (name) {
         entries.emplace_back(ht2.hash(suppkey), suppkey, *name);
         found++;
      }
   });
   ht2.setSize(found2);
   parallel_insert(entries2, ht2);

   // --- ht for join part-partsupp
   Hashset<types::Integer, hash> ht3;
   tbb::enumerable_thread_specific<runtime::Stack<decltype(ht3)::Entry>>
     entries3;
   auto& part = db["part"];
   auto p_partkey = part["p_partkey"].data<types::Integer>();
   auto p_name = part["p_name"].data<types::Varchar<55>>();
   // do selection on part and put selected elements into ht
   auto found3 = PARALLEL_SELECT(part.tup_c, entries3, {
       auto& pk = p_partkey[i];
       auto& pn = p_name[i];
       if (memmem(pn.value, pn.len, contains.value, contains.len) != nullptr){
          entries.emplace_back(ht3.hash(pk), pk);
          found++;
       }
     });
   ht3.setSize(found3);
   parallel_insert(entries3, ht3);

   Hashmapx<tuple<types::Integer, types::Integer>,
            tuple<types::Char<25>, types::Numeric<12, 2>>, hash>
       ht4;
   tbb::enumerable_thread_specific<runtime::Stack<decltype(ht4)::Entry>>
       entries4;
   auto& partsupp = db["partsupp"];
   auto ps_partkey = partsupp["ps_partkey"].data<types::Integer>();
   auto ps_suppkey = partsupp["ps_suppkey"].data<types::Integer>();
   auto ps_supplycost = partsupp["ps_supplycost"].data<types::Numeric<12, 2>>();
   auto found4 = PARALLEL_SELECT(partsupp.tup_c, entries4, {
      if (ht3.contains(ps_partkey[i])) {
         auto nation = ht2.findOne(ps_suppkey[i]);
         if (nation) {
            auto key = make_tuple(ps_partkey[i], ps_suppkey[i]);
            auto value = make_tuple(*nation, ps_supplycost[i]);
            entries.emplace_back(ht4.hash(key), key, value);
            found++;
         }
      }
   });
   ht4.setSize(found4);
   parallel_insert(entries4, ht4);

   Hashmapx<
       types::Integer,
       tuple<types::Numeric<12, 2>, types::Numeric<12, 2>,
             types::Numeric<12, 2>, types::Numeric<12, 2>, types::Char<25>>,
       hash>
       ht5;
   tbb::enumerable_thread_specific<runtime::Stack<decltype(ht5)::Entry>>
       entries5;
   auto& li = db["lineitem"];
   auto l_orderkey = li["l_orderkey"].data<types::Integer>();
   auto l_partkey = li["l_partkey"].data<types::Integer>();
   auto l_suppkey = li["l_suppkey"].data<types::Integer>();
   auto l_extendedprice = li["l_extendedprice"].data<types::Numeric<12, 2>>();
   auto l_discount = li["l_discount"].data<types::Numeric<12, 2>>();
   auto l_quantity = li["l_quantity"].data<types::Numeric<12, 2>>();
   auto found5 =
       PARALLEL_SELECT(li.tup_c, entries5, {
          auto part = ht4.findOne(make_tuple(l_partkey[i], l_suppkey[i]));
          if (part) {
             auto& key = l_orderkey[i];
             auto value =
                 make_tuple(l_extendedprice[i], l_discount[i], l_quantity[i],
                            get<1>(*part), get<0>(*part));
             entries.emplace_back(ht5.hash(key), key, value);
             found++;
          }
       });
   ht5.setSize(found5);
   parallel_insert(entries5, ht5);

   auto& ord = db["orders"];
   auto o_orderkey = ord["o_orderkey"].template data<types::Integer>();
   auto o_orderdate = ord["o_orderdate"].template data<types::Date>();
   const auto one = types::Numeric<12, 2>::castString("1.00");
   const auto zero = types::Numeric<12, 4>::castString("0.00");
   auto groupOp = make_GroupBy<tuple<types::Char<25>, types::Integer>, types::Numeric<12, 4>, hash>(
       [](auto& acc, auto&& value) { acc += value; }, zero, nrThreads);
   // preaggregation
   tbb::parallel_for(
       tbb::blocked_range<size_t>(0, ord.tup_c, morselSize),
       [&](const tbb::blocked_range<size_t>& r) {
          auto groupLocals = groupOp.preAggLocals();

          for (size_t i = r.begin(), end = r.end(); i != end; ++i) {
             auto h = ht5.hash(o_orderkey[i]);
             auto entry = ht5.findOneEntry(o_orderkey[i], h);
             for (; entry;
                  entry = reinterpret_cast<decltype(entry)>(entry->h.next)) {
                if (entry->h.hash != h || entry->k != o_orderkey[i]) continue;
                auto& v = entry->v;
                auto year = extractYear(o_orderdate[i]);
                auto& extp = get<0>(v);
                auto& disc = get<1>(v);
                auto& quant = get<2>(v);
                auto& supplcost = get<3>(v);
                auto& name = get<4>(v);
                // l_extendedprice * (1 - l_discount) - ps_supplycost * l_quantity as
                auto amount = (extp * (one - disc)) - (supplcost * quant);
                groupLocals.consume(make_tuple(name, year), amount);
             }
          }
       });

   // --- output
   auto& result = resources.query->result;
   auto nationAttr = result->addAttribute("nation", sizeof(types::Char<25>));
   auto yearAttr = result->addAttribute("o_year", sizeof(types::Integer));
   auto profitAttr = result->addAttribute("sum_profit", sizeof(types::Numeric<12, 4>));

   groupOp.forallGroups([&](auto& groups) {
      // write aggregates to result
      auto block = result->createBlock(groups.size());
      auto nation = reinterpret_cast<types::Char<25>*>(block.data(nationAttr));
      auto year = reinterpret_cast<types::Integer*>(block.data(yearAttr));
      auto profit = reinterpret_cast<types::Numeric<12, 4>*>(block.data(profitAttr));
      for (auto block : groups)
         for (auto& group : block) {
            *nation++ = get<0>(group.k);
            *year++ = get<1>(group.k);
            *profit++ = group.v;
         }
      block.addedElements(groups.size());
   });

   leaveQuery(nrThreads);
   return move(resources.query);
}

std::unique_ptr<Q9Builder::Q9> Q9Builder::getQuery(){

   using namespace vectorwise;
   auto result = Result();
   previous = result.resultWriter.shared.result->participate();

   auto r = make_unique<Q9>();
   auto nation = Scan("nation");
   auto supplier = Scan("supplier");
   //join nation supplier
   HashJoin(Buffer(nation_supplier, sizeof(pos_t)), conf.joinAll())
       .addBuildKey(Column(nation, "n_nationkey"), //
                    conf.hash_int32_t_col(),       //
                    primitives::scatter_int32_t_col)
       .addBuildValue(Column(nation, "n_name"), //
                      primitives::scatter_Char_25_col,
                      Buffer(n_name, sizeof(Char_25)),
                      primitives::gather_col_Char_25_col)
       .addProbeKey(Column(supplier, "s_nationkey"), //
                    conf.hash_int32_t_col(),       //
                    primitives::keys_equal_int32_t_col);

   auto part = Scan("part");
   Select(Expression().addOp(primitives::sel_contains_Varchar_55_col_Varchar_55_val,
                             Buffer(sel_part, sizeof(pos_t)),
                             Column(part, "p_name"), //
                             Value(&r->contains)));
   auto partsupp = Scan("partsupp");
   HashJoin(Buffer(part_partsupp, sizeof(pos_t)), conf.joinAll())
       .addBuildKey(Column(part, "p_partkey"), //
                    Buffer(sel_part),          //
                    conf.hash_sel_int32_t_col(),
                    primitives::scatter_sel_int32_t_col)
       .addProbeKey(Column(partsupp, "ps_partkey"), //
                    conf.hash_int32_t_col(),       //
                    primitives::keys_equal_int32_t_col);

   HashJoin(Buffer(pspp, sizeof(pos_t)), conf.joinAll())
       .addBuildKey(Column(supplier, "s_suppkey"), //
                    Buffer(nation_supplier),       //
                    conf.hash_sel_int32_t_col(),
                    primitives::scatter_sel_int32_t_col)
       .addBuildValue(Buffer(n_name), //
                      primitives::scatter_Char_25_col, Buffer(n_name),
                      primitives::gather_col_Char_25_col)
       .setProbeSelVector(Buffer(part_partsupp), conf.joinSel())
       .addProbeKey(Column(partsupp, "ps_suppkey"), //
                    Buffer(part_partsupp),          //
                    conf.hash_sel_int32_t_col(),
                    primitives::keys_equal_int32_t_col);

   auto lineitem = Scan("lineitem");
   HashJoin(Buffer(xlineitem, sizeof(pos_t)), conf.joinAll())
       .addBuildKey(Column(partsupp, "ps_partkey"),   //
                    Buffer(pspp),                     //
                    conf.hash_sel_int32_t_col(),
                    primitives::scatter_sel_int32_t_col)
       .addBuildKey(Column(partsupp, "ps_suppkey"),     //
                    Buffer(pspp),                       //
                    conf.rehash_sel_int32_t_col(),
                    primitives::scatter_sel_int32_t_col)
       .addBuildValue(Buffer(n_name),                  //
                      primitives::scatter_Char_25_col, //
                      Buffer(n_name),                  //
                      primitives::gather_col_Char_25_col)
       .addBuildValue(Column(partsupp, "ps_supplycost"), //
                      Buffer(pspp),                      //
                      primitives::scatter_sel_int64_t_col,
                      Buffer(ps_supplycost, sizeof(int64_t)), //
                      primitives::gather_col_int64_t_col)
       .addProbeKey(Column(lineitem, "l_partkey"), //
                    conf.hash_int32_t_col(),
                    primitives::keys_equal_int32_t_col)
       .addProbeKey(Column(lineitem, "l_suppkey"), //
                    conf.rehash_int32_t_col(),
                    primitives::keys_equal_int32_t_col);

   auto orders = Scan("orders");
   HashJoin(Buffer(ordersx, sizeof(pos_t)), conf.joinAll())
       .addBuildKey(Column(lineitem, "l_orderkey"), //
                    Buffer(xlineitem),              //
                    conf.hash_sel_int32_t_col(),
                    primitives::scatter_sel_int32_t_col)
       .addProbeKey(Column(orders, "o_orderkey"), //
                    conf.hash_int32_t_col(),      //
                    primitives::keys_equal_int32_t_col)
       .addBuildValue(Column(lineitem, "l_extendedprice"), //
                      Buffer(xlineitem),                   //
                      primitives::scatter_sel_int64_t_col,
                      Buffer(l_extendedprice, sizeof(int64_t)),
                      primitives::gather_col_int64_t_col)
       .addBuildValue(Column(lineitem, "l_discount"), //
                      Buffer(xlineitem),              //
                      primitives::scatter_sel_int64_t_col,
                      Buffer(l_discount, sizeof(int64_t)),
                      primitives::gather_col_int64_t_col)
       .addBuildValue(Column(lineitem, "l_quantity"), //
                      Buffer(xlineitem),              //
                      primitives::scatter_sel_int64_t_col,
                      Buffer(l_quantity, sizeof(int64_t)),
                      primitives::gather_col_int64_t_col)
       .addBuildValue(Buffer(ps_supplycost),           //
                      primitives::scatter_int64_t_col, //
                      Buffer(ps_supplycost),           //
                      primitives::gather_col_int64_t_col)
       .addBuildValue(Buffer(n_name),                  //
                      primitives::scatter_Char_25_col, //
                      Buffer(n_name),                  //
                      primitives::gather_col_Char_25_col);

   Project()
       // l_extendedprice * (1 - l_discount) - ps_supplycost * l_quantity as
       // amount
       .addExpression(
           Expression()
               .addOp(primitives::proj_minus_int64_t_val_int64_t_col,
                      Buffer(result_proj_minus, sizeof(int64_t)),
                      Value(&r->one), Buffer(l_discount))
               .addOp(primitives::proj_multiplies_int64_t_col_int64_t_col,
                      Buffer(disc_price, sizeof(int64_t)),
                      Buffer(l_extendedprice),
                      Buffer(result_proj_minus, sizeof(int64_t)))
               .addOp(primitives::proj_multiplies_int64_t_col_int64_t_col,
                      Buffer(total_cost, sizeof(int64_t)),
                      Buffer(ps_supplycost), //
                      Buffer(l_quantity))
               .addOp(primitives::proj_minus_int64_t_col_int64_t_col,
                      Buffer(amount, sizeof(int64_t)),
                      Buffer(disc_price, sizeof(int64_t)), //
                      Buffer(total_cost, sizeof(int64_t))))
       .addExpression(
           Expression().addOp(primitives::apply_extract_year_sel_col,
                              Buffer(o_year, sizeof(types::Integer)), //
                              Buffer(ordersx),                        //
                              Column(orders, "o_orderdate")));        //

   HashGroup()
       .addKey(Buffer(n_name), //
               primitives::hash_Char_25_col,
               primitives::keys_not_equal_Char_25_col,
               primitives::partition_by_key_Char_25_col,
               primitives::scatter_sel_Char_25_col,
               primitives::keys_not_equal_row_Char_25_col,
               primitives::partition_by_key_row_Char_25_col,
               primitives::scatter_sel_row_Char_25_col,
               primitives::gather_val_Char_25_col, Buffer(n_name))
       .addKey(Buffer(o_year),            //
               conf.rehash_int32_t_col(), //
               primitives::keys_not_equal_int32_t_col,
               primitives::partition_by_key_int32_t_col,
               primitives::scatter_sel_int32_t_col,
               primitives::keys_not_equal_row_int32_t_col,
               primitives::partition_by_key_row_int32_t_col,
               primitives::scatter_sel_row_int32_t_col,
               primitives::gather_val_int32_t_col, Buffer(o_year))
       .addValue(Buffer(amount), //
                 primitives::aggr_init_plus_int64_t_col,
                 primitives::aggr_plus_int64_t_col,
                 primitives::aggr_row_plus_int64_t_col,
                 primitives::gather_val_int64_t_col,
                 Buffer(sum_profit, sizeof(int64_t)));

   result.addValue("nation", Buffer(n_name))
       .addValue("o_year", Buffer(o_year))
       .addValue("sum_profit", Buffer(sum_profit))
       .finalize();

   r->rootOp = popOperator();
   return r;
}

std::unique_ptr<runtime::Query>
q9_vectorwise(runtime::Database& db, size_t nrThreads, size_t vectorSize) {

  using namespace vectorwise;
  WorkerGroup workers(nrThreads);
  vectorwise::SharedStateManager shared;
  std::unique_ptr<runtime::Query> result;
  workers.run([&]() {
      Q9Builder builder(db, shared, vectorSize);
      auto query = builder.getQuery();
      /* auto found = */ query->rootOp->next();
      auto leader = barrier();
      if (leader)
        result = move(
                      dynamic_cast<ResultWriter*>(query->rootOp.get())->shared.result);
    });

  return result;
}
