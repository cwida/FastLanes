#include "vectorwise/Operations.hpp"

namespace vectorwise {

pos_t Expression::evaluate(pos_t n) {
   pos_t found = n;
   for (auto& op : ops) { found = op->run(found); }
   return found;
}

void Expression::operator+=(std::unique_ptr<Expression> other) {
   for (auto& op : other->ops) { ops.push_back(move(op)); }
   other->ops.clear();
}
void Expression::operator+=(std::unique_ptr<Op>&& op) {
   ops.push_back(move(op));
}

void Aggregates::operator+=(std::unique_ptr<Expression> other) {
   for (auto& op : other->ops) { ops.push_back(move(op)); }
   other->ops.clear();
}
void Aggregates::operator+=(std::unique_ptr<Op>&& op) {
   ops.push_back(move(op));
}

pos_t Aggregates::evaluate(pos_t n) {
   auto found = 0;
   for (auto& aggr : ops) found = aggr->run(n);
   return found;
}

Scatter::ScatterInfo::ScatterInfo(std::unique_ptr<Op>&& operation, void** s,
                                  size_t off)
    : op(move(operation)), start(s), offset(off) {}

pos_t Scatter::evaluate(pos_t n, void* start) {
   for (auto& scat : ops) {
      *scat.start = reinterpret_cast<uint8_t*>(start) + scat.offset;
      scat.op->run(n);
   }
   return n;
}

GatherOpCol::GatherOpCol(primitives::FGather o, void** s, size_t off, void* t)
    : op(o), source(s), offset(off), target(t) {}

pos_t GatherOpCol::run(pos_t n) { return op(n, source, offset, target); }

GatherOpVal::GatherOpVal(primitives::FGatherVal o, void** s, size_t off,
                         size_t* s_s, void* t)
    : op(o), sourceStart(s), offset(off), struct_size(s_s), target(t) {}

pos_t GatherOpVal::run(pos_t n) {
   return op(n, sourceStart, offset, struct_size, target);
}

EqualityCheck::EqualityCheck(primitives::EQCheck p, void** ptrs, size_t off,
                             pos_t* probeI, void* probeD)
    : prim(p), pointers(ptrs), offset(off), probeIdxs(probeI),
      probeData(probeD) {}

pos_t EqualityCheck::run(pos_t n) {
   return prim(n, pointers, offset, probeIdxs, probeData);
}
NEqualityCheck::NEqualityCheck(primitives::NEQCheck e, pos_t* en, void** entr,
                               void* p, size_t off, SizeBuffer<pos_t>* nEq)
    : eq(e), entryIdx(en), entry(entr), probeKey(p), offset(off), notEq(nEq) {}

pos_t NEqualityCheck::run(pos_t n) {
   return eq(n, entryIdx, entry, probeKey, offset, notEq);
}

NEqualityCheckSel::NEqualityCheckSel(primitives::NEQCheckSel e, pos_t* idx,
                                     void** entr, pos_t* prob, void* probeK,
                                     size_t off, SizeBuffer<pos_t>* nEq)
    : eq(e), entryIdx(idx), entry(entr), probeSel(prob), probeKey(probeK),
      offset(off), notEq(nEq){};

pos_t NEqualityCheckSel::run(pos_t n) {
   return eq(n, entryIdx, entry, probeSel, probeKey, offset, notEq);
}

pos_t F1_Op::run(pos_t n) { return operation(n, input); }
pos_t F2_Op::run(pos_t n) { return operation(n, input, param1); }
pos_t F3_Op::run(pos_t n) {
   return operation(n, outputSelectionV, param1, param2);
}
pos_t F4_Op::run(pos_t n) {
   return operation(n, inputSelectionV, outputSelectionV, param1, param2);
}
}
