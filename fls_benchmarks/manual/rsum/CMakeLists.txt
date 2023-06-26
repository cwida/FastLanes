add_library(rsum OBJECT
            rsum_src.cpp)
target_compile_definitions(rsum PRIVATE IS_SCALAR)
set(FLAG -march=native -fno-builtin)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if(HAS_FLAG)
else()
	message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif()
target_compile_options(rsum PUBLIC ${FLAG})
cmake_print_properties(TARGETS rsum
                       PROPERTIES COMPILE_DEFINITIONS
                       PROPERTIES COMPILE_OPTIONS)
LIST(APPEND FLS_GENERATED_OBJECT_FILES
     $<TARGET_OBJECTS:rsum>)
get_target_property(TARGET_NAME rsum NAME)
get_target_property(TARGET_COMPILE_OPTIONS rsum COMPILE_OPTIONS)
#-----------------------------------------------------------------------------------------------------------------------
add_executable(rsum_test rsum_test.cpp)
target_link_libraries(rsum_test PRIVATE rsum)
target_link_libraries(rsum_test PRIVATE test_bench_helper)
target_link_libraries(rsum_test PRIVATE gtest_main)
target_include_directories(rsum_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
gtest_discover_tests(rsum_test)
#-----------------------------------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/fls_bench/fls_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/rsum_bench.hpp)
add_executable(rsum_bench rsum_bench.cpp)
target_link_libraries(rsum_bench PRIVATE rsum)
target_link_libraries(rsum_bench PRIVATE test_bench_helper)
target_include_directories(rsum_bench PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_compile_options(rsum_bench PUBLIC -march=native)
#add_fls_benchmark(rsum_bench)