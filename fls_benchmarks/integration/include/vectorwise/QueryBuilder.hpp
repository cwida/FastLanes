#pragma once
#include "Operators.hpp"
#include "common/runtime/Database.hpp"
#include "vectorwise/VectorAllocator.hpp"
#include <memory>
#include <stack>
#include <vector>

namespace vectorwise {

class QueryBuilder {
public:
	QueryBuilder(runtime::Database& db_, SharedStateManager& s, size_t vSize = 1024)
	    : db(db_)
	    , operatorState(s)
	    , vecs(vSize) {}

public:
	runtime::GlobalPool* previous; //
protected:
	std::stack<std::unique_ptr<Operator>>                operatorStack;
	runtime::Database&                                   db;
	SharedStateManager&                                  operatorState;
	VectorAllocator                                      vecs;
	std::unordered_map<size_t, std::pair<size_t, void*>> buffers;

	struct DataStorage
	/// handle for data sources, e.g. base table columns or cache buffers
	{
		enum BufferSpec { BUFFER, COLUMN, VALUE, NONE } buf = NONE;
		size_t      data_size;
		void*       data = nullptr;
		class Scan* scan = nullptr;
		std::string attribute;
		void        registerDS(void** location);
		void        registerDS(pos_t** location);
		            operator void*() const;
		            operator pos_t*() const;
	};
	using DS = DataStorage;

	struct ResultBuilder {
		using RB = ResultBuilder;
		QueryBuilder&                 base;
		ResultWriter&                 resultWriter;
		std::unique_ptr<ResultWriter> resultWriterOwning;
		RB&                           addValue(std::string name, DS buffer);
		void                          finalize();
	};

	struct ScanBuilder {
		class Scan&        scan;
		runtime::Relation& rel;
	};

	struct ProjectionBuilder {
		QueryBuilder&      base;
		Project&           project;
		ProjectionBuilder& addExpression(std::unique_ptr<Expression>&& exp);
	};

	struct HashJoinBuilder {
		QueryBuilder&      base;
		bool               probeHasSelection = false;
		std::deque<size_t> keyOffsets;
		void*              buildHashBuffer = nullptr;
		void*              probeHashBuffer = nullptr;
		Hashjoin*          join;
		HashJoinBuilder(QueryBuilder& b);
		~HashJoinBuilder();
		using B = HashJoinBuilder;

		B& addBuildKey(DS col, primitives::F2 hash, primitives::FScatter scatter);
		B& addBuildKey(DS col, DS sel, primitives::F3 hash, primitives::FScatterSel scatter);
		B& addProbeKey(DS col, primitives::F2 hash, primitives::EQCheck eq);
		B& addProbeKey(DS col, DS sel, primitives::F3 hash, primitives::EQCheck eq);
		B& addProbeKey(DS col, DS sel, primitives::F3 hash, DS selEq, primitives::EQCheck eq);
		B& addBuildValue(DS source, primitives::FScatter scatter, DS target, primitives::FGather gather);
		B& addBuildValue(DS source, DS sel, primitives::FScatterSel scatter, DS target, primitives::FGather gather);
		B& setProbeSelVector(DS vec, pos_t (Hashjoin::*join)() = &Hashjoin::joinSelParallel);
		B& pushProbeSelVector(DS sel, DS target);
	};

	struct HashGroupBuilder {
		QueryBuilder& base;
		HashGroup*    group;

		struct Lookup {
			pos_t* partitionEndsIn;
			pos_t* partitionEndsOut;
			pos_t* unpartitionedRows;
			pos_t* partitionedRows;
		} localLookup, globalLookup;

		HashGroupBuilder(QueryBuilder& base);

		using B = HashGroupBuilder;
		B& addKey(DS             col,
		          primitives::F2 hash,
		          /**** global aggr *****/
		          primitives::NEQCheck        eq,
		          primitives::FPartitionByKey partitionByKey,
		          primitives::FScatterSel     scatter,
		          /**** global aggr *****/
		          primitives::NEQCheckRow        eqG,
		          primitives::FPartitionByKeyRow partitionByKeyG,
		          primitives::FScatterSelRow     scatterG,
		          /**** output *****/
		          primitives::FGatherVal gather,
		          DS                     out);
		B& addKey(
		    /**** input *****/
		    DS             col,
		    DS             sel,
		    primitives::F3 hash,
		    /**** local aggregation *****/
		    primitives::NEQCheckSel        eq,
		    primitives::FPartitionByKeySel partitionByKey,
		    DS                             selScat,
		    primitives::FScatterSel        scatter,
		    /**** global aggregation *****/
		    primitives::NEQCheckRow        eqG,
		    primitives::FPartitionByKeyRow partitionByKeyG,
		    primitives::FScatterSelRow     scatterG,
		    /**** output *****/
		    primitives::FGatherVal gather,
		    DS                     out);
		B& pushKeySelVec(DS sel, DS outBuf);
		B& addValue(DS                     col,
		            primitives::FAggrInit  aggrInit,
		            primitives::FAggr      aggr,
		            primitives::FAggrRow   aggrGlobal,
		            primitives::FGatherVal gather,
		            DS                     out);
		B& addValue(DS                     col,
		            DS                     sel,
		            primitives::FAggrInit  aggrInit,
		            primitives::FAggrSel   aggr,
		            primitives::FAggrRow   aggrGlobal,
		            primitives::FGatherVal gather,
		            DS                     out);
		B& padToAlign(size_t align);
		~HashGroupBuilder();
	};

	struct ExpressionBuilder {
		std::unique_ptr<Expression> expression;
		using DS = DataStorage;
		ExpressionBuilder& addOp(primitives::F1 op, DS a);
		ExpressionBuilder& addOp(primitives::F2 op, DS a, DS b);
		ExpressionBuilder& addOp(primitives::F3 op, DS a, DS b, DS c);
		ExpressionBuilder& addOp(primitives::F4 op, DS a, DS b, DS c, DS d);
		                   operator std::unique_ptr<vectorwise::Expression>();
		                   operator std::unique_ptr<vectorwise::Aggregates>();
	};

	size_t opNr   = 0;
	size_t onceNr = 0;
	size_t nextOpNr();
	size_t nextOnceNr();

	ResultBuilder Result();
	ScanBuilder   Scan(std::string relation);
	template <typename PAYLOAD>
	void              Debug(std::function<void(size_t, PAYLOAD&)> step, std::function<void(PAYLOAD&)> finish);
	void              DebugCounter(std::string message);
	void              Select(std::unique_ptr<Expression>&& exp);
	ProjectionBuilder Project();
	void              FixedAggregation(std::unique_ptr<Aggregates>&& aggrs);
	HashJoinBuilder   HashJoin(DS probeMatches, pos_t (Hashjoin::*join)() = &Hashjoin::joinAllParallel);
	HashGroupBuilder  HashGroup();

	~QueryBuilder();

	ExpressionBuilder Expression();

	DS Buffer(size_t nr, size_t entrySize);
	DS Buffer(size_t nr);
	DS Column(ScanBuilder& scan_bdr, std::string attribute);
	DS Value(void*);

	void                      pushOperator(std::unique_ptr<Operator>&& op);
	std::unique_ptr<Operator> popOperator();
};

template <typename PAYLOAD>
void QueryBuilder::Debug(std::function<void(size_t, PAYLOAD&)> step, std::function<void(PAYLOAD&)> finish) {

	auto& shared = operatorState.get<typename DebugOperator<PAYLOAD>::Shared>(nextOpNr());
	auto  debug  = std::make_unique<DebugOperator<PAYLOAD>>(shared, std::move(step), std::move(finish));
	debug->child = popOperator();
	pushOperator(std::move(debug));
}
} // namespace vectorwise
