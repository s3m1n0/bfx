/*
runtime no JIT compilation yet
*/

#ifndef RUNTIME_H
#define RUNTIME_H
#include <array>
#include <vector>

#include "optimize.hpp"

class RunTimeInterface {
 protected:
  virtual void run(const std::vector<IR>& ir) = 0;
};

class SimpleRuntime : public RunTimeInterface {
 public:
  SimpleRuntime() : m_pointer{0} {};
  void run(const std::vector<IR>& ir);

 private:
  std::array<int, 30'000> m_memory{};
  int m_pointer;
};

#endif