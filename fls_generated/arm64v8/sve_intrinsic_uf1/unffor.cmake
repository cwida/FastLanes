add_library(arm64v8_sve_intrinsic_1024_uf1_unffor OBJECT
            arm64v8_sve_intrinsic_1024_uf1_unffor_src.cpp)
target_compile_definitions(arm64v8_sve_intrinsic_1024_uf1_unffor PRIVATE IS_SCALAR)
set(FLAG -O3)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if(HAS_FLAG)
else()
 message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif()
target_compile_options(arm64v8_sve_intrinsic_1024_uf1_unffor PUBLIC ${FLAG})
cmake_print_properties(TARGETS arm64v8_sve_intrinsic_1024_uf1_unffor
                       PROPERTIES COMPILE_DEFINITIONS
                       PROPERTIES COMPILE_OPTIONS)
LIST (APPEND FLS_GENERATED_OBJECT_FILES
      $<TARGET_OBJECTS:arm64v8_sve_intrinsic_1024_uf1_unffor>)
get_target_property(TARGET_NAME arm64v8_sve_intrinsic_1024_uf1_unffor NAME)
get_target_property(TARGET_COMPILE_OPTIONS arm64v8_sve_intrinsic_1024_uf1_unffor COMPILE_OPTIONS)
#------------------------------------------------------------------------------------------------------
add_executable(arm64v8_sve_intrinsic_1024_uf1_unffor_test arm64v8_sve_intrinsic_1024_uf1_unffor_test.cpp)
target_link_libraries(arm64v8_sve_intrinsic_1024_uf1_unffor_test PRIVATE arm64v8_sve_intrinsic_1024_uf1_unffor)
target_link_libraries(arm64v8_sve_intrinsic_1024_uf1_unffor_test PRIVATE test_bench_helper)
target_link_libraries(arm64v8_sve_intrinsic_1024_uf1_unffor_test PRIVATE gtest_main)
target_include_directories(arm64v8_sve_intrinsic_1024_uf1_unffor_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
gtest_discover_tests(arm64v8_sve_intrinsic_1024_uf1_unffor_test)
#------------------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/fls_bench/fls_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/arm64v8_sve_intrinsic_1024_uf1_unffor_bench.hpp)
add_executable(arm64v8_sve_intrinsic_1024_uf1_unffor_bench arm64v8_sve_intrinsic_1024_uf1_unffor_bench.cpp)
target_link_libraries(arm64v8_sve_intrinsic_1024_uf1_unffor_bench PRIVATE arm64v8_sve_intrinsic_1024_uf1_unffor)
target_link_libraries(arm64v8_sve_intrinsic_1024_uf1_unffor_bench PRIVATE test_bench_helper)
target_include_directories(arm64v8_sve_intrinsic_1024_uf1_unffor_bench PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
add_fls_benchmark(arm64v8_sve_intrinsic_1024_uf1_unffor_bench)
