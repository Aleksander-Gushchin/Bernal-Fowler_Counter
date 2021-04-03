#include "invariant.h"
#include <iostream>
#include <iomanip>
#include <utility>

int inline Invariant::Monom::exctract(int val)
{
  return 2 * val - 1;
}

Invariant::Monom::Monom(int _c,const std::vector<bool>& vec) : cons(_c) , exp(vec)
{
}

int Invariant::Monom::getValue(const Graph& g)
{
  if (g.getSize() != exp.size())
    throw 1;

  int res = 1;

  for (int i = 0; i < exp.size(); ++i)
    res *= exctract(g[i]) * exp[i] + (1 - exp[i]);
  return cons * res;
}


Invariant::Invariant(const std::vector<int>& cons, const std::vector<std::vector<bool>>& vec)
{
  if (cons.size() != vec.size())
    throw 1;

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
