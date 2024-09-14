add_library(fls_std
        OBJECT
        #[[]]
        filesystem.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_std>
        PARENT_SCOPE)

if (FLS_ENABLE_IWYU)
    set_property(TARGET fls_std PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()