#include "benchmarks/tpch/Queries.hpp"
#include "common/runtime/Hash.hpp"
#include "common/runtime/Types.hpp"
#include "vectorwise/Operations.hpp"
#include "vectorwise/Operators.hpp"
#include "vectorwise/Primitives.hpp"
#include "vectorwise/QueryBuilder.hpp"
#include "vectorwise/VectorAllocator.hpp"
#include <deque>
#include <iostream>

using namespace runtime;
using namespace std;
using vectorwise::primitives::Char_10;
using vectorwise::primitives::Char_25;
using vectorwise::primitives::hash_t;

// select
// sum(l_extendedprice * l_discount) as revenue
//   count(*) as count
// from
//   customer,
//   orders,
//   lineitem,
//   supplier,
//   nation,
//   region
// where
//   c_custkey = o_custkey
//   and l_orderkey = o_orderkey
//   and l_suppkey = s_suppkey
//   and c_nationkey = s_nationkey
//   and s_nationkey = n_nationkey
//   and n_regionkey = r_regionkey

using namespace runtime;
using namespace std;
NOVECTORIZE Relation q5_no_sel_hyper(Database& db) {

   // --- aggregates
   types::Numeric<12, 4> revenue = 0;
   int64_t count = 0;

   auto& su = db["supplier"];
   auto& re = db["region"];
   auto& na = db["nation"];
   auto& cu = db["customer"];
   auto& ord = db["orders"];
   auto& li = db["lineitem"];

   using hash = runtime::CRC32Hash;

   auto& r_regionkey = re["r_regionkey"].typedAccess<types::Integer>();
   // --- select region and build ht
   Hashset<types::Integer, hash> ht1;
   deque<decltype(ht1)::Entry> entries1;
   for (size_t i = 0; i < re.tup_c; ++i)
      entries1.emplace_back(ht1.hash(r_regionkey[i]), r_regionkey[i]);
   ht1.setSize(entries1.size());
   ht1.insertAll(entries1);

   // --- join on region and build ht
   auto& n_regionkey = na["n_regionkey"].typedAccess<types::Integer>();
   auto& n_nationkey = na["n_nationkey"].typedAccess<types::Integer>();
   Hashset<types::Integer, hash> ht2;
   deque<decltype(ht2)::Entry> entries2;
   for (size_t i = 0; i < na.tup_c; ++i)
      if (ht1.contains(n_regionkey[i]))
         entries2.emplace_back(ht2.hash(n_nationkey[i]), n_nationkey[i]);
   ht2.setSize(entries2.size());
   ht2.insertAll(entries2);

   // --- join on nation and build ht
   auto& c_nationkey = cu["c_nationkey"].typedAccess<types::Integer>();
   auto& c_custkey = cu["c_custkey"].typedAccess<types::Integer>();
   Hashmapx<types::Integer, types::Integer, hash> ht3;
   deque<decltype(ht3)::Entry> entries3;
   for (size_t i = 0; i < cu.tup_c; ++i)
      if (ht2.contains(c_nationkey[i]))
         entries3.emplace_back(ht3.hash(c_custkey[i]), c_custkey[i],
                               c_nationkey[i]);
   ht3.setSize(entries3.size());
   ht3.insertAll(entries3);

   // --- join on customer and build ht
   auto& o_orderkey = ord["o_orderkey"].typedAccess<types::Integer>();
   auto& o_custkey = ord["o_custkey"].typedAccess<types::Integer>();
   Hashmapx<types::Integer, types::Integer, hash> ht4;
   deque<decltype(ht4)::Entry> entries4;
   for (size_t i = 0; i < ord.tup_c; ++i) {
      types::Integer* v;
      if ((v = ht3.findOne(o_custkey[i])))
         entries4.emplace_back(ht4.hash(o_orderkey[i]), o_orderkey[i], *v);
   }
   ht4.setSize(entries4.size());
   ht4.insertAll(entries4);

   // --- build ht for supplier
   auto& s_suppkey = su["s_suppkey"].typedAccess<types::Integer>();
   auto& s_nationkey = su["s_nationkey"].typedAccess<types::Integer>();
   Hashset<std::tuple<types::Integer, types::Integer>, hash> ht5;
   deque<decltype(ht5)::Entry> entries5;
   for (size_t i = 0; i < su.tup_c; ++i) {
      auto key = make_tuple(s_suppkey[i], s_nationkey[i]);
      entries5.emplace_back(ht5.hash(key), key);
   }
   ht5.setSize(entries5.size());
   ht5.insertAll(entries5);

   // --- join on customer and build ht
   auto& l_orderkey = li["l_orderkey"].typedAccess<types::Integer>();
   auto& l_suppkey = li["l_suppkey"].typedAccess<types::Integer>();
   auto& l_extendedprice =
       li["l_extendedprice"].typedAccess<types::Numeric<12, 2>>();
   auto& l_discount = li["l_discount"].typedAccess<types::Numeric<12, 2>>();
   for (size_t i = 0; i < li.tup_c; ++i) {
      auto v = ht4.findOne(l_orderkey[i]);
      if (v) {
         auto suppkey = make_tuple(l_suppkey[i], *v);
         if (ht5.contains(suppkey)) {
            revenue += l_extendedprice[i] * l_discount[i];
            count++;
         }
      }
   }

   // --- output
   Relation result;
   result.insert("revenue", make_unique<algebra::Numeric>(12, 4));
   result.insert("count", make_unique<algebra::BigInt>());
   auto& rev = result["revenue"].typedAccessForChange<types::Numeric<12, 4>>();
   rev.reset(1);
   rev.push_back(revenue);
   auto& ct = result["count"].typedAccessForChange<int64_t>();
   ct.reset(1);
   ct.push_back(count);
   result.tup_c = 1;
   return result;
}

unique_ptr<Q5Builder::Q5> Q5Builder::getNoSelQuery() {
   using namespace vectorwise;
   auto result = Result();
   previous = result.resultWriter.shared.result->participate();
   auto r = make_unique<Q5>();
   auto supplier = Scan("supplier");
   auto region = Scan("region");
   auto nation = Scan("nation");
   HashJoin(Buffer(join_reg_nat, sizeof(pos_t)))
       .addBuildKey(Column(region, "r_regionkey"), primitives::hash_int32_t_col,
                    primitives::scatter_int32_t_col)
       .addProbeKey(Column(nation, "n_regionkey"), primitives::hash_int32_t_col,
                    primitives::keys_equal_int32_t_col);
   auto customer = Scan("customer");
   HashJoin(Buffer(join_cust, sizeof(pos_t)))
       .addBuildKey(Column(nation, "n_nationkey"), primitives::hash_int32_t_col,
                    primitives::scatter_int32_t_col)
       .addProbeKey(Column(customer, "c_nationkey"),
                    primitives::hash_int32_t_col,
                    primitives::keys_equal_int32_t_col)
       .addBuildValue(Column(nation, "n_name"), Buffer(join_reg_nat),
                      primitives::scatter_sel_Char_25_col,
                      Buffer(n_name, sizeof(Char_25)),
                      primitives::gather_col_Char_25_col);
   auto orders = Scan("orders");
   HashJoin(Buffer(join_ord, sizeof(pos_t)))
       .addBuildKey(Column(customer, "c_custkey"), primitives::hash_int32_t_col,
                    primitives::scatter_int32_t_col)
       .addProbeKey(Column(orders, "o_custkey"), primitives::hash_int32_t_col,
                    primitives::keys_equal_int32_t_col)
       .addBuildValue(Column(customer, "c_nationkey"),
                      primitives::scatter_int32_t_col,
                      Buffer(join_ord_nationkey, sizeof(int32_t)),
                      primitives::gather_col_int32_t_col)
       .addBuildValue(Buffer(n_name), primitives::scatter_Char_25_col,
                      Buffer(n_name2, sizeof(Char_25)),
                      primitives::gather_col_Char_25_col);
   auto lineitem = Scan("lineitem");
   HashJoin(Buffer(join_line, sizeof(pos_t)))
       .addBuildKey(Column(orders, "o_orderkey"), Buffer(join_ord),
                    primitives::hash_sel_int32_t_col,
                    primitives::scatter_sel_int32_t_col)
       .addProbeKey(Column(lineitem, "l_orderkey"),
                    primitives::hash_int32_t_col,
                    primitives::keys_equal_int32_t_col)
       .addBuildValue(Buffer(join_ord_nationkey),
                      primitives::scatter_int32_t_col,
                      Buffer(join_line_nationkey, sizeof(int32_t)),
                      primitives::gather_col_int32_t_col)
       .addBuildValue(Buffer(n_name2), primitives::scatter_Char_25_col,
                      Buffer(n_name, sizeof(Char_25)),
                      primitives::gather_col_Char_25_col);
   HashJoin(Buffer(join_supp, sizeof(pos_t)))
       .addBuildKey(Column(supplier, "s_nationkey"),
                    primitives::hash_int32_t_col,
                    primitives::scatter_int32_t_col)
       .addBuildKey(Column(supplier, "s_suppkey"),
                    primitives::rehash_int32_t_col,
                    primitives::scatter_int32_t_col)
       .addProbeKey(Buffer(join_line_nationkey), primitives::hash_int32_t_col,
                    primitives::keys_equal_int32_t_col)
       .pushProbeSelVector(Buffer(join_line),
                           Buffer(join_supp_line, sizeof(pos_t)))
       .addProbeKey(Column(lineitem, "l_suppkey"), Buffer(join_line),
                    primitives::rehash_sel_int32_t_col,
                    Buffer(join_supp_line, sizeof(pos_t)),
                    primitives::keys_equal_int32_t_col);
   Project().addExpression(
       Expression()
           .addOp(primitives::proj_sel_minus_int64_t_val_int64_t_col,
                  Buffer(join_supp_line),
                  Buffer(result_proj_minus, sizeof(int64_t)), Value(&r->one),
                  Column(lineitem, "l_discount"))
           .addOp(primitives::proj_multiplies_sel_int64_t_col_int64_t_col,
                  Buffer(join_supp_line),
                  Buffer(result_project, sizeof(int64_t)),
                  Column(lineitem, "l_extendedprice"),
                  Buffer(result_proj_minus, sizeof(int64_t))));
   HashGroup()
       .pushKeySelVec(Buffer(join_supp), Buffer(selScat, sizeof(pos_t)))
       .addKey(
           Buffer(n_name), Buffer(join_supp), primitives::hash_sel_Char_25_col,
           primitives::keys_not_equal_sel_Char_25_col,
           primitives::partition_by_key_sel_Char_25_col,
           Buffer(selScat, sizeof(pos_t)), primitives::scatter_sel_Char_25_col,
           primitives::keys_not_equal_row_Char_25_col,
           primitives::partition_by_key_row_Char_25_col,
           primitives::scatter_sel_row_Char_25_col,
           primitives::gather_val_Char_25_col, Buffer(n_name))
       .addValue(Buffer(result_project), primitives::aggr_init_plus_int64_t_col,
                 primitives::aggr_plus_int64_t_col,
                 primitives::aggr_row_plus_int64_t_col,
                 primitives::gather_val_int64_t_col,
                 Buffer(sum, sizeof(int64_t)));
   result //
       .addValue("n_name", Buffer(n_name))
       .addValue("revenue", Buffer(sum))
       .finalize();
   r->rootOp = popOperator();
   assert(operatorStack.size() == 0);
   return r;
}

std::unique_ptr<BlockRelation> q5_no_sel_vectorwise(Database& db,
                                                    size_t nrThreads) {
   using namespace vectorwise;

   WorkerGroup workers(nrThreads);
   vectorwise::SharedStateManager shared;
   std::unique_ptr<BlockRelation> result;
   workers.run([&]() {
      Q5Builder builder(db, shared);
      auto query = builder.getNoSelQuery();
      /* auto found = */ query->rootOp->next();
      auto leader = barrier();
      if (leader)
         result = move(dynamic_cast<ResultWriter*>(query->rootOp.get())
                           ->shared.result->result);
   });
   return result;
}
