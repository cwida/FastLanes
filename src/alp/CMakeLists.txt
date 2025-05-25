# Options : ------------------------------------------------------------------------------------------------------------
option(ALP_BUILD_LIBRARY "Build ALP Library" ON)
option(ALP_BUILD_TESTING "Build Testing" OFF)
option(ALP_BUILD_BENCHMARKING "Build Benchmarking" OFF)
option(ALP_ENABLE_CLANG_TIDY "Enable clang_tidy on all targets" ON)
option(ALP_ENABLE_VERBOSE_OUTPUT "Enable verbose output" OFF)
option(ALP_ENABLE_ADAPTIVE_MODE "Enable adaptive mode" ON)

# Adaptivity : ---------------------------------------------------------------------------------------------------------
if (ALP_ENABLE_ADAPTIVE_MODE)
    message("---------------------------------------------------------------------------------------------------------")
    add_compile_definitions(ALP_IS_ADAPTIVE_MODE_ENABLED=true)
    message("-- ALP: adaptive mode is enabled.")
else ()
    add_compile_definitions(ALP_IS_ADAPTIVE_MODE_ENABLED=false)
    message("-- ALP: adaptive mode is disabled.")
endif ()

# Verbose : ------------------------------------------------------------------------------------------------------------
if (ALP_ENABLE_VERBOSE_OUTPUT)
    message("---------------------------------------------------------------------------------------------------------")
    message("-- ALP: Verbose Enabled:")

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
            CMAKE_CURRENT_SOURCE_DIR
            CMAKE_LINKER
            CMAKE_CXX_FLAGS
            CMAKE_C_FLAGS
            CMAKE_CROSSCOMPILING
    )
endif ()


# Src: -----------------------------------------------------------------------------------------------------------------
if (true)
    message("---------------------------------------------------------------------------------------------------------")
    message("-- ALP: Build Library: Version ${PROJECT_VERSION}")
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src)


    add_library(fls_alp
            OBJECT
            alp.cpp
    )

    set(FASTLANES_OBJECT_FILES
            ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_alp>
            PARENT_SCOPE)

    if (ENABLE_IWYU)
        set_property(TARGET fls_alp PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
    endif ()


    target_link_libraries(fls_alp
            PUBLIC
            FastLanes::headers
    )

endif ()




