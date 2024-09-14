add_library(fls_alp_exp
        OBJECT
        alp_exp.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_alp_exp>
        PARENT_SCOPE)

if (ENABLE_IWYU)
    set_property(TARGET fls_alp_exp PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()