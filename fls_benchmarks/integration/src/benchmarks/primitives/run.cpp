#include "profile.hpp"
#include "vectorwise/Primitives.hpp"
#include "vectorwise/defs.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

using namespace std;
using vectorwise::pos_t;
using namespace vectorwise::primitives;

template <typename T>
void putRandom(vector<T>& v, size_t min = 0, size_t max = 99) {
   mt19937 mersenne_engine(1337);
   uniform_int_distribution<T> dist(min, max);
   auto gen = std::bind(dist, mersenne_engine);
   generate(begin(v), end(v), gen);
}

template <typename T>
void putRandom(vector<pos_t>& sel, vector<T>& v, size_t min = 0,
               size_t max = 99) {
   mt19937 mersenne_engine(1337);
   uniform_int_distribution<T> dist(min, max);
   auto gen = std::bind(dist, mersenne_engine);
   for (auto pos : sel) v[pos] = gen();
}

#define EACH_T(M, args...) M(args, int8_t)

#define EACH_SEL(M, args...)                                                   \
   M(args, 0)                                                                  \
   M(args, 1)                                                                  \
   M(args, 5)                                                                  \
   M(args, 10) M(args, 30) M(args, 50) M(args, 65) M(args, 80) M(args, 100)

#define EACH_BF(M, args...) M(args, ) M(args, _bf)

#define BENCH_LESS(BF, TYPE, SEL)                                              \
   {                                                                           \
      vector<TYPE> input(n);                                                   \
      putRandom(input);                                                        \
      TYPE val = SEL;                                                          \
      vector<pos_t> output;                                                    \
      output.assign(n, 0);                                                     \
                                                                               \
      e.timeAndProfile("sel_lt" + string(#BF) + "\t" + string(#SEL) + "\t" +   \
                           string(#TYPE) + "\t",                               \
                       n,                                                      \
                       [&]() {                                                 \
                          sel_less_##TYPE##_col_##TYPE##_val##BF(              \
                              n, output.data(), input.data(), &val);           \
                       },                                                      \
                       repetitions);                                           \
   }

#define BENCH_LESS_SEL(BF, TYPE, SEL)                                          \
   {                                                                           \
      vector<pos_t> sel(n);                                                    \
      putRandom(sel, 0, vecSize);                                              \
      vector<TYPE> input(vecSize);                                             \
      putRandom(sel, input);                                                   \
      TYPE val = SEL;                                                          \
      vector<pos_t> output;                                                    \
      output.assign(n, 0);                                                     \
                                                                               \
      e.timeAndProfile("selsel_lt" + string(#BF) + "\t" + string(#SEL) +       \
                           "\t" + string(#TYPE) + "\t",                        \
                       n,                                                      \
                       [&]() {                                                 \
                          selsel_less_##TYPE##_col_##TYPE##_val##BF(           \
                              n, sel.data(), output.data(), input.data(),      \
                              &val);                                           \
                       },                                                      \
                       repetitions);                                           \
   }

int main() {
   size_t vecSize = 1024 * 8;
   size_t n = 1024 * 8;
   size_t repetitions = 100000;
   PerfEvents e;
   // run selection primitives with different selectivities
   EACH_BF(EACH_T, EACH_SEL, BENCH_LESS);
   n = 1024 * 4;
   EACH_BF(EACH_T, EACH_SEL, BENCH_LESS_SEL);
   return 0;
}
