#include "../runtime.hpp"

#include <iostream>

void SimpleRuntime::run(const std::vector<IR>& ir) {
  for (int i{0}; i < ir.size(); i++) {
    IR instruction{ir[i]};
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
