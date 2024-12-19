#include <gtest/gtest.h>

#include "Mesh.h"
#include "readMesh.h"
#include <cmath>
#include <cstddef>
#include <string>

// template <typename T1, typename T2>
// ::testing::AssertionResult
// AlmostEqualRelativeAndAbs(const T1 &actualValue, const T2 &expectedValue,
//                           const double maxDiff, const double maxRelativeDiff)
//                           {

//   bool almostEqual = false;

//   // Check if the numbers are really close when comparing numbers near zero
//   double absDiff = std::fabs(expectedValue - actualValue);
//   if (absDiff <= maxDiff) {
//     almostEqual = true;
//   }

//   // Check if the numbers are really close when comparing numbers away from
//   // zero
//   auto expectedAbsValue = std::fabs(expectedValue);
//   auto actualAbsValue = std::fabs(actualValue);
//   auto largerAbsValue =
//       (expectedAbsValue > actualAbsValue) ? expectedAbsValue :
//       actualAbsValue;

//   if (absDiff <= largerAbsValue * maxRelativeDiff) {
//     almostEqual = true;
//   }
//   // almostEqual = false;
// }

TEST(ProcessingOpenFoamMeshTest, ReadingPointsWorks) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the number of nodes
  EXPECT_EQ(fvMesh.nNodes(), 1074);
}