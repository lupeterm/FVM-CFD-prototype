#ifndef LINEAR_SOLVER_HPP
#define LINEAR_SOLVER_HPP

#include <ginkgo/ginkgo.hpp> // Required for Ginkgo library
#include <vector>

class LinearSolver {
public:
  // Solve the linear system of equations
  template <typename ValueType, typename IndexType>
  void solve(gko::matrix_data<ValueType, IndexType> &coeffMatrix,
             std::vector<ValueType> &RHS, std::vector<ValueType> &solVector,
             gko::remove_complex<ValueType> reduction_factor,
             IndexType maxNumIterations);

private:
  // Add any private member variables or helper functions if needed
};

// Prevent implicit instantiation of the template function for these types
extern template void
LinearSolver::solve(gko::matrix_data<double, int> &coeffMatrix,
                    std::vector<double> &RHS, std::vector<double> &solVector,
                    gko::remove_complex<double> reduction_factor,
                    int maxNumIterations);

#endif // LINEAR_SOLVER_HPP