#include <cstdint>
#include <thread>
#include <iostream>
#include "benchmarks/Primitives.hpp"
#include "common/runtime/Barrier.hpp"

using namespace std;

static void clobber() {
  asm volatile("" : : : "memory");
}

struct Input{
  std::vector<uint64_t> data;
  uint64_t* out;
  std::vector<uint64_t> outCount;
  Input(size_t n):data(n), outCount(n){};
};

std::vector<Input> inputs;

void prepare(size_t n, size_t nrPartitions){
  inputs.emplace_back(n);
  auto& i = inputs.back();
  i.out = new uint64_t[nrPartitions * n];
  putRandom(i.data.data(), n, 0, ~0);
}

const size_t nrParts = 1024;

void run(Input& i, size_t nrPartitions){
  auto mask = nrPartitions -1;
  for(auto&c : i.outCount) c = 0;
  auto c = i.outCount.data();
  for(auto& d : i.data){
    auto part = d&mask;
    auto& pos = c[part];
    i.out[part*nrParts+pos] = d;
    pos = pos+1;
  }
  clobber();
}

int main(int argc, char** argv) {
  if(argc != 3){
    cout << "Usage: " << argv[0] << " <threadCount> <nrItems>";
    return 0;
  }
  unsigned threadCount=atoi(argv[1]);
  size_t n = atoi(argv[2]);
  size_t nrPartitions = 1024;

  for(size_t i = 0; i < threadCount; i++)
    prepare(n, nrPartitions);

  PerfEvents e;
  e.timeAndProfile("writePartitions", n * threadCount,
  [&](){
      vector<thread> threads;
      threads.reserve(threadCount - 1);
      for(size_t i = 0; i < threadCount-1; i++)
        threads.emplace_back(run, std::ref(inputs[i]), nrPartitions);
      run(inputs[threadCount-1], nrPartitions);
      for(auto& t : threads) t.join();
    }, 1);
}
