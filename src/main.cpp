#include <iostream>
#include <span>

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cout << "please provide a file path";
    return 1;
  }
  for (auto i : std::span<char*>(argv, argc)) {
    std::cout << i << "\n";
  }
}