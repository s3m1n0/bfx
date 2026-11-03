/*
runtime no JIT compilation yet
*/

#ifndef RUNTIME_H
#define RUNTIME_H
#include <vector>

#include "optimize.hpp"

void simple_runtime(const std::vector<IR>& ir);

#endif