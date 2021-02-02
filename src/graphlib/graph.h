#pragma once

#include <vector>
#include "permutation.h"

class Graph {
private:
  uint32_t bitfield;
public:
  Graph();
  Graph(uint32_t i);
  void set(uint32_t i);
  uint32_t get();
  Graph operator*(const Permutation & p);
};