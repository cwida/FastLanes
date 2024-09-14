#pragma once
#include "Primitives.hpp"
#include <experimental/tuple>
#include <functional>
#include <memory>
#include <vector>

namespace vectorwise {

// TODO: Put a class hierarchy into functions: Operation, Aggregate, Scatter,
// Gather

struct Op;
class Expression {
 public:
   std::vector<std::unique_ptr<Op>> ops;
   /// Evaluate all operations of this expression
   pos_t evaluate(pos_t n);
   void operator+=(std::unique_ptr<Expression> other);
   void operator+=(std::unique_ptr<Op>&& op);
};

class Aggregates {
 public:
   std::vector<std::unique_ptr<Op>> ops;
   /// Evaluate all operations of this aggregate
   pos_t evaluate(pos_t n);
   void operator+=(std::unique_ptr<Expression> other);
   void operator+=(std::unique_ptr<Op>&& op);
};

class Scatter {
   struct ScatterInfo {
      std::unique_ptr<Op> op;
      void** start;
      size_t offset;
      ScatterInfo(std::unique_ptr<Op>&& operation, void** s, size_t off);
   };

 public:
   std::vector<ScatterInfo> ops;
   /// run scatter operations to spread to memory region pointed to by start
   pos_t evaluate(pos_t n, void* start);
};

struct Op {
   virtual pos_t run(pos_t n) = 0;
   virtual ~Op() = default;
};

template <typename> class OpArgs;

template <typename... Args>
class OpArgs<pos_t (*)(pos_t, Args...)> : public Op {
   std::function<pos_t(pos_t, Args...)> function;

 public:
   std::tuple<Args...> args;

   OpArgs(pos_t(f)(pos_t, Args...), Args... x) : function(f), args(x...) {}

   template <unsigned n> decltype(std::get<n>(args)) get() {
      return std::get<n>(args);
   }

   virtual pos_t run(pos_t n) override {
      return std::experimental::apply(function,
                                      std::tuple_cat(std::make_tuple(n), args));
   }
};

using FScatterOp = OpArgs<primitives::FScatter>;
using FScatterSelOp = OpArgs<primitives::FScatterSel>;
using FScatterSelRowOp = OpArgs<primitives::FScatterSelRow>;
using FAggrOp = OpArgs<primitives::FAggr>;
using FAggrSelOp = OpArgs<primitives::FAggrSel>;
using FAggrRowOp = OpArgs<primitives::FAggrRow>;
using FAggrInitOp = OpArgs<primitives::FAggrInit>;
using FPartitionByKeyOp = OpArgs<primitives::FPartitionByKey>;
using FPartitionByKeySelOp = OpArgs<primitives::FPartitionByKeySel>;
using FPartitionByKeyRowOp = OpArgs<primitives::FPartitionByKeyRow>;
using NEQCheckRowOp = OpArgs<primitives::NEQCheckRow>;
using F6_Op = OpArgs<primitives::F6>;
using F7_Op = OpArgs<primitives::F7>;

struct GatherOpCol : public Op {
   primitives::FGather op;
   void** source;
   size_t offset;
   void* target;
   GatherOpCol(primitives::FGather op, void** source, size_t off, void* target);
   virtual pos_t run(pos_t n) override;
};

struct GatherOpVal : public Op {
   primitives::FGatherVal op;
   void** sourceStart;
   size_t offset;
   size_t* struct_size;
   void* target;
   GatherOpVal(primitives::FGatherVal op, void** source, size_t off,
               size_t* struct_size, void* target);
   virtual pos_t run(pos_t n) override;
};

struct EqualityCheck : public Op {
   primitives::EQCheck prim;
   void** pointers;
   size_t offset;
   pos_t* probeIdxs;
   void* probeData;
   EqualityCheck(primitives::EQCheck p, void** ptrs, size_t off,
                 pos_t* probeIdxs, void* probeData);
   /// run check operations
   virtual pos_t run(pos_t n) override;
};

struct NEqualityCheck : public Op {
   primitives::NEQCheck eq;
   pos_t* entryIdx;
   void** entry;
   void* probeKey;
   size_t offset;
   SizeBuffer<pos_t>* notEq;
   NEqualityCheck(primitives::NEQCheck eq, pos_t* entryIdx, void** entry,
                  void* probeKey, size_t offset, SizeBuffer<pos_t>* notEq);
   virtual pos_t run(pos_t n) override;
};

struct NEqualityCheckSel : public Op {
   primitives::NEQCheckSel eq;
   pos_t* entryIdx;
   void** entry;
   pos_t* probeSel;
   void* probeKey;
   size_t offset;
   SizeBuffer<pos_t>* notEq;
   NEqualityCheckSel(primitives::NEQCheckSel eq, pos_t* entryIdx, void** entry,
                     pos_t* probes, void* probeKey, size_t offset,
                     SizeBuffer<pos_t>* notEq);
   virtual pos_t run(pos_t n) override;
};

struct F1_Op : public Op {
   void* input;
   primitives::F1 operation;
   F1_Op(void* i, primitives::F1 op) : input(i), operation(op) {}
   virtual pos_t run(pos_t n) override;
};

struct F2_Op : public Op {
   void* input;
   void* param1;
   primitives::F2 operation;
   F2_Op(void* i, void* p1, primitives::F2 op)
       : input(i), param1(p1), operation(op) {}
   virtual pos_t run(pos_t n) override;
};

struct F3_Op : public Op
/// selection with two params
{
   void* outputSelectionV;
   void* param1;
   void* param2;
   primitives::F3 operation;
   F3_Op(void* out, void* p1, void* p2, primitives::F3 o)
       : outputSelectionV(out), param1(p1), param2(p2), operation(o) {}
   virtual pos_t run(pos_t n) override;
};

struct F4_Op : public Op
/// selection with input select and two params
{
   void* inputSelectionV;
   void* outputSelectionV;
   void* param1;
   void* param2;
   primitives::F4 operation;
   F4_Op(void* in, void* out, void* p1, void* p2, primitives::F4 o)
       : inputSelectionV(in), outputSelectionV(out), param1(p1), param2(p2),
         operation(o) {}
   virtual pos_t run(pos_t n) override;
};
}
