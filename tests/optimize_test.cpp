#include "../src/optimize.hpp"

#include <gtest/gtest.h>

#include <vector>

namespace {

Token MakeToken(TokenInstructions instruction, size_t jump_target = 0) {
  return Token{
      .instruction = instruction, .jump_target = jump_target, .source_line = 0};
}

}  // namespace

TEST(OptimizeTest, EmptyTokenListProducesEmptyIR) {
  EXPECT_TRUE(parse_instruction_tokens({}).empty());
}

TEST(OptimizeTest, CombinesConsecutiveIncrements) {
  const std::vector<Token> tokens{MakeToken(TokenInstructions::AddPointer),
                                  MakeToken(TokenInstructions::AddPointer),
                                  MakeToken(TokenInstructions::AddPointer)};

  const auto ir = parse_instruction_tokens(tokens);

  ASSERT_EQ(ir.size(), 1);
  EXPECT_EQ(ir[0].instruction, IRInstructions::AddPointer);
  EXPECT_EQ(ir[0].value, 3);
}

TEST(OptimizeTest, CombinesConsecutiveRightPointerMoves) {
  const std::vector<Token> tokens{
      MakeToken(TokenInstructions::MovePointerToRight),
      MakeToken(TokenInstructions::MovePointerToRight)};

  const auto ir = parse_instruction_tokens(tokens);

  ASSERT_EQ(ir.size(), 1);
  EXPECT_EQ(ir[0].instruction, IRInstructions::MovePointer);
  EXPECT_EQ(ir[0].value, 2);
}

TEST(OptimizeTest, DifferentOperationsEndACombinedRun) {
  const std::vector<Token> tokens{
      MakeToken(TokenInstructions::AddPointer),
      MakeToken(TokenInstructions::AddPointer),
      MakeToken(TokenInstructions::MovePointerToRight),
      MakeToken(TokenInstructions::AddPointer)};

  const auto ir = parse_instruction_tokens(tokens);

  ASSERT_EQ(ir.size(), 3);
  EXPECT_EQ(ir[0].instruction, IRInstructions::AddPointer);
  EXPECT_EQ(ir[0].value, 2);
  EXPECT_EQ(ir[1].instruction, IRInstructions::MovePointer);
  EXPECT_EQ(ir[1].value, 1);
  EXPECT_EQ(ir[2].instruction, IRInstructions::AddPointer);
  EXPECT_EQ(ir[2].value, 1);
}

TEST(OptimizeTest, PreservesIOInstructionsAndLoopTargets) {
  const std::vector<Token> tokens{
      MakeToken(TokenInstructions::JumpIfZero, 3),
      MakeToken(TokenInstructions::Input), MakeToken(TokenInstructions::Output),
      MakeToken(TokenInstructions::JumpIfNotZero, 0)};

  const auto ir = parse_instruction_tokens(tokens);

  ASSERT_EQ(ir.size(), 4);
  EXPECT_EQ(ir[0].instruction, IRInstructions::LoopStart);
  EXPECT_EQ(ir[0].value, 3);
  EXPECT_EQ(ir[1].instruction, IRInstructions::Input);
  EXPECT_EQ(ir[2].instruction, IRInstructions::Output);
  EXPECT_EQ(ir[3].instruction, IRInstructions::Loopend);
  EXPECT_EQ(ir[3].value, 0);
}

TEST(OptimizeTest, DoesNotCombineIncrementsAcrossIO) {
  const std::vector<Token> tokens{MakeToken(TokenInstructions::AddPointer),
                                  MakeToken(TokenInstructions::Output),
                                  MakeToken(TokenInstructions::AddPointer)};

  const auto ir = parse_instruction_tokens(tokens);

  ASSERT_EQ(ir.size(), 3);
  EXPECT_EQ(ir[0].instruction, IRInstructions::AddPointer);
  EXPECT_EQ(ir[0].value, 1);
  EXPECT_EQ(ir[1].instruction, IRInstructions::Output);
  EXPECT_EQ(ir[2].instruction, IRInstructions::AddPointer);
  EXPECT_EQ(ir[2].value, 1);
}
