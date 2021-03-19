#include <gtest.h>

#include "graph.h"

TEST(graph, basic_init) {
  ASSERT_NO_THROW(Graph(0xFF));
}

TEST(graph, set) {
  Graph a(0xFF);
  EXPECT_EQ(a[1], true);
}

TEST(graph, get) {
  Graph a(0xFF);
  a[1] = false;
  EXPECT_EQ(a[1], false);
}

TEST(graph, perm_basic) {
  Graph a(0xF0, 16);

  std::vector<int16_t> vec1 = {
    1, 2, 5, 6, 3, 4, 7,
    8, 9, 10, 11, 12, 13, 14, 15, 16
  };

  Graph act = a * Permutation(vec1);
  Graph exp(0xCC, 16);

  bool isCorrect = act == exp;
  EXPECT_EQ(true, isCorrect);
}

TEST(graph, perm_comp) {
  Graph a(0xF0, 16);
  //TODO
  std::vector<int16_t> vec1 = {
    -1, -2, -5, -6, 3, 4, 7,
    8, 9, 10, 11, 12, 13, 14, 15, 16
  };

  Graph act = a * Permutation(vec1);
  Graph exp(0xC3, 16);

  bool isCorrect = act == exp;
  EXPECT_EQ(true, isCorrect);
}