#ifndef LINEAR_SOLVER_HPP
#define LINEAR_SOLVER_HPP

#include <vector>

class LinearSolver {
public:
  // Solve the linear system Ax = b
  // A: Coefficient matrix (in a generic format, e.g., dense or sparse)
  // b: Right-hand side vector
  // x: Solution vector (output)
  template <typename MatrixType, typename VectorType>
  void solve(const MatrixType &A, const VectorType &b, VectorType &x) const;

private:
  // Add any private member variables or helper functions if needed
};

#endif // LINEAR_SOLVER_HPP