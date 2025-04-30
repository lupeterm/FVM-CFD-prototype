#include "AssembleDiffusionTerm.hpp"
#include "Field.hpp"
#include "IO.hpp"
#include "LinearSolver.hpp"
#include "Matrix.hpp"
#include "Mesh.hpp"
#include "ReadInitialBoundaryConditions.hpp"
#include "ReadMesh.hpp"
#include "ginkgo/ginkgo.hpp"

int main() {
  // Read the mesh from the OpenFOAM case directory
  std::string caseDirectory(
      "../../cases/heat-conduction/2D-heat-conduction-on-a-2-by-2-mesh");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;
  meshReader.readOpenFoamMesh(fvMesh);

  using ValueType = double;
  using IndexType = int;
  using RealValueType = gko::remove_complex<ValueType>;

  // Define the thermal conductivity and source term
  std::vector<ValueType> thermalConductivity(fvMesh.nFaces(), 1.0);
  std::vector<ValueType> heatSource(fvMesh.nElements(), 0.0);

  // Read initial condition and boundary conditions
  Field<ValueType> internalTemperatureField(fvMesh.nElements());
  std::vector<boundaryField<ValueType>> boundaryTemperatureFields;
  ReadInitialBoundaryConditions initialBoundaryConditionsReader;
  initialBoundaryConditionsReader.readTemperatureField(
      fvMesh, internalTemperatureField, boundaryTemperatureFields);

  // Assemble the coefficient matrix and RHS vector
  gko::matrix_data<ValueType, IndexType> coeffMatrix;
  std::vector<ValueType> RHS(fvMesh.nElements(), 0.0);

  AssembleDiffusionTerm diffusionTermAssembler;
  diffusionTermAssembler.elementBasedAssemble(
      fvMesh, thermalConductivity, heatSource, boundaryTemperatureFields,
      coeffMatrix, RHS);

  std::vector<ValueType> solution(fvMesh.nElements(), 0.0);

  // Set up parameters
  const RealValueType reduction_factor{1e-7};
  const IndexType maxNumIterations = 1000;

  // Solve the linear system
  LinearSolver solver;
  solver.solve(coeffMatrix, RHS, solution, reduction_factor, maxNumIterations);

  // Print the solution
  std::cout << "Solution:" << std::endl;
  IO::printVector(solution);

  // Write the solution to a file
  std::string timePoint = "1";
  std::string solutionFileName = "T";
  IO::writeSolutionToFile(solution, caseDirectory, timePoint, solutionFileName);

  return 0;
}