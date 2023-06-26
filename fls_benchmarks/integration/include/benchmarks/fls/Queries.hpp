#pragma once
#include "benchmarks/fls/config.hpp"
#include "benchmarks/tpch/Queries.hpp"

class fls_q_builder : public vectorwise::QueryBuilder {
public:
	struct query {
		int32_t                               aggregator = 0;
		std::unique_ptr<vectorwise::Operator> root_op;
	}; //
public:
	fls_q_builder(runtime::Database& db, vectorwise::SharedStateManager& shared, size_t size)
	    : QueryBuilder(db, shared, size) {} //
public:
	std::unique_ptr<query> get_q();
};

runtime::Relation fls_q(runtime::Database& db, size_t t_c, size_t vec_sz);