add_library(x86_64_avx2_intrinsic_1024_uf1_unpack OBJECT
            x86_64_avx2_intrinsic_1024_uf1_unpack_src.cpp)
target_compile_definitions(x86_64_avx2_intrinsic_1024_uf1_unpack PRIVATE IS_SCALAR)
set(FLAG -mavx2 -fno-builtin)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if(HAS_FLAG)
else()
 message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif()
target_compile_options(x86_64_avx2_intrinsic_1024_uf1_unpack PUBLIC ${FLAG})
cmake_print_properties(TARGETS x86_64_avx2_intrinsic_1024_uf1_unpack
                       PROPERTIES COMPILE_DEFINITIONS
                       PROPERTIES COMPILE_OPTIONS)
LIST (APPEND FLS_GENERATED_OBJECT_FILES
      $<TARGET_OBJECTS:x86_64_avx2_intrinsic_1024_uf1_unpack>)
get_target_property(TARGET_NAME x86_64_avx2_intrinsic_1024_uf1_unpack NAME)
get_target_property(TARGET_COMPILE_OPTIONS x86_64_avx2_intrinsic_1024_uf1_unpack COMPILE_OPTIONS)
#------------------------------------------------------------------------------------------------------
add_executable(x86_64_avx2_intrinsic_1024_uf1_unpack_test x86_64_avx2_intrinsic_1024_uf1_unpack_test.cpp)
target_link_libraries(x86_64_avx2_intrinsic_1024_uf1_unpack_test PRIVATE x86_64_avx2_intrinsic_1024_uf1_unpack)
target_link_libraries(x86_64_avx2_intrinsic_1024_uf1_unpack_test PRIVATE test_bench_helper)
target_link_libraries(x86_64_avx2_intrinsic_1024_uf1_unpack_test PRIVATE gtest_main)
target_include_directories(x86_64_avx2_intrinsic_1024_uf1_unpack_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
gtest_discover_tests(x86_64_avx2_intrinsic_1024_uf1_unpack_test)
#------------------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/fls_bench/fls_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/x86_64_avx2_intrinsic_1024_uf1_unpack_bench.hpp)
add_executable(x86_64_avx2_intrinsic_1024_uf1_unpack_bench x86_64_avx2_intrinsic_1024_uf1_unpack_bench.cpp)
target_link_libraries(x86_64_avx2_intrinsic_1024_uf1_unpack_bench PRIVATE x86_64_avx2_intrinsic_1024_uf1_unpack)
target_link_libraries(x86_64_avx2_intrinsic_1024_uf1_unpack_bench PRIVATE test_bench_helper)
target_include_directories(x86_64_avx2_intrinsic_1024_uf1_unpack_bench PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
add_fls_benchmark(x86_64_avx2_intrinsic_1024_uf1_unpack_bench)
