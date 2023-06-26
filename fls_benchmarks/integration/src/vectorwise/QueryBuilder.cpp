#include "vectorwise/QueryBuilder.hpp"
#include "benchmarks/fls/config.hpp"
#include <cstddef>

using namespace std;

namespace vectorwise {
using runtime::barrier;

size_t padding(size_t size, size_t align) {
   auto moreThanAlign = size % align;
   auto pad = moreThanAlign ? align - moreThanAlign : 0;
   return pad;
}

size_t QueryBuilder::nextOpNr() { return opNr++; }
size_t QueryBuilder::nextOnceNr() { return onceNr++; }
QueryBuilder::~QueryBuilder() {
   runtime::this_worker->allocator.setSource(previous);
}

QueryBuilder::ResultBuilder QueryBuilder::Result() {
   auto nr = nextOpNr();
   auto& s = operatorState.get<ResultWriter::Shared>(nr);
   auto resultBuilder = make_unique<ResultWriter>(s);
   auto writer = resultBuilder.get();
   return {*this, *writer, move(resultBuilder)};
}

void QueryBuilder::ResultBuilder::finalize() {
   resultWriter.child = base.popOperator();
   base.pushOperator(move(resultWriterOwning));
}

QueryBuilder::ResultBuilder&
QueryBuilder::ResultBuilder::addValue(std::string name, DS buffer) {
   barrier([&]() {
      resultWriter.shared.result->result->addAttribute(name, buffer.data_size);
   });
   // TODO: fix code below and replace barrier variant
   // Code below assures one time execution. addAttribute and getAttribute can
   // be called concurrently which they are however not prepared for.
   //
   // base.operatorState.once(base.nextOnceNr(), [&]() {
   //     // concurrent append
   //    resultWriter.shared.result->addAttribute(name, buffer.dataSize);
   // });
   // concurrent read of appended
   auto attr = resultWriter.shared.result->result->getAttribute(name);
   resultWriter.inputs.emplace_back(buffer.data, buffer.data_size, attr);
   buffer.registerDS(&resultWriter.inputs.back().data);
   return *this;
}

QueryBuilder::ScanBuilder QueryBuilder::Scan(std::string relation) {
   auto& rel = db[relation];
   auto nr = nextOpNr();
   auto& s = operatorState.get<Scan::Shared>(nr);
   auto scan = make_unique<class Scan>(s, rel.tup_c, vecs.getVecSize());
   auto res = scan.get();
   pushOperator(move(scan));
   return {*res, rel};
}

void QueryBuilder::DebugCounter(std::string message) {
   struct Counter {
      size_t counter;
   };
   Debug<Counter>(
       [](size_t n, Counter& c) { c.counter += n; },
       [message](Counter& c) { cout << message << ": " << c.counter << endl; });
}

void QueryBuilder::Select(std::unique_ptr<class Expression>&& exp) {
   auto select = make_unique<class Select>();
   select->condition = move(exp);
   select->child = popOperator();
   pushOperator(move(select));
}

QueryBuilder::ProjectionBuilder QueryBuilder::Project() {
   auto project = make_unique<class Project>();
   auto p = project.get();
   p->child = popOperator();
   pushOperator(move(project));
   return {*this, *p};
}

void QueryBuilder::FixedAggregation(std::unique_ptr<Aggregates>&& aggrs) {
   auto aggregation = make_unique<FixedAggr>();
   aggregation->aggregates = move(*aggrs);
   aggregation->child = popOperator();
   pushOperator(move(aggregation));
}

QueryBuilder::ProjectionBuilder& QueryBuilder::ProjectionBuilder::addExpression(
    std::unique_ptr<class Expression>&& exp) {
   project.expressions.push_back(move(exp));
   return *this;
}

QueryBuilder::ExpressionBuilder QueryBuilder::Expression() {
   QueryBuilder::ExpressionBuilder b;
   b.expression = make_unique<class Expression>();
   return b;
}

QueryBuilder::DS QueryBuilder::Buffer(size_t nr, size_t entrySize) {
   if (buffers.find(nr) == buffers.end())
      buffers.emplace(nr, make_pair(entrySize, vecs.get(entrySize)));
   return Buffer(nr);
}

QueryBuilder::DS QueryBuilder::Buffer(size_t nr) {
   if (buffers.find(nr) == buffers.end())
      throw runtime_error("Buffer " + to_string(nr) + " not found");
   DS r;
   r.buf = DataStorage::BufferSpec::BUFFER;
   auto& buf = buffers[nr];
   r.data_size = buf.first;
   r.data = buf.second;
   return r;
}

QueryBuilder::DS QueryBuilder::Column(ScanBuilder& scan_bdr,
                                      std::string attribute) {
   DS r;
   r.buf = DataStorage::BufferSpec::COLUMN;
   auto& attr = scan_bdr.rel[attribute];
   r.data_size = attr.type->rt_size();
   r.data = attr.data();
   r.scan = &scan_bdr.scan;
   return r;
}

QueryBuilder::DS QueryBuilder::Value(void* data) {
   DS r;
   r.buf = DataStorage::BufferSpec::VALUE;
   r.data = data;
   return r;
}

void QueryBuilder::pushOperator(std::unique_ptr<Operator>&& op) {
   operatorStack.push(move(op));
}

std::unique_ptr<Operator> QueryBuilder::popOperator() {
   auto el = move(operatorStack.top());
   operatorStack.pop();
   return el;
}

void QueryBuilder::DataStorage::registerDS(void** location) {
	if (buf == DataStorage::BufferSpec::COLUMN) {
		assert(location);
		assert(scan);
		assert(data_size);

		if(cfg::is_bitpacked) {
			// bitpacked
			 scan->addConsumer(location, cfg::bw);
		} else{
			// none bitpacked
			scan->addConsumer(location, data_size);
		}
	}
}

void QueryBuilder::DataStorage::registerDS(pos_t** location) {
   registerDS(reinterpret_cast<void**>(location));
}

QueryBuilder::DataStorage::operator void*() const { return data; }
QueryBuilder::DataStorage::operator pos_t*() const {
   return reinterpret_cast<pos_t*>(data);
}

QueryBuilder::ExpressionBuilder&
QueryBuilder::ExpressionBuilder::addOp(primitives::F1 op, DS a) {
   auto f1 = make_unique<F1_Op>(a, op);
   a.registerDS(&f1->input);
   expression->ops.push_back(move(f1));
   return *this;
}

QueryBuilder::ExpressionBuilder&
QueryBuilder::ExpressionBuilder::addOp(primitives::F2 op, DS a, DS b) {
   auto f2 = make_unique<F2_Op>(a, b, op);
   a.registerDS(&f2->input);
   b.registerDS(&f2->param1);
   expression->ops.push_back(move(f2));
   return *this;
}

QueryBuilder::ExpressionBuilder&
QueryBuilder::ExpressionBuilder::addOp(primitives::F3 op, DS a, DS b, DS c) {
   auto f3 = make_unique<F3_Op>(a, b, c, op);
   a.registerDS(&f3->outputSelectionV);
   b.registerDS(&f3->param1);
   c.registerDS(&f3->param2);
   expression->ops.push_back(move(f3));
   return *this;
}
QueryBuilder::ExpressionBuilder&
QueryBuilder::ExpressionBuilder::addOp(primitives::F4 op, DS a, DS b, DS c,
                                       DS d) {
   auto f4 = make_unique<F4_Op>(a, b, c, d, op);
   a.registerDS(&f4->inputSelectionV);
   b.registerDS(&f4->outputSelectionV);
   c.registerDS(&f4->param1);
   d.registerDS(&f4->param2);
   expression->ops.push_back(move(f4));
   return *this;
}
QueryBuilder::ExpressionBuilder::
operator std::unique_ptr<vectorwise::Expression>() {
   return move(expression);
}

QueryBuilder::ExpressionBuilder::
operator std::unique_ptr<vectorwise::Aggregates>() {
   auto r = make_unique<vectorwise::Aggregates>();
   r->ops = move(expression->ops);
   return r;
}

QueryBuilder::HashJoinBuilder::HashJoinBuilder(QueryBuilder& b) : base(b) {}
QueryBuilder::HashJoinBuilder::~HashJoinBuilder() {
   join->ht_entry_size += padding(join->ht_entry_size, 8);
}

QueryBuilder::HashJoinBuilder
QueryBuilder::HashJoin(DS probeMatches, pos_t (Hashjoin::*joinFun)()) {
   HashJoinBuilder b(*this);
   auto nr = nextOpNr();
   auto& s = operatorState.get<Hashjoin::Shared>(nr);
   auto join = make_unique<Hashjoin>(s);
   join->followupIds = reinterpret_cast<decltype(join->followupIds)>(
       vecs.getPlus1(sizeof(*join->followupIds)));
   join->followupEntries = reinterpret_cast<decltype(join->followupEntries)>(
       vecs.getPlus1(sizeof(*join->followupEntries)));
   join->followupBufferSize = vecs.getVecSize() + 1;
   b.join = join.get();
   b.join->join = joinFun;
   b.join->ht_entry_size = sizeof(runtime::Hashmap::EntryHeader);
   b.join->batchSize = vecs.getVecSize();
   b.join->buildMatches = static_cast<runtime::Hashmap::EntryHeader**>(
       vecs.get(sizeof(runtime::Hashmap::EntryHeader*)));
   b.join->probeMatches = probeMatches;
   b.buildHashBuffer = vecs.get(sizeof(runtime::Hashmap::hash_t));
   b.probeHashBuffer = vecs.get(sizeof(runtime::Hashmap::hash_t));

   auto scatter_hash = make_unique<FScatterOp>(
       primitives::scatter_hash_t_col, b.buildHashBuffer,
       reinterpret_cast<void**>(&b.join->scatterStart), &b.join->ht_entry_size,
       offsetof(runtime::Hashmap::EntryHeader, hash));
   b.join->buildScatter += move(scatter_hash);
   b.join->right = popOperator();
   b.join->left = popOperator();
   pushOperator(move(join));
   return b;
}

QueryBuilder::HashJoinBuilder&
QueryBuilder::HashJoinBuilder::addBuildKey(DS col, primitives::F2 hash,
                                           primitives::FScatter scatter) {

   auto entryOffset = join->ht_entry_size;
   keyOffsets.push_back(entryOffset);
   join->ht_entry_size += col.data_size;

   // create hash primitive for build side
   auto hash_build = make_unique<F2_Op>(buildHashBuffer, col, hash);
   col.registerDS(&hash_build->param1);
   join->buildHash.ops.push_back(move(hash_build));

   // build scatter
   auto scatter_build = make_unique<FScatterOp>(
       scatter, col, reinterpret_cast<void**>(&join->scatterStart),
       &join->ht_entry_size, entryOffset);
   col.registerDS(&scatter_build->get<0>());
   join->buildScatter += move(scatter_build);
   return *this;
}

QueryBuilder::HashJoinBuilder&
QueryBuilder::HashJoinBuilder::addBuildKey(DS col, DS sel, primitives::F3 hash,
                                           primitives::FScatterSel scatter) {

   auto entryOffset = join->ht_entry_size;
   keyOffsets.push_back(entryOffset);
   join->ht_entry_size += col.data_size;

   // create hash primitive for build side
   auto hash_build = make_unique<F3_Op>(sel, buildHashBuffer, col, hash);
   sel.registerDS(&hash_build->outputSelectionV);
   col.registerDS(&hash_build->param2);
   join->buildHash.ops.push_back(move(hash_build));

   // build scatter
   auto scatter_build = make_unique<FScatterSelOp>(
       scatter, sel, col, reinterpret_cast<void**>(&join->scatterStart),
       &join->ht_entry_size, entryOffset);
   col.registerDS(&scatter_build->get<1>());
   join->buildScatter += move(scatter_build);
   return *this;
}

QueryBuilder::HashJoinBuilder&
QueryBuilder::HashJoinBuilder::addProbeKey(DS col, primitives::F2 hash,
                                           primitives::EQCheck eq) {
   if (probeHasSelection)
      throw runtime_error("Probe key without selection vector was added, but "
                          "join uses selection vector");
   auto entryOffset = keyOffsets.front();
   keyOffsets.pop_front();

   // create hash primitive for probe side
   auto hash_probe = make_unique<F2_Op>(probeHashBuffer, col, hash);
   col.registerDS(&hash_probe->param1);
   join->probeHash.ops.push_back(move(hash_probe));
   join->probeHashes =
       reinterpret_cast<runtime::Hashmap::hash_t*>(probeHashBuffer);

   // key equality
   auto keyEq = make_unique<EqualityCheck>(
       eq, (void**)join->buildMatches, entryOffset, join->probeMatches, col);
   col.registerDS(&keyEq->probeData);
   join->keyEquality.ops.push_back(move(keyEq));

   return *this;
}

QueryBuilder::HashJoinBuilder&
QueryBuilder::HashJoinBuilder::addProbeKey(DS col, DS sel, primitives::F3 hash,
                                           primitives::EQCheck eq) {
   if (!probeHasSelection)
      throw runtime_error("Probe key with selection vector was added, but "
                          "join doesn't use selection vector");
   auto entryOffset = keyOffsets.front();
   keyOffsets.pop_front();

   // create hash primitive for probe side
   auto hash_probe = make_unique<F3_Op>(sel, probeHashBuffer, col, hash);
   sel.registerDS(&hash_probe->outputSelectionV);
   col.registerDS(&hash_probe->param2);
   join->probeHash.ops.push_back(move(hash_probe));
   join->probeHashes =
       reinterpret_cast<runtime::Hashmap::hash_t*>(probeHashBuffer);

   // key equality
   auto keyEq = make_unique<EqualityCheck>(
       eq, (void**)join->buildMatches, entryOffset, join->probeMatches, col);
   col.registerDS(&keyEq->probeData);
   join->keyEquality.ops.push_back(move(keyEq));

   return *this;
}

QueryBuilder::HashJoinBuilder&
QueryBuilder::HashJoinBuilder::addProbeKey(DS col, DS sel, primitives::F3 hash,
                                           DS selEq, primitives::EQCheck eq) {
   auto entryOffset = keyOffsets.front();
   keyOffsets.pop_front();

   // create hash primitive for probe side
   auto hash_probe = make_unique<F3_Op>(sel, probeHashBuffer, col, hash);
   sel.registerDS(&hash_probe->outputSelectionV);
   col.registerDS(&hash_probe->param2);
   join->probeHash.ops.push_back(move(hash_probe));
   join->probeHashes =
       reinterpret_cast<runtime::Hashmap::hash_t*>(probeHashBuffer);

   // key equality
   auto keyEq = make_unique<EqualityCheck>(eq, (void**)join->buildMatches,
                                           entryOffset, selEq, col);
   selEq.registerDS((void**)&keyEq->probeIdxs);
   col.registerDS(&keyEq->probeData);
   join->keyEquality.ops.push_back(move(keyEq));

   return *this;
}

QueryBuilder::HashJoinBuilder& QueryBuilder::HashJoinBuilder::addBuildValue(
    DS source, primitives::FScatter scatter, DS target,
    primitives::FGather gather) {
   auto entryOffset = join->ht_entry_size;
   join->ht_entry_size += source.data_size;

   // build scatter
   auto scatter_build = make_unique<FScatterOp>(
       scatter, source, reinterpret_cast<void**>(&join->scatterStart),
       &join->ht_entry_size, entryOffset);
   source.registerDS(&scatter_build->get<0>());
   join->buildScatter += move(scatter_build);
   // gather
   auto gather_build = make_unique<GatherOpCol>(
       gather, (void**)join->buildMatches, entryOffset, target);
   join->buildGather.ops.push_back(move(gather_build));
   return *this;
}

QueryBuilder::HashJoinBuilder& QueryBuilder::HashJoinBuilder::addBuildValue(
    DS source, DS sel, primitives::FScatterSel scatter, DS target,
    primitives::FGather gather) {

   auto entryOffset = join->ht_entry_size;
   join->ht_entry_size += source.data_size;

   // build scatter
   auto scatter_build = make_unique<FScatterSelOp>(
       scatter, sel, source, reinterpret_cast<void**>(&join->scatterStart),
       &join->ht_entry_size, entryOffset);
   source.registerDS(&scatter_build->get<1>());
   join->buildScatter += move(scatter_build);
   // gather
   auto gather_build = make_unique<GatherOpCol>(
       gather, (void**)join->buildMatches, entryOffset, target);
   join->buildGather.ops.push_back(move(gather_build));
   return *this;
}

QueryBuilder::HashJoinBuilder&
QueryBuilder::HashJoinBuilder::setProbeSelVector(DS sel,
                                                 pos_t (Hashjoin::*joinFun)()) {
   if (join->probeHash.ops.size())
      throw runtime_error("Probe selection vector was added when probe keys "
                          "were already present");
   join->probeSel = sel;
   join->join = joinFun;
   probeHasSelection = true;
   return *this;
}

QueryBuilder::HashJoinBuilder&
QueryBuilder::HashJoinBuilder::pushProbeSelVector(DS sel, DS target) {
   if (probeHasSelection)
      throw runtime_error("Pushing a probe selection vector is in conflict "
                          "with first setting a probe selection vector.");
   // add lookup to keys_equal
   auto lookup = move(base.Expression().addOp(
       primitives::lookup_sel, target, base.Value(join->probeMatches), sel));
   join->keyEquality.ops.push_back(move(lookup.expression->ops.back()));
   return *this;
}

QueryBuilder::HashGroupBuilder::HashGroupBuilder(QueryBuilder& b) : base(b) {}

QueryBuilder::HashGroupBuilder QueryBuilder::HashGroup() {
   HashGroupBuilder b(*this);
   auto nr = nextOpNr();
   auto& s = operatorState.get<HashGroup::Shared>(nr);
   auto gr = make_unique<class HashGroup>(s);
   b.group = gr.get();
   gr->vecSize = vecs.getVecSize();
   gr->groupStore.setSource(&runtime::this_worker->allocator);

   auto& op = *gr;
   op.groupHt =
       make_unique<runtime::HashmapSmall<pos_t, pos_t>>(vecs.getVecSize());
   // --- set up preAggregation
   auto& local = op.preAggregation;
   local.ht_entry_size = sizeof(runtime::Hashmap::EntryHeader);
   local.groupHashes = static_cast<runtime::Hashmap::hash_t*>(
       vecs.get(8 /*sizeof(runtime::Hashmap::hash_t)*/));
   local.htMatches = static_cast<runtime::Hashmap::EntryHeader**>(
       vecs.get(sizeof(runtime::Hashmap::EntryHeader*)));
   local.groupsFound = static_cast<pos_t*>(vecs.get(sizeof(pos_t)));
   local.groupsNotFound =
       reinterpret_cast<SizeBuffer<pos_t>*>(vecs.getSizeBuffer(sizeof(pos_t)));
   local.keysNEq =
       reinterpret_cast<SizeBuffer<pos_t>*>(vecs.getSizeBuffer(sizeof(pos_t)));
   local.partitionEndsIn = static_cast<pos_t*>(vecs.get(sizeof(pos_t)));
   local.partitionEndsOut = static_cast<pos_t*>(vecs.get(sizeof(pos_t)));
   // set input for partitioning to groupsNotFound so that output of lookup is
   // transferred to partitioning
   local.unpartitionedRows = local.groupsNotFound->data();
   local.partitionedRows = static_cast<pos_t*>(vecs.get(sizeof(pos_t)));
   local.groupRepresentatives = static_cast<pos_t*>(vecs.get(sizeof(pos_t)));

   b.localLookup.partitionEndsIn = local.partitionEndsIn;
   b.localLookup.partitionEndsOut = local.partitionEndsOut;
   b.localLookup.unpartitionedRows = local.unpartitionedRows;
   b.localLookup.partitionedRows = local.partitionedRows;

   // --- set up global aggregation
   auto& global = op.globalAggregation;
   global.ht_entry_size = sizeof(runtime::Hashmap::EntryHeader);
   global.groupHashes = local.groupHashes;
   global.htMatches = local.htMatches;
   global.groupsFound = local.groupsFound;
   global.groupsNotFound = local.groupsNotFound;
   global.keysNEq = local.keysNEq;
   global.partitionEndsIn = local.partitionEndsIn;
   global.partitionEndsOut = local.partitionEndsOut;
   // set input for partitioning to groupsNotFound so that output of lookup is
   // transferred to partitioning
   global.unpartitionedRows = global.groupsNotFound->data();
   global.partitionedRows = local.partitionedRows;
   global.groupRepresentatives = local.groupRepresentatives;

   // buffers are shared with local lookups buffers, because local aggregation
   // and global aggregation never work at the same time
   b.globalLookup.partitionEndsIn = local.partitionEndsIn;
   b.globalLookup.partitionEndsOut = local.partitionEndsOut;
   b.globalLookup.unpartitionedRows = local.unpartitionedRows;
   b.globalLookup.partitionedRows = local.partitionedRows;

   // scatter hash
   auto scatter_build = make_unique<FScatterSelOp>(
       primitives::scatter_sel_hash_t_col, Value(local.groupRepresentatives),
       Value(local.groupHashes), reinterpret_cast<void**>(&local.scatterStart),
       &local.ht_entry_size, offsetof(runtime::Hashmap::EntryHeader, hash));
   local.buildScatter += move(scatter_build);

   auto scatter_build_global = make_unique<FScatterSelRowOp>(
       primitives::scatter_sel_row_hash_t_col,
       Value(global.groupRepresentatives), &global.rowData, &global.rowSize, 0,
       reinterpret_cast<void**>(&global.scatterStart), &global.ht_entry_size,
       offsetof(runtime::Hashmap::EntryHeader, hash));
   global.buildScatter += move(scatter_build_global);

   op.child = popOperator();
   pushOperator(move(gr));
   return b;
}

QueryBuilder::HashGroupBuilder::~HashGroupBuilder() {

   // set partitioning buffers in operator
   // This way, op will know the actual output pointers
   auto& op = *group;
   auto& local = op.preAggregation;
   auto& global = op.globalAggregation;
   local.partitionEndsOut = localLookup.partitionEndsIn;
   local.partitionedRows = localLookup.unpartitionedRows;
   global.partitionEndsOut = globalLookup.partitionEndsIn;
   global.partitionedRows = globalLookup.unpartitionedRows;

   // round up ht_entry_size to next 8 aligned value
   local.ht_entry_size += padding(local.ht_entry_size, 8);
   global.ht_entry_size += padding(local.ht_entry_size, 8);

   // create spillStorage for this thread
   // use 8 * <number of workers> partitions

   // next pointer is not copied to spillStorage
   auto rowSize =
       local.ht_entry_size - sizeof(runtime::Hashmap::EntryHeader::next);
   // TODO: this seems wrong!
   auto& spill = op.shared.spillStorage.create(
       runtime::this_worker->group->size * 4, rowSize);
   op.nrPartitions = spill.getPartitions().size();
   global.rowSize = rowSize;
}

QueryBuilder::HashGroupBuilder& QueryBuilder::HashGroupBuilder::addKey(
    DS col, primitives::F2 hash,
    /**** global aggr *****/
    primitives::NEQCheck eq, primitives::FPartitionByKey partitionByKey,
    primitives::FScatterSel scatter,
    /**** global aggr *****/
    primitives::NEQCheckRow eqG, primitives::FPartitionByKeyRow partitionByKeyG,
    primitives::FScatterSelRow scatterG,
    /**** output *****/
    primitives::FGatherVal gather, DS out) {
   auto& op = *this->group;
   auto& local = op.preAggregation;
   auto& global = op.globalAggregation;
   auto entryOffset = local.ht_entry_size;
   local.ht_entry_size += col.data_size;
   global.ht_entry_size += col.data_size;

   auto partitionOffset =
       entryOffset - sizeof(runtime::Hashmap::EntryHeader::next);

   op.groupHash +=
       base.Expression().addOp(hash, base.Value(local.groupHashes), col);

   auto neqCheck = make_unique<NEqualityCheck>(
       eq, local.groupsFound, reinterpret_cast<void**>(local.htMatches), col,
       entryOffset, local.keysNEq);
   col.registerDS(&neqCheck->probeKey);
   local.keyEquality += move(neqCheck);

   auto neqCheckGlobal = make_unique<NEQCheckRowOp>(
       eqG, global.groupsFound, reinterpret_cast<void**>(global.htMatches),
       &global.rowData, entryOffset, &global.rowSize, partitionOffset,
       global.keysNEq);
   global.keyEquality += move(neqCheckGlobal);

   auto partition = make_unique<FPartitionByKeyOp>(
       partitionByKey, localLookup.unpartitionedRows, col, local.groupHashes,
       localLookup.partitionEndsIn, localLookup.partitionedRows,
       localLookup.partitionEndsOut, op.groupHt.get());
   col.registerDS(&partition->get<1>());
   local.partitionKeys += move(partition);
   // swap buffers so that next key reads output of this partition primitive
   std::swap(localLookup.partitionEndsIn, localLookup.partitionEndsOut);
   std::swap(localLookup.unpartitionedRows, localLookup.partitionedRows);

   auto partitionGlobal = make_unique<FPartitionByKeyRowOp>(
       partitionByKeyG, globalLookup.unpartitionedRows, &global.rowData, 0,
       &global.rowSize, partitionOffset, globalLookup.partitionEndsIn,
       globalLookup.partitionedRows, globalLookup.partitionEndsOut,
       op.groupHt.get());
   global.partitionKeys += move(partitionGlobal);
   // swap buffers so that next key reads output of this partition primitive
   std::swap(globalLookup.partitionEndsIn, globalLookup.partitionEndsOut);
   std::swap(globalLookup.unpartitionedRows, globalLookup.partitionedRows);

   auto scatter_build = make_unique<FScatterSelOp>(
       scatter, base.Value(local.groupRepresentatives), col,
       reinterpret_cast<void**>(&local.scatterStart), &local.ht_entry_size,
       entryOffset);
   col.registerDS(&scatter_build->get<1>());
   local.buildScatter += move(scatter_build);

   auto scatter_build_global = make_unique<FScatterSelRowOp>(
       scatterG, base.Value(global.groupRepresentatives), &global.rowData,
       &global.rowSize, partitionOffset,
       reinterpret_cast<void**>(&global.scatterStart), &global.ht_entry_size,
       entryOffset);
   global.buildScatter += move(scatter_build_global);

   auto gather_groups = make_unique<GatherOpVal>(
       gather, reinterpret_cast<void**>(global.htMatches), entryOffset,
       &global.ht_entry_size, out);
   op.gatherGroups.ops.push_back(move(gather_groups));
   return *this;
}

QueryBuilder::HashGroupBuilder& QueryBuilder::HashGroupBuilder::addKey(
    /**** input *****/
    DS col, DS sel, primitives::F3 hash,
    /**** local aggr *****/
    primitives::NEQCheckSel eq, primitives::FPartitionByKeySel partitionByKey,
    DS selScat, primitives::FScatterSel scatter,
    /**** global aggr *****/
    primitives::NEQCheckRow eqG, primitives::FPartitionByKeyRow partitionByKeyG,
    primitives::FScatterSelRow scatterG,
    /**** output *****/
    primitives::FGatherVal gather, DS out) {

   auto& op = *this->group;
   auto& local = op.preAggregation;
   auto& global = op.globalAggregation;
   auto entryOffset = local.ht_entry_size;
   local.ht_entry_size += col.data_size;
   global.ht_entry_size += col.data_size;

   auto partitionOffset =
       entryOffset - sizeof(runtime::Hashmap::EntryHeader::next);

   op.groupHash +=
       base.Expression().addOp(hash, sel, base.Value(local.groupHashes), col);

   auto neqCheck = make_unique<NEqualityCheckSel>(
       eq, local.groupsFound, reinterpret_cast<void**>(local.htMatches), sel,
       col, entryOffset, local.keysNEq);
   sel.registerDS(&neqCheck->probeSel);
   col.registerDS(&neqCheck->probeKey);
   local.keyEquality += move(neqCheck);

   auto neqCheckGlobal = make_unique<NEQCheckRowOp>(
       eqG, global.groupsFound, reinterpret_cast<void**>(global.htMatches),
       &global.rowData, entryOffset, &global.rowSize, partitionOffset,
       global.keysNEq);
   global.keyEquality += move(neqCheckGlobal);

   auto partition = make_unique<FPartitionByKeySelOp>(
       partitionByKey, localLookup.unpartitionedRows, sel, col,
       local.groupHashes, localLookup.partitionEndsIn,
       localLookup.partitionedRows, localLookup.partitionEndsOut,
       op.groupHt.get());
   col.registerDS(&partition->get<2>());
   local.partitionKeys += move(partition);
   // swap buffers so that next key reads output of this partition primitive
   std::swap(localLookup.partitionEndsIn, localLookup.partitionEndsOut);
   std::swap(localLookup.unpartitionedRows, localLookup.partitionedRows);

   auto partitionGlobal = make_unique<FPartitionByKeyRowOp>(
       partitionByKeyG, globalLookup.unpartitionedRows, &global.rowData, 0,
       &global.rowSize, partitionOffset, globalLookup.partitionEndsIn,
       globalLookup.partitionedRows, globalLookup.partitionEndsOut,
       op.groupHt.get());
   global.partitionKeys += move(partitionGlobal);
   // swap buffers so that next key reads output of this partition primitive
   std::swap(globalLookup.partitionEndsIn, globalLookup.partitionEndsOut);
   std::swap(globalLookup.unpartitionedRows, globalLookup.partitionedRows);

   auto scatter_build = make_unique<FScatterSelOp>(
       scatter, selScat, col, reinterpret_cast<void**>(&local.scatterStart),
       &local.ht_entry_size, entryOffset);
   col.registerDS(&scatter_build->get<1>());
   local.buildScatter += move(scatter_build);

   auto scatter_build_global = make_unique<FScatterSelRowOp>(
       scatterG, base.Value(global.groupRepresentatives), &global.rowData,
       &global.rowSize, partitionOffset,
       reinterpret_cast<void**>(&global.scatterStart), &global.ht_entry_size,
       entryOffset);
   global.buildScatter += move(scatter_build_global);

   auto gather_groups = make_unique<GatherOpVal>(
       gather, reinterpret_cast<void**>(global.htMatches), entryOffset,
       &global.ht_entry_size, out);
   op.gatherGroups.ops.push_back(move(gather_groups));
   return *this;
}

QueryBuilder::HashGroupBuilder& QueryBuilder::HashGroupBuilder::addValue(
    DS col, primitives::FAggrInit aggrInit, primitives::FAggr aggr,
    primitives::FAggrRow aggrGlobal, primitives::FGatherVal gather, DS out) {

   auto& op = *this->group;
   auto& local = op.preAggregation;
   auto& global = op.globalAggregation;
   auto entryOffset = local.ht_entry_size;
   local.ht_entry_size += col.data_size;
   global.ht_entry_size += col.data_size;

   auto partitionOffset =
       entryOffset - sizeof(runtime::Hashmap::EntryHeader::next);

   auto aggregateInitOp = make_unique<FAggrInitOp>(
       aggrInit, reinterpret_cast<void**>(&local.scatterStart),
       &local.ht_entry_size, entryOffset);
   local.buildScatter += move(aggregateInitOp);

   auto aggregateInitGlobalOp = make_unique<FAggrInitOp>(
       aggrInit, reinterpret_cast<void**>(&global.scatterStart),
       &global.ht_entry_size, entryOffset);
   global.buildScatter += move(aggregateInitGlobalOp);

   auto aggr_op = make_unique<FAggrOp>(
       aggr, reinterpret_cast<void**>(local.htMatches), col, entryOffset);
   col.registerDS(&aggr_op->get<1>());
   op.updateGroups += move(aggr_op);

   auto aggrGlobal_op = make_unique<FAggrRowOp>(
       aggrGlobal, reinterpret_cast<void**>(global.htMatches), entryOffset,
       &global.rowData, &global.rowSize, partitionOffset);
   op.updateGroupsFromPartition += move(aggrGlobal_op);

   auto gather_groups = make_unique<GatherOpVal>(
       gather, reinterpret_cast<void**>(global.htMatches), entryOffset,
       &global.ht_entry_size, out);
   op.gatherGroups.ops.push_back(move(gather_groups));
   return *this;
}

QueryBuilder::HashGroupBuilder& QueryBuilder::HashGroupBuilder::addValue(
    DS col, DS sel, primitives::FAggrInit aggrInit, primitives::FAggrSel aggr,
    primitives::FAggrRow aggrGlobal, primitives::FGatherVal gather, DS out) {

   auto& op = *this->group;
   auto& local = op.preAggregation;
   auto& global = op.globalAggregation;
   auto entryOffset = local.ht_entry_size;
   local.ht_entry_size += col.data_size;
   global.ht_entry_size += col.data_size;

   auto partitionOffset =
       entryOffset - sizeof(runtime::Hashmap::EntryHeader::next);

   auto aggregateInitOp = make_unique<FAggrInitOp>(
       aggrInit, reinterpret_cast<void**>(&local.scatterStart),
       &local.ht_entry_size, entryOffset);
   local.buildScatter += move(aggregateInitOp);

   auto aggregateInitGlobalOp = make_unique<FAggrInitOp>(
       aggrInit, reinterpret_cast<void**>(&global.scatterStart),
       &global.ht_entry_size, entryOffset);
   global.buildScatter += move(aggregateInitGlobalOp);

   auto aggr_op = make_unique<FAggrSelOp>(
       aggr, reinterpret_cast<void**>(local.htMatches), sel, col, entryOffset);
   sel.registerDS(&aggr_op->get<1>());
   col.registerDS(&aggr_op->get<2>());
   op.updateGroups += move(aggr_op);

   auto aggrGlobal_op = make_unique<FAggrRowOp>(
       aggrGlobal, reinterpret_cast<void**>(global.htMatches), entryOffset,
       &global.rowData, &global.rowSize, partitionOffset);
   op.updateGroupsFromPartition += move(aggrGlobal_op);

   auto gather_groups = make_unique<GatherOpVal>(
       gather, reinterpret_cast<void**>(global.htMatches), entryOffset,
       &global.ht_entry_size, out);
   op.gatherGroups.ops.push_back(move(gather_groups));
   return *this;
}

QueryBuilder::HashGroupBuilder&
QueryBuilder::HashGroupBuilder::pushKeySelVec(DS sel, DS outBuf) {
   // add lookup to keys_equal
   auto lookup = move(base.Expression().addOp(
       primitives::lookup_sel, outBuf,
       base.Value(group->preAggregation.groupRepresentatives), sel));
   group->preAggregation.buildScatter += move(lookup);
   return *this;
}

QueryBuilder::HashGroupBuilder&
QueryBuilder::HashGroupBuilder::padToAlign(size_t align) {
   group->preAggregation.ht_entry_size +=
       padding(group->preAggregation.ht_entry_size, align);
   group->globalAggregation.ht_entry_size +=
       padding(group->globalAggregation.ht_entry_size, align);
   return *this;
}
} // namespace vectorwise
