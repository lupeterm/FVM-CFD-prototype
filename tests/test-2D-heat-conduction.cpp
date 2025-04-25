#include <gtest/gtest.h>

#include "AssembleDiffusionTerm.hpp"
#include "Field.hpp"
#include "Matrix.hpp"
#include "Mesh.hpp"
#include "ReadInitialBoundaryConditions.hpp"
#include "ReadMesh.hpp"
#include "utilitiesForTesting.hpp"
#include <array>
#include <string>

// ****** Tests ******
TEST(ReadingMeshFor2DHeatConductionTest, ReadingPointsWorks) {
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

TEST(ReadingMeshFor2DHeatConductionTest, ConfirmingElementOrdering) {
  // --- Arrange ---
  std::string caseDirectory(
      "../../cases/heat-conduction/2D-heat-conduction-on-a-2-by-2-mesh");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  const std::array<double, 3> expected_element0_centroid = {
      0.250000000000000, 0.250000000000000, 0.500000000000000};
  const std::array<double, 3> expected_element1_centroid = {
      0.750000000000000, 0.250000000000000, 0.500000000000000};
  const std::array<double, 3> expected_element2_centroid = {
      0.250000000000000, 0.750000000000000, 0.500000000000000};
  const std::array<double, 3> expected_element3_centroid = {
      0.750000000000000, 0.750000000000000, 0.500000000000000};

  const double maxDiff = 1.0e-9;
  const double maxRelativeDiff = 1.0e-4;

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

TEST(ReadInitialBoundaryConditionsTest, ReadingBoundaryTemperatureFieldWorks) {

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

TEST(SortBoundaryFacesFromInteriorFacesTest, LabelingBoundaryFacesWorks) {
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

TEST(DiscretizingDiffusionTermTest,
     Discretizing2DHeatConductionOn2By2MeshWorks) {
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

  // Define the coefficient matrix and RHS vector
  Matrix<double> coeffMatrix(fvMesh.nElements(), fvMesh.nElements());
  std::vector<double> RHS(fvMesh.nElements(), 0.0);

  // Set up expected values for the coefficient matrix and RHS vector
  // The expected coefficient matrix is:
  // |  4.0 -1.0 -1.0  0.0 |
  // | -1.0  4.0  0.0 -1.0 |
  // | -1.0  0.0  4.0 -1.0 |
  // |  0.0 -1.0 -1.0  4.0 |
  const std::array<std::array<double, 4>, 4> expected_coeffMatrix = {
      {{4.0, -1.0, -1.0, 0.0},
       {-1.0, 4.0, 0.0, -1.0},
       {-1.0, 0.0, 4.0, -1.0},
       {0.0, -1.0, -1.0, 4.0}}};
  const std::array<double, 4> expected_RHS = {746.0, 546.0, 746.0, 546.0};
  const double maxDiff = 1.0e-9;
  const double maxRelativeDiff = 1.0e-4;

  // --- Act ---
  AssembleDiffusionTerm diffusionTermAssembler;
  diffusionTermAssembler.elementBasedAssemble(
      fvMesh, thermalConductivity, heatSource, boundaryTemperatureFields,
      coeffMatrix, RHS);

  // --- Assert ---
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

TEST(DiscretizingDiffusionTermTest,
     Discretizing2DHeatConductionOn3By3MeshWorks) {
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

  // Define the coefficient matrix and RHS vector
  Matrix<double> coeffMatrix(fvMesh.nElements(), fvMesh.nElements());
  std::vector<double> RHS(fvMesh.nElements(), 0.0);

  // Set up expected values for the coefficient matrix and RHS vector
  const std::array<std::array<double, 9>, 9> expected_coeffMatrix = {
      {{4.0, -1.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0, 0.0},
       {-1.0, 3.0, -1.0, 0.0, -1.0, 0.0, 0.0, 0.0, 0.0},
       {0.0, -1.0, 4.0, 0.0, 0.0, -1.0, 0.0, 0.0, 0.0},
       {-1.0, 0.0, 0.0, 5.0, -1.0, 0.0, -1.0, 0.0, 0.0},
       {0.0, -1.0, 0.0, -1.0, 4.0, -1.0, 0.0, -1.0, 0.0},
       {0.0, 0.0, -1.0, 0.0, -1.0, 5.0, 0.0, 0.0, -1.0},
       {0.0, 0.0, 0.0, -1.0, 0.0, 0.0, 4.0, -1.0, 0.0},
       {0.0, 0.0, 0.0, 0.0, -1.0, 0.0, -1.0, 3.0, -1.0},
       {0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 0.0, -1.0, 4.0}}};

  const std::array<double, 9> expected_RHS = {746.0, 0.0,   546.0, 746.0, 0.0,
                                              546.0, 746.0, 0.0,   546.0};
  const double maxDiff = 1.0e-9;
  const double maxRelativeDiff = 1.0e-4;

  // --- Act ---
  AssembleDiffusionTerm diffusionTermAssembler;
  diffusionTermAssembler.elementBasedAssemble(
      fvMesh, thermalConductivity, heatSource, boundaryTemperatureFields,
      coeffMatrix, RHS);

  // --- Assert ---
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
