add_library(fallback_unit64_nav_1024_uf1_unpack OBJECT
            fallback_unit64_nav_1024_uf1_unpack_src.cpp)
target_compile_definitions(fallback_unit64_nav_1024_uf1_unpack PRIVATE IS_SCALAR)
set(FLAG -mno-sse -fno-builtin -fno-slp-vectorize -fno-vectorize)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if(HAS_FLAG)
else()
 message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif()
target_compile_options(fallback_unit64_nav_1024_uf1_unpack PRIVATE ${FLAG})
cmake_print_properties(TARGETS fallback_unit64_nav_1024_uf1_unpack
                       PROPERTIES COMPILE_DEFINITIONS
                       PROPERTIES COMPILE_OPTIONS)
LIST (APPEND FLS_GENERATED_OBJECT_FILES
      $<TARGET_OBJECTS:fallback_unit64_nav_1024_uf1_unpack>)
get_target_property(TARGET_NAME fallback_unit64_nav_1024_uf1_unpack NAME)
get_target_property(TARGET_COMPILE_OPTIONS fallback_unit64_nav_1024_uf1_unpack COMPILE_OPTIONS)
#------------------------------------------------------------------------------------------------------
add_executable(fallback_unit64_nav_1024_uf1_unpack_test fallback_unit64_nav_1024_uf1_unpack_test.cpp)
target_link_libraries(fallback_unit64_nav_1024_uf1_unpack_test PRIVATE fallback_unit64_nav_1024_uf1_unpack)
target_link_libraries(fallback_unit64_nav_1024_uf1_unpack_test PRIVATE test_bench_helper)
target_link_libraries(fallback_unit64_nav_1024_uf1_unpack_test PRIVATE gtest_main)
target_include_directories(fallback_unit64_nav_1024_uf1_unpack_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
gtest_discover_tests(fallback_unit64_nav_1024_uf1_unpack_test)
#------------------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/fls_bench/fls_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/fallback_unit64_nav_1024_uf1_unpack_bench.hpp)
add_executable(fallback_unit64_nav_1024_uf1_unpack_bench fallback_unit64_nav_1024_uf1_unpack_bench.cpp)
target_link_libraries(fallback_unit64_nav_1024_uf1_unpack_bench PRIVATE fallback_unit64_nav_1024_uf1_unpack)
target_link_libraries(fallback_unit64_nav_1024_uf1_unpack_bench PRIVATE test_bench_helper)
target_include_directories(fallback_unit64_nav_1024_uf1_unpack_bench PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
add_fls_benchmark(fallback_unit64_nav_1024_uf1_unpack_bench)
