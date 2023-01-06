#pragma once
#include "benchmarks/fls/config.hpp"
#include "benchmarks/tpch/Queries.hpp"

namespace CFG {
extern uint8_t BW;
}

class fls_q1_builder : public vectorwise::QueryBuilder {
public:
	struct query {
		size_t                                n;
		int32_t                               aggregator = 0;
		std::unique_ptr<vectorwise::Operator> rootOp;
	}; //
public:
	fls_q1_builder(runtime::Database& db, vectorwise::SharedStateManager& shared, size_t size = 1024)
	    : QueryBuilder(db, shared, size) {} //
public:
	std::unique_ptr<query> get_uncompressed_query();
};

runtime::Relation fls_q1_vectorwise(runtime::Database& db,
                                    size_t             nrThreads  = std::thread::hardware_concurrency(),
                                    size_t             vectorSize = 1024);