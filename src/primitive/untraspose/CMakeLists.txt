add_library(fls_primitive_untranspose
        OBJECT
        untranspose.cpp
        #
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_primitive_untranspose>
        PARENT_SCOPE)

if (ENABLE_IWYU)
    set_property(TARGET fls_primitive_untranspose PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()