add_library(IntervalMath interval_math.cpp)
target_include_directories(IntervalMath PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(IntervalMath PRIVATE DEBUG_MODE)

  # GTest
  if (GTest_FOUND)
    include(GoogleTest)

    add_executable(IntervalMath_ExtendedSet_test "tests/IntervalMath_ExtendedSet_tests.cpp")
    target_link_libraries(IntervalMath_ExtendedSet_test PRIVATE IntervalMath GTest::gtest_main)
    gtest_discover_tests(IntervalMath_ExtendedSet_test)

    add_executable(IntervalMath_Interval_test "tests/IntervalMath_Interval_test.cpp")
    target_link_libraries(IntervalMath_Interval_test PRIVATE IntervalMath GTest::gtest_main)
    gtest_discover_tests(IntervalMath_Interval_test)
  else()
    message("GTest package is not found! Tests for 'dhmodel' was not compiled.")
  endif()

endif()