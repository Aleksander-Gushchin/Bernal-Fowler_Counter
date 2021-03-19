#include "graph.h"


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

Graph Graph::operator*(const Permutation& p){
  if (p.get_size() != bitfield.size())
    throw;

  std::vector<bool> res(bitfield.size());

  for (int i = 0; i < bitfield.size(); ++i) {
    int index = p[i];
    int sign = (index % 2 + (index + 1) % 2);
    res[i] = sign ^ bitfield[std::abs(index)];
  }

}

std::vector<bool>::reference Graph::operator[](uint32_t i)
{
  return bitfield[i];
}



