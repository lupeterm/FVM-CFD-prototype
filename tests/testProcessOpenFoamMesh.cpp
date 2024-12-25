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
  const std::array<double, 3> expected_face2_centroid = {48.999999999999990, 63,
                                                         0};
  const std::array<double, 3> expected_face1644_centroid = {
      0.577350269333333, 3.000000000000000, 0.937738323900000};
  const std::array<double, 3> expected_face1645_centroid = {
      0.577350269333333, 3, -0.937738323900000};
  const std::array<double, 3> expected_face1646_centroid = {
      1.244016936000000, 1.666666666666667, 0.937738323900000};
  const std::array<double, 3> expected_face3287_centroid = {
      53.686867763333325, 14.990837000000000, -0.937738323900000};
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
  // The first three faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[0].centroid(),
                                expected_face0_centroid, 3, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1].centroid(),
                                expected_face1_centroid, 3, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[2].centroid(),
                                expected_face2_centroid, 3, maxDiff,
                                maxRelativeDiff));

  // The middle three faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1644].centroid(),
                                expected_face1644_centroid, 3, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1645].centroid(),
                                expected_face1645_centroid, 3, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1646].centroid(),
                                expected_face1646_centroid, 3, maxDiff,
                                maxRelativeDiff));

  // The last three faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[3287].centroid(),
                                expected_face3287_centroid, 3, maxDiff,
                                maxRelativeDiff));
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
  const std::array<double, 3> expected_face2_Sf = {3.750953295600000,
                                                   -3.750953295600000, 0};
  const std::array<double, 3> expected_face1644_Sf = {0, 0, 1.732050808000000};
  const std::array<double, 3> expected_face1645_Sf = {0, 0, -1.732050808000000};
  const std::array<double, 3> expected_face1646_Sf = {0, 0, 2.732050808000000};
  const std::array<double, 3> expected_face3287_Sf = {0, 0, -1.007321761549513};
  const std::array<double, 3> expected_face3288_Sf = {0, 0, 1.152196763229249};
  const std::array<double, 3> expected_face3289_Sf = {0, 0, -1.152196763229249};

  const double maxDiff = 1.0e-9;
  const double maxRelativeDiff = 1.0e-4;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the surface vectors of mesh faces
  // The first three faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[0].Sf(), expected_face0_Sf, 3,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1].Sf(), expected_face1_Sf, 3,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[2].Sf(), expected_face2_Sf, 3,
                                maxDiff, maxRelativeDiff));

  // The middle three faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1644].Sf(), expected_face1644_Sf,
                                3, maxDiff, maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1645].Sf(), expected_face1645_Sf,
                                3, maxDiff, maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1646].Sf(), expected_face1646_Sf,
                                3, maxDiff, maxRelativeDiff));

  // The last three faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[3287].Sf(), expected_face3287_Sf,
                                3, maxDiff, maxRelativeDiff));
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
  const double expected_face2_area = 5.304649022465577;
  const double expected_face1644_area = 1.732050808000000;
  const double expected_face1645_area = 1.732050808000000;
  const double expected_face1646_area = 2.732050808000000;
  const double expected_face3287_area = 1.007321761549513;
  const double expected_face3288_area = 1.152196763229249;
  const double expected_face3289_area = 1.152196763229249;

  const double maxDiff = 1.0e-9;
  const double maxRelativeDiff = 1.0e-4;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the surface areas of mesh faces
  // The first three faces
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[0].area(), expected_face0_area,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[1].area(), expected_face1_area,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[2].area(), expected_face2_area,
                                maxDiff, maxRelativeDiff));

  // The middle three faces
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[1644].area(),
                                expected_face1644_area, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[1645].area(),
                                expected_face1645_area, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[1646].area(),
                                expected_face1646_area, maxDiff,
                                maxRelativeDiff));

  // The last three faces
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[3287].area(),
                                expected_face3287_area, maxDiff,
                                maxRelativeDiff));
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
  const double expected_element2_volume = 3.750953295599991;
  const double expected_element458_volume = 1.760514155353620;
  const double expected_element459_volume = 1.476604804863560;
  const double expected_element460_volume = 1.086792891806789;
  const double expected_element915_volume = 1.549771597510417;
  const double expected_element916_volume = 1.889208440606863;
  const double expected_element917_volume = 2.160918123107190;

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
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.elements()[2].volume(),
                                expected_element2_volume, maxDiff,
                                maxRelativeDiff));

  // Verify the volumes of the middle three elements
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.elements()[458].volume(),
                                expected_element458_volume, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.elements()[459].volume(),
                                expected_element459_volume, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.elements()[460].volume(),
                                expected_element460_volume, maxDiff,
                                maxRelativeDiff));

  // Verify the volumes of the last three elements
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.elements()[915].volume(),
                                expected_element915_volume, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.elements()[916].volume(),
                                expected_element916_volume, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.elements()[917].volume(),
                                expected_element917_volume, maxDiff,
                                maxRelativeDiff));
}

TEST(ComputingElementVolumeAndCentroidTest, ComputingElementCentroidWorks) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  const std::array<double, 3> expected_element0_centroid = {
      0.666666666666667, 15.333333333333332, 4.439763456642422e-17};
  const std::array<double, 3> expected_element1_centroid = {
      52.872570040000000, -4.174897670333334, 0};
  const std::array<double, 3> expected_element2_centroid = {
      48.666666666666664, 63.333333333333330, 0};
  const std::array<double, 3> expected_element458_centroid = {
      54.201239489999990, 9.628230276666667, -1.576560775227273e-17};
  const std::array<double, 3> expected_element459_centroid = {
      54.087574729999990, 10.260431970999997, -1.879688832395040e-17};
  const std::array<double, 3> expected_element460_centroid = {
      55.180164206666674, 5.540703773666666, 2.553897419174813e-17};
  const std::array<double, 3> expected_element915_centroid = {
      54.832016820000014, 15.735877276666670, -3.581892410496619e-17};
  const std::array<double, 3> expected_element916_centroid = {
      53.686867763333330, 14.990837000000000, -2.938328563333445e-17};
  const std::array<double, 3> expected_element917_centroid = {
      53.340025863333330, 15.796400383333333, 2.568868789504999e-17};

  const double maxDiff = 1.0e-9;
  const double maxRelativeDiff = 1.0e-4;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the centroids of the first three elements
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[0].centroid(),
                                expected_element0_centroid, 3, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[1].centroid(),
                                expected_element1_centroid, 3, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[2].centroid(),
                                expected_element2_centroid, 3, maxDiff,
                                maxRelativeDiff));

  // Verify the centroids of the middle three elements
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[458].centroid(),
                                expected_element458_centroid, 3, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[459].centroid(),
                                expected_element459_centroid, 3, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[460].centroid(),
                                expected_element460_centroid, 3, maxDiff,
                                maxRelativeDiff));

  // Verify the centroids of the last three elements
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[915].centroid(),
                                expected_element915_centroid, 3, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[916].centroid(),
                                expected_element916_centroid, 3, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[917].centroid(),
                                expected_element917_centroid, 3, maxDiff,
                                maxRelativeDiff));
}