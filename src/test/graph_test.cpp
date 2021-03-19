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

