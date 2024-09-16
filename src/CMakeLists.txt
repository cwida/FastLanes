add_subdirectory(c_api)
add_subdirectory(cfg)
add_subdirectory(common)
add_subdirectory(cor)
add_subdirectory(csv)
add_subdirectory(encoder)
add_subdirectory(expression)
add_subdirectory(filter)
add_subdirectory(footer)
add_subdirectory(io)
add_subdirectory(json)
add_subdirectory(logger)
add_subdirectory(new_encoder)
add_subdirectory(primitive)
add_subdirectory(printer)
add_subdirectory(reader)
add_subdirectory(std)
add_subdirectory(stt)
add_subdirectory(table)
add_subdirectory(utl)
add_subdirectory(wizard)

add_library(fastlanes
        STATIC
        connection.cpp
        ${FASTLANES_OBJECT_FILES})

if (FLS_ENABLE_IWYU)
    set_property(TARGET fastlanes PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

if (FLS_ENABLE_TABLE_LOG)
    target_compile_definitions(fastlanes PRIVATE TABLE_LOG)
endif ()


target_link_libraries(fastlanes PUBLIC primitives ALP)

if (CMAKE_SYSTEM_PROCESSOR MATCHES "(x86)|(X86)|(amd64)|(AMD64)")
    target_compile_options(fastlanes PRIVATE -march=native)
else ()
    target_compile_options(fastlanes PRIVATE -o3)
endif ()

message("---------------------------------------------------------------------------------------------------------")
cmake_print_properties(
        TARGETS
        fastlanes
        PROPERTIES COMPILE_DEFINITIONS
        PROPERTIES COMPILE_OPTIONS
        PROPERTIES COMPILE_FLAGS
        PROPERTIES INCLUDE_DIRECTORIES)


