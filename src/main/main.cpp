#include <iostream>
#include "graph.h"



int main() {

  int counter = 0;

  for (uint32_t b_i = 0; b_i < 32767; ++b_i) {
    std::vector<bool> X(15, 0);
    for (int i = 0; i < 15; ++i)
      X[i] = (b_i & 1 << i) >> i;

    bool isBernaul = true;

    if (X[0] + !X[1] + X[5] + X[6] != 2
      || X[1] + !X[2] + X[7] + X[8] != 2
      || X[2] + !X[3] + X[9] + X[10] != 2
      || X[3] + !X[4] + X[11] + X[12] != 2
      || X[4] + !X[0] + X[13] + X[14] != 2)
      isBernaul = false;


    if (isBernaul == true) {
      for (auto c : X)
        std::cout << c << " ";
      std::cout << "\n";
      counter++;
    }
  }


  std::cout << counter;
  return 0;
}
