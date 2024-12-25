#include <gtest/gtest.h>

#include "Mesh.h"
#include "readMesh.h"
#include <array>
#include <cmath>
#include <cstddef>
#include <string>

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

::testing::AssertionResult ScalarAlmostEqual(const double &actual,
                                             const double &expected,
                                             const double maxDiff,
                                             const double maxRelativeDiff) {

  if (!AlmostEqualAbsAndRelative(actual, expected, maxDiff, maxRelativeDiff)) {
    return ::testing::AssertionFailure()
           << "actual (" << actual << ") != expected (" << expected << ")";
  }
  return ::testing::AssertionSuccess();
}

// ****** Tests ******
TEST(ProcessingBasicFaceGeometryTest, ComputingFaceCentroidWorks) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  const std::array<double, 3> expected_face0_centroid = {1, 14.999999999999998,
                                                         0};
  const std::array<double, 3> expected_face1_centroid = {
      53.0392360700000, -3.99307942350000, 0.0};
  const std::array<double, 3> expected_face1644_centroid = {
      0.577350269333333, 3.000000000000000, 0.937738323900000};
  const std::array<double, 3> expected_face1645_centroid = {
      0.577350269333333, 3, -0.937738323900000};
  const std::array<double, 3> expected_face3288_centroid = {
      53.340025863333340, 15.796400383333335, 0.937738323900000};
  const std::array<double, 3> expected_face3289_centroid = {
      53.340025863333340, 15.796400383333333, -0.937738323900000};

  const double maxDiff = 1.0e-9;
  const double maxRelativeDiff = 1.0e-4;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // *** Verify the centroids of faces ***
  // The first two faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[0].centroid(),
                                expected_face0_centroid, 3, maxDiff,
                                maxRelativeDiff));

  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1].centroid(),
                                expected_face1_centroid, 3, maxDiff,
                                maxRelativeDiff));

  // The middle faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1644].centroid(),
                                expected_face1644_centroid, 3, maxDiff,
                                maxRelativeDiff));

  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1645].centroid(),
                                expected_face1645_centroid, 3, maxDiff,
                                maxRelativeDiff));

  // The last two faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[3288].centroid(),
                                expected_face3288_centroid, 3, maxDiff,
                                maxRelativeDiff));

  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[3289].centroid(),
                                expected_face3289_centroid, 3, maxDiff,
                                maxRelativeDiff));
}

TEST(ProcessingBasicFaceGeometryTest, ComputingFaceSurfaceVectorWorks) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  const std::array<double, 3> expected_face0_Sf = {3.750953295600000,
                                                   -3.750953295600000, 0};
  const std::array<double, 3> expected_face1_Sf = {2.045975256479117,
                                                   1.875483812120801, 0};
  const std::array<double, 3> expected_face1644_Sf = {0, 0, 1.732050808000000};
  const std::array<double, 3> expected_face1645_Sf = {0, 0, -1.732050808000000};
  const std::array<double, 3> expected_face3288_Sf = {0, 0, 1.152196763229249};
  const std::array<double, 3> expected_face3289_Sf = {0, 0, -1.152196763229249};

  const double maxDiff = 1.0e-9;
  const double maxRelativeDiff = 1.0e-4;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the surface vectors of mesh faces
  // The first two faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[0].Sf(), expected_face0_Sf, 3,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1].Sf(), expected_face1_Sf, 3,
                                maxDiff, maxRelativeDiff));

  // The middle faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1644].Sf(), expected_face1644_Sf,
                                3, maxDiff, maxRelativeDiff));

  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1645].Sf(), expected_face1645_Sf,
                                3, maxDiff, maxRelativeDiff));

  // The last two faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[3288].Sf(), expected_face3288_Sf,
                                3, maxDiff, maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[3289].Sf(), expected_face3289_Sf,
                                3, maxDiff, maxRelativeDiff));
}

TEST(ProcessingBasicFaceGeometryTest, ComputingFaceAreaWorks) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  const double expected_face0_area = 5.304649022465577;
  const double expected_face1_area = 2.775509733301608;
  const double expected_face1644_area = 1.732050808000000;
  const double expected_face1645_area = 1.732050808000000;
  const double expected_face3288_area = 1.152196763229249;
  const double expected_face3289_area = 1.152196763229249;

  const double maxDiff = 1.0e-9;
  const double maxRelativeDiff = 1.0e-4;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the surface areas of mesh faces
  // The first two faces
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[0].area(), expected_face0_area,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[1].area(), expected_face1_area,
                                maxDiff, maxRelativeDiff));

  // The middle faces
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[1644].area(),
                                expected_face1644_area, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[1645].area(),
                                expected_face1645_area, maxDiff,
                                maxRelativeDiff));

  // The last two faces
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[3288].area(),
                                expected_face3288_area, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[3289].area(),
                                expected_face3289_area, maxDiff,
                                maxRelativeDiff));
}

TEST(ComputingElementVolumeAndCentroidTest, ComputingElementVolumeWorks) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  const double expected_element0_volume = 3.750953295600002;
  const double expected_element1_volume = 1.022987628239554;

  const double maxDiff = 1.0e-9;
  const double maxRelativeDiff = 1.0e-4;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the volumes of the first three elements
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.elements()[0].volume(),
                                expected_element0_volume, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.elements()[1].volume(),
                                expected_element1_volume, maxDiff,
                                maxRelativeDiff));
}