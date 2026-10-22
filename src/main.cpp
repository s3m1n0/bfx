#include <format>
#include <iostream>
#include <span>

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "please provide a file path\n";
    return 1;
  }
  for (int i = 1; i < argc; i++) {
    std::cout << std::format("{}: [{}]\n", i, argv[i]);
  }
}