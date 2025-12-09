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
#include <vector>

int main(int argc, char *argv[])
{
  // Check for command-line arguments
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0]
              << " <caseDirectory> <assemblyMethod: cell/face/batchedFace>"
              << std::endl;
    return 1;
  }

  std::string caseDirectory(argv[1]);
  std::string assemblyMethod(argv[2]);
  std::string benchmark(argv[3]);

  if (assemblyMethod != "cell" && assemblyMethod != "face" &&
      assemblyMethod != "batchedFace") {
    std::cerr
        << "Invalid assembly method. Use 'cell', 'face', or 'batchedFace'."
        << std::endl;
    return 1;
  }

  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;
  meshReader.readOpenFoamMesh(fvMesh);

  using ValueType = std::array<double, 3>;
  using IndexType = int;
  // using RealValueType = gko::remove_complex<double>;

  double transportPropertyConstant = 0.0;
  if (benchmark == "windsor") {
    transportPropertyConstant = 1.44e-05;
  } else if (benchmark == "lcd-m") {
    transportPropertyConstant = 0.01;
  } else if (benchmark == "lcd-s") {
    transportPropertyConstant = 0.01;
  } else {
    std::cerr << "Benchmark not known. Use 'windsor', 'lcd-s', or 'lcd-m'."
              << std::endl;
    return 1;
  }

  // Define the thermal conductivity and source term
  // std::vector<double> transportproperty(fvMesh.nFaces(),
  // transportPropertyConstant);
  std::vector<ValueType> heatSource(1); // dont use

  Field<ValueType> internalVelocityField(fvMesh.nCells());
  Field<double> p(fvMesh.nCells());

  // Read initial condition and boundary conditions
  Field<ValueType> internalTemperatureField(fvMesh.nCells());
  std::vector<boundaryField<ValueType>> boundaryTemperatureFields;
  std::vector<boundaryField<std::array<double, 3>>> boundaryVelocityFields;

  ReadInitialBoundaryConditions initialBoundaryConditionsReader;
  initialBoundaryConditionsReader.readVelocityField(
      fvMesh,
      internalVelocityField,
      boundaryVelocityFields);
  // initialBoundaryConditionsReader.readTemperatureField(
  //     fvMesh, internalTemperatureField, boundaryTemperatureFields);

  // Assemble the coefficient matrix and RHS vector
  std::vector<gko::matrix_data<double, int>::nonzero_type> coeffMatrix{
      {},
      {},
      {}};
  std::vector<ValueType>
      RHS(fvMesh.nCells());

  AssembleDiffusionTerm diffusionTermAssembler;

  // if (assemblyMethod == "cell") {
  std::cout << "Using cell-based assembly..." << std::endl;
  diffusionTermAssembler.cellBasedAssemble(
      fvMesh,
      transportPropertyConstant,
      internalVelocityField,
      boundaryTemperatureFields,
      coeffMatrix,
      RHS);
  // } else if (assemblyMethod == "face") {
  //   std::cout << "Using face-based assembly..." << std::endl;
  //   diffusionTermAssembler.faceBasedAssemble(
  //       fvMesh, transportproperty, heatSource, boundaryTemperatureFields,
  //       coeffMatrix, RHS);
  // } else if (assemblyMethod == "batchedFace") {
  //   std::cout << "Using batched face-based assembly..." << std::endl;
  //   diffusionTermAssembler.batchedFaceBasedAssemble(
  //       fvMesh, transportproperty, heatSource, boundaryTemperatureFields,
  //       coeffMatrix, RHS);
  // }

  // std::vector<ValueType> solution(fvMesh.nCells(), 0.0);

  // // Set up parameters
  // const RealValueType reduction_factor{1e-7};
  // const IndexType maxNumIterations = 1000;

  // // Solve the linear system
  // LinearSolver solver;
  // solver.solve(coeffMatrix, RHS, solution, reduction_factor,
  // maxNumIterations);

  // // Write the solution to internal temperature field
  // for (std::size_t i = 0; i < fvMesh.nCells(); ++i) {
  //   internalTemperatureField.values()[i] = solution[i];
  // }

  // // Write the solution to a file
  // std::cout << "Writing result to a file..." << std::endl;
  // std::string timePoint = "1";
  // std::string resultFileName = "T";
  // IO::writeResultToFile(internalTemperatureField.values(), caseDirectory,
  //                       timePoint, resultFileName);

  // // Create a .foam file for visualization in ParaView
  // IO::createFoamFile(caseDirectory);

  // // Write the x coordinate of each cell and the corresponding internal
  // // temperature field to a file for plotting
  // std::cout << "Writing results to results.txt for plotting..." << std::endl;
  // std::ofstream outputFile(caseDirectory + "/results.txt");
  // if (!outputFile) {
  //   std::cerr << "Error opening file for writing results." << std::endl;
  //   return 1;
  // }
  // outputFile << "x_coordinate temperature" << std::endl;
  // for (std::size_t i = 0; i < fvMesh.nCells(); ++i) {
  //   outputFile << fvMesh.cells()[i].centroid()[0] << " "
  //              << internalTemperatureField.values()[i] << std::endl;
  // }
  // outputFile.close();
  // std::cout << "Results written to " << caseDirectory + "/results.txt"
  //           << std::endl;
  // std::cout << "Simulation completed successfully." << std::endl;
  return 0;
}