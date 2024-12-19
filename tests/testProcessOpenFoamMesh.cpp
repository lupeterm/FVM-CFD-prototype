#include <gtest/gtest.h>

#include "Mesh.h"
#include "readMesh.h"
#include <cstddef>
#include <string>

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