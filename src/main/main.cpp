#include <iostream>
#include "graph.h"
#include "invariant.h"
#include <list>
#include <omp.h>

int main() {
  std::vector<Graph> graph_list;
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
      graph_list.push_back(Graph(X));
      counter++;
    }
  }

  std::cout << "Orgraph count: " << graph_list.size() << "\n";

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
      rotate72 * flip,
      (rotate72 * rotate72) * flip,
      (rotate72 * rotate72 * rotate72) * flip,
      (rotate72 * rotate72 * rotate72 * rotate72) * flip};
    
    if ((i & 1) == 1)
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

  auto invariant_list = graph_list;

  std::cout << "G group size: " << group.size() << "\n";

  std::vector< std::list<Graph> > orbit;

  int index_of_graph = 0;
  auto start = omp_get_wtime();
  for (auto it = graph_list.begin(); it != graph_list.end(); ++it) {
    orbit.push_back(std::list<Graph>(1, *it));
    std::vector<Graph> isom_group(group.size());
    for (int i = 0; i < group.size(); ++i)
      isom_group[i] = *it * group[i];
    auto inner_it = it;
    ++inner_it;
    for (; inner_it != graph_list.end(); ++inner_it) {
      for (auto& c : isom_group)
        if (c == *inner_it) {
          orbit[index_of_graph].push_back(std::move(*inner_it));
          inner_it = graph_list.erase(inner_it);
          --inner_it;
          break;
        }
    }
    ++index_of_graph;
  }
  auto end = omp_get_wtime();
  std::cout << "Time: " << end - start << " sec\n";

  class InvariantID {
  protected:
    std::list<int> id_list;
  public:
    InvariantID() {};
    InvariantID(const InvariantID& tmp) : id_list(tmp.id_list){};

    void add(int val) { id_list.push_back(val); };

    bool operator==(const InvariantID& inv_list) const {
      auto it_left = id_list.begin();
      auto it_right = inv_list.id_list.begin();

      for (; it_left != id_list.end() || it_right != inv_list.id_list.end(); ++it_left, ++it_right)
        if (*it_left != *it_right)
          return false;
      return true;
    };

    std::string print() const {
      std::string tmp = "";
      char text_buff[16];
      for (auto c : id_list) {
        tmp += itoa(c, text_buff, 10);
        tmp += " ";
      }
      return tmp;
    };
  };

  class InvGraphList : public InvariantID {
    std::list<Graph> list_graph;
  public:
    InvGraphList(const InvariantID& _id) : InvariantID(_id) {};
    void moveGraph(Graph&& g) { list_graph.push_back(std::move(g)); }
    int size() const { return list_graph.size(); }
    const std::list<Graph>& getList() const { return list_graph; };
  };

  std::vector<Invariant> invariant_group;
  invariant_group.push_back(Invariant({ 2,2,2,2,2 }, { 0x3, 0x11, 0x18, 0xC, 0x6 }, 15));
  invariant_group.push_back(Invariant({ 2,2,2,2,2 }, { 0xF, 0x17, 0x1B, 0x1D, 0x1E }, 15));
  
  std::list<std::pair<Graph, InvariantID>> inv_split;
  
  for (auto& c : invariant_list)
    inv_split.push_back(std::make_pair(std::move(c), InvariantID()));

  start = omp_get_wtime();
  auto start1 = omp_get_wtime();
  for (auto& invariant : invariant_group) {
    for (auto& cur_item : inv_split)
      cur_item.second.add(invariant.getValue(cur_item.first));
  }
  auto end1 = omp_get_wtime();
  auto start2 = omp_get_wtime();
  std::vector<InvGraphList> inv_gr;
  for (auto& cur_item : inv_split) {
    bool insert = true;
    for (auto& c : inv_gr)
      if (c == cur_item.second) {
        c.moveGraph(std::move(cur_item.first));
        insert = false;
      }
    if (insert == true) {
      inv_gr.push_back(cur_item.second);
      (--inv_gr.end())->moveGraph(std::move(cur_item.first));
    }
    
  }
  auto end2 = omp_get_wtime();
  end = omp_get_wtime();
  std::cout << "Time(Invariant): " << end - start << " sec\n";

  for (const auto& c : orbit)
    std::cout << "Orbit length: " << c.size() << "\n";

  for (auto& c : inv_gr)
    std::cout << "Orbit length(Invariant): " << c.size() << "\n";

  std::cout << "Nonisomorphic graph count: " << graph_list.size() << "\n";
  for (const auto& c : graph_list)
    std::cout << c << "\n";
  std::cout << "Nonisomorphic graph count(invariant): " << inv_gr.size() << "\n";
  for (const auto& c : inv_gr)
    std::cout << c.getList().front() << "\n";

  std::cout << "Invariant value: " << inv_gr.size() << "\n";
  for (const auto& c : inv_gr)
    std::cout << c.print() << "\n";

  return 0;
}
