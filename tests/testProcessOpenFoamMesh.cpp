#include <gtest/gtest.h>

#include "Mesh.h"
#include "readMesh.h"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <string>

// template <typename T> void printOutVector(std::vector<T> &customVector) {
//   for (std::size_t iCoordinate = 0; iCoordinate < customVector.size();
//        ++iCoordinate) {
//     std::cout << customVector[iCoordinate] << "\n";
//   }
//   std::cout << std::endl;
// }

bool AlmostEqualAbsAndRelative(const double &actualValue,
                               const double &expectedValue,
                               const double maxDiff,
                               const double maxRelativeDiff) {

  // Check if the numbers are really close when comparing not very small numbers
  // or comparing against zero
  double absDiff = std::fabs(actualValue - expectedValue);
  if (absDiff <= maxDiff) {
    return true;
  }

  // Check if the numbers are really close when comparing very small non-zero
  // numbers
  auto expectedAbsValue = std::fabs(expectedValue);
  auto actualAbsValue = std::fabs(actualValue);

  if (absDiff <= expectedAbsValue * maxRelativeDiff) {
    return true;
  }
  return false;
}

template <typename T1, typename T2>
::testing::AssertionResult
VectorAlmostEqual(const T1 &actual, const T2 &expected, const std::size_t size,
                  const double maxDiff, const double maxRelativeDiff) {
  for (std::size_t i = 0; i < size; ++i) {
    if (!AlmostEqualAbsAndRelative(actual[i], expected[i], maxDiff,
                                   maxRelativeDiff)) {
      return ::testing::AssertionFailure()
             << "actual[" << i << "] (" << actual[i] << ") != expected[" << i
             << "] (" << expected[i] << ")";
    }
  }
  return ::testing::AssertionSuccess();
}

TEST(ProcessingBasicFaceGeometryTest, ComputingFaceCentroidWorks) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  std::vector<double> face0_centroid = {1.0, 15.0, 0.0};
  std::vector<double> face1_centroid = {53.0392360700000, -3.99307942350000,
                                        0.0};
  std::vector<double> face1644_centroid = {0.577350269333333, 3.000000000000000,
                                           0.937738323900000};
  std::vector<double> face1645_centroid = {0.577350269333333, 3,
                                           -0.937738323900000};
  std::vector<double> face3288_centroid = {
      53.340025863333340, 15.796400383333335, 0.937738323900000};
  std::vector<double> face3289_centroid = {
      53.340025863333340, 15.796400383333333, -0.937738323900000};

  const double maxDiff = 1.0e-9;
  const double maxRelativeDiff = 1.0e-4;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // *** Verify the centroids of faces ***
  // The first two faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[0].centroid(), face0_centroid, 3,
                                maxDiff, maxRelativeDiff));

  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1].centroid(), face1_centroid, 3,
                                maxDiff, maxRelativeDiff));

  // The middle faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1644].centroid(),
                                face1644_centroid, 3, maxDiff,
                                maxRelativeDiff));

  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1645].centroid(),
                                face1645_centroid, 3, maxDiff,
                                maxRelativeDiff));

  // The last two faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[3288].centroid(),
                                face3288_centroid, 3, maxDiff,
                                maxRelativeDiff));

  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[3289].centroid(),
                                face3289_centroid, 3, maxDiff,
                                maxRelativeDiff));
}

TEST(ProcessingBasicFaceGeometryTest, ComputingFaceSurfaceVectorWorks) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  std::vector<double> face0_Sf = {3.750953295600000, -3.750953295600000, 0};
  std::vector<double> face1_Sf = {2.045975256479117, 1.875483812120801, 0};
  std::vector<double> face1644_Sf = {0, 0, 1.732050808000000};
  std::vector<double> face1645_Sf = {0, 0, -1.732050808000000};
  std::vector<double> face3288_Sf = {0, 0, 1.152196763229249};
  std::vector<double> face3289_Sf = {0, 0, -1.152196763229249};

  const double maxDiff = 1.0e-9;
  const double maxRelativeDiff = 1.0e-4;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the surface vectors of mesh faces
  // The first two faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[0].Sf(), face0_Sf, 3, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1].Sf(), face1_Sf, 3, maxDiff,
                                maxRelativeDiff));

  // The middle faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1644].Sf(), face1644_Sf, 3,
                                maxDiff, maxRelativeDiff));

  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1645].Sf(), face1645_Sf, 3,
                                maxDiff, maxRelativeDiff));

  // The last two faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[3288].Sf(), face3288_Sf, 3,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[3289].Sf(), face3289_Sf, 3,
                                maxDiff, maxRelativeDiff));
}