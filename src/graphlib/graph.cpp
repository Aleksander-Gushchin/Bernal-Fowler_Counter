#include "graph.h"


Graph::Graph() : bitfield(0) {}

Graph::Graph(uint32_t i) : bitfield(i) {}

void Graph::set(uint32_t i)
{
  if (i < 0)
    throw;

  bitfield |= 1 << i;
}

uint32_t Graph::get()
{
  return bitfield;
}

Graph Graph::operator*(const Permutation& p)
{
  uint32_t res;

  for (int i = 0; i < 32; ++i) {
    res |= ((bitfield & 1 << i) >> i) << p[i];
  }

  return Graph(res);
}

