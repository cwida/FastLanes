add_library(lemire_bitunpack OBJECT
            lemire_bitunpack_src.cpp)
target_compile_definitions(lemire_bitunpack PRIVATE IS_SCALAR)
set(FLAG -mavx512bw -fno-builtin)
check_cxx_compiler_flag(${FLAG} HAS_FLAG)
if(HAS_FLAG)
else()
	message(STATUS "The flag ${FLAG} is not supported by the current compiler")
endif()
target_compile_options(lemire_bitunpack PUBLIC ${FLAG})
cmake_print_properties(TARGETS lemire_bitunpack
                       PROPERTIES COMPILE_DEFINITIONS
                       PROPERTIES COMPILE_OPTIONS)
LIST(APPEND FLS_GENERATED_OBJECT_FILES
     $<TARGET_OBJECTS:lemire_bitunpack>)
get_target_property(TARGET_NAME lemire_bitunpack NAME)
get_target_property(TARGET_COMPILE_OPTIONS lemire_bitunpack COMPILE_OPTIONS)
#-----------------------------------------------------------------------------------------------------------------------
add_executable(lemire_bitunpack_test lemire_bitunpack_test.cpp)
target_link_libraries(lemire_bitunpack_test PRIVATE lemire_bitunpack)
target_link_libraries(lemire_bitunpack_test PRIVATE gtest_main)
target_include_directories(lemire_bitunpack_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
gtest_discover_tests(lemire_bitunpack_test)
#-----------------------------------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/fls_bench/fls_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/lemire_bitunpack_bench.hpp)
add_executable(avx512bw_lemire_bitunpack_bench avx512bw.cpp)
target_include_directories(avx512bw_lemire_bitunpack_bench PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_compile_options(avx512bw_lemire_bitunpack_bench PUBLIC -mavx512bw)
#-----------------------------------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/fls_bench/fls_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/lemire_bitunpack_bench.hpp)
add_executable(avx2_lemire_bitunpack_bench avx2.cpp)
target_include_directories(avx2_lemire_bitunpack_bench PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_compile_options(avx2_lemire_bitunpack_bench PUBLIC -mavx2)
#-----------------------------------------------------------------------------------------------------------------------
configure_file(${CMAKE_SOURCE_DIR}/fls_bench/fls_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/lemire_bitunpack_bench.hpp)
add_executable(sse_lemire_bitunpack_bench sse.cpp)
target_include_directories(sse_lemire_bitunpack_bench PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_compile_options(sse_lemire_bitunpack_bench PUBLIC -msse4)
#-----------------------------------------------------------------------------------------------------------------------

