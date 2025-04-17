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
  std::string caseDirectory("../../cases/2D-heat-conduction");
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
  std::string caseDirectory("../../cases/2D-heat-conduction");
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

TEST(ReadingMeshFor2DHeatConductionTest, DiscretizingDiffusionTermWorks) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/2D-heat-conduction");
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
  //   Matrix<double> coeffMatrix(fvMesh.nElements(), fvMesh.nElements(), 0.0);
  std::vector<std::vector<double>> coeffMatrix(
      fvMesh.nElements(), std::vector<double>(fvMesh.nElements(), 0.0));
  std::vector<double> RHS(fvMesh.nElements(), 0.0);

  // Set up expected values for the coefficient matrix and RHS vector

  //   const std::array<double, 3> expected_element0_centroid = {
  //       0.250000000000000, 0.250000000000000, 0.500000000000000};
  //   const std::array<double, 3> expected_element1_centroid = {
  //       0.750000000000000, 0.250000000000000, 0.500000000000000};
  //   const std::array<double, 3> expected_element2_centroid = {
  //       0.250000000000000, 0.750000000000000, 0.500000000000000};
  //   const std::array<double, 3> expected_element3_centroid = {
  //       0.750000000000000, 0.750000000000000, 0.500000000000000};

  //   const double maxDiff = 1.0e-9;
  //   const double maxRelativeDiff = 1.0e-4;

  // --- Act ---
  AssembleDiffusionTerm diffusionTermAssembler;
  diffusionTermAssembler.elementBasedAssemble(
      fvMesh, thermalConductivity, heatSource, boundaryTemperatureFields,
      coeffMatrix, RHS);

  // --- Assert ---
  // Verify the coefficient matrix
  // Print out coefficient matrix for debugging
  for (size_t i = 0; i < coeffMatrix.size(); ++i) {
    for (size_t j = 0; j < coeffMatrix[i].size(); ++j) {
      std::cout << coeffMatrix[i][j] << " ";
    }
    std::cout << std::endl;
  }

  // Print out the RHS vector for debugging
  for (size_t i = 0; i < RHS.size(); ++i) {
    std::cout << RHS[i] << std::endl;
  }
  //   EXPECT_EQ(coeffMatrix[0][0], 4);
  // EXPECT_TRUE(ScalarAlmostEqual
  //   std::cout << "coeffMatrix[0][0]: " << coeffMatrix[0][0] << std::endl;
  //   EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[0].centroid(),
  //                                 expected_element0_centroid, 3, maxDiff,
  //                                 maxRelativeDiff));
  //   EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[1].centroid(),
  //                                 expected_element1_centroid, 3, maxDiff,
  //                                 maxRelativeDiff));
  //   EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[2].centroid(),
  //                                 expected_element2_centroid, 3, maxDiff,
  //                                 maxRelativeDiff));
  //   EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[3].centroid(),
  //                                 expected_element3_centroid, 3, maxDiff,
  //                                 maxRelativeDiff));
}
