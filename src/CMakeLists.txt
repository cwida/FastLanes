add_subdirectory(c_api)
add_subdirectory(cfg)
add_subdirectory(common)
add_subdirectory(cor)
add_subdirectory(csv)
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
add_subdirectory(printer)
add_subdirectory(reader)
add_subdirectory(std)
add_subdirectory(stt)
add_subdirectory(table)
add_subdirectory(utl)
add_subdirectory(wizard)

add_library(FastLanes
        STATIC
        connection.cpp
        ${FASTLANES_OBJECT_FILES})

if (FLS_ENABLE_IWYU)
    set_property(TARGET FastLanes PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

target_link_libraries(FastLanes PUBLIC primitives ALP)


install(
        TARGETS FastLanes
        EXPORT FLSTargets        # Add to the export set
        LIBRARY DESTINATION lib          # For shared libraries
        ARCHIVE DESTINATION lib          # For static libraries
        RUNTIME DESTINATION bin          # For executables (if any)
)