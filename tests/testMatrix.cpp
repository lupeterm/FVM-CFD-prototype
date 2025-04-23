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

// Test writing and reading values in COO format
TEST(MatrixTest, WriteAndReadCOO) {
  Matrix<double> mat(3, 3);

  mat.build(0, 0, 1.0);
  mat.build(1, 2, 2.5);
  mat.build(2, 1, -3.0);

  EXPECT_EQ(mat.getValue(0, 0), 1.0);
  EXPECT_EQ(mat.getValue(1, 2), 2.5);
  EXPECT_EQ(mat.getValue(2, 1), -3.0);

  // Test default value for non-existent entries
  EXPECT_EQ(mat.getValue(0, 1), 0.0);
  EXPECT_EQ(mat.getValue(2, 2), 0.0);
}

// Test out-of-range access
TEST(MatrixTest, OutOfRangeAccess) {
  Matrix<double> mat(3, 3);

  EXPECT_THROW(mat.build(3, 0, 1.0), std::out_of_range);
  EXPECT_THROW(mat.build(0, 3, 1.0), std::out_of_range);
  EXPECT_THROW(mat.getValue(3, 0), std::out_of_range);
  EXPECT_THROW(mat.getValue(0, 3), std::out_of_range);
}

// Test overwriting values in COO format
TEST(MatrixTest, OverbuildValue) {
  Matrix<double> mat(3, 3);

  mat.build(1, 1, 5.0);
  EXPECT_EQ(mat.getValue(1, 1), 5.0);

  mat.setValue(1, 1, 10.0); // Overwrite the value
  EXPECT_EQ(mat.getValue(1, 1), 10.0);
}