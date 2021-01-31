#pragma once

#include <vector>
#include "permutation.h"

class Graph {
private:
  uint64_t bitfield;
public:
  Graph();
  void set(int32_t i);
  bool get(int32_t i);
  Graph operator*(const Permutation & p);
};