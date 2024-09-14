// generated!
// NOLINTBEGIN
#include "fallback_scalar_aav_1024_uf1_unrsum_bench.hpp"
#include "fallback_scalar_aav_1024_uf1_unrsum_helper.hpp"
#include "fls_gen/rsum/rsum.hpp"
#include "fls_gen/rsum_and_untranspose/rsum_and_untranspose.hpp"
#include "fls_gen/transpose/transpose.hpp"
#include "fls_gen/untranspose/untranspose.hpp"
#include <iostream>
// empty
void benchmark_all(benchmark::Benchmark& benchmark) {}
int  main() {
    benchmark::Benchmark benchmark =
        benchmark::create("fallback_scalar_aav_1024_uf1_unrsum")
            .save()
            .at(std::string(SOURCE_DIR) + "/fls_pub/results/" + benchmark::CmakeInfo::getCmakeToolchainFile())
            .print()
            .add_extra_info(benchmark::CmakeInfo::getCmakeInfo());
    benchmark_all(benchmark);
}
