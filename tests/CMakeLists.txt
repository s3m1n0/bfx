enable_testing()

add_executable(
  potential_test
  potential_test.cpp
)
target_link_libraries(
  potential_test
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(potential_test)
