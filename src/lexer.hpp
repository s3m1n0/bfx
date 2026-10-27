#ifndef LEXER_H
#define LEXER_H

#include <stddef.h>

#include <string>
#include <vector>

enum class TokenInstructions {
  AddPointer,          // +
  SubstracktPointer,   // -
  MovePointerToRight,  // >
  MovePointerToLeft,   // <
  JumpIfZero,          // [
  JumpIfNotZero,       // ]
  Input,               // ,
  Output               // .
};

struct Token {
  TokenInstructions instruction;
  int jump_target;
  size_t source_line;
};

std::vector<Token> parse_source_code(std::string_view source_code);

#endif
