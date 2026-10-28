#include "../src/optimize.hpp"

#include <gtest/gtest.h>

#include <vector>

// Test parsing of Input and Output instructions
TEST(ParseInstructionTokensTest, ParsesInputAndOutput) {
  std::vector<Token> tokens = {
      {.instruction = TokenInstructions::Input, .jump_target = 0},
      {.instruction = TokenInstructions::Output, .jump_target = 0}};

  std::vector<IR> ir = parse_instruction_tokens(tokens);

  ASSERT_EQ(ir.size(), 2);
  EXPECT_EQ(ir[0].instruction, IRInstructions::Input);
  EXPECT_EQ(ir[0].value, 0);

  EXPECT_EQ(ir[1].instruction, IRInstructions::Output);
  EXPECT_EQ(ir[1].value, 0);
}

// Test pointer movement instructions (Right and Left)
TEST(ParseInstructionTokensTest, ParsesPointerMovements) {
  std::vector<Token> tokens = {
      {.instruction = TokenInstructions::MovePointerToRight, .jump_target = 0},
      {.instruction = TokenInstructions::MovePointerToLeft, .jump_target = 0}};

  std::vector<IR> ir = parse_instruction_tokens(tokens);

  ASSERT_EQ(ir.size(), 2);
  EXPECT_EQ(ir[0].instruction, IRInstructions::MovePointer);
  EXPECT_EQ(ir[0].value, 1);

  EXPECT_EQ(ir[1].instruction, IRInstructions::MovePointer);
  EXPECT_EQ(ir[1].value, -1);
}

// Test pointer arithmetic instructions
TEST(ParseInstructionTokensTest, ParsesPointerArithmetic) {
  std::vector<Token> tokens = {
      {.instruction = TokenInstructions::AddPointer, .jump_target = 0},
      {.instruction = TokenInstructions::SubstractPointer, .jump_target = 0}};

  std::vector<IR> ir = parse_instruction_tokens(tokens);

  ASSERT_EQ(ir.size(), 2);
  EXPECT_EQ(ir[0].instruction, IRInstructions::AddPointer);
  EXPECT_EQ(ir[0].value, 1);

  EXPECT_EQ(ir[1].instruction, IRInstructions::AddPointer);
  EXPECT_EQ(ir[1].value, -1);
}

// Test jump/loop instructions with targets
TEST(ParseInstructionTokensTest, ParsesJumpsAndLoops) {
  std::vector<Token> tokens = {
      {.instruction = TokenInstructions::JumpIfZero, .jump_target = 5},
      {.instruction = TokenInstructions::JumpIfNotZero, .jump_target = 2}};

  std::vector<IR> ir = parse_instruction_tokens(tokens);

  ASSERT_EQ(ir.size(), 2);
  EXPECT_EQ(ir[0].instruction, IRInstructions::LoopStart);
  EXPECT_EQ(ir[0].value, 5);

  EXPECT_EQ(ir[1].instruction, IRInstructions::LoopEnd);
  EXPECT_EQ(ir[1].value, 2);
}

// Test handling of an empty token list
TEST(ParseInstructionTokensTest, HandlesEmptyTokenList) {
  std::vector<Token> tokens = {};
  std::vector<IR> ir = parse_instruction_tokens(tokens);

  EXPECT_TRUE(ir.empty());
}

TEST(OptimizeTest, EmptyTokenListProducesEmptyIR) {
  std::vector<IR> ir = parse_instruction_tokens({});
  optimize_instructions(ir);
  EXPECT_TRUE(ir.empty());
}

TEST(OptimizeTest, CombinesConsecutiveIncrements) {
  const std::vector<Token> tokens{
      {.instruction = TokenInstructions::AddPointer, .jump_target = 0},
      {.instruction = TokenInstructions::AddPointer, .jump_target = 0},
      {.instruction = TokenInstructions::AddPointer, .jump_target = 0}};

  auto ir = parse_instruction_tokens(tokens);
  optimize_instructions(ir);

  ASSERT_EQ(ir.size(), 1);
  EXPECT_EQ(ir[0].instruction, IRInstructions::AddPointer);
  EXPECT_EQ(ir[0].value, 3);
}

TEST(OptimizeTest, CombinesConsecutiveRightPointerMoves) {
  const std::vector<Token> tokens{
      {.instruction = TokenInstructions::MovePointerToRight, .jump_target = 0},
      {.instruction = TokenInstructions::MovePointerToRight, .jump_target = 0}};

  auto ir = parse_instruction_tokens(tokens);
  optimize_instructions(ir);

  ASSERT_EQ(ir.size(), 1);
  EXPECT_EQ(ir[0].instruction, IRInstructions::MovePointer);
  EXPECT_EQ(ir[0].value, 2);
}

TEST(OptimizeTest, DifferentOperationsEndACombinedRun) {
  const std::vector<Token> tokens{
      {.instruction = TokenInstructions::AddPointer, .jump_target = 0},
      {.instruction = TokenInstructions::AddPointer, .jump_target = 0},
      {.instruction = TokenInstructions::MovePointerToRight, .jump_target = 0},
      {.instruction = TokenInstructions::AddPointer, .jump_target = 0}};

  auto ir = parse_instruction_tokens(tokens);
  optimize_instructions(ir);

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
      {.instruction = TokenInstructions::JumpIfZero, .jump_target = 3},
      {.instruction = TokenInstructions::Input, .jump_target = 0},
      {.instruction = TokenInstructions::Output, .jump_target = 0},
      {.instruction = TokenInstructions::JumpIfNotZero, .jump_target = 0}};

  auto ir = parse_instruction_tokens(tokens);
  optimize_instructions(ir);

  ASSERT_EQ(ir.size(), 4);
  EXPECT_EQ(ir[0].instruction, IRInstructions::LoopStart);
  EXPECT_EQ(ir[0].value, 3);
  EXPECT_EQ(ir[1].instruction, IRInstructions::Input);
  EXPECT_EQ(ir[2].instruction, IRInstructions::Output);
  EXPECT_EQ(ir[3].instruction, IRInstructions::LoopEnd);
  EXPECT_EQ(ir[3].value, 0);
}

TEST(OptimizeTest, DoesNotCombineIncrementsAcrossIO) {
  const std::vector<Token> tokens{
      {.instruction = TokenInstructions::AddPointer, .jump_target = 0},
      {.instruction = TokenInstructions::Output, .jump_target = 0},
      {.instruction = TokenInstructions::AddPointer, .jump_target = 0}};

  auto ir = parse_instruction_tokens(tokens);
  optimize_instructions(ir);

  ASSERT_EQ(ir.size(), 3);
  EXPECT_EQ(ir[0].instruction, IRInstructions::AddPointer);
  EXPECT_EQ(ir[0].value, 1);
  EXPECT_EQ(ir[1].instruction, IRInstructions::Output);
  EXPECT_EQ(ir[2].instruction, IRInstructions::AddPointer);
  EXPECT_EQ(ir[2].value, 1);
}