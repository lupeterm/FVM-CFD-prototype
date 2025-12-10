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
#include <iomanip>
#include <vector>

void export_mtx(const std::string path, std::shared_ptr<const gko::matrix::Csr<double, int>> A)
{
  std::cout << "[CFD-PROT LOG] exporting " << path << std::endl;
  std::ofstream stream{path};
  stream << std::setprecision(15);

  gko::write(stream, A.get());
}

int main(int argc, char *argv[])
{
  // Check for command-line arguments
  if (argc < 3) {
    std::cerr << "Usage: " << argv[0]
              << " <caseDirectory> <assemblyMethod: cell/face/batchedFace>"
              << std::endl;
    return 1;
  }
  std::cout << "int: " << sizeof(int) << "\n";
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
  // std::vector<ValueType> heatSource(1); // dont use

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
  std::vector<gko::matrix_data<double, int>> coeffMatrix{{}, {}, {}};
  std::vector<ValueType>
      RHS(fvMesh.nCells());

  AssembleDiffusionTerm diffusionTermAssembler;

  // if (assemblyMethod == "cell") {
  std::cout << "Using cell-based assembly..." << std::endl;
  auto g_tic = std::chrono::steady_clock::now();

  diffusionTermAssembler.cellBasedAssemble(
      fvMesh,
      transportPropertyConstant,
      internalVelocityField,
      boundaryVelocityFields,
      coeffMatrix,
      RHS);
  auto g_tac = std::chrono::steady_clock::now();
  auto generate_time =
      std::chrono::duration_cast<std::chrono::nanoseconds>(g_tac - g_tic);
  std::cout << "Matrix assembly took " << generate_time.count() / 1000000 << "ms \n";
  // for (size_t dim = 0; dim < 3; dim++) {

  //   using mtx = gko::matrix::Csr<double, int>;

  //   const auto exec = gko::ReferenceExecutor::create();
  //   // coeffMatrix[dim].sort_row_major();

  //   auto gko_coeffMatrix = gko::share(mtx::create(exec, coeffMatrix[dim].size, coeffMatrix[dim].nonzeros.size()));
  //   std::cout << "1\n";
  //   gko_coeffMatrix->read(coeffMatrix[dim]);
  //   std::cout << "[CFD-PROT LOG] exporting " << "example.max" << std::endl;
  //   std::string file = "coeffmatrix_X.mtx";
  //   if (dim == 1) {
  //     file = "coeffmatrix_Y.mtx";
  //   } else if (dim == 2) {
  //     file = "coeffmatrix_Z.mtx";
  //   }
  //   std::ofstream stream{file};
  //   std::cout << "2\n";

  //   stream << std::setprecision(15);

  //   gko::write(stream, gko_coeffMatrix.get());
  // }
  return 0;
}
