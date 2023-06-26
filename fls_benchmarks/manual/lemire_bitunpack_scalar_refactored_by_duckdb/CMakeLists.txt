add_library(lemire_scalar_bitunpack SHARED bitpacking.cpp)
target_compile_definitions(lemire_scalar_bitunpack PRIVATE IS_SCALAR)
set(FLAG -mno-sse -fno-builtin -fno-slp-vectorize -fno-vectorize)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if(HAS_FLAG)
else()
	message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif()
target_compile_options(lemire_scalar_bitunpack PRIVATE ${FLAG})
cmake_print_properties(TARGETS lemire_scalar_bitunpack
                       PROPERTIES COMPILE_DEFINITIONS
                       PROPERTIES COMPILE_OPTIONS)
LIST(APPEND FLS_GENERATED_OBJECT_FILES
     $<TARGET_OBJECTS:lemire_scalar_bitunpack>)
get_target_property(TARGET_NAME lemire_scalar_bitunpack NAME)
get_target_property(TARGET_COMPILE_OPTIONS lemire_scalar_bitunpack COMPILE_OPTIONS)
#-----------------------------------------------------------------------------------------------------------------------
add_executable(lemire_scalar_bitunpack_test lemire_scalar_bitunpack_test.cpp)
target_link_libraries(lemire_scalar_bitunpack_test PRIVATE lemire_scalar_bitunpack)
target_link_libraries(lemire_scalar_bitunpack_test PRIVATE gtest_main)
target_include_directories(lemire_scalar_bitunpack_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
gtest_discover_tests(lemire_scalar_bitunpack_test)
#-----------------------------------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/fls_bench/fls_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/lemire_scalar_bitunpack_bench.hpp)
add_executable(lemire_scalar_bitunpack_bench lemire_scalar_bitunpack_bench.cpp)
target_link_libraries(lemire_scalar_bitunpack_bench PRIVATE lemire_scalar_bitunpack)
target_include_directories(lemire_scalar_bitunpack_bench PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_compile_options(lemire_scalar_bitunpack_bench PUBLIC -fno-builtin -fno-slp-vectorize -fno-vectorize)

