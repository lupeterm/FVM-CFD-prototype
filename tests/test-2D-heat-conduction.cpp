#include <gtest/gtest.h>

#include "Mesh.hpp"
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

TEST(ReadingMeshFor2DHeatConductionTest, ComputingElementCentroidWorks) {
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
