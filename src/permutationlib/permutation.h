#pragma once

#include <vector>


class Permutation {
private:
  uint8_t perm[32];
  uint32_t reverse;
public:
  Permutation();
  Permutation(std::vector<uint8_t> _perm, uint32_t reverse_bf);
  Permutation(uint8_t _perm[32], uint32_t reverse_bf);

  
  Permutation operator*(const Permutation& p);
  Permutation& operator=(const Permutation& p);

  bool operator==(const Permutation& p);

  uint8_t & operator[](int32_t i);
  const uint8_t& operator[](int32_t i) const;
};