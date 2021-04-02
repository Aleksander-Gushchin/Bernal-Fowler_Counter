#pragma once

#include <vector>
#include "graph.h"
#include <ostream>
#include <list>

class Invariant {
private:
  class Monom {
  private:
    uint8_t cons;
    std::vector<bool> exp;
    int inline exctract(int val);
  public:
    Monom(uint8_t _c, const std::vector<bool>& vec);
    int getValue(const Graph& g);
  };

  std::list<Monom> polynom;

  
public:
  Invariant(const std::vector<int>& cons,const std::vector<std::vector<bool> >& vec);
  int getHash(const Graph& g);
};