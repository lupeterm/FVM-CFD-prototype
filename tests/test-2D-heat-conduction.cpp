#include <gtest/gtest.h>

#include "AssembleDiffusionTerm.hpp"
#include "Field.hpp"
#include "LinearSolver.hpp"
#include "Matrix.hpp"
#include "Mesh.hpp"
#include "ReadInitialBoundaryConditions.hpp"
#include "ReadMesh.hpp"
#include "ginkgo/ginkgo.hpp"
#include "utilitiesForTesting.hpp"
#include <array>
#include <string>

// ****** Tests ******
TEST(MeshFor2DHeatConductionTest, ReadPoints) {
  // --- Arrange ---
  std::string caseDirectory(
      "../../cases/heat-conduction/2D-heat-conduction-on-a-2-by-2-mesh");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  const std::array<double, 3> expected_node0_centroid = {0.0, 0.0, 0.0};
  const std::array<double, 3> expected_node1_centroid = {0.5, 0.0, 0.0};

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the number of nodes
  EXPECT_EQ(fvMesh.nNodes(), 18);

  // Verify the 1st two nodes
  EXPECT_TRUE(
      VectorMatch(fvMesh.nodes()[0].centroid(), expected_node0_centroid, 3));
  EXPECT_TRUE(
      VectorMatch(fvMesh.nodes()[1].centroid(), expected_node1_centroid, 3));
}

TEST(MeshFor2DHeatConductionTest, ConfirmElementOrdering) {
  // --- Arrange ---
  std::string caseDirectory(
      "../../cases/heat-conduction/2D-heat-conduction-on-a-2-by-2-mesh");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  const std::array<double, 3> expected_element0_centroid = {
      0.250000000000000, 0.250000000000000, 0.05};
  const std::array<double, 3> expected_element1_centroid = {
      0.750000000000000, 0.250000000000000, 0.05};
  const std::array<double, 3> expected_element2_centroid = {
      0.250000000000000, 0.750000000000000, 0.05};
  const std::array<double, 3> expected_element3_centroid = {
      0.750000000000000, 0.750000000000000, 0.05};

  const double maxDiff = 1.0e-12;
  const double maxRelativeDiff = 1.0e-8;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the centroids of all the four elements
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[0].centroid(),
                                expected_element0_centroid, 3, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[1].centroid(),
                                expected_element1_centroid, 3, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[2].centroid(),
                                expected_element2_centroid, 3, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[3].centroid(),
                                expected_element3_centroid, 3, maxDiff,
                                maxRelativeDiff));
}

TEST(InitialBoundaryConditionsTest, ReadBoundaryTemperatureField) {

  // --- Arrange ---
  std::string caseDirectory(
      "../../cases/heat-conduction/2D-heat-conduction-on-a-2-by-2-mesh");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  const std::size_t expected_nBoundaries = 5;
  const std::array<std::string, expected_nBoundaries> expected_boundary_types =
      {"zeroGradient", "zeroGradient", "fixedValue", "fixedValue", "empty"};

  const std::array<std::size_t, expected_nBoundaries> expected_boundary_nFaces =
      {2, 2, 2, 2, 8};

  const std::array<double, 2> expected_boundary_temperature_Field = {373.0,
                                                                     273.0};

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);
  Field<double> internalTemperatureField(fvMesh.nElements());
  std::vector<boundaryField<double>> boundaryTemperatureFields;
  ReadInitialBoundaryConditions initialBoundaryConditionsReader;
  initialBoundaryConditionsReader.readTemperatureField(
      fvMesh, internalTemperatureField, boundaryTemperatureFields);

  // --- Assert ---
  EXPECT_EQ(boundaryTemperatureFields.size(), expected_nBoundaries);

  // --- The 1st boundary ---
  EXPECT_EQ(boundaryTemperatureFields[0].boundaryType(),
            expected_boundary_types[0]);
  EXPECT_EQ(boundaryTemperatureFields[0].size(), expected_boundary_nFaces[0]);

  // --- The 2nd boundary ---
  EXPECT_EQ(boundaryTemperatureFields[1].boundaryType(),
            expected_boundary_types[1]);
  EXPECT_EQ(boundaryTemperatureFields[1].size(), expected_boundary_nFaces[1]);

  // --- The 3rd boundary ---
  EXPECT_EQ(boundaryTemperatureFields[2].boundaryType(),
            expected_boundary_types[2]);
  EXPECT_EQ(boundaryTemperatureFields[2].size(), expected_boundary_nFaces[2]);

  // The two faces
  EXPECT_EQ(boundaryTemperatureFields[2].values()[0],
            expected_boundary_temperature_Field[0]);
  EXPECT_EQ(boundaryTemperatureFields[2].values()[1],
            expected_boundary_temperature_Field[0]);

  // --- The 4th boundary ---
  EXPECT_EQ(boundaryTemperatureFields[3].boundaryType(),
            expected_boundary_types[3]);
  EXPECT_EQ(boundaryTemperatureFields[3].size(), expected_boundary_nFaces[3]);

  // The two faces
  EXPECT_EQ(boundaryTemperatureFields[3].values()[0],
            expected_boundary_temperature_Field[1]);
  EXPECT_EQ(boundaryTemperatureFields[3].values()[1],
            expected_boundary_temperature_Field[1]);

  // --- The 5th boundary ---
  EXPECT_EQ(boundaryTemperatureFields[4].boundaryType(),
            expected_boundary_types[4]);
  EXPECT_EQ(boundaryTemperatureFields[4].size(), expected_boundary_nFaces[4]);
}

TEST(MeshFor2DHeatConductionTest, LabelBoundaryFaces) {
  // --- Arrange ---
  std::string caseDirectory(
      "../../cases/heat-conduction/2D-heat-conduction-on-a-2-by-2-mesh");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  EXPECT_EQ(fvMesh.faces()[0].patchIndex(), -1);
  EXPECT_EQ(fvMesh.faces()[1].patchIndex(), -1);
  EXPECT_EQ(fvMesh.faces()[2].patchIndex(), -1);
  EXPECT_EQ(fvMesh.faces()[3].patchIndex(), -1);
  EXPECT_EQ(fvMesh.faces()[4].patchIndex(), 0);
  EXPECT_EQ(fvMesh.faces()[5].patchIndex(), 0);
  EXPECT_EQ(fvMesh.faces()[6].patchIndex(), 1);
  EXPECT_EQ(fvMesh.faces()[7].patchIndex(), 1);
  EXPECT_EQ(fvMesh.faces()[8].patchIndex(), 2);
  EXPECT_EQ(fvMesh.faces()[9].patchIndex(), 2);
  EXPECT_EQ(fvMesh.faces()[10].patchIndex(), 3);
  EXPECT_EQ(fvMesh.faces()[11].patchIndex(), 3);
  EXPECT_EQ(fvMesh.faces()[12].patchIndex(), 4);
  EXPECT_EQ(fvMesh.faces()[13].patchIndex(), 4);
  EXPECT_EQ(fvMesh.faces()[18].patchIndex(), 4);
  EXPECT_EQ(fvMesh.faces()[19].patchIndex(), 4);
}

TEST(DiffusionTermDiscretizationTest, Discretize2DHeatConductionOn2By2Mesh) {
  // --- Arrange ---
  std::string caseDirectory(
      "../../cases/heat-conduction/2D-heat-conduction-on-a-2-by-2-mesh");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;
  meshReader.readOpenFoamMesh(fvMesh);

  // Define the thermal conductivity and source term
  std::vector<double> thermalConductivity(fvMesh.nFaces(), 1.0);
  std::vector<double> heatSource(fvMesh.nElements(), 0.0);

  // Read initial condition and boundary conditions
  Field<double> internalTemperatureField(fvMesh.nElements());
  std::vector<boundaryField<double>> boundaryTemperatureFields;
  ReadInitialBoundaryConditions initialBoundaryConditionsReader;
  initialBoundaryConditionsReader.readTemperatureField(
      fvMesh, internalTemperatureField, boundaryTemperatureFields);

  // Set up expected values for the coefficient matrix and RHS vector
  const std::array<std::array<double, 4>, 4> expected_coeffMatrix = {
      {{0.4, -0.1, -0.1, 0.0},
       {-0.1, 0.4, 0.0, -0.1},
       {-0.1, 0.0, 0.4, -0.1},
       {0.0, -0.1, -0.1, 0.4}}};
  const std::array<double, 4> expected_RHS = {74.6, 54.6, 74.6, 54.6};
  const double maxDiff = 1.0e-12;
  const double maxRelativeDiff = 1.0e-8;

  // --- Act & Assert for Matrix<double> ---
  {
    Matrix<double> coeffMatrix(fvMesh.nElements(), fvMesh.nElements());
    std::vector<double> RHS(fvMesh.nElements(), 0.0);

    AssembleDiffusionTerm diffusionTermAssembler;
    diffusionTermAssembler.elementBasedAssemble(
        fvMesh, thermalConductivity, heatSource, boundaryTemperatureFields,
        coeffMatrix, RHS);

    // Verify the coefficient matrix
    for (std::size_t i = 0; i < 4; ++i) {
      for (std::size_t j = 0; j < 4; ++j) {
        EXPECT_TRUE(ScalarAlmostEqual(coeffMatrix(i, j),
                                      expected_coeffMatrix[i][j], maxDiff,
                                      maxRelativeDiff));
      }
    }

    // Verify the RHS vector
    for (std::size_t i = 0; i < 4; ++i) {
      EXPECT_TRUE(
          ScalarAlmostEqual(RHS[i], expected_RHS[i], maxDiff, maxRelativeDiff));
    }
  }

  // --- Act & Assert for gko::matrix_data ---
  {
    gko::matrix_data<double, int> coeffMatrix;
    std::vector<double> RHS(fvMesh.nElements(), 0.0);

    AssembleDiffusionTerm diffusionTermAssembler;
    diffusionTermAssembler.elementBasedAssemble(
        fvMesh, thermalConductivity, heatSource, boundaryTemperatureFields,
        coeffMatrix, RHS);

    // Verify the coefficient matrix
    for (std::size_t i = 0; i < 4; ++i) {
      for (std::size_t j = 0; j < 4; ++j) {
        double value = 0.0;
        for (const auto &entry : coeffMatrix.nonzeros) {
          if (entry.row == i && entry.column == j) {
            value = entry.value;
            break;
          }
        }
        EXPECT_TRUE(ScalarAlmostEqual(value, expected_coeffMatrix[i][j],
                                      maxDiff, maxRelativeDiff));
      }
    }

    // Verify the RHS vector
    for (std::size_t i = 0; i < 4; ++i) {
      EXPECT_TRUE(
          ScalarAlmostEqual(RHS[i], expected_RHS[i], maxDiff, maxRelativeDiff));
    }
  }
}

TEST(DiffusionTermDiscretizationTest, Discretize2DHeatConductionOn3By3Mesh) {
  // --- Arrange ---
  std::string caseDirectory(
      "../../cases/heat-conduction/2D-heat-conduction-on-a-3-by-3-mesh");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;
  meshReader.readOpenFoamMesh(fvMesh);

  // Define the thermal conductivity and source term
  std::vector<double> thermalConductivity(fvMesh.nFaces(), 1.0);
  std::vector<double> heatSource(fvMesh.nElements(), 0.0);

  // Read initial condition and boundary conditions
  Field<double> internalTemperatureField(fvMesh.nElements());
  std::vector<boundaryField<double>> boundaryTemperatureFields;
  ReadInitialBoundaryConditions initialBoundaryConditionsReader;
  initialBoundaryConditionsReader.readTemperatureField(
      fvMesh, internalTemperatureField, boundaryTemperatureFields);

  // Define the expected coefficient matrix and RHS vector
  const std::array<std::array<double, 9>, 9> expected_coeffMatrix = {
      {{0.4, -0.1, 0.0, -0.1, 0.0, 0.0, 0.0, 0.0, 0.0},
       {-0.1, 0.3, -0.1, 0.0, -0.1, 0.0, 0.0, 0.0, 0.0},
       {0.0, -0.1, 0.4, 0.0, 0.0, -0.1, 0.0, 0.0, 0.0},
       {-0.1, 0.0, 0.0, 0.5, -0.1, 0.0, -0.1, 0.0, 0.0},
       {0.0, -0.1, 0.0, -0.1, 0.4, -0.1, 0.0, -0.1, 0.0},
       {0.0, 0.0, -0.1, 0.0, -0.1, 0.5, 0.0, 0.0, -0.1},
       {0.0, 0.0, 0.0, -0.1, 0.0, 0.0, 0.4, -0.1, 0.0},
       {0.0, 0.0, 0.0, 0.0, -0.1, 0.0, -0.1, 0.3, -0.1},
       {0.0, 0.0, 0.0, 0.0, 0.0, -0.1, 0.0, -0.1, 0.4}}};

  const std::array<double, 9> expected_RHS = {74.6, 0.0,  54.6, 74.6, 0.0,
                                              54.6, 74.6, 0.0,  54.6};
  const double maxDiff = 1.0e-12;
  const double maxRelativeDiff = 1.0e-8;

  // --- Act & Assert for Matrix<double> ---
  {
    Matrix<double> coeffMatrix(fvMesh.nElements(), fvMesh.nElements());
    std::vector<double> RHS(fvMesh.nElements(), 0.0);

    AssembleDiffusionTerm diffusionTermAssembler;
    diffusionTermAssembler.elementBasedAssemble(
        fvMesh, thermalConductivity, heatSource, boundaryTemperatureFields,
        coeffMatrix, RHS);

    // Verify the coefficient matrix
    for (std::size_t i = 0; i < 9; ++i) {
      for (std::size_t j = 0; j < 9; ++j) {
        EXPECT_TRUE(ScalarAlmostEqual(coeffMatrix(i, j),
                                      expected_coeffMatrix[i][j], maxDiff,
                                      maxRelativeDiff));
      }
    }

    // Verify the RHS vector
    for (std::size_t i = 0; i < 9; ++i) {
      EXPECT_TRUE(
          ScalarAlmostEqual(RHS[i], expected_RHS[i], maxDiff, maxRelativeDiff));
    }
  }

  // --- Act & Assert for gko::matrix_data ---
  {
    gko::matrix_data<double, int> coeffMatrix;
    std::vector<double> RHS(fvMesh.nElements(), 0.0);

    AssembleDiffusionTerm diffusionTermAssembler;
    diffusionTermAssembler.elementBasedAssemble(
        fvMesh, thermalConductivity, heatSource, boundaryTemperatureFields,
        coeffMatrix, RHS);

    // Verify the coefficient matrix
    for (std::size_t i = 0; i < 9; ++i) {
      for (std::size_t j = 0; j < 9; ++j) {
        double value = 0.0;
        for (const auto &entry : coeffMatrix.nonzeros) {
          if (entry.row == i && entry.column == j) {
            value = entry.value;
            break;
          }
        }
        EXPECT_TRUE(ScalarAlmostEqual(value, expected_coeffMatrix[i][j],
                                      maxDiff, maxRelativeDiff));
      }
    }

    // Verify the RHS vector
    for (std::size_t i = 0; i < 9; ++i) {
      EXPECT_TRUE(
          ScalarAlmostEqual(RHS[i], expected_RHS[i], maxDiff, maxRelativeDiff));
    }
  }
}

TEST(LinearSolverTest, Solve2DHeatConductionOn2By2Mesh) {
  // --- Arrange ---
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

  // Expected solution vector
  const std::vector<ValueType> expectedSolution = {348.0, 298.0, 348.0, 298.0};
  std::vector<ValueType> solution(fvMesh.nElements(), 0.0);

  // Set up parameters
  const ValueType maxDiff = 1.0e-12;
  const ValueType maxRelativeDiff = 1.0e-8;
  const RealValueType reduction_factor{1e-7};
  const IndexType maxNumIterations = 1000;

  // --- Act ---
  LinearSolver solver;
  solver.solve(coeffMatrix, RHS, solution, reduction_factor, maxNumIterations);

  // --- Assert ---
  for (std::size_t i = 0; i < solution.size(); ++i) {
    EXPECT_TRUE(ScalarAlmostEqual(solution[i], expectedSolution[i], maxDiff,
                                  maxRelativeDiff));
  }
}

TEST(LinearSolverTest, Solve2DHeatConductionOn3By3Mesh) {
  // --- Arrange ---
  std::string caseDirectory(
      "../../cases/heat-conduction/2D-heat-conduction-on-a-3-by-3-mesh");
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
  const ValueType maxDiff = 1.0e-12;
  const ValueType maxRelativeDiff = 1.0e-8;
  const RealValueType reduction_factor{1e-7};
  const IndexType maxNumIterations = 1000;

  // --- Act ---
  LinearSolver solver;
  solver.solve(coeffMatrix, RHS, solution, reduction_factor, maxNumIterations);

  // --- Assert ---
  // Substitute the solution into the coefficient matrix and compare the result
  // to the RHS
  for (std::size_t i = 0; i < solution.size(); ++i) {
    ValueType result = 0.0;
    for (const auto &entry : coeffMatrix.nonzeros) {
      if (entry.row == i) {
        result += entry.value * solution[entry.column];
      }
    }
    EXPECT_TRUE(ScalarAlmostEqual(result, RHS[i], maxDiff, maxRelativeDiff));
  }
}