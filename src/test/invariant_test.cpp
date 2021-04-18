#include <gtest.h>

#include "invariant.h"

TEST(invariant, basic_init) {
  ASSERT_NO_THROW(Invariant({ 1, 1, 1 },
    { {1, 0, 1}, {1, 0, 1},{1, 0, 1} }));
}

TEST(invariant, can_throw_when_invalid_args) {
  ASSERT_ANY_THROW(Invariant({ 1, 1, 1, 1 },
    { {1, 0, 1}, {1, 0, 1},{1, 0, 1} }));
}

TEST(invariant, get_value) {
  Invariant inv({ 1, 3, 1 , -2},
    { {1, 0, 1}, {1, 1, 1},{0, 0, 1} , {1, 1, 0} });

  Graph g({ 1, 0, 1 });

  int res = inv.getValue(g);

  EXPECT_EQ(1, res);
}