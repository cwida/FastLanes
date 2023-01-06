add_library(rle OBJECT
            rle_src.cpp)
target_compile_definitions(rle PRIVATE IS_SCALAR)
set(FLAG -mavx512bw -fno-builtin)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if(HAS_FLAG)
else()
 message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif()
target_compile_options(rle PUBLIC ${FLAG})
cmake_print_properties(TARGETS rle
                       PROPERTIES COMPILE_DEFINITIONS
                       PROPERTIES COMPILE_OPTIONS)
LIST(APPEND FLS_GENERATED_OBJECT_FILES
     $<TARGET_OBJECTS:rle>)
get_target_property(TARGET_NAME rle NAME)
get_target_property(TARGET_COMPILE_OPTIONS rle COMPILE_OPTIONS)
#-----------------------------------------------------------------------------------------------------------------------
add_executable(rle_test rle_test.cpp)
target_link_libraries(rle_test PRIVATE rle)
target_link_libraries(rle_test PRIVATE test_bench_helper)
target_link_libraries(rle_test PRIVATE gtest_main)
target_include_directories(rle_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
gtest_discover_tests(rle_test)
#-----------------------------------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/fls_bench/fls_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/rle_bench.hpp)
add_executable(rle_bench rle_bench.cpp)
target_link_libraries(rle_bench PRIVATE test_bench_helper)
target_include_directories(rle_bench PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_compile_options(rle_bench PUBLIC -mavx512bw)
#add_fls_benchmark(rle_bench)
#-----------------------------------------------------------------------------------------------------------------------
