#include "optimize.hpp"

#include <stddef.h>

#include <optional>
#include <vector>

#include "lexer.hpp"

std::vector<IR> parse_instruction_tokens(
    const std::vector<Token>& instructions) {
  std::vector<IR> ir{};
  std::vector<Token> instruction_stack{};

  for (size_t i{0}; i < instructions.size(); i++) {
    Token token{instructions[i]};

    switch (token.instruction) {
      case (TokenInstructions::Input):
        ir.push_back(IR{.instruction = IRInstructions::Input, .value = 0});
        break;
      case (TokenInstructions::Output):
        ir.push_back(IR{.instruction = IRInstructions::Output, .value = 0});
        break;
      case (TokenInstructions::MovePointerToRight):
        ir.push_back(
            IR{.instruction = IRInstructions::MovePointer, .value = 1});
        break;
      case (TokenInstructions::MovePointerToLeft):
        ir.push_back(
            IR{.instruction = IRInstructions::MovePointer, .value = -1});
        break;
      case (TokenInstructions::AddPointer):
        ir.push_back(IR{.instruction = IRInstructions::AddPointer, .value = 1});
        break;
      case (TokenInstructions::SubstractPointer):
        ir.push_back(
            IR{.instruction = IRInstructions::AddPointer, .value = -1});
        break;
      case (TokenInstructions::JumpIfZero):
        ir.push_back(IR{.instruction = IRInstructions::LoopStart,
                        .value = token.jump_target});
        break;
      case (TokenInstructions::JumpIfNotZero):
        ir.push_back(IR{.instruction = IRInstructions::LoopEnd,
                        .value = token.jump_target});
        break;
    }
  }
  return ir;
}

// AddPointer wraps at 255, pointer movement at the cell boundaries 0 - 30k
int combine_instruction_value(int value1, int value2, int wrap_min_boundary,
                              int wrap_max_boundary, int wrap_min_snapback) {
  int result = value1 + value2;
  if (result > wrap_max_boundary) result = 0;
  if (result < wrap_min_boundary) result = wrap_min_snapback;
  return result;
}

void optimize_instructions(std::vector<IR>& ir) {
  if (ir.size() < 0) {
    return;
  }
  std::vector<IR> optimized_ir{ir[0]};
  optimized_ir.reserve(ir.size());
  for (size_t i{1}; i < ir.size(); i++) {
    IR current_ir{ir[i]};
    switch (current_ir.instruction) {
      case IRInstructions::AddPointer: {
        if (optimized_ir.back().instruction == current_ir.instruction) {
          optimized_ir.back().value = combine_instruction_value(
              optimized_ir.back().value, current_ir.value, 0, 255, 255);
        } else {
          optimized_ir.push_back(current_ir);
        }
        break;
      }
      case IRInstructions::MovePointer: {
        if (optimized_ir.back().instruction == current_ir.instruction) {
          optimized_ir.back().value = combine_instruction_value(
              optimized_ir.back().value, current_ir.value, 0, 30000, 30000);
        } else {
          optimized_ir.push_back(current_ir);
        }
        break;
      }
    }
  }
}