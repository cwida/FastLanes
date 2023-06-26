cmake_minimum_required(VERSION 3.2)

if(UNIX AND NOT APPLE)
	set(LINUX true)
else()
	set(LINUX)
endif()

#[[=====================================================================================================================
FLS: [CHG] ]]
#
# prefer to use clang
# prefer to use c++17
# COMMENTED: -------------------------------------------------------------------------------------------------------
#if (LINUX)
#    set(CMAKE_C_COMPILER gcc)
#    set(CMAKE_CXX_COMPILER g++)
#    ADD_DEFINITIONS(-D_LIBCPP_VERSION=1) # tbb clang compatibility
#else ()
#    set(CMAKE_C_COMPILER gcc)
#    set(CMAKE_CXX_COMPILER g++)
#endif ()

#set(CMAKE_CXX_STANDARD 14)
#[[===================================================================================================================]]

set(CMAKE_CXX_STANDARD_REQUIRED ON)

OPTION(VECTORWISE_BRANCHING "Use branching vectorwise primitives" OFF)
OPTION(AUTOVECTORIZE "Allow the compiler to autovectorize" OFF)
OPTION(DATADIR "Directory containing testdata" "")
OPTION(AVX512EXPERIMENTS OFF)
OPTION(HARDWARE_BENCHMARKS OFF)
OPTION(INTERPRET_SEPARATE OFF)
OPTION(HASH_SIZE_32 OFF)

# Compiler flags for the different targets
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -mtune=native -std=c++14 -fPIC -Wall -Wextra -fno-omit-frame-pointer -Wno-unknown-pragmas ")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC -Wall -Wextra -fno-omit-frame-pointer -march=native -fdiagnostics-color ")

if(LINUX)
	#  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -static-libasan")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -pthread")
else()
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -fsanitize=address")
	# set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ")
endif(LINUX)

string(REPLACE "-O2" "" CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
string(REPLACE "-O2" "" CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}")
set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE}  -O3")

string(REPLACE "-O2" "" CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -O3")
#set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO} -fopt-info -fopt-info-missed -O3")
string(REPLACE "-O2" "" CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELWITHDEBINFO}")
set(CMAKE_CFLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} -O3")

set(CMAKE_MACOSX_RPATH 1)

IF(VECTORWISE_BRANCHING)
	ADD_DEFINITIONS(-DBRANCHING)
ENDIF(VECTORWISE_BRANCHING)
IF(INTERPRET_SEPARATE)
	ADD_DEFINITIONS(-DINTERPRET_SEPARATE)
ENDIF(INTERPRET_SEPARATE)
IF(HASH_SIZE_32)
	ADD_DEFINITIONS(-DHASH_SIZE=32)
ELSE()
	ADD_DEFINITIONS(-DHASH_SIZE=64)
ENDIF()

IF(AUTOVECTORIZE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftree-vectorize")
ELSE(AUTOVECTORIZE)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-tree-vectorize")
ENDIF(AUTOVECTORIZE)

## Download and unpack googletest at configure time
#configure_file(3rdparty/GTest.CMakeLists.txt googletest-download/CMakeLists.txt)
#execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
#        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download")
#execute_process(COMMAND "${CMAKE_COMMAND}" --build .
#        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/googletest-download")
#
## Prevent GoogleTest from overriding our compiler/linker options
## when building with Visual Studio
#set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
#
## Add googletest directly to our build. This adds
## the following targets: gtest, gtest_main, gmock
## and gmock_main
#add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
#        "${CMAKE_BINARY_DIR}/googletest-build")
#
## The gtest/gmock targets carry header search path
## dependencies automatically when using CMake 2.8.11 or
## later. Otherwise we have to add them here ourselves.
#if (CMAKE_VERSION VERSION_LESS 2.8.11)
#    include_directories("${gtest_SOURCE_DIR}/include"
#            "${gmock_SOURCE_DIR}/include")
#endif ()
#
## Now simply link your own targets against gtest, gmock,
## etc. as appropriate
#

IF(DATADIR)
	message(STATUS "setting datadir to user defined")
	message(STATUS "${DATADIR}")
	
	ADD_DEFINITIONS(-DDATADIR="${DATADIR}")
ELSE(DATADIR)
	message(STATUS "setting datadir to proj dir ")
	message(STATUS "${PROJECT_SOURCE_DIR}/data")
	ADD_DEFINITIONS(-DDATADIR="${PROJECT_SOURCE_DIR}/data")
ENDIF(DATADIR)

include(FetchContent)
FetchContent_Declare(tbb
                     GIT_REPOSITORY https://github.com/oneapi-src/oneTBB.git
                     GIT_TAG master
                     )
FetchContent_MakeAvailable(tbb)
set(TBB_LIBRARIES tbb)
include_directories(${tbb_SOURCE_DIR}/include)

# Gtest: ---------------------------------------------------------------------------------------------------------------
include(GoogleTest)
FetchContent_Declare(googletest
                     URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include_directories(${googletest_SOURCE_DIR}/googletest/include)

IF(LINUX)
	add_subdirectory(3rdparty/jevents)
	set(JEVENTSLIB "jevents")
ELSE(LINUX)
	set(JEVENTSLIB "")
ENDIF(LINUX)

add_library(common
            src/common/algebra/Operators.cpp
            src/common/algebra/Types.cpp
            src/common/runtime/Database.cpp
            src/common/runtime/MemoryPool.cpp
            src/common/runtime/Types.cpp
            src/common/runtime/String.cpp
            src/common/runtime/Import.cpp
            src/common/runtime/Hashmap.cpp
            src/common/runtime/Concurrency.cpp
            src/common/runtime/Profile.cpp
            )
target_include_directories(common PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
                           PRIVATE src)

set(HYPER_TRANSLATORS
    src/hyper/codegen/operators/Map.cpp
    src/hyper/codegen/operators/Print.cpp
    src/hyper/codegen/operators/Scan.cpp
    )

add_library(hyper
            src/hyper/codegen/Translator.cpp
            src/hyper/codegen/TranslatorRegistry.cpp
            )
target_include_directories(hyper PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
                           PRIVATE src)
target_link_libraries(hyper common)

file(GLOB PRIMITIVES src/vectorwise/primitives/*.cpp)
add_library(vectorwise
            src/vectorwise/Operations.cpp
            src/vectorwise/Operators.cpp
            ${PRIMITIVES}
            src/vectorwise/QueryBuilder.cpp
            )
target_include_directories(vectorwise PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
                           PRIVATE src)
# Set architecture if AVX512 exerperiments are requested
if(AVX512EXPERIMENTS)
	SET_TARGET_PROPERTIES(vectorwise PROPERTIES
	                      COMPILE_FLAGS "-march=skylake-avx512"
	                      )
endif()
target_link_libraries(vectorwise common)

add_executable(bench
               ${HYPER_TRANSLATORS}
               src/bench.cpp)
target_include_directories(bench PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
                           PRIVATE src)
target_link_libraries(bench hyper vectorwise common)

add_library(benchmark_config
            src/benchmarks/config.cpp)
target_include_directories(benchmark_config PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
                           PRIVATE src)
target_link_libraries(benchmark_config vectorwise common)

file(GLOB TPCHQUERIES
     src/benchmarks/tpch/queries/q1.cpp
     src/benchmarks/tpch/queries/q3.cpp
     src/benchmarks/tpch/queries/q5.cpp
     src/benchmarks/tpch/queries/q5_no_sel.cpp
     src/benchmarks/tpch/queries/q6.cpp
     src/benchmarks/tpch/queries/q9.cpp
     src/benchmarks/tpch/queries/q18.cpp)

add_library(tpch
            ${TPCHQUERIES}
            )
target_include_directories(tpch PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
                           PRIVATE src)
target_link_libraries(tpch benchmark_config pthread hyper ${TBB_LIBRARIES} vectorwise common)

# ============================== target : bitpacking avx512
#add_subdirectory(fls)

# ============================== target : run_tpch
add_executable(run_tpch
               ${HYPER_TRANSLATORS}
               src/benchmarks/tpch/run.cpp
               )
target_include_directories(run_tpch PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
                           PRIVATE src)
target_link_libraries(run_tpch tpch hyper vectorwise common ${JEVENTSLIB})

#[[=====================================================================================================================
FLS: [CHG] ]]

add_executable(run_fls
               ${HYPER_TRANSLATORS}
               src/benchmarks/fls/run.cpp
               src/benchmarks/fls/queries/config.cpp
               src/benchmarks/fls/queries/q1.cpp
               fls/x86_64_avx512bw_intrinsic_1024_uf1_unpack_src.cpp
               fls/fallback_scalar_av_1024_uf1_pack_src.cpp
               src/lemire/bitpacking.cpp)

target_compile_options(run_fls PUBLIC -fno-builtin)

target_include_directories(run_fls PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
                           PRIVATE src)
target_link_libraries(run_fls tpch hyper vectorwise common ${JEVENTSLIB})

file(GLOB SBBQUERIES src/benchmarks/sbb/queries/*.cpp)
add_library(ssb
            ${SBBQUERIES}
            )
target_include_directories(ssb PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
                           PRIVATE src)
target_link_libraries(ssb benchmark_config pthread hyper ${TBB_LIBRARIES} vectorwise common)

add_executable(run_ssb
               ${HYPER_TRANSLATORS}
               src/benchmarks/sbb/run.cpp
               )
target_include_directories(run_ssb PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
                           PRIVATE src)
target_link_libraries(run_ssb ssb hyper vectorwise common ${JEVENTSLIB})

add_executable(run_prim
               src/benchmarks/primitives/run.cpp
               )
target_include_directories(run_prim PUBLIC
                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
                           $<INSTALL_INTERFACE:include>
                           PRIVATE src)
target_link_libraries(run_prim vectorwise common ${TBB_LIBRARIES} ${JEVENTSLIB})

#[[===================================================================================================================]]

# Enable tests
enable_testing()
set(CTEST_OUTPUT_ON_FAILURE "1")

add_executable(test_all
               src/test/tpch_expected.cpp
               src/test/ssb_expected.cpp
               src/test/tpch.cpp
               src/test/ssb.cpp
               src/test/vectorwise/primitives.cpp
               src/test/vectorwise/Operators.cpp
               src/test/common/Hashmap.cpp
               src/test/common/Database.cpp
               src/test/common/PartitionedDeque.cpp
               src/test/common/Mmap.cpp
               src/test/common/runtime/Stack.cpp
               )
target_link_libraries(test_all common hyper vectorwise tpch ssb gtest gtest_main)

if(HARDWARE_BENCHMARKS)
	add_executable(latency
	               src/benchmarks/hardware/latency.cpp)
	target_link_libraries(latency pthread)
	add_executable(randomWrites
	               src/benchmarks/hardware/randomWrites.cpp)
	target_include_directories(randomWrites PUBLIC
	                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	                           $<INSTALL_INTERFACE:include>
	                           PRIVATE src)
	target_link_libraries(randomWrites common pthread ${JEVENTSLIB})
endif()

if(AVX512EXPERIMENTS)
	add_executable(simdJoin src/benchmarks/simdJoin.cpp)
	SET_TARGET_PROPERTIES(simdJoin PROPERTIES
	                      COMPILE_FLAGS "-march=skylake-avx512"
	                      )
	target_include_directories(simdJoin PUBLIC
	                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	                           $<INSTALL_INTERFACE:include>
	                           PRIVATE src)
	
	target_link_libraries(simdJoin common ${JEVENTSLIB})
	
	add_executable(run_simd
	               src/benchmarks/primitives/simdselection.cpp
	               )
	SET_TARGET_PROPERTIES(run_simd PROPERTIES
	                      COMPILE_FLAGS "-march=skylake-avx512"
	                      )
	target_include_directories(run_simd PUBLIC
	                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	                           $<INSTALL_INTERFACE:include>
	                           PRIVATE src)
	target_link_libraries(run_simd vectorwise common ${TBB_LIBRARIES} ${JEVENTSLIB})
	
	add_executable(run_join
	               src/benchmarks/primitives/joinmicrobench.cpp
	               )
	SET_TARGET_PROPERTIES(run_join PROPERTIES
	                      COMPILE_FLAGS "-march=skylake-avx512"
	                      )
	target_include_directories(run_join PUBLIC
	                           $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
	                           $<INSTALL_INTERFACE:include>
	                           PRIVATE src)
	target_link_libraries(run_join vectorwise common ${TBB_LIBRARIES} ${JEVENTSLIB})
endif(AVX512EXPERIMENTS)
