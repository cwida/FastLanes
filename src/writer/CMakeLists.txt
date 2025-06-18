add_library(fls_writer
        OBJECT
        writer.cpp
)

if (FLS_BUILD_SHARED_LIBS)
    target_compile_definitions(fls_writer
            PRIVATE
            FLS_BUILD_DLL
    )
else ()
    target_compile_definitions(fls_writer
            PUBLIC
            FLS_STATIC
    )
endif ()

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_writer>
        PARENT_SCOPE)

if (FLS_ENABLE_IWYU)
    set_property(TARGET fls_writer PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

target_link_libraries(fls_writer
        PUBLIC
        FastLanes::headers
)