###########################################################################
# Usage in sub-directories (example)
###########################################################################
#   target_link_libraries(example
#       PUBLIC
#           FastLanes::headers   # include path
#           FastLanes::core      # links against FastLanes lib
#   )
###########################################################################

###########################################################################
# 1. Public-header interface target
###########################################################################
add_library(fls_headers INTERFACE)

target_include_directories(fls_headers
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

add_library(FastLanes::headers ALIAS fls_headers)

###########################################################################
# 2. Sub-directories that build individual components
###########################################################################
add_subdirectory(alp)
add_subdirectory(c_api)
add_subdirectory(cfg)
add_subdirectory(common)
add_subdirectory(cor)
add_subdirectory(csv)
add_subdirectory(detail)
add_subdirectory(encoder)
add_subdirectory(expression)
add_subdirectory(file)
add_subdirectory(filter)
add_subdirectory(flatbuffers)
add_subdirectory(footer)
add_subdirectory(io)
add_subdirectory(json)
add_subdirectory(logger)
add_subdirectory(primitive)
add_subdirectory(primitives)
add_subdirectory(printer)
add_subdirectory(reader)
add_subdirectory(std)
add_subdirectory(stt)
add_subdirectory(table)
add_subdirectory(utl)
add_subdirectory(wizard)

###########################################################################
# 3. Core FastLanes library
###########################################################################
if (FLS_BUILD_SHARED_LIBS)
    add_library(FastLanes SHARED
            connection.cpp
            ${FASTLANES_OBJECT_FILES}
    )
    target_compile_definitions(FastLanes
            PRIVATE
            FLS_BUILD_DLL
    )
else ()
    add_library(FastLanes STATIC
            connection.cpp
            ${FASTLANES_OBJECT_FILES}
    )
    target_compile_definitions(FastLanes
            PUBLIC
            FLS_STATIC
    )
endif ()

target_compile_features(FastLanes PUBLIC cxx_std_20)

target_link_libraries(FastLanes
        PUBLIC
        FastLanes::headers
)

add_library(FastLanes::core ALIAS FastLanes)

# Optional IWYU integration
if (FLS_ENABLE_IWYU)
    set_property(TARGET FastLanes PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

if (FLS_ENABLE_INSTALL)
    ###########################################################################
    # 4. Installation
    ###########################################################################

    install(
            TARGETS FastLanes fls_headers
            EXPORT FLSTargets
            ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}   # .a / import-libs
            LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}   # .so / .dylib
            RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}   # Windows .dll / executables
            INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )

    # Export set for find_package(FLS)
    install(
            EXPORT FLSTargets
            FILE FLSTargets.cmake
            NAMESPACE FLS::
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/FLS
    )

    # Export file to the build tree for downstream projects
    export(
            EXPORT FLSTargets
            FILE "${CMAKE_BINARY_DIR}/FLSTargets.cmake"
            NAMESPACE FLS::
    )

    ###########################################################################
    # 5. Header-only tree
    ###########################################################################
    install(
            DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            FILES_MATCHING
            PATTERN "*.h"
            PATTERN "*.hpp"
    )
endif ()  # FLS_ENABLE_INSTALL
