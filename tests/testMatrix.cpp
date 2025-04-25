#include "Matrix.hpp"
#include <gtest/gtest.h>

// Test constructor and dimension getters
TEST(MatrixTest, ConstructorAndDimensions) {
  Matrix<double> mat(3, 4);

  EXPECT_EQ(mat.nRows(), 3);
  EXPECT_EQ(mat.nCols(), 4);
}

// Test invalid constructor arguments
TEST(MatrixTest, InvalidConstructor) {
  EXPECT_THROW(Matrix<double> mat(0, 4), std::invalid_argument);
  EXPECT_THROW(Matrix<double> mat(3, 0), std::invalid_argument);
}

// Test writing and reading values
TEST(MatrixTest, WriteAndReadValues) {
  Matrix<double> mat(3, 3);

  mat(0, 0) = 1.0;
  mat(1, 2) = 2.5;
  mat(2, 1) = -3.0;

  EXPECT_EQ(mat(0, 0), 1.0);
  EXPECT_EQ(mat(1, 2), 2.5);
  EXPECT_EQ(mat(2, 1), -3.0);

  // Test default value for uninitialized entries
  EXPECT_EQ(mat(0, 1), 0.0);
  EXPECT_EQ(mat(2, 2), 0.0);
}

// Test out-of-range access
TEST(MatrixTest, OutOfRangeAccess) {
  Matrix<double> mat(3, 3);

  EXPECT_THROW(mat(3, 0) = 1.0, std::out_of_range);
  EXPECT_THROW(mat(0, 3) = 1.0, std::out_of_range);
  EXPECT_THROW(mat(3, 0), std::out_of_range);
  EXPECT_THROW(mat(0, 3), std::out_of_range);
}

// Test overwriting values
TEST(MatrixTest, OverwriteValue) {
  Matrix<double> mat(3, 3);

  mat(1, 1) = 5.0;
  EXPECT_EQ(mat(1, 1), 5.0);

  mat(1, 1) = 10.0; // Overwrite the value
  EXPECT_EQ(mat(1, 1), 10.0);
}

// Test filling the matrix with a single value
TEST(MatrixTest, FillMatrix) {
  Matrix<double> mat(3, 3);

  mat.fill(7.0);

  for (std::size_t i = 0; i < mat.nRows(); ++i) {
    for (std::size_t j = 0; j < mat.nCols(); ++j) {
      EXPECT_EQ(mat(i, j), 7.0);
    }
  }
}