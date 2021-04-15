#include <iostream>
#include "graph.h"
#include "invariant.h"
#include <list>
#include <omp.h>
#include <map>

int main() {

  std::list<Graph> graph_list;
  int counter = 0;

  for (uint32_t b_i = 0; b_i < 0x7FFF + 1; ++b_i) {
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
      /*for (const auto& c : X)
        std::cout << c << " ";
      std::cout << "\n";*/
      graph_list.push_back(Graph(X));
      counter++;
    }
  }

  Permutation rotate72({
    5, 1, 2, 3, 4,
    14, 15, 6, 7, 8, 9, 10, 11, 12, 13
    });

  Permutation flip({
    -2, -1, -5, -4, -3,
    7, 6, 15, 14, 13, 12, 11, 10, 9, 8
    });

  Permutation swap1({
    1, 2, 3, 4, 5,
    7, 6, 8, 9, 10, 11, 12, 13, 14, 15
    });

  Permutation swap2({
    1, 2, 3, 4, 5,
    6, 7, 9, 8, 10, 11, 12, 13, 14, 15
    });

  Permutation swap3({
    1, 2, 3, 4, 5,
    6, 7, 8, 9, 11, 10, 12, 13, 14, 15
    });

  Permutation swap4({
    1, 2, 3, 4, 5,
    6, 7, 8, 9, 10, 11, 13, 12, 14, 15
    });

  Permutation swap5({
    1, 2, 3, 4, 5,
    6, 7, 8, 9, 10, 11, 12, 13, 15, 14
    });

  Permutation def({
    1, 2, 3, 4, 5,
    6, 7, 8, 9, 10, 11, 12, 13, 14, 15
    });

  std::vector<Permutation> group;
  for (int i = 0; i < 0x20; ++i) {
    std::vector<Permutation> basis = {
      def,
      rotate72,
      rotate72 * rotate72,
      rotate72 * rotate72 * rotate72,
      rotate72 * rotate72  * rotate72  * rotate72,
      flip,
      flip * rotate72,
      flip * (rotate72* rotate72),
      flip * (rotate72* rotate72* rotate72),
      flip * (rotate72* rotate72* rotate72* rotate72)};
    
    if (i & 1 == 1)
      for (auto& c : basis)
        c *= swap1;

    if ((i & 1 << 1) == 1 << 1)
      for (auto& c : basis)
        c *= swap2;

    if ((i & 1 << 2) == 1 << 2)
      for (auto& c : basis)
        c *= swap3;

    if ((i & 1 << 3) == 1 << 3)
      for (auto& c : basis)
        c *= swap4;

    if ((i & 1 << 4) == 1 << 4)
      for (auto& c : basis)
        c *= swap5;
    
    for (const auto& c : basis)
      group.push_back(c);
  }

//#define __SHOW_GROUP
#ifdef __SHOW_GROUP
  std::vector<Permutation> basis = {
      def,
      rotate72,
      rotate72 * rotate72,
      rotate72 * rotate72 * rotate72,
      rotate72 * rotate72 * rotate72 * rotate72,
      flip,
      flip * rotate72,
      flip * (rotate72 * rotate72),
      flip * (rotate72 * rotate72 * rotate72),
      flip * (rotate72 * rotate72 * rotate72 * rotate72) };
  for (auto& c : basis)
    std::cout << c << "\n";
#endif // !__SHOW_GROUP


  auto invariant_list = graph_list;

  std::cout << "Group size: " << group.size() << "\n";

  std::vector< std::vector<Graph> > orbit;

  int index_of_graph = 0;
  auto start = omp_get_wtime();
  for (auto it = graph_list.begin(); it != graph_list.end(); ++it) {
    orbit.push_back(std::vector<Graph>(1, *it));
    std::vector<Graph> isom_group(group.size());
    for (int i = 0; i < group.size(); ++i)
      isom_group[i] = *it * group[i];
    auto inner_it = it;
    ++inner_it;
    for (; inner_it != graph_list.end(); ++inner_it) {
      for (auto c : isom_group)
        if (c == *inner_it) {
          orbit[index_of_graph].push_back(*inner_it);
          inner_it = graph_list.erase(inner_it);
          --inner_it;
          break;
        }
    }
    ++index_of_graph;
  }
  auto end = omp_get_wtime();
  std::cout << "Time: " << end - start << "\n";

  for(const auto& c:orbit)
    std::cout << "Size: " << c.size() << "\n";

  class Counter {
    int count;
    int key;
  public:
    Counter(int _key) :key(_key), count(1) {};
    void update() { count++; };
    int getKey() { return key; };
    int getCount() { return count; };
  };

  std::vector<Invariant> invariant_group;
  invariant_group.push_back(Invariant({ 2,2,2,2,2 }, { 0x3, 0x11, 0x18, 0xC, 0x6 }, 15));
  
  std::map<int, std::list<Graph>> tmp_arr;
  start = omp_get_wtime();
  for (auto& invariant : invariant_group) {
    std::vector<Counter> counter_vec;
    for (auto& c : invariant_list) {
      int res = invariant.getValue(c);

      bool isNew = true;
      for (auto& co : counter_vec) {
        if (co.getKey() == res) {
          isNew = false;
          co.update();
          break;
        }
      }
      if (isNew == true)
        counter_vec.push_back(Counter(res));
    }
    for (auto& c : counter_vec)
      std::cout << "Item: " << c.getKey() << " Count: " << c.getCount() << "\n";
  }
  end = omp_get_wtime();
  std::cout << "Time: " << end - start << "\n";

  std::cout << "All graphs count: " << counter << "\n";
  std::cout << "Non-isomorphic graphs count: " << graph_list.size() << "\n";
  for (const auto& c : graph_list)
    std::cout << c << "\n";

  return 0;
}
