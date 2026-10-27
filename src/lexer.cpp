#include "lexer.hpp"

#include <format>
#include <iostream>
#include <optional>
#include <string>
#include <vector>

void report_fatal_error(std::string_view error_message,
                        size_t character_index) {
  std::cerr << std::format("error encountered: [{}] at character {}",
                           error_message, character_index)
            << std::endl;
  std::exit(1);
}

std::vector<Token> parse_source_code(std::string_view source_code) {
  using enum TokenInstructions;
  std::vector<Token> output{};
  std::vector<size_t> loop_stack{};
  for (size_t i{0}; i < source_code.length(); i++) {
    std::optional<TokenInstructions> instruction;
    const char c = source_code[i];
    switch (c) {
      case '+':
        instruction = AddPointer;
        break;
      case '-':
        instruction = SubstractPointer;
        break;
      case '>':
        instruction = MovePointerToRight;
        break;
      case '<':
        instruction = MovePointerToLeft;
        break;
      case ',':
        instruction = Input;
        break;
      case '.':
        instruction = Output;
        break;
      case '[': {
        const size_t token_index = output.size();

        output.push_back(Token{
            .instruction = JumpIfZero,
            .jump_target = 0,
            .source_line = i,
        });

        loop_stack.push_back(token_index);
        break;
      }

      case ']': {
        if (loop_stack.empty()) {
          report_fatal_error(
              "encountered a loop closing symbol, but no loop was opened", i);
        }

        const size_t opening_index = loop_stack.back();
        loop_stack.pop_back();

        const size_t closing_index = output.size();

        output.push_back(Token{
            .instruction = JumpIfNotZero,
            .jump_target = opening_index,
            .source_line = i,
        });

        output[opening_index].jump_target = closing_index;
        break;
      }
    }

    if (instruction.has_value()) {
      output.push_back(Token{.instruction = instruction.value(),
                             .jump_target = 0,
                             .source_line = i});
    }
  }

  if (!loop_stack.empty())
    report_fatal_error("unclosed loop", output[loop_stack.back()].source_line);
  return output;
}