#include "optimize.hpp"

#include <stddef.h>

#include <vector>

#include "lexer.hpp"

std::vector<IR> parse_instruction_tokens(
    const std::vector<Token>& instructions) {
  std::vector<IR> ir{};

  for (size_t i{0}; i < instructions.size(); i++) {
    Token token{instructions[i]};
  }
  return ir;
}