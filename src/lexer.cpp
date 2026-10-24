#include "lexer.hpp"

#include <iostream>
#include <optional>
#include <string>
#include <vector>

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
        instruction = SubstracktPointer;
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
    }

    if (instruction.has_value()) {
      output.push_back(Token{.instruction = instruction.value(),
                             .jump_target = 0,
                             .source_line = i});
    }
  }

  return output;
}