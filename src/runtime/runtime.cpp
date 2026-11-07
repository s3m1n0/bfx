#include "../runtime.hpp"

#include <iostream>

void SimpleRuntime::run(const Optimization& ir) {
  const auto& instructions = ir.get_ir();
  for (int i{0}; i < instructions.size(); i++) {
    IR instruction{instructions[i]};
    switch (instruction.instruction) {
      case IRInstructions::AddPointer:
        m_memory[m_pointer] = (m_memory[m_pointer] + instruction.value) % 256;
        break;
      case IRInstructions::MovePointer:
        m_pointer = (m_pointer + instruction.value) % 30'000;
        break;
      case IRInstructions::Output:
        std::cout << static_cast<char>(m_memory[m_pointer]);
        break;
      case IRInstructions::Input: {
        char input;
        if (std::cin.get(input)) {
          m_memory[m_pointer] = static_cast<unsigned char>(input);
        }
        break;
      }
      case IRInstructions::LoopStart: {
        if (m_memory[m_pointer] == 0) i = instruction.value;
        break;
      }
      case IRInstructions::LoopEnd: {
        if (m_memory[m_pointer] != 0) i = instruction.value;
        break;
      }
    }
  }
  std::cout << std::endl;
}
