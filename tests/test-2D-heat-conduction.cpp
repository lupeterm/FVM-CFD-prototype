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

// TEST(ReadingMeshFor2DHeatConductionTest, ComputingElementCentroidWorks) {
//   // --- Arrange ---
//   std::string caseDirectory("../../cases/2D-heat-conduction");
//   Mesh fvMesh(caseDirectory);
//   ReadMesh meshReader;

//   const std::array<double, 3> expected_element0_centroid = {
//       0.00250000000000000, 0.00250000000000000, 0.00500000000000000};
//   const std::array<double, 3> expected_element1_centroid = {
//       0.00750000000000000, 0.00250000000000000, 0.00500000000000000};

//   const std::array<double, 3> expected_element198_centroid = {
//       0.0925000000000000, 0.0475000000000000, 0.00500000000000000};
//   const std::array<double, 3> expected_element199_centroid = {
//       0.0975000000000000, 0.0475000000000000, 0.00500000000000000};

//   const std::array<double, 3> expected_element398_centroid = {
//       0.0925000000000000, 0.0975000000000000, 0.00500000000000000};
//   const std::array<double, 3> expected_element399_centroid = {
//       0.0975000000000000, 0.0975000000000000, 0.00500000000000000};

//   const double maxDiff = 1.0e-9;
//   const double maxRelativeDiff = 1.0e-4;

//   // --- Act ---
//   meshReader.readOpenFoamMesh(fvMesh);

//   // --- Assert ---
//   // Verify the centroids of the first two elements
//   EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[0].centroid(),
//                                 expected_element0_centroid, 3, maxDiff,
//                                 maxRelativeDiff));
//   EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[1].centroid(),
//                                 expected_element1_centroid, 3, maxDiff,
//                                 maxRelativeDiff));

//   // Verify the centroids of the middle two elements
//   EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[198].centroid(),
//                                 expected_element198_centroid, 3, maxDiff,
//                                 maxRelativeDiff));
//   EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[199].centroid(),
//                                 expected_element199_centroid, 3, maxDiff,
//                                 maxRelativeDiff));

//   // Verify the centroids of the last two elements
//   EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[398].centroid(),
//                                 expected_element398_centroid, 3, maxDiff,
//                                 maxRelativeDiff));
//   EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[399].centroid(),
//                                 expected_element399_centroid, 3, maxDiff,
//                                 maxRelativeDiff));
// }
