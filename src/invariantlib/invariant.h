#pragma once

#include <vector>
#include "graph.h"
#include <ostream>
#include <list>

class Invariant {
private:
  class Monom {
  private:
    int cons;
    std::vector<bool> exp;
    int inline exctract(int val);
  public:
    Monom(int _c, const std::vector<bool>& vec);
    int getValue(const Graph& g);
  };

  std::list<Monom> polynom;

  
public:
  Invariant(const std::vector<int>& cons,const std::vector<std::vector<bool> >& vec);
  int getValue(const Graph& g);
};