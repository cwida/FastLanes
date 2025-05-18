# File: cmake/verbose_options.cmake
# -----------------------------------------------------------------------------
# Module: verbose_options
# Purpose: When FLS_ENABLE_VERBOSE_OUTPUT is ON, dumps:
#   1) All cache options prefixed with FLS_
#   2) Selected core CMake variables
# Usage:
#   include(verbose_options)
#   print_verbose_options()
# -----------------------------------------------------------------------------

function(print_verbose_options)
    message("---------------------------------------------------------------------------------------------------------")
    message(STATUS "FLS: VERBOSE OUTPUT ENABLED.")

    # 1) Gather all options starting with FLS_
    get_cmake_property(_all_vars VARIABLES)
    set(_user_vars)
    foreach (_var IN LISTS _all_vars)
        if (_var MATCHES "^FLS_")
            list(APPEND _user_vars ${_var})
        endif ()
    endforeach ()

    # Print user-facing options
    if (_user_vars)
        message(STATUS "FLS: User Options (prefix: FLS_):")
        cmake_print_variables(${_user_vars})
    else ()
        message(STATUS "No FLS_* options found.")
    endif ()

    message("---------------------------------------------------------------------------------------------------------")

    # 2) Print core CMake variables for context
    set(_core_vars
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
    message(STATUS "FLS : Core CMake Variables:")
    cmake_print_variables(${_core_vars})
endfunction()

