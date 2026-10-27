#ifndef OPTIMIZE_H
#define OPTIMIZE_H

#include <stddef.h>

#include <vector>

#include "lexer.hpp"

enum class IRInstructions {
  // basic instructions
  AddPointer,
  MovePointer,

  // io
  Input,
  Output,

  // loop basics
  LoopStart,
  Loopend,

  // optimization
  ClearPointer,     // [-]
  MovePointerValue  // [->+<]
};

struct IR {
  IRInstructions instruction;
  int value;
};

std::vector<IR> parse_instruction_tokens(
    const std::vector<Token>& instructions);
void optimize_instructions(std::vector<IR>& ir);
#endif
