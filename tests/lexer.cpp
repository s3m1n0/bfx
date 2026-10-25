
#include "../src/lexer.hpp"

#include <gtest/gtest.h>

#include <string_view>
#include <vector>

using enum TokenInstructions;

TEST(LexerTest, ParsesEveryInstruction) {
  const auto tokens = parse_source_code("+-<> ,.");

  ASSERT_EQ(tokens.size(), 6);

  EXPECT_EQ(tokens[0].instruction, AddPointer);
  EXPECT_EQ(tokens[1].instruction, SubstracktPointer);
  EXPECT_EQ(tokens[2].instruction, MovePointerToLeft);
  EXPECT_EQ(tokens[3].instruction, MovePointerToRight);
  EXPECT_EQ(tokens[4].instruction, Input);
  EXPECT_EQ(tokens[5].instruction, Output);
}

TEST(LexerTest, ParsesMultipleInstructions) {
  const auto tokens = parse_source_code("++>--<");

  ASSERT_EQ(tokens.size(), 6);

  EXPECT_EQ(tokens[0].instruction, AddPointer);
  EXPECT_EQ(tokens[1].instruction, AddPointer);
  EXPECT_EQ(tokens[2].instruction, MovePointerToRight);
  EXPECT_EQ(tokens[3].instruction, SubstracktPointer);
  EXPECT_EQ(tokens[4].instruction, SubstracktPointer);
  EXPECT_EQ(tokens[5].instruction, MovePointerToLeft);
}

TEST(LexerTest, IgnoresNonInstructionCharacters) {
  const auto tokens = parse_source_code("abc+xyz>123.");

  ASSERT_EQ(tokens.size(), 3);

  EXPECT_EQ(tokens[0].instruction, AddPointer);
  EXPECT_EQ(tokens[1].instruction, MovePointerToRight);
  EXPECT_EQ(tokens[2].instruction, Output);
}

TEST(LexerTest, RecordsSourcePositions) {
  const auto tokens = parse_source_code("abc+>.");

  ASSERT_EQ(tokens.size(), 3);

  EXPECT_EQ(tokens[0].source_line, 3);
  EXPECT_EQ(tokens[1].source_line, 4);
  EXPECT_EQ(tokens[2].source_line, 5);
}

TEST(LexerTest, EmptySourceProducesNoTokens) {
  const auto tokens = parse_source_code("");

  EXPECT_TRUE(tokens.empty());
}

TEST(LexerTest, SourceWithoutInstructionsProducesNoTokens) {
  const auto tokens = parse_source_code("hello world! 123");

  EXPECT_TRUE(tokens.empty());
}

TEST(LexerTest, InitializesJumpTargetToZero) {
  const auto tokens = parse_source_code("+->");

  ASSERT_EQ(tokens.size(), 3);

  for (const auto& token : tokens) {
    EXPECT_EQ(token.jump_target, 0);
  }
}

TEST(LexerTest, HandlesInstructionAtBeginningAndEnd) {
  const auto tokens = parse_source_code("+abc.");

  ASSERT_EQ(tokens.size(), 2);

  EXPECT_EQ(tokens[0].instruction, AddPointer);
  EXPECT_EQ(tokens[0].source_line, 0);

  EXPECT_EQ(tokens[1].instruction, Output);
  EXPECT_EQ(tokens[1].source_line, 4);
}
