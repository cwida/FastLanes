add_library(fls_primitive_patch
        OBJECT
        patch.cpp
)


set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_primitive_patch>
        PARENT_SCOPE)

if (ENABLE_IWYU)
    set_property(TARGET fls_primitive_patch PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

target_compile_options(fls_primitive_patch PRIVATE -Wno-macro-redefined)

target_link_libraries(fls_primitive_patch
        PUBLIC
        FastLanes::headers
)
