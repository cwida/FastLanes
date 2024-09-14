add_library(fls_csv
        OBJECT
        #
        csv.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_csv>
        PARENT_SCOPE)

if (FLS_ENABLE_IWYU)
    set_property(TARGET fls_csv PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()