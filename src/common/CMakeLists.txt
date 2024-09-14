add_library(fls_common
        OBJECT
        assert.cpp
        byte_c.cpp
        #[[]]
        common.cpp
        str.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_common>
        PARENT_SCOPE)

if (FLS_ENABLE_IWYU)
    set_property(TARGET fls_common PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()
