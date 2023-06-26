#include "common/runtime/Concurrency.hpp"

namespace runtime {

thread_local Worker* this_worker;
thread_local bool currentBarrier = false;

WorkerGroup mainGroup(1);
HierarchicBarrier mainBarrier(1, nullptr);
GlobalPool defaultPool;
Worker mainWorker(&mainGroup, &mainBarrier, defaultPool);
} // namespace runtime
