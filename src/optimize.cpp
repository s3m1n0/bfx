#include "optimize.hpp"

#include <stddef.h>

#include <optional>
#include <span>
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

// could alter code behaviour. MOVE TO RUNTIME
// int wrap_add(int value1, int value2, int wrap_min_boundary,
//              int wrap_max_boundary) {
//   const int range = wrap_max_boundary - wrap_min_boundary + 1;
//   int result = (value1 + value2 - wrap_min_boundary) % range;

//   if (result < 0) result += range;

//   return result + wrap_min_boundary;
// }

void combine_instructions(std::vector<IR>& ir) {
  std::vector<IR> optimized_ir;
  std::vector<size_t> loop_stack;

  optimized_ir.reserve(ir.size());

  for (const IR& current_ir : ir) {
    switch (current_ir.instruction) {
      case IRInstructions::AddPointer:
      case IRInstructions::MovePointer: {
        if (!optimized_ir.empty() &&
            optimized_ir.back().instruction == current_ir.instruction) {
          optimized_ir.back().value += current_ir.value;
        } else {
          optimized_ir.push_back(current_ir);
        }
        break;
      }

      case IRInstructions::LoopStart: {
        size_t loop_start = optimized_ir.size();

        loop_stack.push_back(loop_start);

        optimized_ir.push_back(
            IR{.instruction = IRInstructions::LoopStart, .value = 0});
        break;
      }

      case IRInstructions::LoopEnd: {
        size_t loop_start = loop_stack.back();
        size_t loop_end = optimized_ir.size();

        optimized_ir.push_back(IR{.instruction = IRInstructions::LoopEnd,
                                  .value = static_cast<int>(loop_start)});

        optimized_ir[loop_start].value = static_cast<int>(loop_end);

        loop_stack.pop_back();
        break;
      }

      default:
        optimized_ir.push_back(current_ir);
        break;
    }
  }

  ir = std::move(optimized_ir);
}