add_library(fls_printer
        OBJECT
        #[[]]
        output.cpp
        output_factory.cpp
        to_str.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_printer>
        PARENT_SCOPE)

if (FLS_ENABLE_IWYU)
    set_property(TARGET fls_printer PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()