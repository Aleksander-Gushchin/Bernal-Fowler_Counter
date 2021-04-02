#include "invariant.h"
#include <iostream>
#include <iomanip>
#include <utility>

int inline Invariant::Monom::exctract(int val)
{
  return 2 * val - 1;
}

Invariant::Monom::Monom(uint8_t _c,const std::vector<bool>& vec) : cons(_c) , exp(vec)
{
}

int Invariant::Monom::getValue(const Graph& g)
{
  if (g.getSize() != exp.size())
    throw;

  int res = 0;

  for (int i = 0; i < exp.size(); ++i)
    res += exp[i] * exctract(g[i]);
  return cons * res;
}


Invariant::Invariant(const std::vector<int>& cons, const std::vector<std::vector<bool>>& vec)
{
  if (cons.size() != vec.size())
    throw;

  for (int i = 0; i < vec.size();++i)
    polynom.push_back(Monom(cons[i], vec[i]));
}

int Invariant::getValue(const Graph& g)
{
  int res = 0;
  for (auto& c : polynom)
    res += c.getValue(g);
  return res;
}
