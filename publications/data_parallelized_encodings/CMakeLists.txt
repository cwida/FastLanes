cmake_minimum_required(VERSION 3.22)
project(fastlanesfileformat)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

# Requirements : -------------------------------------------------------------------------------------------------------
if (NOT "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    message(FATAL_ERROR "Only Clang is supported!")
endif ()
if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13)
    message(FATAL_ERROR "Only Clang >= 13 is supported!")
endif ()

# FLAGS : --------------------------------------------------------------------------------------------------------------
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Winconsistent-missing-override -Wshadow -Wconversion -Wnon-virtual-dtor -Wunused -Wpedantic -Woverloaded-virtual")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wshadow -Wconversion")

if ("${CMAKE_SYSTEM_PROCESSOR}" MATCHES "x86")
    #    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")  # FSST
endif ()

#-----------------------------------------------------------------------------------------------------------------------
include(FetchContent)
include(CheckCXXCompilerFlag)
include(CMakePrintHelpers)
# https://stackoverflow.com/questions/56089330/cmake-creates-lots-of-targets-i-didnt-specify
set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)
include(CTest)

# Options : ------------------------------------------------------------------------------------------------------------
option(FLS_BUILD_FLS "Build FLS" ON)
option(FLS_BUILD_TESTING "Build Test" OFF)
option(FLS_BUILD_BENCHMARKING "Enable Benchmark Build" OFF)
option(FLS_BUILD_EXAMPLE "Build Example" OFF)
option(FLS_BUILD_GPU "Build GPU" OFF)
option(FLS_BUILD_GTEST "Build GTEST" OFF)
option(FLS_ENABLE_CLANG_TIDY "Enable clang_tidy on all targets" ON)
option(FLS_ENABLE_IWYU "Enable include-what-you-use tool" OFF)
option(FLS_ENABLE_DOC "Enable Doc build" OFF)
option(FLS_ENABLE_TABLE_LOG "Enable Table Log" OFF)

# GTEST : ------------------------------------------------------------------------------------------------------------
if (FLS_BUILD_TESTING OR FLS_BUILD_GPU)
    message("---------------------------------------------------------------------------------------------------------")
    message("-- FLS: Building GTEST:")
    include(GoogleTest)
    # Gtest: -----------------------------------------------------------------------------------------------------------
    FetchContent_Declare(googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG e2239ee6043f73722e7aa812a459f54a28552929 # release-1.11.0
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    # Silence clang-tidy warnings from googletest
    set_target_properties(gtest PROPERTIES CXX_CLANG_TIDY "")
    set_target_properties(gtest_main PROPERTIES CXX_CLANG_TIDY "")
    set_target_properties(gmock PROPERTIES CXX_CLANG_TIDY "")
    set_target_properties(gmock_main PROPERTIES CXX_CLANG_TIDY "")
endif ()


# DATA : ---------------------------------------------------------------------------------------------------------------
if (FLS_BUILD_TESTING OR FLS_BUILD_BENCHMARKING OR FLS_BUILD_EXAMPLE)
    message("---------------------------------------------------------------------------------------------------------")
    message("-- FLS: Enabling Sample Data.")

    include_directories(${CMAKE_SOURCE_DIR}/data/include)
endif ()

# Definitions: ---------------------------------------------------------------------------------------------------------
add_compile_definitions(CMAKE_SOURCE_DIR="${CMAKE_SOURCE_DIR}")

if (FLS_ENABLE_CLANG_TIDY)
    message("---------------------------------------------------------------------------------------------------------")
    message("-- FLS: Enabling CLANG-TIDY.")
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    if (NOT CLANG_TIDY_EXE)
        message(FATAL_ERROR "-- FLS: clang-tidy not found.")
    else ()
        set(CMAKE_CXX_CLANG_TIDY
                ${CLANG_TIDY_EXE};
                -header-filter=include;
                -warnings-as-errors=*;)

    endif ()
endif ()

if (FLS_ENABLE_IWYU)
    message("---------------------------------------------------------------------------------------------------------")
    message("-- FLS: Enabling IWYU")
    find_program(iwyu_path NAMES include-what-you-use iwyu REQUIRED)
    if (NOT iwyu_path)
        message(WARNING "-- FLS_ERROR: Could not find the program include-what-you-use")
    endif ()
endif ()

if (FLS_ENABLE_DOC)
    find_package(Doxygen OPTIONAL_COMPONENTS dot)
    if (DOXYGEN_FOUND)
        set(DOXYGEN_USE_MDFILE_AS_MAINPAGE "${CMAKE_SOURCE_DIR}/README.md")
        doxygen_add_docs(doc
                ${CMAKE_SOURCE_DIR}
        )
    endif (DOXYGEN_FOUND)
endif ()

if (FLS_ENABLE_TABLE_LOG)
endif ()


if (FLS_BUILD_FLS)
    # FLGs: ------------------------------------------------------------------------------------------------------------
    message("---------------------------------------------------------------------------------------------------------")
    message("- FFF:")
    cmake_print_variables(CMAKE_OSX_ARCHITECTURES)
    cmake_print_variables(CMAKE_HOST_SYSTEM_PROCESSOR)
    cmake_print_variables(CMAKE_SYSTEM_PROCESSOR)
    cmake_print_variables(CMAKE_HOST_SYSTEM_NAME)
    cmake_print_variables(CMAKE_SYSTEM_NAME)
    cmake_print_variables(CMAKE_C_COMPILER)
    cmake_print_variables(CMAKE_CXX_COMPILER)
    cmake_print_variables(CMAKE_CXX_COMPILER_ID)
    cmake_print_variables(CMAKE_CXX_COMPILER_VERSION)
    cmake_print_variables(CMAKE_LINKER)
    cmake_print_variables(CMAKE_CROSSCOMPILING)
    cmake_print_variables(CMAKE_CXX_FLAGS)
    cmake_print_variables(CMAKE_CXX_FLAGS_DEBUG)
    cmake_print_variables(CMAKE_CXX_FLAGS_RELEASE)
    cmake_print_variables(CMAKE_BUILD_TYPE)
    cmake_print_variables(CMAKE_CXX_STANDARD)

    # Include : --------------------------------------------------------------------------------------------------------
    include_directories(${CMAKE_SOURCE_DIR}/include)
    include_directories(${CMAKE_SOURCE_DIR}/third_party)

    # Primitives: ------------------------------------------------------------------------------------------------------
    add_subdirectory(${CMAKE_SOURCE_DIR}/primitives)

    # Source: ----------------------------------------------------------------------------------------------------------
    add_subdirectory(${CMAKE_SOURCE_DIR}/src)

    # Third_party: -----------------------------------------------------------------------------------------------------
    add_subdirectory(${CMAKE_SOURCE_DIR}/third_party)
endif ()

# Benchmark : ----------------------------------------------------------------------------------------------------------
if (FLS_BUILD_BENCHMARKING)
    message("---------------------------------------------------------------------------------------------------------")
    message("- Benchmark:")
    if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
        message(FATAL_ERROR "CMAKE_TOOLCHAIN_FILE is not set")
    endif (NOT DEFINED CMAKE_TOOLCHAIN_FILE)

    configure_file(${CMAKE_SOURCE_DIR}/fls_bench/fls_bench.hpp ${CMAKE_CURRENT_BINARY_DIR}/fls_bench.hpp)

    include_directories(${CMAKE_CURRENT_BINARY_DIR})
    include_directories(${CMAKE_SOURCE_DIR}/benchmark/include)

    add_subdirectory(${CMAKE_SOURCE_DIR}/benchmark)
endif ()

# Test: ----------------------------------------------------------------------------------------------------------------
if (FLS_BUILD_TESTING)
    include_directories(${CMAKE_SOURCE_DIR}/test/include)
    add_subdirectory(${CMAKE_SOURCE_DIR}/test)
endif ()

# Example : ------------------------------------------------------------------------------------------------------------
if (FLS_BUILD_EXAMPLE)
    message("---------------------------------------------------------------------------------------------------------")
    message("- Examples:")
    add_subdirectory(${CMAKE_SOURCE_DIR}/example)
endif ()

# GPU : ----------------------------------------------------------------------------------------------------------------
if (FLS_BUILD_GPU)
    message("---------------------------------------------------------------------------------------------------------")
    message("- GPU:")
    add_subdirectory(${CMAKE_SOURCE_DIR}/gpu)
endif ()
