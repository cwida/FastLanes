cmake_minimum_required(VERSION 3.22)

# Requirements : -------------------------------------------------------------------------------------------------------
find_program(CLANG_CXX NAMES clang++ REQUIRED)
find_program(CLANG_C NAMES clang REQUIRED)

if (CLANG_CXX AND CLANG_C)
    # Set Clang as the compiler explicitly
    set(CMAKE_C_COMPILER "${CLANG_C}" CACHE STRING "C Compiler" FORCE)
    set(CMAKE_CXX_COMPILER "${CLANG_CXX}" CACHE STRING "C++ Compiler" FORCE)
endif ()


#  ---------------------------------------------------------------------------------------------------------------------
# Prevent Windows <minwindef.h> from defining min/max macros,
# which collide with std::numeric_limits<…>::max() and
# Flatbuffers’ own max() methods.
#
# Defining NOMINMAX here ensures that any inclusion of
# windows.h or other Win32 headers won’t inject those macros.
# ----------------------------------------------------------------------------------------------------------------------
add_compile_definitions(NOMINMAX)


# Project : ------------------------------------------------------------------------------------------------------------
project(FastLanes)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE TRUE)

#-----------------------------------------------------------------------------------------------------------------------
include(FetchContent)
include(CheckCXXCompilerFlag)
include(CMakePrintHelpers)
# https://stackoverflow.com/questions/56089330/cmake-creates-lots-of-targets-i-didnt-specify
set_property(GLOBAL PROPERTY CTEST_TARGETS_ADDED 1)
include(CTest)

# Checks : -------------------------------------------------------------------------------------------------------
if (NOT "${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    message(FATAL_ERROR "Only Clang is supported!")
endif ()
if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 13)
    message(FATAL_ERROR "Only Clang >= 13 is supported!")
endif ()

# Disallow configuring in the source tree
if (CMAKE_SOURCE_DIR STREQUAL CMAKE_BINARY_DIR)
    message(FATAL_ERROR "-- FLS : Please run CMake in a separate build directory!")
endif ()
# Flags : --------------------------------------------------------------------------------------------------------------
message("---------------------------------------------------------------------------------------------------------")
message("-- FLS: detecting flags.")
# First, check if running on GitHub Actions
if (DEFINED ENV{GITHUB_ACTIONS} AND "$ENV{GITHUB_ACTIONS}" STREQUAL "true")
    message(STATUS "Running on GitHub Actions runner.")
    set(IS_GITHUB_ACTIONS ON)
endif ()

# Check if the compiler supports -mavx512dq
check_cxx_compiler_flag("-mavx512dq" COMPILER_SUPPORTS_AVX512DQ)

# Detect AVX-512DQ hardware support via /proc/cpuinfo
set(HAS_HW_AVX512DQ OFF)
if (EXISTS "/proc/cpuinfo")
    file(READ "/proc/cpuinfo" CPUINFO_CONTENT)
    if (CPUINFO_CONTENT MATCHES "avx512dq")
        set(HAS_HW_AVX512DQ ON)
    endif ()
endif ()

if (COMPILER_SUPPORTS_AVX512DQ AND HAS_HW_AVX512DQ AND NOT IS_GITHUB_ACTIONS)
    message(STATUS "Compiler and hardware both support AVX-512DQ. Adding flag '-mavx512dq'.")
    set(FLAGS "-mavx512dq")
elseif (COMPILER_SUPPORTS_AVX512DQ AND HAS_HW_AVX512DQ AND IS_GITHUB_ACTIONS)
    message(WARNING "Hardware supports AVX-512DQ, but not adding on GitHub Actions runner.")
elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|i[3-6]86")
    message(STATUS "Setting '-march=native' for x86 processors without AVX-512DQ.")
    set(FLAGS "-march=native")
else ()
    message(STATUS "No instruction set flags applied.")
endif ()

# Append the computed FLAGS to the compiler flags if defined
if (FLAGS)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS}")
endif ()

# Flags for warnings and errors:
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -Winconsistent-missing-override -Wshadow -Wconversion -Wnon-virtual-dtor -Wunused -Wpedantic -Woverloaded-virtual -Wshorten-64-to-32")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wshadow -Wconversion")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("---------------------------------------------------------------------------------------------------------")
    message("-- FLS: Debug mode enabled. Adding -g and -O0.")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
    set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0")
endif ()

# Options : ------------------------------------------------------------------------------------------------------------
option(FLS_BUILD_TESTING "Build Test" OFF)
option(FLS_BUILD_BENCHMARKING "Enable Benchmark Build" OFF)
option(FLS_BUILD_EXAMPLES "Build Examples" OFF)
option(FLS_BUILD_GPU "Build GPU" OFF)
option(FLS_BUILD_GTEST "Build GTEST" OFF)
option(FLS_ENABLE_CLANG_TIDY "Enable clang_tidy on all targets" ON)
option(FLS_ENABLE_IWYU "Enable include-what-you-use tool" OFF)
option(FLS_ENABLE_DOC "Enable Doc build" OFF)
option(FLS_ENABLE_TABLE_LOG "Enable Table Log" OFF)
option(FLS_ENABLE_VERBOSE_OUTPUT "Enable verbose output" OFF)
option(FLS_ENABLE_DATA "Enable Data" OFF)
option(FLS_ENABLE_FSST_TESTING_AND_BENCHMARKING "Build FSST" OFF)

# Definitions: ---------------------------------------------------------------------------------------------------------
add_compile_definitions(FLS_CMAKE_SOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")


# GTEST : --------------------------------------------------------------------------------------------------------------
if (FLS_BUILD_TESTING OR FLS_BUILD_GPU OR FLS_ENABLE_FSST_TESTING_AND_BENCHMARKING)
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

    # On Windows, GoogleTest uses Microsoft-specific language extensions like `__try`
    # that trigger Clang's `-Wlanguage-extension-token` warning.
    # Since we build with `-Werror`, this causes the build to fail.
    # This block selectively disables that warning (and suppresses all warnings with `-w`)
    # only for GoogleTest targets, avoiding global suppression across the project.
    if (MSVC OR WIN32)
        foreach (target gtest gtest_main gmock gmock_main)
            if (TARGET ${target})
                target_compile_options(${target} PRIVATE -Wno-language-extension-token -w)
            endif ()
        endforeach ()
    endif ()
endif ()

# ALP: -----------------------------------------------------------------------------------------------------------------
if (true)
    message("---------------------------------------------------------------------------------------------------------")
    message("-- FLS: Building ALP Lib.")
    add_compile_definitions(ALP_N_VECTORS_PER_ROWGROUP=64)
    set(ALP_ENABLE_ADAPTIVE_MODE OFF CACHE BOOL "Enable adaptive mode" FORCE)
    add_subdirectory(alp)
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/alp/src/include)
endif ()


if (true)
    message("---------------------------------------------------------------------------------------------------------")
    message("-- FLS: Building FastLanes Lib.")
    # Include : --------------------------------------------------------------------------------------------------------
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

    # External Include: -----------------------------------------------------------------------------------------------------
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/flatbuffers)

    # Primitives: ------------------------------------------------------------------------------------------------------
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/primitives)

    # Source: ----------------------------------------------------------------------------------------------------------
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)

    install(
            EXPORT FLSTargets
            FILE FLSTargets.cmake
            DESTINATION lib/FLS
            NAMESPACE FLS::
    )

    export(
            EXPORT FLSTargets
            FILE "${CMAKE_BINARY_DIR}/FLSTargets.cmake"
            NAMESPACE FLS::
    )

endif ()

# DATA : ---------------------------------------------------------------------------------------------------------------
if (FLS_BUILD_TESTING OR FLS_BUILD_BENCHMARKING OR FLS_BUILD_EXAMPLES OR FLS_ENABLE_DATA)
    message("---------------------------------------------------------------------------------------------------------")
    message("-- FLS: Enabling Data.")

    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/data/include)

    FetchContent_Declare(
            data
            GIT_REPOSITORY https://github.com/cwida/FastLanes_Data.git
            GIT_TAG main
    )

    FetchContent_MakeAvailable(data)

    add_compile_definitions(FASTLANES_DATA_DIR="${data_SOURCE_DIR}")
    cmake_print_variables(data_SOURCE_DIR)

endif ()

if (FLS_ENABLE_CLANG_TIDY)
    message("---------------------------------------------------------------------------------------------------------")
    message("-- FLS: Enabling CLANG-TIDY.")
    find_program(CLANG_TIDY_EXE NAMES clang-tidy)
    if (NOT CLANG_TIDY_EXE)
        message(FATAL_ERROR "-- FLS: clang-tidy not found.")
    else ()
        if (NOT DEFINED CMAKE_CXX_CLANG_TIDY)
            set(CMAKE_CXX_CLANG_TIDY
                    ${CLANG_TIDY_EXE};
                    --quiet;
                    --config-file=${CMAKE_SOURCE_DIR}/.clang-tidy)
            message("-- FLS: Using project-level .clang-tidy")
        else ()
            message(FATAL_ERROR "-- FLS: Do not override the clang-tidy configuration. Use the project-level .clang-tidy file instead. Current setting: ${CMAKE_CXX_CLANG_TIDY}")
        endif ()

        execute_process(
                COMMAND ${CLANG_TIDY_EXE} --version
                OUTPUT_VARIABLE CLANG_TIDY_VERSION
                OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        message("-- FLS: clang-tidy version: ${CLANG_TIDY_VERSION}")

        execute_process(
                COMMAND ${CLANG_TIDY_EXE} --version
                OUTPUT_VARIABLE CLANG_TIDY_VERSION
                OUTPUT_STRIP_TRAILING_WHITESPACE
        )
        message("-- FLS: clang-tidy version: ${CLANG_TIDY_VERSION}")

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

if (FLS_ENABLE_VERBOSE_OUTPUT)
    message("---------------------------------------------------------------------------------------------------------")
    message("-- FLS: Verbose Enabled:")

    cmake_print_variables(
            CMAKE_SYSTEM_PROCESSOR
            CMAKE_SYSTEM_NAME
            CMAKE_VERSION
            CMAKE_BUILD_TYPE
            CMAKE_CXX_COMPILER
            CMAKE_CXX_COMPILER_VERSION
            CMAKE_CXX_STANDARD
            CMAKE_SYSTEM
            CMAKE_HOST_SYSTEM_NAME
            CMAKE_HOST_SYSTEM_PROCESSOR
            CMAKE_GENERATOR
            CMAKE_BINARY_DIR
            CMAKE_SOURCE_DIR
            CMAKE_LINKER
            CMAKE_CXX_FLAGS
            CMAKE_C_FLAGS
            CMAKE_CROSSCOMPILING
            CMAKE_CXX_FLAGS_DEBUG
    )
endif ()

# Benchmark : ----------------------------------------------------------------------------------------------------------
if (FLS_BUILD_BENCHMARKING)
    message("---------------------------------------------------------------------------------------------------------")
    message("- Benchmark:")

    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/benchmark)
endif ()

# Test: ----------------------------------------------------------------------------------------------------------------
if (FLS_BUILD_TESTING)
    message("---------------------------------------------------------------------------------------------------------")
    message("-- FLS: Build Testing.")
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/test/include)

    # Helper to apply sanitizer flags only on non-Windows platforms
    function(fls_enable_sanitizers target)
        if (NOT WIN32)
            target_compile_options(${target}
                    PRIVATE -fsanitize=address -fsanitize=undefined)
            target_link_options(${target}
                    PRIVATE -fsanitize=address -fsanitize=undefined)
        endif ()
    endfunction()


    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)


endif ()


# FSST: ----------------------------------------------------------------------------------------------------------------
if (FLS_ENABLE_FSST_TESTING_AND_BENCHMARKING)
    message("---------------------------------------------------------------------------------------------------------")
    message("-- FLS: Adding FSST Testing and Benchmarking.")
    add_subdirectory(fsst)
endif ()


# Example : ------------------------------------------------------------------------------------------------------------
if (FLS_BUILD_EXAMPLES)
    message("---------------------------------------------------------------------------------------------------------")
    message("- Examples:")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/examples)
endif ()

# GPU : ----------------------------------------------------------------------------------------------------------------
if (FLS_BUILD_GPU)
    message("---------------------------------------------------------------------------------------------------------")
    message("- GPU:")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/gpu)
endif ()

# Playground : ---------------------------------------------------------------------------------------------------------
if (EXISTS "${CMAKE_SOURCE_DIR}/playground/CMakeLists.txt")
    message("---------------------------------------------------------------------------------------------------------")
    message("- FLS: Adding Playground ")
    add_subdirectory(playground)
endif ()
# Python : -------------------------------------------------------------------------------------------------------------
if (FLS_BUILD_PYTHON)
    message("-------------------------------------------------------------")
    message("- FLS: Building FastLanes Python Extension")

    add_subdirectory(python)   # your module’s CMakeLists.txt
endif ()


