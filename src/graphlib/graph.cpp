#include "graph.h"


Graph::Graph() : bitfield(0) {}

void Graph::set(int32_t i)
{
  if (i < 0)
    throw;

  bitfield |= 1 << i;
}

bool Graph::get(int32_t i)
{
  if (i < 0)
    throw;

  return bitfield & i << i;
}

Graph Graph::operator*(const Permutation& p)
{
    return Graph();
}

