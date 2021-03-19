#pragma once

#include <vector>
#include "permutation.h"

class Graph {
private:
  std::vector<bool> bitfield;
public:
  Graph();
  Graph(uint32_t b_field, uint8_t size);
  Graph(const std::vector<bool>& vec);

  Graph operator*(const Permutation & p);

  bool get(uint32_t i);
};