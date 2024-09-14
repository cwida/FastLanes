add_library(x86_64_sse_intrinsic_1024_uf1_rsum OBJECT
            x86_64_sse_intrinsic_1024_uf1_rsum_src.cpp)
target_compile_definitions(x86_64_sse_intrinsic_1024_uf1_rsum PRIVATE IS_SCALAR)
set(FLAG -fno-builtin)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if(HAS_FLAG)
else()
 message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif()
target_compile_options(x86_64_sse_intrinsic_1024_uf1_rsum PUBLIC ${FLAG})
cmake_print_properties(TARGETS x86_64_sse_intrinsic_1024_uf1_rsum
                       PROPERTIES COMPILE_DEFINITIONS
                       PROPERTIES COMPILE_OPTIONS)
LIST (APPEND FLS_GENERATED_OBJECT_FILES
      $<TARGET_OBJECTS:x86_64_sse_intrinsic_1024_uf1_rsum>)
get_target_property(TARGET_NAME x86_64_sse_intrinsic_1024_uf1_rsum NAME)
get_target_property(TARGET_COMPILE_OPTIONS x86_64_sse_intrinsic_1024_uf1_rsum COMPILE_OPTIONS)
#------------------------------------------------------------------------------------------------------
add_executable(x86_64_sse_intrinsic_1024_uf1_rsum_test x86_64_sse_intrinsic_1024_uf1_rsum_test.cpp)
target_link_libraries(x86_64_sse_intrinsic_1024_uf1_rsum_test PRIVATE x86_64_sse_intrinsic_1024_uf1_rsum)
target_link_libraries(x86_64_sse_intrinsic_1024_uf1_rsum_test PRIVATE test_bench_helper)
target_link_libraries(x86_64_sse_intrinsic_1024_uf1_rsum_test PRIVATE gtest_main)
target_include_directories(x86_64_sse_intrinsic_1024_uf1_rsum_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
gtest_discover_tests(x86_64_sse_intrinsic_1024_uf1_rsum_test)
#-------------------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/fls_bench/fls_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/x86_64_sse_intrinsic_1024_uf1_rsum_bench.hpp)
add_executable(x86_64_sse_intrinsic_1024_uf1_rsum_bench x86_64_sse_intrinsic_1024_uf1_rsum_bench.cpp)
target_link_libraries(x86_64_sse_intrinsic_1024_uf1_rsum_bench PRIVATE x86_64_sse_intrinsic_1024_uf1_rsum)
target_link_libraries(x86_64_sse_intrinsic_1024_uf1_rsum_bench PRIVATE test_bench_helper)
target_include_directories(x86_64_sse_intrinsic_1024_uf1_rsum_bench PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
add_fls_benchmark(x86_64_sse_intrinsic_1024_uf1_rsum_bench)
