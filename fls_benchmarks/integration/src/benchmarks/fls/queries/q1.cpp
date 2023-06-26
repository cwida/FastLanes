#include "benchmarks/fls/Queries.hpp"
#include "benchmarks/fls/config.hpp"
#include "common/runtime/Types.hpp"
#include "fls/unpack.hpp"
#include "lemire/bitpackinghelpers.hpp"
#include "tbb/tbb.h"
#include "vectorwise/Operations.hpp"
#include "vectorwise/Operators.hpp"
#include "vectorwise/Primitives.hpp"
#include "vectorwise/QueryBuilder.hpp"
#include "vectorwise/VectorAllocator.hpp"
#include <iostream>

using namespace runtime;
using namespace std;

namespace fls { namespace function {
// using F2 = pos_t (*)(pos_t n, void* result, void* param1);

using pos_t = uint32_t;
pos_t bitunpack_32(pos_t n, void* result, void* param1) {
	auto in  = reinterpret_cast<uint32_t*>(param1);
	auto out = reinterpret_cast<uint32_t*>(result);
	generated::unpack::x86_64::avx512bw::unpack(in, out, cfg::bw);
	return n;
}

pos_t bitunpack_32_nothing(pos_t n, void* result, void* param1) {
	auto in  = reinterpret_cast<uint32_t*>(param1);
	auto out = reinterpret_cast<uint32_t*>(result);
	return n;
}

pos_t bitunpack_32_scalar(pos_t n, void* result, void* param1) {
	auto in  = reinterpret_cast<uint32_t*>(param1);
	auto out = reinterpret_cast<uint32_t*>(result);
	for (size_t i {0}; i < 1024; i = i + 32) {
		duckdb_fastpforlib::fastunpack((in + cfg::bw), out + i, cfg::bw);
	}
	return n;
}

/// aggregate column into single value
pos_t aggr_static_col_nothing(pos_t n, void* RES result, void* RES param1) { return n > 0; }

}} // namespace fls::function

std::unique_ptr<fls_q_builder::query> fls_q_builder::get_q() {
	using namespace vectorwise;
	// --- constants
	auto  res    = make_unique<query>();
	auto& consts = *res;
	enum { bitunpacked };

	auto scan_bdr = Scan(cfg::name);

	switch (cfg::query_t) {
	case cfg::BITPACKED_DEBUG:
		FixedAggregation(Expression()
		                     .addOp(fls::function::bitunpack_32,
		                            Buffer(bitunpacked, sizeof(int32_t)), //
		                            Column(scan_bdr, cfg::schema[0]))
		                     .addOp(primitives::aggr_static_plus_int32_t_col,
		                            Value(&consts.aggregator), //
		                            Buffer(bitunpacked)));
		break;
	case cfg::BITPACKED:
		FixedAggregation(Expression()
		                     .addOp(fls::function::bitunpack_32,
		                            Buffer(bitunpacked, sizeof(int32_t)), //
		                            Column(scan_bdr, cfg::schema[0]))
		                     .addOp(primitives::aggr_static_plus_int32_t_col,
		                            Value(&consts.aggregator), //
		                            Buffer(bitunpacked)));
		break;
	case cfg::BITPACKED_OVERHEAD:
		FixedAggregation(Expression()
		                     .addOp(fls::function::bitunpack_32_nothing,
		                            Buffer(bitunpacked, sizeof(int32_t)), //
		                            Column(scan_bdr, cfg::schema[0]))
		                     .addOp(fls::function::aggr_static_col_nothing,
		                            Value(&consts.aggregator), //
		                            Buffer(bitunpacked)));
		break;
	case cfg::NORMAL:
		FixedAggregation(Expression()                          //
		                     .addOp(primitives::aggr_static_plus_int32_t_col,
		                            Value(&consts.aggregator), //
		                            Column(scan_bdr, cfg::schema[0])));
		break;
	case cfg::NORMAL_DEBUG:
		FixedAggregation(Expression()                          //
		                     .addOp(primitives::aggr_static_plus_int32_t_col,
		                            Value(&consts.aggregator), //
		                            Column(scan_bdr, cfg::schema[0])));
		break;
	case cfg::NORMAL_OVERHEAD:
		FixedAggregation(Expression()                          //
		                     .addOp(fls::function::aggr_static_col_nothing,
		                            Value(&consts.aggregator), //
		                            Column(scan_bdr, cfg::schema[0])));
		break;
	case cfg::BITPACKED_NORMAL:
		FixedAggregation(Expression()
		                     .addOp(fls::function::bitunpack_32_scalar,
		                            Buffer(bitunpacked, sizeof(int32_t)), //
		                            Column(scan_bdr, cfg::schema[0]))
		                     .addOp(primitives::aggr_static_plus_int32_t_col,
		                            Value(&consts.aggregator), //
		                            Buffer(bitunpacked)));
		break;
	}

	res->root_op = popOperator();
	assert(operatorStack.size() == 0);
	return res;
}

runtime::Relation fls_q(Database& db, size_t t_c, size_t vec_sz) {
	using namespace vectorwise;

	runtime::Relation              result;
	vectorwise::SharedStateManager shared;
	WorkerGroup                    workers(t_c);
	GlobalPool                     pool;
	std::atomic<int32_t>           aggr;
	aggr = 0;

	workers.run([&]() {
		fls_q_builder b(db, shared, vec_sz);
		b.previous = this_worker->allocator.setSource(&pool);
		auto query = b.get_q();
		query->root_op->next();
		aggr.fetch_add(query->aggregator);

		auto leader = barrier();
		if (leader) {
			result.insert("aggr", make_unique<algebra::Integer>());
			auto& sum = result["aggr"].template typedAccessForChange<int32_t>();
			sum.reset(1);
			auto a = aggr.load();
			sum.push_back(a);
			result.tup_c = 1;
		}
	});

	return result;
}
