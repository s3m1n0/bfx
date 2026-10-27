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
        ir.push_back(
            IR{.instruction = IRInstructions::AddPointer, .value = -1});
        break;
      case (TokenInstructions::SubstracktPointer):
        ir.push_back(
            IR{.instruction = IRInstructions::AddPointer, .value = -1});
        break;
      case (TokenInstructions::JumpIfZero):
        ir.push_back(IR{.instruction = IRInstructions::LoopStart,
                        .value = token.jump_target});
        break;
      case (TokenInstructions::JumpIfNotZero):
        ir.push_back(IR{.instruction = IRInstructions::Loopend,
                        .value = token.jump_target});
        break;
    }
  }
  return ir;
}
