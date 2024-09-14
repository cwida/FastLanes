add_library(helper_scalar_av_1024_uf1_transpose OBJECT
            helper_scalar_av_1024_uf1_transpose_src.cpp)
target_compile_definitions(helper_scalar_av_1024_uf1_transpose PRIVATE IS_SCALAR)
set(FLAG -Rpass-analysis=loop-vectorize)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if(HAS_FLAG)
else()
 message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif()
target_compile_options(helper_scalar_av_1024_uf1_transpose PUBLIC ${FLAG})
cmake_print_properties(TARGETS helper_scalar_av_1024_uf1_transpose
                       PROPERTIES COMPILE_DEFINITIONS
                       PROPERTIES COMPILE_OPTIONS)
LIST (APPEND FLS_GENERATED_OBJECT_FILES
      $<TARGET_OBJECTS:helper_scalar_av_1024_uf1_transpose>)
get_target_property(TARGET_NAME helper_scalar_av_1024_uf1_transpose NAME)
get_target_property(TARGET_COMPILE_OPTIONS helper_scalar_av_1024_uf1_transpose COMPILE_OPTIONS)
#------------------------------------------------------------------------------------------------------
add_executable(helper_scalar_av_1024_uf1_transpose_test helper_scalar_av_1024_uf1_transpose_test.cpp)
target_link_libraries(helper_scalar_av_1024_uf1_transpose_test PRIVATE helper_scalar_av_1024_uf1_transpose)
target_link_libraries(helper_scalar_av_1024_uf1_transpose_test PRIVATE test_bench_helper)
target_link_libraries(helper_scalar_av_1024_uf1_transpose_test PRIVATE gtest_main)
target_include_directories(helper_scalar_av_1024_uf1_transpose_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
gtest_discover_tests(helper_scalar_av_1024_uf1_transpose_test)
#-------------------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/fls_bench/fls_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/helper_scalar_av_1024_uf1_transpose_bench.hpp)
add_executable(helper_scalar_av_1024_uf1_transpose_bench helper_scalar_av_1024_uf1_transpose_bench.cpp)
target_link_libraries(helper_scalar_av_1024_uf1_transpose_bench PRIVATE helper_scalar_av_1024_uf1_transpose)
target_link_libraries(helper_scalar_av_1024_uf1_transpose_bench PRIVATE test_bench_helper)
target_include_directories(helper_scalar_av_1024_uf1_transpose_bench PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
add_fls_benchmark(helper_scalar_av_1024_uf1_transpose_bench)
