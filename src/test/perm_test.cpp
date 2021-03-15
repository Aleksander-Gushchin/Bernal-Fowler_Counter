#include <gtest.h>

#include <algorithm>
#include "permutation.h"

TEST(permutation, basic_init) {
  ASSERT_NO_THROW(Permutation());
}

TEST(permutation, construct) {
  std::vector<uint8_t> vec1 = {
    0, 27, 2, 3, 4, 23, 6, 7, // 0 - 7
    8, 9, 10, 11, 12, 13, 14, 15, // 8 - 15
    16, 17, 18, 19, 20, 21, 22, 5, // 16 - 23
    24, 25, 26, 1, 28, 29, 30, 31 }; // 24 - 32

  Permutation act(vec1, 0);

  std::vector<uint8_t> test_vec(32);

  for (int i = 0; i < 32; ++i)
    test_vec[i] = act[i];

  sort(test_vec.begin(), test_vec.end());
  
  bool isCorrect = true;

  for (int i = 0; i < 32; ++i)
    if (test_vec[i] != i)
      isCorrect = false;

  EXPECT_EQ(true, isCorrect);
}

TEST(permutation, basic_mult) {
  std::vector<uint8_t> vec1 = {
    0, 2, 1, 3, 5, 4, 6, 7, // 0 - 7
    8, 9, 10, 11, 12, 13, 14, 15, // 8 - 15
    16, 17, 18, 19, 20, 21, 22, 23, // 16 - 23
    24, 25, 26, 27, 28, 29, 30, 31 }; // 24 - 32

  std::vector<uint8_t> vec2 = {
    0, 3, 2, 1, 4, 5, 6, 7, // 0 - 7
    8, 9, 10, 11, 12, 13, 14, 15, // 8 - 15
    16, 17, 18, 19, 20, 21, 22, 23, // 16 - 23
    24, 25, 26, 27, 28, 29, 30, 31 }; // 24 - 32

  Permutation A(vec1, 0);
  Permutation B(vec2, 0);

  std::vector<uint8_t> vec3 = {
    0, 3, 1, 2, 5, 4, 6, 7, // 0 - 7
    8, 9, 10, 11, 12, 13, 14, 15, // 8 - 15
    16, 17, 18, 19, 20, 21, 22, 23, // 16 - 23
    24, 25, 26, 27, 28, 29, 30, 31 }; // 24 - 32

  Permutation act = A * B;
  Permutation exp(vec3, 0);

  bool isCorrect = exp == act;

  EXPECT_EQ(true, isCorrect);
}