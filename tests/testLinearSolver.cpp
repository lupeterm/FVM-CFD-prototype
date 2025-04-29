#include <gtest/gtest.h>

#include "LinearSolver.hpp"
#include "ginkgo/ginkgo.hpp"
#include "utilitiesForTesting.hpp"

TEST(LinearSolverTest, SolveSimpleCase) {
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

  const ValueType maxDiff = 1.0e-9;
  const ValueType maxRelativeDiff = 1.0e-4;
  const RealValueType reduction_factor{1e-7};
  const IndexType maxNumIterations = 1000;

  // --- Act ---
  LinearSolver solver;
  solver.solve(coeffMatrix, RHS, solution, reduction_factor, 1000);

  // --- Assert ---
  for (std::size_t i = 0; i < solution.size(); ++i) {
    EXPECT_TRUE(ScalarAlmostEqual(solution[i], expectedSolution[i], maxDiff,
                                  maxRelativeDiff));
  }
}