add_library(wasm_simd128_intrinsic_1024_uf1_unffor OBJECT
            wasm_simd128_intrinsic_1024_uf1_unffor_src.cpp)
target_compile_definitions(wasm_simd128_intrinsic_1024_uf1_unffor PRIVATE IS_SCALAR)
set(FLAG -msimd128)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if(HAS_FLAG)
else()
 message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif()
target_compile_options(wasm_simd128_intrinsic_1024_uf1_unffor PUBLIC ${FLAG})
cmake_print_properties(TARGETS wasm_simd128_intrinsic_1024_uf1_unffor
                       PROPERTIES COMPILE_DEFINITIONS
                       PROPERTIES COMPILE_OPTIONS)
LIST (APPEND FLS_GENERATED_OBJECT_FILES
      $<TARGET_OBJECTS:wasm_simd128_intrinsic_1024_uf1_unffor>)
get_target_property(TARGET_NAME wasm_simd128_intrinsic_1024_uf1_unffor NAME)
get_target_property(TARGET_COMPILE_OPTIONS wasm_simd128_intrinsic_1024_uf1_unffor COMPILE_OPTIONS)
#------------------------------------------------------------------------------------------------------
add_executable(wasm_simd128_intrinsic_1024_uf1_unffor_test wasm_simd128_intrinsic_1024_uf1_unffor_test.cpp)
target_link_libraries(wasm_simd128_intrinsic_1024_uf1_unffor_test PRIVATE wasm_simd128_intrinsic_1024_uf1_unffor)
target_link_libraries(wasm_simd128_intrinsic_1024_uf1_unffor_test PRIVATE test_bench_helper)
target_link_libraries(wasm_simd128_intrinsic_1024_uf1_unffor_test PRIVATE gtest_main)
target_include_directories(wasm_simd128_intrinsic_1024_uf1_unffor_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
gtest_discover_tests(wasm_simd128_intrinsic_1024_uf1_unffor_test)
#------------------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/fls_bench/fls_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/wasm_simd128_intrinsic_1024_uf1_unffor_bench.hpp)
add_executable(wasm_simd128_intrinsic_1024_uf1_unffor_bench wasm_simd128_intrinsic_1024_uf1_unffor_bench.cpp)
target_link_libraries(wasm_simd128_intrinsic_1024_uf1_unffor_bench PRIVATE wasm_simd128_intrinsic_1024_uf1_unffor)
target_link_libraries(wasm_simd128_intrinsic_1024_uf1_unffor_bench PRIVATE test_bench_helper)
target_include_directories(wasm_simd128_intrinsic_1024_uf1_unffor_bench PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
add_fls_benchmark(wasm_simd128_intrinsic_1024_uf1_unffor_bench)
