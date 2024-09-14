add_library(fls_expression
        OBJECT
        encoding_operator.cpp
        expression_executor.cpp
        interpreter.cpp
        logical_expression.cpp
        new_rpn.cpp
        physical_expression.cpp
        predicate_operator.cpp
        selection_ds.cpp
        data_type.cpp
        store_operator.cpp
)

if (FLS_ENABLE_IWYU)
    set_target_properties(fls_expression PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_expression>
        PARENT_SCOPE)