#ifndef FASTLANES_FOR_HPP
#define FASTLANES_FOR_HPP

#include "fast_lanes/common/common.hpp"
#include "fmt/printf.h"
#include <iostream>
#include <stdio.h>

namespace fast_lanes {
template <typename T>
void FOR(T* des_p, T* data_p, T* reference_p) {
	assert(des_p != nullptr);
	assert(data_p != nullptr);
	assert(reference_p != nullptr);

	/* Actual computation. */
	duckdb_fmt::print(std::cerr, "{}:{}__{} executed!\n", __FILE__, __LINE__, __func__); /* Debug. */
	//	T reference = &reference_p;                                                        /* Load reference. */
}
} // namespace fast_lanes

#endif // FASTLANES_FOR_HPP
