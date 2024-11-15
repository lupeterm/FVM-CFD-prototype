#include <gtest/gtest.h>

#include "Mesh.h"
#include "readMesh.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

TEST(ReadingOpenFoamMeshTest, ReadingMeshPointsWorks) {

  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  //   std::vector<Node> nodes;
  //   std::vector<Face> faces;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);
  //   // cfdReadOpenFoamMesh(nodes, faces, caseDirectory);
  //   Mesh fvMesh{caseDirectory, nodes, faces};

  // --- Assert ---
  //   // Verify the number of nodes
  EXPECT_EQ(fvMesh.nNodes(), 1074);
  //   EXPECT_EQ(fvMesh.nodes().size(), 1074);

  //   // Verify the first 3 nodes
  //   EXPECT_EQ(fvMesh.nodes()[0].centroid[0], 32);
  //   EXPECT_EQ(fvMesh.nodes()[0].centroid[1], 16);
  //   EXPECT_EQ(fvMesh.nodes()[0].centroid[2], 0.9377383239);

  //   EXPECT_EQ(fvMesh.nodes()[1].centroid[0], 33.9429245);
  //   EXPECT_EQ(fvMesh.nodes()[1].centroid[1], 16.11834526);
  //   EXPECT_EQ(fvMesh.nodes()[1].centroid[2], 0.9377383239);

  //   EXPECT_EQ(fvMesh.nodes()[2].centroid[0], 35.84160614);
  //   EXPECT_EQ(fvMesh.nodes()[2].centroid[1], 16.46798134);
  //   EXPECT_EQ(fvMesh.nodes()[2].centroid[2], 0.9377383239);

  //   // Verify the last 3 nodes
  //   EXPECT_EQ(fvMesh.nodes()[1071].centroid[0], 47.07066231);
  //   EXPECT_EQ(fvMesh.nodes()[1071].centroid[1], 11.31027148);
  //   EXPECT_EQ(fvMesh.nodes()[1071].centroid[2], -0.9377383239);

  //   EXPECT_EQ(fvMesh.nodes()[1072].centroid[0], 54.24871481);
  //   EXPECT_EQ(fvMesh.nodes()[1072].centroid[1], 14.34322867);
  //   EXPECT_EQ(fvMesh.nodes()[1072].centroid[2], -0.9377383239);

  //   EXPECT_EQ(fvMesh.nodes()[1073].centroid[0], 54.15826673);
  //   EXPECT_EQ(fvMesh.nodes()[1073].centroid[1], 15.64273318);
  //   EXPECT_EQ(fvMesh.nodes()[1073].centroid[2], -0.9377383239);
}

// TEST(ReadingOpenFoamMeshTest, ReadingMeshFacesWorks) {

//   // --- Arrange ---
//   std::string caseDirectory("../../cases/elbow");
//   std::vector<Node> nodes;
//   std::vector<Face> faces;

//   // --- Act ---
//   // cfdReadOpenFoamMesh(nodes, faces, caseDirectory);
//   Mesh fvMesh{caseDirectory, nodes, faces};

//   // --- Assert ---
//   // Verify the number of faces
//   EXPECT_EQ(fvMesh.faces().size(), 3290);

//   // Verify the 1st face
//   EXPECT_EQ(fvMesh.faces()[0].iNodes.size(), 4);
//   EXPECT_EQ(fvMesh.faces()[0].iNodes[0], 36);
//   EXPECT_EQ(fvMesh.faces()[0].iNodes[1], 573);
//   EXPECT_EQ(fvMesh.faces()[0].iNodes[2], 589);
//   EXPECT_EQ(fvMesh.faces()[0].iNodes[3], 52);

//   // Verify the 2nd face
//   EXPECT_EQ(fvMesh.faces()[1].iNodes.size(), 4);
//   EXPECT_EQ(fvMesh.faces()[1].iNodes[0], 41);
//   EXPECT_EQ(fvMesh.faces()[1].iNodes[1], 578);
//   EXPECT_EQ(fvMesh.faces()[1].iNodes[2], 634);
//   EXPECT_EQ(fvMesh.faces()[1].iNodes[3], 97);

//   // Verify the 3rd face
//   EXPECT_EQ(fvMesh.faces()[2].iNodes.size(), 4);
//   EXPECT_EQ(fvMesh.faces()[2].iNodes[0], 44);
//   EXPECT_EQ(fvMesh.faces()[2].iNodes[1], 81);
//   EXPECT_EQ(fvMesh.faces()[2].iNodes[2], 618);
//   EXPECT_EQ(fvMesh.faces()[2].iNodes[3], 581);

//   // Verify the third from the last face
//   EXPECT_EQ(fvMesh.faces()[3287].iNodes.size(), 3);
//   EXPECT_EQ(fvMesh.faces()[3287].iNodes[0], 1072);
//   EXPECT_EQ(fvMesh.faces()[3287].iNodes[1], 945);
//   EXPECT_EQ(fvMesh.faces()[3287].iNodes[2], 1073);

//   // Verify the third from the last face
//   EXPECT_EQ(fvMesh.faces()[3288].iNodes.size(), 3);
//   EXPECT_EQ(fvMesh.faces()[3288].iNodes[0], 536);
//   EXPECT_EQ(fvMesh.faces()[3288].iNodes[1], 475);
//   EXPECT_EQ(fvMesh.faces()[3288].iNodes[2], 408);

//   // Verify the third from the last face
//   EXPECT_EQ(fvMesh.faces()[3289].iNodes.size(), 3);
//   EXPECT_EQ(fvMesh.faces()[3289].iNodes[0], 1073);
//   EXPECT_EQ(fvMesh.faces()[3289].iNodes[1], 945);
//   EXPECT_EQ(fvMesh.faces()[3289].iNodes[2], 1012);
// }

// TEST(ReadingOpenFoamMeshTest, ReadingMeshOwnersWorks) {
//   // --- Arrange ---
//   std::string caseDirectory("../../cases/elbow");
//   std::vector<Node> nodes;
//   std::vector<Face> faces;

//   // --- Act ---
//   // cfdReadOpenFoamMesh(nodes, faces, caseDirectory);
//   Mesh fvMesh{caseDirectory, nodes, faces};

//   // --- Assert ---
//   // Verify the number of elements
//   // EXPECT_EQ(fvMesh.numberOfElement(), 918);
//   EXPECT_EQ(fvMesh.faces()[0].iOwner, 0);
//   EXPECT_EQ(fvMesh.faces()[1].iOwner, 1);
//   EXPECT_EQ(fvMesh.faces()[2].iOwner, 2);
//   EXPECT_EQ(fvMesh.faces()[3].iOwner, 3);
//   EXPECT_EQ(fvMesh.faces()[4].iOwner, 4);
//   EXPECT_EQ(fvMesh.faces()[5].iOwner, 5);
//   EXPECT_EQ(fvMesh.faces()[6].iOwner, 6);
//   EXPECT_EQ(fvMesh.faces()[7].iOwner, 6);
//   EXPECT_EQ(fvMesh.faces()[8].iOwner, 7);
//   EXPECT_EQ(fvMesh.faces()[9].iOwner, 7);
// }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
