enable_testing()

add_executable(
  tests
  lexer_test.cpp
  optimize_test.cpp
)
target_link_libraries(
  tests 
  PRIVATE
    bfx_lib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
