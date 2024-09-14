#include "profile.hpp"
#include "vectorwise/Primitives.hpp"
#include "vectorwise/defs.hpp"
#include <algorithm>
#include <functional>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>


template <typename T>
void putRandom(T* v, size_t n, size_t min = 0, size_t max = 99) {
  std::mt19937 mersenne_engine(1337);
  std::uniform_int_distribution<T> dist(min, max);
  auto gen = std::bind(dist, mersenne_engine);
  for(size_t i = 0; i < n; i++)
    v[i] = gen();
}


template <typename T>
void putRandom(vectorwise::pos_t n, vectorwise::pos_t* sel, T* v, size_t min = 0,
               size_t max = 99) {
  std::mt19937 mersenne_engine(1337);
  std::uniform_int_distribution<T> dist(min, max);
  auto gen = std::bind(dist, mersenne_engine);
  for (size_t i = 0; i < n; i++) v[sel[i]] = gen();
}
