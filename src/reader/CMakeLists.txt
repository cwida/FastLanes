add_library(fls_reader
        OBJECT
        horizontal_column.cpp
        fls_rowgroup.cpp
        reader.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_reader>
        PARENT_SCOPE)

if (FLS_ENABLE_IWYU)
    set_property(TARGET fls_reader PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()