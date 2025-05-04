add_library(fls_primitive_fsst
        OBJECT
        fsst.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_primitive_fsst>
        PARENT_SCOPE)

if (ENABLE_IWYU)
    set_property(TARGET fls_primitive_fsst PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

target_compile_options(fls_primitive_fsst PRIVATE -Wno-macro-redefined)
