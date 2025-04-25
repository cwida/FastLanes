add_library(fls_reader
        OBJECT
        column_view.cpp
        csv_reader.cpp
        external_reader.cpp
        json_reader.cpp
        rowgroup_view.cpp
        rowgroup_reader.cpp
        segment.cpp
        table_reader.cpp
        table_view.cpp
)

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_reader>
        PARENT_SCOPE)

if (FLS_ENABLE_IWYU)
    set_property(TARGET fls_reader PROPERTY CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()