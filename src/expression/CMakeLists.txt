add_library(fls_expression
        OBJECT
        alp_expression.cpp
        analyze_operator.cpp
        # CMakeLists.txt
        cross_rle_operator.cpp
        data_type.cpp
        decoding_operator.cpp
        dict_expression.cpp
        encoding_operator.cpp
        expression_executor.cpp
        frequency_operator.cpp
        fsst12_dict_operator.cpp
        fsst12_expression.cpp
        fsst_dict_operator.cpp
        fsst_expression.cpp
        interpreter.cpp
        new_rpn.cpp
        null_operator.cpp
        physical_expression.cpp
        predicate_operator.cpp
        rle_expression.cpp
        rsum_operator.cpp
        scan_operator.cpp
        selection_ds.cpp
        slpatch_operator.cpp
        transpose_operator.cpp
)

if (FLS_ENABLE_IWYU)
    set_target_properties(fls_expression PROPERTIES CXX_INCLUDE_WHAT_YOU_USE ${iwyu_path})
endif ()

set(FASTLANES_OBJECT_FILES
        ${FASTLANES_OBJECT_FILES} $<TARGET_OBJECTS:fls_expression>
        PARENT_SCOPE)


target_compile_options(fls_expression PRIVATE -Wno-macro-redefined)
