#include "permutation.h"
#include <list>
#include <algorithm>
#define __TEST

Permutation::Permutation()
{
  for (int i = 0; i < 32; ++i)
    perm[i] = i;
}

Permutation::Permutation(std::vector<uint8_t> _perm)
{
  if (_perm.size() != 32)
    throw;

#ifdef __TEST
  std::vector<uint8_t> a(_perm);
  sort(a.begin(), a.end());
  for (int i = 0; i < 31; ++i)
    if (a[i] != i)
      throw;
#endif // __TEST

  for (int i = 0; i < 32; ++i)
    perm[i] = _perm[i];

}

Permutation::Permutation(uint8_t _perm[32])
{
  for (int i = 0; i < 32; ++i)
    perm[i] = _perm[i];
}

Permutation Permutation::operator*(const Permutation& p)
{
  uint8_t res[32];

  for (int i = 0; i < 32; ++i)
    res[i] = perm[(p[i])];

  return Permutation(res);
}

Permutation& Permutation::operator=(const Permutation& p)
{

  for (int i = 0; i < 32; ++i)
    this->perm[i] = p[i];

#ifdef __TEST
  std::vector<uint8_t> a;
  for (int i = 0; i < 32; ++i)
    a.push_back(this->perm[i]);
  sort(a.begin(), a.end());
  for (int i = 0; i < 31; ++i)
    if (a[i] != i)
      throw;
#endif // __TEST

  return *this;
}

uint8_t & Permutation::operator[](const int32_t i)
{
  if (i < 0 || i > 31)
    throw;

  return perm[i];
}

const uint8_t& Permutation::operator[](int32_t i) const
{
  if (i < 0 || i > 31)
    throw;

  return perm[i];
}
