# On MSVC (and clang-cl), large heap allocations can touch guard pages whose
# transient 0xc0000005 exceptions are caught by GoogleTest's SEH wrapper,
# causing spurious test failures.  This small static library installs a VEH
# handler that commits those pages before GTest intercepts the fault.
# On non-MSVC toolchains the source compiles to an empty translation unit.
add_library(msvc_heap_guard OBJECT msvc_heap_guard.cpp)

add_subdirectory(dataset_tests)
add_subdirectory(expression_tests)
add_subdirectory(fls_reader_tests)
add_subdirectory(primitive_tests)
add_subdirectory(quick_fuzz_tests)
add_subdirectory(unit_tests)

