add_library(ALP
        STATIC
        encoder.cpp
        falp.cpp
        fastlanes_ffor.cpp
        fastlanes_generated_unffor.cpp
        fastlanes_generated_ffor.cpp
        fastlanes_unffor.cpp
)


# Add include directories for the ALP target
target_include_directories(ALP PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

if (ALP_ENABLE_VERBOSE_OUTPUT)
    cmake_print_properties(TARGETS ALP PROPERTIES COMPILE_DEFINITIONS PROPERTIES COMPILE_OPTIONS)
endif ()

install(
        TARGETS ALP
        EXPORT ALPTargets
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)


