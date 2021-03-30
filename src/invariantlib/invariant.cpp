#include "invariant.h"
#include <iostream>
#include <iomanip>
#include <utility>

Invariant::Monom::Monom(uint8_t _c, std::vector<uint8_t> vec) : cons(_c) , exp(vec)
{
}
