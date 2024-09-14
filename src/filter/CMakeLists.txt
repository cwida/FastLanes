add_library(fls_filter
        OBJECT
        #[[]]
        filter.cpp
)

if (FLS_ENABLE_IWYU)
    set_target_properties(fls_filter PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_filter>
        PARENT_SCOPE)