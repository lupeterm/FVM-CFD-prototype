#include "IO.hpp"
#include "Mesh.hpp"
#include "ReadMesh.hpp"
#include <gtest/gtest.h>

// ****** Tests ******
TEST(IOTest, GettingDirectoryWorks) {
  // --- Arrange ---
  ReadMesh meshReader;
  Mesh fvMesh;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the number of nodes for the elbow case (../../cases/elbow)
  EXPECT_EQ(fvMesh.nNodes(), 1074);
}
