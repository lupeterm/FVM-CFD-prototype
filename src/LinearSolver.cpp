#include "LinearSolver.hpp"
#include <iostream>

template <typename ValueType, typename IndexType>
void LinearSolver::solve(gko::matrix_data<ValueType, IndexType> &coeffMatrix,
                         std::vector<ValueType> &RHS,
                         std::vector<ValueType> &solVector,
                         gko::remove_complex<ValueType> reduction_factor,
                         IndexType maxNumIterations) {
  // Create an executor (e.g., CPU executor)
  auto exec = gko::ReferenceExecutor::create();

  // === Prepare the Ginkgo matrix and vectors to be used by a Ginkgo solver ===
  // --- Convert the input matrix coeffMatrix to a Ginkgo matrix ---
  using mtx = gko::matrix::Coo<ValueType, IndexType>;
  using vec = gko::matrix::Dense<ValueType>;
  using val_array = gko::array<ValueType>;

  coeffMatrix.sort_row_major();

  auto gko_coeffMatrix = gko::share(
      mtx::create(exec, coeffMatrix.size, coeffMatrix.nonzeros.size()));

  gko_coeffMatrix->read(coeffMatrix);

  // --- Convert the input RHS vector to a Ginkgo vector ---
  // executor where the application initialized the data
  const auto app_exec = exec->get_master();
  const auto nMeshPoints = RHS.size();
  auto gko_RHS =
      vec::create(exec, gko::dim<2>(nMeshPoints, 1),
                  val_array::view(app_exec, nMeshPoints, RHS.data()), 1);

  //   -- -Create a Ginkgo matrix to store the solution vector-- -
  //   Create an initial guess vector
  auto gko_x =
      vec::create(app_exec, gko::dim<2>(nMeshPoints, 1),
                  val_array::view(app_exec, nMeshPoints, solVector.data()), 1);

  // === Solve the linear system of equations ===
  // --- Generate solver ---
  // Generate a Ginkgo CG solver with the block Jacobi preconditioner
  using cg = gko::solver::Cg<ValueType>;
  using bj = gko::preconditioner::Jacobi<ValueType, IndexType>;

  auto solver_factory =
      cg::build()
          .with_criteria(
              gko::stop::Iteration::build().with_max_iters(
                  gko::size_type(maxNumIterations)),
              gko::stop::ResidualNorm<ValueType>::build().with_reduction_factor(
                  reduction_factor))
          .with_preconditioner(bj::build())
          .on(exec);
  auto solver = solver_factory->generate(gko_coeffMatrix);

  // --- Solve system ---
  solver->apply(gko_RHS, gko_x);
}

template void LinearSolver::solve(gko::matrix_data<double, int> &coeffMatrix,
                                  std::vector<double> &RHS,
                                  std::vector<double> &solVector,
                                  gko::remove_complex<double> reduction_factor,
                                  int maxNumIterations);