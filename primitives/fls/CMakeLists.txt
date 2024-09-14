add_library(fls_manual
        OBJECT
        double_scalar_transpose.cpp
        double_scalar_untranspose.cpp)

set(FLS_GENERATED_OBJECT_FILES
        ${FLS_GENERATED_OBJECT_FILES} $<TARGET_OBJECTS:fls_manual>
        PARENT_SCOPE)