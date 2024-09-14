add_library(helper_scalar_av_1024_uf1_untranspose OBJECT
            helper_scalar_av_1024_uf1_untranspose_src.cpp)
target_compile_definitions(helper_scalar_av_1024_uf1_untranspose PRIVATE IS_SCALAR)
set(FLAG -Rpass-analysis=loop-vectorize)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if(HAS_FLAG)
else()
 message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif()
target_compile_options(helper_scalar_av_1024_uf1_untranspose PUBLIC ${FLAG})
cmake_print_properties(TARGETS helper_scalar_av_1024_uf1_untranspose
                       PROPERTIES COMPILE_DEFINITIONS
                       PROPERTIES COMPILE_OPTIONS)
LIST (APPEND FLS_GENERATED_OBJECT_FILES
      $<TARGET_OBJECTS:helper_scalar_av_1024_uf1_untranspose>)
get_target_property(TARGET_NAME helper_scalar_av_1024_uf1_untranspose NAME)
get_target_property(TARGET_COMPILE_OPTIONS helper_scalar_av_1024_uf1_untranspose COMPILE_OPTIONS)
#------------------------------------------------------------------------------------------------------
add_executable(helper_scalar_av_1024_uf1_untranspose_test helper_scalar_av_1024_uf1_untranspose_test.cpp)
target_link_libraries(helper_scalar_av_1024_uf1_untranspose_test PRIVATE helper_scalar_av_1024_uf1_untranspose)
target_link_libraries(helper_scalar_av_1024_uf1_untranspose_test PRIVATE test_bench_helper)
target_link_libraries(helper_scalar_av_1024_uf1_untranspose_test PRIVATE gtest_main)
target_include_directories(helper_scalar_av_1024_uf1_untranspose_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
gtest_discover_tests(helper_scalar_av_1024_uf1_untranspose_test)
#-------------------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/fls_bench/fls_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/helper_scalar_av_1024_uf1_untranspose_bench.hpp)
add_executable(helper_scalar_av_1024_uf1_untranspose_bench helper_scalar_av_1024_uf1_untranspose_bench.cpp)
target_link_libraries(helper_scalar_av_1024_uf1_untranspose_bench PRIVATE helper_scalar_av_1024_uf1_untranspose)
target_link_libraries(helper_scalar_av_1024_uf1_untranspose_bench PRIVATE test_bench_helper)
target_include_directories(helper_scalar_av_1024_uf1_untranspose_bench PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
add_fls_benchmark(helper_scalar_av_1024_uf1_untranspose_bench)
