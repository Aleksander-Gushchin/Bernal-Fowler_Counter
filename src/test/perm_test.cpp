#include <gtest.h>

#include <algorithm>
#include "permutation.h"

TEST(permutation, basic_init) {
  ASSERT_NO_THROW(Permutation());
}

TEST(permutation, construct) {
  std::vector<int16_t> vec1 = {
    1, 27, 2, 3, 4, 23, 6, 7, // 0 - 7
    8, 9, 10, 11, 12, 13, 14, 15, // 8 - 15
    16, 17, 18, 19, 20, 21, 22, 5, // 16 - 23
    24, 25, 26, 32, 28, 29, 30, 31 }; // 24 - 32

  Permutation act(vec1);

  std::vector<int16_t> test_vec(vec1.size());

  for (int i = 0; i < vec1.size(); ++i)
    test_vec[i] = std::abs(act[i]);

  sort(test_vec.begin(), test_vec.end());
  
  bool isCorrect = true;

  for (int i = 0; i < 32; ++i)
    if (test_vec[i] != i + 1)
      isCorrect = false;

  EXPECT_EQ(true, isCorrect);
}

TEST(permutation, basic_mult) {
  std::vector<int16_t> vec1 = {
    2, 1, 3, 5, 4, 6, 7,
    8, 9, 10, 11, 12, 13, 14, 15, 
    16, 17, 18, 19, 20, 21, 22, 23, 
    24, 25, 26, 27, 28, 29, 30, 31 ,32}; 

  std::vector<int16_t> vec2 = {
    3, 2, 1, 4, 5, 6, 7,
    8, 9, 10, 11, 12, 13, 14, 15, 
    16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29, 30, 31 , 32 };

  Permutation A(vec1);
  Permutation B(vec2);

  std::vector<int16_t> vec3 = {
    3, 1, 2, 5, 4, 6, 7,
    8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29, 30, 31, 32};

  Permutation act = A * B;
  Permutation exp(vec3);

  bool isCorrect = exp == act;

  EXPECT_EQ(true, isCorrect);
}

TEST(permutation, basic_mult_eq) {
  std::vector<int16_t> vec1 = {
    2, 1, 3, 5, 4, 6, 7,
    8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29, 30, 31 ,32 };

  std::vector<int16_t> vec2 = {
    3, 2, 1, 4, 5, 6, 7,
    8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29, 30, 31 , 32 };

  Permutation act(vec1);
  Permutation B(vec2);

  std::vector<int16_t> vec3 = {
    3, 1, 2, 5, 4, 6, 7,
    8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23,
    24, 25, 26, 27, 28, 29, 30, 31, 32 };

  act *= B;
  Permutation exp(vec3);

  bool isCorrect = exp == act;

  EXPECT_EQ(true, isCorrect);
}

TEST(permutation, comp_mult_1) {
  std::vector<int16_t> vec1 = {
    2, 1, -3, 5, 4, 6, 7,
    8, 9, 10, 11, 12, 13, 14, 15, 16
  };

  std::vector<int16_t> vec2 = {
    3, -2, -1, 4, 5, 6, 7,
    8, 9, 10, 11, 12, 13, 14, 15, 16
  };

  Permutation A(vec1);
  Permutation B(vec2);

  std::vector<int16_t> vec3 = {
    -3, -1, -2, 5, 4, 6, 7,
    8, 9, 10, 11, 12, 13, 14, 15, 16
  };

  Permutation act = A * B;
  Permutation exp(vec3);

  bool isCorrect = exp == act;

  EXPECT_EQ(true, isCorrect);
}

TEST(permutation, full_rotate) {
  std::vector<int16_t> vec1 = {
    5, 1, 2, 3, 4, // f-b points
    14, 15, 6, 7, 8, 9, 10, 11, 12, 13
  };

  
  std::vector<int16_t> vec2 = {
    1, 2, 3, 4, 5,
    6, 7, 8, 9, 10, 11, 12, 13, 14, 15
  };

  Permutation rotate(vec1);

  Permutation act = rotate * rotate * rotate * rotate * rotate;
  Permutation exp(vec2);

  bool isCorrect = exp == act;

  EXPECT_EQ(true, isCorrect);
}

TEST(permutation, double_flip) {
  std::vector<int16_t> vec1 = {
    -2, -1, -5, -4, -3, // f-b points
    7, 6, 15, 14, 13, 12, 11, 10, 9, 8
  };


  std::vector<int16_t> vec2 = {
    1, 2, 3, 4, 5,
    6, 7, 8, 9, 10, 11, 12, 13, 14, 15
  };

  Permutation flip(vec1);

  Permutation act = flip * flip;
  Permutation exp(vec2);

  bool isCorrect = exp == act;

  EXPECT_EQ(true, isCorrect);
}


TEST(permutation, rotate_and_flip) {
  std::vector<int16_t> vec1 = {
    -2, -1, -5, -4, -3, // f-b points
    7, 6, 15, 14, 13, 12, 11, 10, 9, 8
  };

  std::vector<int16_t> vec2 = {
    5, 1, 2, 3, 4, // f-b points
    14, 15, 6, 7, 8, 9, 10, 11, 12, 13
  };

  std::vector<int16_t> vec3 = {
    -4, -3, -2, -1, -5,
    11, 10, 9, 8, 7, 6, 15, 14, 13, 12
  };

  Permutation flip(vec1);
  Permutation rotate(vec2);

  Permutation act =  flip * (rotate * rotate);
  Permutation exp(vec3);

  bool isCorrect = exp == act;

  EXPECT_EQ(true, isCorrect);
}
