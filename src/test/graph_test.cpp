#include <gtest.h>

#include "graph.h"

TEST(graph, basic_init) {
  ASSERT_NO_THROW(Graph(0xFF));
}

TEST(graph, set) {
  Graph a(0xEF);
  a.set(4);
  EXPECT_EQ(a.get(), 0xFF);
}