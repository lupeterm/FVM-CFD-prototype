#include "LinearSolver.hpp"
// #include <ginkgo/ginkgo.hpp> // Required for Ginkgo library
#include <stdexcept> // Required for std::invalid_argument

void LinearSolver::solve(gko::matrix_data<double, int> &coeffMatrix,
                         std::vector<double> &RHS,
                         std::vector<double> &solVector) {
  // Create an executor (e.g., CPU executor)
  auto exec = gko::ReferenceExecutor::create();

  // === Prepare the Ginkgo matrix and vectors to be used by a Ginkgo solver ===
  // --- Convert the input matrix coeffMatrix to a Ginkgo matrix ---
  using IndexType = int; // int or int64
  using ValueType = double;
  using mtx = gko::matrix::Coo<ValueType, IndexType>;
  using vec = gko::matrix::Dense<ValueType>;
  using val_array = gko::array<ValueType>;

  coeffMatrix.sort_row_major();

  auto gko_coeffMatrix = mtx::create(exec);
  gko_coeffMatrix->read(coeffMatrix);

  // --- Convert the input RHS vector to a Ginkgo vector ---
  const auto &nMeshPoints = RHS.size();

  // executor where the application initialized the data
  const auto app_exec = exec->get_master();
  auto gko_RHS =
      vec::create(exec, gko::dim<2>(nMeshPoints, 1),
                  val_array::view(app_exec, nMeshPoints, RHS.data()), 1);

  std::vector<ValueType> x0(nMeshPoints, 0.0);
  auto gko_x =
      vec::create(app_exec, gko::dim<2>(nMeshPoints, 1),
                  val_array::view(app_exec, nMeshPoints, x0.data()), 1);

  // === Solve the linear system of equations ===
}