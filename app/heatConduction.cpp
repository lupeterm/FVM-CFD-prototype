#include "AssembleDiffusionTerm.hpp"
#include "Field.hpp"
#include "IO.hpp"
#include "LinearSolver.hpp"
#include "Matrix.hpp"
#include "Mesh.hpp"
#include "PostProcessing.hpp"
#include "ReadInitialBoundaryConditions.hpp"
#include "ReadMesh.hpp"
#include "ginkgo/ginkgo.hpp"

int main(int argc, char *argv[]) {
  // Check for command-line arguments
  if (argc < 2) {
    std::cerr << "Usage: " << argv[0] << " <caseDirectory>" << std::endl;
    return 1;
  }

  std::string caseDirectory(argv[1]);
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

  // Write the solution to internal temperature field
  for (std::size_t i = 0; i < fvMesh.nElements(); ++i) {
    internalTemperatureField.values()[i] = solution[i];
  }

  // Print the internal temperature field
  std::cout << "Internal Temperature Field:" << std::endl;
  IO::printVector(internalTemperatureField.values());

  // Write the solution to a file
  std::cout << "Writing result to a file..." << std::endl;
  std::string timePoint = "1";
  std::string resultFileName = "T";
  IO::writeResultToFile(internalTemperatureField.values(), caseDirectory,
                        timePoint, resultFileName);

  // Create a .foam file for visualization in ParaView
  IO::createFoamFile(caseDirectory);

  // Write the x coordinate of each element and the corresponding internal
  // temperature field to a file for plotting
  std::cout << "Writing results to results.txt for plotting..." << std::endl;
  std::ofstream outputFile(caseDirectory + "/results.txt");
  if (!outputFile) {
    std::cerr << "Error opening file for writing results." << std::endl;
    return 1;
  }
  outputFile << "x_coordinate temperature" << std::endl;
  for (std::size_t i = 0; i < fvMesh.nElements(); ++i) {
    outputFile << fvMesh.elements()[i].centroid()[0] << " "
               << internalTemperatureField.values()[i] << std::endl;
  }
  outputFile.close();
  std::cout << "Results written to " << caseDirectory + "/results.txt"
            << std::endl;
  std::cout << "Simulation completed successfully." << std::endl;
  return 0;
}