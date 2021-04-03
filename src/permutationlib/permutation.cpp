#include "permutation.h"
#include <list>
#include <algorithm>
#include <iostream>
#define __TEST

Permutation::Permutation()
{
}

Permutation::Permutation(const std::vector<int16_t> & _perm) : perm(_perm) {}

Permutation Permutation::operator*(const Permutation& p)
{
  if (perm.size() != p.perm.size())
    throw 1;

  std::vector<int16_t> res(perm.size());

  for (int i = 0; i < perm.size(); ++i) {
    int sign = (p.perm[i] % 2 + (p.perm[i] + 1) % 2);
    res[i] = sign * perm[std::abs(p.perm[i]) - 1];
  }
  return Permutation(res);
}

Permutation& Permutation::operator*=(const Permutation& p)
{
  if (perm.size() != p.perm.size())
    throw 1;

  std::vector<int16_t> res(perm.size());

  for (int i = 0; i < perm.size(); ++i) {
    int sign = (p.perm[i] % 2 + (p.perm[i] + 1) % 2);
    res[i] = sign * perm[std::abs(p.perm[i]) - 1];
  }

  perm = res;

  return *this;
}

Permutation& Permutation::operator=(const Permutation& p)
{
  perm = p.perm;
  return *this;
}

bool Permutation::operator==(const Permutation& p)
{
  if (p.perm.size() != perm.size())
    return false;

  for (int i = 0; i < perm.size(); i++)
    if (perm[i] != p.perm[i])
      return false;
  
  return true;
}


int16_t & Permutation::operator[](const int32_t i)
{
  return perm[i];
}

const int16_t& Permutation::operator[](int32_t i) const
{
  return perm[i];
}

const uint32_t Permutation::get_size() const
{
  return perm.size();
}

std::ostream& operator<<(std::ostream& os, Permutation g)
{
  for (auto c : g.perm)
    std::cout << c << " ";
  return os;
}
