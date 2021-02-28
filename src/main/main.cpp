#include <iostream>
#include "graph.h"


void f(std::vector<uint8_t> & a) {
  for (auto&& c : a)
    --c;
  a[0] = a.size() - 1;
}

void la(const int& a) {
  
}


int main() {

  Graph g(0xFF);



  std::vector<uint8_t> test = {
    0, 1, 2, 3, 4, 5, 6, 7, // 0 - 7
    8, 9, 10, 11, 12, 13, 14, 15, // 8 - 15
    16, 17, 18, 19, 20, 21, 22, 23, // 16 - 23
    24, 25, 26, 27, 28, 29, 30, 31}; // 24 - 32

  Permutation a(test);

  Permutation b;
  b = a * a;

  std::cout << g.get();
  return 0;
}
