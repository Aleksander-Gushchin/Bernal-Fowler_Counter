#pragma once

#include <vector>
#include "permutation.h"

class Graph {
private:
  std::vector<bool> bitfield;
public:
  Graph();
  Graph(uint32_t b_field, uint8_t size = 32);
  Graph(const std::vector<bool>& vec);

  Graph& operator=(const Graph& g);

  Graph operator*(const Permutation & p);
  bool operator==(const Graph& g);
  bool operator==(Graph&& g);

  std::vector< bool >::reference operator[](uint32_t i);
};