add_library(fls_logger
        OBJECT
        #[[]]
        logger.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_logger>
        PARENT_SCOPE)

if (FLS_ENABLE_IWYU)
    set_property(TARGET fls_logger PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()