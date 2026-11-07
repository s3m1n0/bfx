#include <iostream>

#include "optimize.hpp"

void print_ir(const IR& ir) {
  switch (ir.instruction) {
    case IRInstructions::AddPointer:
      std::cout << "AddPointer(" << ir.value << ")";
      break;

    case IRInstructions::MovePointer:
      std::cout << "MovePointer(" << ir.value << ")";
      break;

    case IRInstructions::Input:
      std::cout << "Input";
      break;

    case IRInstructions::Output:
      std::cout << "Output";
      break;

    case IRInstructions::LoopStart:
      std::cout << "LoopStart";
      break;

    case IRInstructions::LoopEnd:
      std::cout << "LoopEnd";
      break;

    case IRInstructions::ClearPointer:
      std::cout << "ClearPointer";
      break;

    case IRInstructions::MovePointerValue:
      std::cout << "MovePointerValue(" << ir.value << ")";
      break;
  }
}

void print_token(const Token& token) {
  switch (token.instruction) {
    case TokenInstructions::AddPointer:
      std::cout << "AddPointer" << " at character" << token.source_line;
      break;

    case TokenInstructions::SubstractPointer:
      std::cout << "SubstractPointer" << " at character" << token.source_line;
      break;

    case TokenInstructions::Input:
      std::cout << "Input" << " at character" << token.source_line;
      break;

    case TokenInstructions::Output:
      std::cout << "Output" << " at character" << token.source_line;
      break;

    case TokenInstructions::JumpIfZero:
      std::cout << "LoopStart" << " at character" << token.source_line;
      break;

    case TokenInstructions::JumpIfNotZero:
      std::cout << "LoopEnd" << " at character" << token.source_line;
      break;
  }
}