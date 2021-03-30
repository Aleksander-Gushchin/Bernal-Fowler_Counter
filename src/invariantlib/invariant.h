#pragma once

#include <vector>
#include "graph.h"
#include <ostream>


class Invariant {
private:
  class Monom {
    uint8_t cons;
    std::vector<uint8_t> exp;
  public:
    Monom(uint8_t _c, std::vector<uint8_t> vec);
  };
public:
 
};