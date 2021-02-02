

#include <iostream>
#include "graph.h"




int main() {

  Graph g;

  g.set(0xF1F);

  std::vector<uint8_t> test(32, 0);

  for (int i = 0; i < 32; ++i)
    test[i] = 32 - 1 - i;

  Permutation a(test);

  Permutation b = a * a;

  std::cout << g.get();
  return 0;
}
