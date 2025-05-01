add_library(fls_file
        OBJECT
        #[[]]
        file_header.cpp
        file_footer.cpp
)

if (FLS_ENABLE_IWYU)
    set_target_properties(fls_file PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_file>
        PARENT_SCOPE)