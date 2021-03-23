#include "graph.h"
#include <iostream>
#include <iomanip>
#include <utility>

Graph::Graph(){}

Graph::Graph(uint32_t b_field, uint8_t size){
  int real_size = size < 32 ? size : 32;
  bitfield = std::vector <bool>(real_size);
  for (int i = 0; i < real_size; ++i)
    bitfield[i] = (b_field & 1 << i) >> i;
}

Graph::Graph(const std::vector<bool>& vec){
  bitfield = vec;
}

Graph::Graph(const Graph& g)
{
  bitfield = g.bitfield;
}


Graph& Graph::operator=(const Graph& g)
{
  bitfield = g.bitfield;
  return *this;
}

Graph& Graph::operator=(Graph&& g) noexcept
{
  bitfield = move(g.bitfield);
  return *this;
}

Graph Graph::operator*(const Permutation& p){
  if (p.get_size() != bitfield.size())
    throw;

  std::vector<bool> res(bitfield.size());

  for (int i = 0; i < bitfield.size(); ++i) {
    int index = p[i];
    int sign = (index % 2 + (index + 1) % 2);
    res[i] = (-sign + 1)/2 ^ bitfield[std::abs(index) - 1];
  }

  return Graph(res);
}

bool Graph::operator==(const Graph& g)
{
  if (g.bitfield.size() != bitfield.size())
    return false;

  for (int i = 0; i < bitfield.size(); i++)
    if (bitfield[i] != g.bitfield[i])
      return false;

  return true;
}

bool Graph::operator==(Graph&& g)
{
  if (g.bitfield.size() != bitfield.size())
    return false;

  for (int i = 0; i < bitfield.size(); i++)
    if (bitfield[i] != g.bitfield[i])
      return false;

  return true;
}

std::vector<bool>::reference Graph::operator[](uint32_t i)
{
  return bitfield[i];
}

std::ostream& operator<<(std::ostream& os, Graph g)
{
  for (auto c : g.bitfield)
    std::cout << static_cast<int>(c) << " ";

  return os;
}
