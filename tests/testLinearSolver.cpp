#include <gtest/gtest.h>

#include "LinearSolver.hpp"
#include "ginkgo/ginkgo.hpp"
#include "utilitiesForTesting.hpp"

TEST(LinearSolverTest, Solve2x2Matrix) {
  // --- Arrange ---
  // Define a simple 2x2 linear system:
  // [4 -1] [x1] = [3]
  // [-1 3] [x2]   [2]
  using ValueType = double;
  using IndexType = int;
  using RealValueType = gko::remove_complex<ValueType>;

  gko::matrix_data<ValueType, IndexType> coeffMatrix;
  coeffMatrix.size = {2, 2};
  coeffMatrix.nonzeros = {
      {0, 0, 4.0},
      {0, 1, -1.0}, // Row 0
      {1, 0, -1.0},
      {1, 1, 3.0} // Row 1
  };

  std::vector<ValueType> RHS = {3.0, 2.0}; // Right-hand side vector
  std::vector<ValueType> expectedSolution = {1.0, 1.0}; // Expected solution
  std::vector<ValueType> solution(2, 0.0); // Solution vector initialized to 0

  const ValueType absTol = 1.0e-12;
  const ValueType relTol = 1.0e-8;
  const RealValueType reduction_factor{1e-7};
  const IndexType maxNumIterations = 1000;

  // --- Act ---
  LinearSolver solver;
  solver.solve(coeffMatrix, RHS, solution, reduction_factor, maxNumIterations);

  // --- Assert ---
  for (std::size_t i = 0; i < solution.size(); ++i) {
    EXPECT_TRUE(
        ScalarAlmostEqual(solution[i], expectedSolution[i], absTol, relTol));
  }
}

TEST(LinearSolverTest, Solve3x3Matrix) {
  // --- Arrange ---
  // Define a 3x3 linear system:
  // [ 4 -1  0] [x1] = [8.0]
  // [-1  4 -1] [x2] = [3.0]
  // [ 0 -1  3] [x3] = [5.5]
  using ValueType = double;
  using IndexType = int;
  using RealValueType = gko::remove_complex<ValueType>;

  gko::matrix_data<ValueType, IndexType> coeffMatrix;
  coeffMatrix.size = {3, 3};
  coeffMatrix.nonzeros = {
      {0, 0, 4.0},  {0, 1, -1.0},               // Row 0
      {1, 0, -1.0}, {1, 1, 4.0},  {1, 2, -1.0}, // Row 1
      {2, 1, -1.0}, {2, 2, 3.0}                 // Row 2
  };

  std::vector<ValueType> RHS = {8.0, 3.0, 5.5}; // Right-hand side vector
  std::vector<ValueType> expectedSolution = {2.5, 2.0,
                                             2.5}; // Expected solution
  std::vector<ValueType> solution(3, 0.0); // Solution vector initialized to 0

  const ValueType absTol = 1.0e-12;
  const ValueType relTol = 1.0e-8;
  const RealValueType reduction_factor{1e-7};
  const IndexType maxNumIterations = 1000;

  // --- Act ---
  LinearSolver solver;
  solver.solve(coeffMatrix, RHS, solution, reduction_factor, maxNumIterations);

  // --- Assert ---
  for (std::size_t i = 0; i < solution.size(); ++i) {
    EXPECT_TRUE(
        ScalarAlmostEqual(solution[i], expectedSolution[i], absTol, relTol));
  }
}

TEST(LinearSolverTest, Solve4x4Matrix) {
  // --- Arrange ---
  // Define a 4x4 linear system:
  // [ 4 -1  0  0] [x1] = [8.0]
  // [-1  4 -1  0] [x2] = [3.5]
  // [ 0 -1  4 -1] [x3] = [3.5]
  // [ 0  0 -1  3] [x4] = [5.5]
  using ValueType = double;
  using IndexType = int;
  using RealValueType = gko::remove_complex<ValueType>;

  gko::matrix_data<ValueType, IndexType> coeffMatrix;
  coeffMatrix.size = {4, 4};
  coeffMatrix.nonzeros = {
      {0, 0, 4.0},  {0, 1, -1.0},               // Row 0
      {1, 0, -1.0}, {1, 1, 4.0},  {1, 2, -1.0}, // Row 1
      {2, 1, -1.0}, {2, 2, 4.0},  {2, 3, -1.0}, // Row 2
      {3, 2, -1.0}, {3, 3, 3.0}                 // Row 3
  };

  std::vector<ValueType> RHS = {8.0, 3.5, 3.5, 5.5}; // Right-hand side   vector
  std::vector<ValueType> expectedSolution = {2.5, 2.0, 2.0,
                                             2.5}; // Expected solution
  std::vector<ValueType> solution(4, 0.0); // Solution vector initialized to 0

  const ValueType absTol = 1.0e-12;
  const ValueType relTol = 1.0e-8;
  const RealValueType reduction_factor{1e-7};
  const IndexType maxNumIterations = 1000;

  // --- Act ---
  LinearSolver solver;
  solver.solve(coeffMatrix, RHS, solution, reduction_factor, maxNumIterations);

  // --- Assert ---
  for (std::size_t i = 0; i < solution.size(); ++i) {
    EXPECT_TRUE(
        ScalarAlmostEqual(solution[i], expectedSolution[i], absTol, relTol));
  }
}