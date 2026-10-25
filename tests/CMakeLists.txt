enable_testing()

add_executable(
  lexer_test
  lexer.cpp
)
target_link_libraries(
  lexer_test 
  PRIVATE
    bfx_lib
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(lexer_test)
