#include <gtest/gtest.h>

#include "Mesh.h"
#include "readMesh.h"
#include <string>

TEST(ReadingOpenFoamMeshTest, ReadingPointsWorks) {

  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the number of nodes
  EXPECT_EQ(fvMesh.nNodes(), 1074);

  // Verify the first 3 nodes
  EXPECT_EQ(fvMesh.nodes()[0].x(), 32);
  EXPECT_EQ(fvMesh.nodes()[0].y(), 16);
  EXPECT_EQ(fvMesh.nodes()[0].z(), 0.9377383239);

  EXPECT_EQ(fvMesh.nodes()[1].x(), 33.9429245);
  EXPECT_EQ(fvMesh.nodes()[1].y(), 16.11834526);
  EXPECT_EQ(fvMesh.nodes()[1].z(), 0.9377383239);

  EXPECT_EQ(fvMesh.nodes()[2].x(), 35.84160614);
  EXPECT_EQ(fvMesh.nodes()[2].y(), 16.46798134);
  EXPECT_EQ(fvMesh.nodes()[2].z(), 0.9377383239);

  // Verify the last 3 nodes
  EXPECT_EQ(fvMesh.nodes()[1071].x(), 47.07066231);
  EXPECT_EQ(fvMesh.nodes()[1071].y(), 11.31027148);
  EXPECT_EQ(fvMesh.nodes()[1071].z(), -0.9377383239);

  EXPECT_EQ(fvMesh.nodes()[1072].x(), 54.24871481);
  EXPECT_EQ(fvMesh.nodes()[1072].y(), 14.34322867);
  EXPECT_EQ(fvMesh.nodes()[1072].z(), -0.9377383239);

  EXPECT_EQ(fvMesh.nodes()[1073].x(), 54.15826673);
  EXPECT_EQ(fvMesh.nodes()[1073].y(), 15.64273318);
  EXPECT_EQ(fvMesh.nodes()[1073].z(), -0.9377383239);
}

TEST(ReadingOpenFoamMeshTest, ReadingFacesWorks) {

  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the number of faces
  EXPECT_EQ(fvMesh.nFaces(), 3290);

  // Verify the 1st face
  EXPECT_EQ(fvMesh.faces()[0].nNodes(), 4);
  EXPECT_EQ(fvMesh.faces()[0].iNodes()[0], 36);
  EXPECT_EQ(fvMesh.faces()[0].iNodes()[1], 573);
  EXPECT_EQ(fvMesh.faces()[0].iNodes()[2], 589);
  EXPECT_EQ(fvMesh.faces()[0].iNodes()[3], 52);

  // Verify the 2nd face
  EXPECT_EQ(fvMesh.faces()[1].nNodes(), 4);
  EXPECT_EQ(fvMesh.faces()[1].iNodes()[0], 41);
  EXPECT_EQ(fvMesh.faces()[1].iNodes()[1], 578);
  EXPECT_EQ(fvMesh.faces()[1].iNodes()[2], 634);
  EXPECT_EQ(fvMesh.faces()[1].iNodes()[3], 97);

  // Verify the 3rd face
  EXPECT_EQ(fvMesh.faces()[2].nNodes(), 4);
  EXPECT_EQ(fvMesh.faces()[2].iNodes()[0], 44);
  EXPECT_EQ(fvMesh.faces()[2].iNodes()[1], 81);
  EXPECT_EQ(fvMesh.faces()[2].iNodes()[2], 618);
  EXPECT_EQ(fvMesh.faces()[2].iNodes()[3], 581);

  // Verify the third from the last face
  EXPECT_EQ(fvMesh.faces()[3287].nNodes(), 3);
  EXPECT_EQ(fvMesh.faces()[3287].iNodes()[0], 1072);
  EXPECT_EQ(fvMesh.faces()[3287].iNodes()[1], 945);
  EXPECT_EQ(fvMesh.faces()[3287].iNodes()[2], 1073);

  // Verify the third from the last face
  EXPECT_EQ(fvMesh.faces()[3288].nNodes(), 3);
  EXPECT_EQ(fvMesh.faces()[3288].iNodes()[0], 536);
  EXPECT_EQ(fvMesh.faces()[3288].iNodes()[1], 475);
  EXPECT_EQ(fvMesh.faces()[3288].iNodes()[2], 408);

  // Verify the third from the last face
  EXPECT_EQ(fvMesh.faces()[3289].nNodes(), 3);
  EXPECT_EQ(fvMesh.faces()[3289].iNodes()[0], 1073);
  EXPECT_EQ(fvMesh.faces()[3289].iNodes()[1], 945);
  EXPECT_EQ(fvMesh.faces()[3289].iNodes()[2], 1012);
}

TEST(ReadingOpenFoamMeshTest, ReadingOwnersWorks) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  EXPECT_EQ(fvMesh.nOwners(), 3290);
  EXPECT_EQ(fvMesh.nElements(), 918);

  // Verify the first 10 entries in the owner file
  EXPECT_EQ(fvMesh.faces()[0].iOwner(), 0);
  EXPECT_EQ(fvMesh.faces()[1].iOwner(), 1);
  EXPECT_EQ(fvMesh.faces()[2].iOwner(), 2);
  EXPECT_EQ(fvMesh.faces()[3].iOwner(), 3);
  EXPECT_EQ(fvMesh.faces()[4].iOwner(), 4);
  EXPECT_EQ(fvMesh.faces()[5].iOwner(), 5);
  EXPECT_EQ(fvMesh.faces()[6].iOwner(), 6);
  EXPECT_EQ(fvMesh.faces()[7].iOwner(), 6);
  EXPECT_EQ(fvMesh.faces()[8].iOwner(), 7);
  EXPECT_EQ(fvMesh.faces()[9].iOwner(), 7);

  // Verify the last 10 entries in the owner file
  EXPECT_EQ(fvMesh.faces()[3280].iOwner(), 913);
  EXPECT_EQ(fvMesh.faces()[3281].iOwner(), 913);
  EXPECT_EQ(fvMesh.faces()[3282].iOwner(), 914);
  EXPECT_EQ(fvMesh.faces()[3283].iOwner(), 914);
  EXPECT_EQ(fvMesh.faces()[3284].iOwner(), 915);
  EXPECT_EQ(fvMesh.faces()[3285].iOwner(), 915);
  EXPECT_EQ(fvMesh.faces()[3286].iOwner(), 916);
  EXPECT_EQ(fvMesh.faces()[3287].iOwner(), 916);
  EXPECT_EQ(fvMesh.faces()[3288].iOwner(), 917);
  EXPECT_EQ(fvMesh.faces()[3289].iOwner(), 917);
}

TEST(ReadingOpenFoamMeshTest, ReadingNeighborsWorks) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  EXPECT_EQ(fvMesh.nInteriorFaces(), 1300);

  // Verify the first 10 entries in the neighbor file
  EXPECT_EQ(fvMesh.faces()[0].iNeighbor(), 22);
  EXPECT_EQ(fvMesh.faces()[1].iNeighbor(), 68);
  EXPECT_EQ(fvMesh.faces()[2].iNeighbor(), 29);
  EXPECT_EQ(fvMesh.faces()[3].iNeighbor(), 96);
  EXPECT_EQ(fvMesh.faces()[4].iNeighbor(), 31);
  EXPECT_EQ(fvMesh.faces()[5].iNeighbor(), 34);
  EXPECT_EQ(fvMesh.faces()[6].iNeighbor(), 38);
  EXPECT_EQ(fvMesh.faces()[7].iNeighbor(), 40);
  EXPECT_EQ(fvMesh.faces()[8].iNeighbor(), 42);
  EXPECT_EQ(fvMesh.faces()[9].iNeighbor(), 45);

  // Verify the last 10 entries in the neighbor file
  EXPECT_EQ(fvMesh.faces()[1290].iNeighbor(), 910);
  EXPECT_EQ(fvMesh.faces()[1291].iNeighbor(), 911);
  EXPECT_EQ(fvMesh.faces()[1292].iNeighbor(), 914);
  EXPECT_EQ(fvMesh.faces()[1293].iNeighbor(), 912);
  EXPECT_EQ(fvMesh.faces()[1294].iNeighbor(), 916);
  EXPECT_EQ(fvMesh.faces()[1295].iNeighbor(), 915);
  EXPECT_EQ(fvMesh.faces()[1296].iNeighbor(), 917);
  EXPECT_EQ(fvMesh.faces()[1297].iNeighbor(), 915);
  EXPECT_EQ(fvMesh.faces()[1298].iNeighbor(), 916);
  EXPECT_EQ(fvMesh.faces()[1299].iNeighbor(), 917);
}

TEST(ReadingOpenFoamMeshTest, ReadingBoundariesWorks) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  EXPECT_EQ(fvMesh.nBoundaries(), 6);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
