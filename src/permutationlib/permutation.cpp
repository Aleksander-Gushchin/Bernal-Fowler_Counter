#include "permutation.h"
#include <list>
#include <algorithm>
#define __TEST

Permutation::Permutation()
{
  reverse = 0;
  for (int i = 0; i < 32; ++i)
    perm[i] = i;
}

Permutation::Permutation(std::vector<uint8_t> _perm, uint32_t reverse_bf)
{
  if (_perm.size() != 32)
    throw;

  reverse = reverse_bf;
  for (int i = 0; i < 32; ++i)
    perm[i] = _perm[i];

}

Permutation::Permutation(uint8_t _perm[32], uint32_t reverse_bf)
{
  reverse = reverse_bf;
  for (int i = 0; i < 32; ++i)
    perm[i] = _perm[i];
}

Permutation Permutation::operator*(const Permutation& p)
{
  uint8_t res[32];
  uint32_t reverse_res = 0;

  for (int i = 0; i < 32; ++i) {
    uint32_t index = p.perm[i];
    reverse_res |= 
      (((p.reverse & (1 << i)) >> i) ^ // from operand
      ((reverse & (1 << index)) >> index)) // from source
      << i;
    res[i] = perm[index];
  }
  return Permutation(res, reverse_res);
}

Permutation& Permutation::operator=(const Permutation& p)
{
  reverse = p.reverse;
  for (int i = 0; i < 32; ++i)
    perm[i] = p.perm[i];

  return *this;
}

bool Permutation::operator==(const Permutation& p)
{
  if (reverse != p.reverse)
    return false;

  for (int i = 0; i < 32; i++)
    if (perm[i] != p.perm[i])
      return false;
  
  return true;
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
