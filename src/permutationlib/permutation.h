#pragma once

#include <vector>


class Permutation {
private:
  std::vector<int16_t> perm;
public:
  Permutation();
  Permutation(const std::vector<int16_t>& _perm);
  
  Permutation operator*(const Permutation& p);
  Permutation& operator=(const Permutation& p);

  bool operator==(const Permutation& p);

  int16_t & operator[](int32_t i);
  const int16_t& operator[](int32_t i) const;

  
};