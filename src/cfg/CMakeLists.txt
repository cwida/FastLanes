add_library(fls_cfg
        OBJECT
        cfg.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_cfg>
        PARENT_SCOPE)

if (FLS_ENABLE_IWYU)
    set_property(TARGET fls_cfg PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()