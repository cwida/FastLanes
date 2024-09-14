add_library(fls_footer
        OBJECT
        #[[]]
        col_description.cpp
        rowgroup_footer.cpp
)

if (FLS_ENABLE_IWYU)
    set_target_properties(fls_footer PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_footer>
        PARENT_SCOPE)