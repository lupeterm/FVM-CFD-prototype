#ifndef LINEAR_SOLVER_HPP
#define LINEAR_SOLVER_HPP

#include <ginkgo/ginkgo.hpp> // Required for Ginkgo library
#include <vector>

class LinearSolver {
public:
  // Solve the linear system of equations
  void solve(gko::matrix_data<double, int> &coeffMatrix,
             std::vector<double> &RHS, std::vector<double> &solVector);

private:
  // Add any private member variables or helper functions if needed
};

#endif // LINEAR_SOLVER_HPP