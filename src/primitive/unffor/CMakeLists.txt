add_library(fls_primitive_unffor
        OBJECT
        unffor.cpp
        #
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_primitive_unffor>
        PARENT_SCOPE)

if (ENABLE_IWYU)
    set_property(TARGET fls_primitive_unffor PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()