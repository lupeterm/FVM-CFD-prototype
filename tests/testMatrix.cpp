#include "Matrix.hpp"
#include <gtest/gtest.h>

// Test Matrix constructor
TEST(MatrixTest, ConstructorInitializesCorrectly) {
  Matrix<int> mat(3, 4, 5);
  EXPECT_EQ(mat.nRows(), 3);
  EXPECT_EQ(mat.nCols(), 4);
  for (std::size_t i = 0; i < 3; ++i) {
    for (std::size_t j = 0; j < 4; ++j) {
      EXPECT_EQ(mat(i, j), 5);
    }
  }
}

// Test element access (read/write)
TEST(MatrixTest, ElementAccess) {
  Matrix<int> mat(2, 2, 0);
  mat(0, 0) = 10;
  mat(1, 1) = 20;
  EXPECT_EQ(mat(0, 0), 10);
  EXPECT_EQ(mat(1, 1), 20);
}

// Test out-of-range access
TEST(MatrixTest, OutOfRangeAccess) {
  Matrix<int> mat(2, 2, 0);
  EXPECT_THROW(mat(2, 0), std::out_of_range);
  EXPECT_THROW(mat(0, 2), std::out_of_range);
  EXPECT_THROW(mat(3, 3), std::out_of_range);
}

// Test fill method
TEST(MatrixTest, FillMethod) {
  Matrix<int> mat(3, 3, 0);
  mat.fill(7);
  for (std::size_t i = 0; i < 3; ++i) {
    for (std::size_t j = 0; j < 3; ++j) {
      EXPECT_EQ(mat(i, j), 7);
    }
  }
}

// Test const element access
TEST(MatrixTest, ConstElementAccess) {
  const Matrix<int> mat(2, 2, 42);
  EXPECT_EQ(mat(0, 0), 42);
  EXPECT_EQ(mat(1, 1), 42);
}