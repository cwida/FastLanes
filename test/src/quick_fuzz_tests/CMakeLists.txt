include(GoogleTest)                   # keep only once in the whole tree

add_executable(quick_fuzz_test
        quick_fuzz_test.cpp)

target_link_libraries(quick_fuzz_test
        PRIVATE
        GTest::gtest_main
        FastLanes)

fls_enable_sanitizers(quick_fuzz_test)

gtest_discover_tests(
        quick_fuzz_test

        # --- 1️⃣  DROP the second --gtest_filter -----------------
        # Leave only the flag you really need below
        EXTRA_ARGS
        --gtest_also_run_disabled_tests  # (optional; keep if you want this)
        # --- 2️⃣  ADD a prefix so CI can match names cleanly ------
        TEST_PREFIX QuickFuzz_               # final names like "QuickFuzz_QuickFuzz_Case0.Random"
        PROPERTIES
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        DISCOVERY_TIMEOUT 30
)
