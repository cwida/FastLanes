#include "benchmarks/fls/Queries.hpp"
#include "benchmarks/fls/config.hpp"
#include "common/runtime/Types.hpp"
#include "fls/unpack.hpp"
#include "tbb/tbb.h"
#include "vectorwise/Operations.hpp"
#include "vectorwise/Operators.hpp"
#include "vectorwise/Primitives.hpp"
#include "vectorwise/QueryBuilder.hpp"
#include "vectorwise/VectorAllocator.hpp"
#include <iostream>

using namespace runtime;
using namespace std;

namespace fls {
// using F2 = pos_t (*)(pos_t n, void* result, void* param1);

using pos_t = uint32_t;
pos_t memcpy_32(pos_t n, void* result, void* param1) { std::memcpy(result, param1, 1024 * 4); }
pos_t bitunpack_32(pos_t n, void* result, void* param1) {
	auto in  = reinterpret_cast<uint32_t*>(param1);
	auto out = reinterpret_cast<uint32_t*>(result);
	generated::unpack::x86_64::avx512bw::unpack(in, out, CFG::BW);
	return n;
}

} // namespace fls

std::unique_ptr<fls_q1_builder::query> fls_q1_builder::get_uncompressed_query() {
	using namespace vectorwise;
	// --- constants
	auto  res    = make_unique<query>();
	auto& consts = *res;
	enum { bitunpacked };

	auto relation = Scan(CFG::NAME);

	if (CFG::BITPACK_QUERY) {
		// bitpacked
		FixedAggregation(Expression()
		                     .addOp(fls::bitunpack_32,
		                            Buffer(bitunpacked, sizeof(int32_t)), //
		                            Column(relation, "first"))
		                     .addOp(primitives::aggr_static_plus_int32_t_col,
		                            Value(&consts.aggregator), //
		                            Buffer(bitunpacked)));
	} else {

		// non bitpacked
		FixedAggregation(Expression() //
		                     .addOp(primitives::aggr_static_plus_int32_t_col,
		                            Value(&consts.aggregator), //
		                            Column(relation, "first")));
	}

	res->rootOp = popOperator();
	assert(operatorStack.size() == 0);
	return res;
}

runtime::Relation fls_q1_vectorwise(Database& db, size_t nrThreads, size_t vectorSize) {
	using namespace vectorwise;

	std::atomic<size_t>            n;
	runtime::Relation              result;
	vectorwise::SharedStateManager shared;
	WorkerGroup                    workers(nrThreads);
	GlobalPool                     pool;
	std::atomic<int32_t>           aggr;
	aggr = 0;
	n    = 0;
	workers.run([&]() {
		fls_q1_builder b(db, shared, vectorSize);
		b.previous = this_worker->allocator.setSource(&pool);
		auto query = b.get_uncompressed_query();
		auto n_    = query->rootOp->next();
		if (n_) {
			aggr.fetch_add(query->aggregator);
			n.fetch_add(n_);
		}

		auto leader = barrier();
		if (leader) {
			result.insert("result", make_unique<algebra::Integer>());
			if (n.load()) {
				auto& sum = result["result"].template typedAccessForChange<int32_t>();
				sum.reset(1);
				auto a = aggr.load();
				sum.push_back(a);
				result.tup_c = 1;
			}
		}
	});

	return result;
}
