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

  // Verify the 1st boundary
  EXPECT_EQ(fvMesh.boundaries()[0].userName(), "wall-4");
  EXPECT_EQ(fvMesh.boundaries()[0].index(), 0);
  EXPECT_EQ(fvMesh.boundaries()[0].type(), "wall");
  EXPECT_EQ(fvMesh.boundaries()[0].nFaces(), 100);
  EXPECT_EQ(fvMesh.boundaries()[0].startFace(), 1300);

  // Verify the 2nd boundary
  EXPECT_EQ(fvMesh.boundaries()[1].userName(), "velocity-inlet-5");
  EXPECT_EQ(fvMesh.boundaries()[1].index(), 1);
  EXPECT_EQ(fvMesh.boundaries()[1].type(), "inlet");
  EXPECT_EQ(fvMesh.boundaries()[1].nFaces(), 8);
  EXPECT_EQ(fvMesh.boundaries()[1].startFace(), 1400);

  // Verify the 3rd boundary
  EXPECT_EQ(fvMesh.boundaries()[2].userName(), "velocity-inlet-6");
  EXPECT_EQ(fvMesh.boundaries()[2].index(), 2);
  EXPECT_EQ(fvMesh.boundaries()[2].type(), "inlet");
  EXPECT_EQ(fvMesh.boundaries()[2].nFaces(), 4);
  EXPECT_EQ(fvMesh.boundaries()[2].startFace(), 1408);

  // Verify the 4th boundary
  EXPECT_EQ(fvMesh.boundaries()[3].userName(), "pressure-outlet-7");
  EXPECT_EQ(fvMesh.boundaries()[3].index(), 3);
  EXPECT_EQ(fvMesh.boundaries()[3].type(), "outlet");
  EXPECT_EQ(fvMesh.boundaries()[3].nFaces(), 8);
  EXPECT_EQ(fvMesh.boundaries()[3].startFace(), 1412);

  // Verify the 5th boundary
  EXPECT_EQ(fvMesh.boundaries()[4].userName(), "wall-8");
  EXPECT_EQ(fvMesh.boundaries()[4].index(), 4);
  EXPECT_EQ(fvMesh.boundaries()[4].type(), "wall");
  EXPECT_EQ(fvMesh.boundaries()[4].nFaces(), 34);
  EXPECT_EQ(fvMesh.boundaries()[4].startFace(), 1420);

  // Verify the 6th boundary
  EXPECT_EQ(fvMesh.boundaries()[5].userName(), "frontAndBackPlanes");
  EXPECT_EQ(fvMesh.boundaries()[5].index(), 5);
  EXPECT_EQ(fvMesh.boundaries()[5].type(), "empty");
  EXPECT_EQ(fvMesh.boundaries()[5].nFaces(), 1836);
  EXPECT_EQ(fvMesh.boundaries()[5].startFace(), 1454);
}

TEST(ReadingOpenFoamMeshTest, constructingElementNeighborsWorks) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // *** Verify neighbors for the given finite volume elements ***
  EXPECT_EQ(fvMesh.elements()[0].nNeighbors(), 1);
  EXPECT_EQ(fvMesh.elements()[0].iNeighbors()[0], 22);

  EXPECT_EQ(fvMesh.elements()[1].nNeighbors(), 1);
  EXPECT_EQ(fvMesh.elements()[1].iNeighbors()[0], 68);

  EXPECT_EQ(fvMesh.elements()[99].nNeighbors(), 3);
  EXPECT_EQ(fvMesh.elements()[99].iNeighbors()[0], 19);
  EXPECT_EQ(fvMesh.elements()[99].iNeighbors()[1], 100);
  EXPECT_EQ(fvMesh.elements()[99].iNeighbors()[2], 326);

  EXPECT_EQ(fvMesh.elements()[100].nNeighbors(), 2);
  EXPECT_EQ(fvMesh.elements()[100].iNeighbors()[0], 99);
  EXPECT_EQ(fvMesh.elements()[100].iNeighbors()[1], 213);

  // Last two elements
  EXPECT_EQ(fvMesh.elements()[916].nNeighbors(), 3);
  EXPECT_EQ(fvMesh.elements()[916].iNeighbors()[0], 912);
  EXPECT_EQ(fvMesh.elements()[916].iNeighbors()[1], 914);
  EXPECT_EQ(fvMesh.elements()[916].iNeighbors()[2], 917);

  EXPECT_EQ(fvMesh.elements()[917].nNeighbors(), 3);
  EXPECT_EQ(fvMesh.elements()[917].iNeighbors()[0], 802);
  EXPECT_EQ(fvMesh.elements()[917].iNeighbors()[1], 913);
  EXPECT_EQ(fvMesh.elements()[917].iNeighbors()[2], 916);
}

TEST(ReadingOpenFoamMeshTest, constructingElementFacesWorks) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // *** Verify face indices for the given finite volume elements ***
  EXPECT_EQ(fvMesh.elements()[0].iFaces().size(), 5);
  EXPECT_EQ(fvMesh.elements()[0].iFaces()[0], 0);
  EXPECT_EQ(fvMesh.elements()[0].iFaces()[1], 1300);
  EXPECT_EQ(fvMesh.elements()[0].iFaces()[2], 1400);
  EXPECT_EQ(fvMesh.elements()[0].iFaces()[3], 1454);
  EXPECT_EQ(fvMesh.elements()[0].iFaces()[4], 1455);

  EXPECT_EQ(fvMesh.elements()[1].iFaces().size(), 5);
  EXPECT_EQ(fvMesh.elements()[1].iFaces()[0], 1);
  EXPECT_EQ(fvMesh.elements()[1].iFaces()[1], 1301);
  EXPECT_EQ(fvMesh.elements()[1].iFaces()[2], 1408);
  EXPECT_EQ(fvMesh.elements()[1].iFaces()[3], 1456);
  EXPECT_EQ(fvMesh.elements()[1].iFaces()[4], 1457);

  EXPECT_EQ(fvMesh.elements()[99].iFaces().size(), 5);
  EXPECT_EQ(fvMesh.elements()[99].iFaces()[0], 32);
  EXPECT_EQ(fvMesh.elements()[99].iFaces()[1], 154);
  EXPECT_EQ(fvMesh.elements()[99].iFaces()[2], 155);
  EXPECT_EQ(fvMesh.elements()[99].iFaces()[3], 1652);
  EXPECT_EQ(fvMesh.elements()[99].iFaces()[4], 1653);

  EXPECT_EQ(fvMesh.elements()[100].iFaces().size(), 5);
  EXPECT_EQ(fvMesh.elements()[100].iFaces()[0], 154);
  EXPECT_EQ(fvMesh.elements()[100].iFaces()[1], 156);
  EXPECT_EQ(fvMesh.elements()[100].iFaces()[2], 1349);
  EXPECT_EQ(fvMesh.elements()[100].iFaces()[3], 1654);
  EXPECT_EQ(fvMesh.elements()[100].iFaces()[4], 1655);

  // Last two elements
  EXPECT_EQ(fvMesh.elements()[916].iFaces().size(), 5);
  EXPECT_EQ(fvMesh.elements()[916].iFaces()[0], 1294);
  EXPECT_EQ(fvMesh.elements()[916].iFaces()[1], 1298);
  EXPECT_EQ(fvMesh.elements()[916].iFaces()[2], 1299);
  EXPECT_EQ(fvMesh.elements()[916].iFaces()[3], 3286);
  EXPECT_EQ(fvMesh.elements()[916].iFaces()[4], 3287);

  EXPECT_EQ(fvMesh.elements()[917].iFaces().size(), 5);
  EXPECT_EQ(fvMesh.elements()[917].iFaces()[0], 1171);
  EXPECT_EQ(fvMesh.elements()[917].iFaces()[1], 1296);
  EXPECT_EQ(fvMesh.elements()[917].iFaces()[2], 1299);
  EXPECT_EQ(fvMesh.elements()[917].iFaces()[3], 3288);
  EXPECT_EQ(fvMesh.elements()[917].iFaces()[4], 3289);
}

TEST(ReadingOpenFoamMeshTest, constructingElementFaceSignsWorks) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // *** Verify face signs for the given finite volume elements ***
  EXPECT_EQ(fvMesh.elements()[0].faceSigns()[0], 1);
  EXPECT_EQ(fvMesh.elements()[0].faceSigns()[1], 1);
  EXPECT_EQ(fvMesh.elements()[0].faceSigns()[2], 1);
  EXPECT_EQ(fvMesh.elements()[0].faceSigns()[3], 1);
  EXPECT_EQ(fvMesh.elements()[0].faceSigns()[4], 1);

  EXPECT_EQ(fvMesh.elements()[1].faceSigns()[0], 1);
  EXPECT_EQ(fvMesh.elements()[1].faceSigns()[1], 1);
  EXPECT_EQ(fvMesh.elements()[1].faceSigns()[2], 1);
  EXPECT_EQ(fvMesh.elements()[1].faceSigns()[3], 1);
  EXPECT_EQ(fvMesh.elements()[1].faceSigns()[4], 1);

  EXPECT_EQ(fvMesh.elements()[99].faceSigns()[0], -1);
  EXPECT_EQ(fvMesh.elements()[99].faceSigns()[1], 1);
  EXPECT_EQ(fvMesh.elements()[99].faceSigns()[2], 1);
  EXPECT_EQ(fvMesh.elements()[99].faceSigns()[3], 1);
  EXPECT_EQ(fvMesh.elements()[99].faceSigns()[4], 1);

  EXPECT_EQ(fvMesh.elements()[101].faceSigns()[0], -1);
  EXPECT_EQ(fvMesh.elements()[101].faceSigns()[1], 1);
  EXPECT_EQ(fvMesh.elements()[101].faceSigns()[2], 1);
  EXPECT_EQ(fvMesh.elements()[101].faceSigns()[3], 1);
  EXPECT_EQ(fvMesh.elements()[101].faceSigns()[4], 1);

  // Last two elements
  EXPECT_EQ(fvMesh.elements()[916].faceSigns()[0], -1);
  EXPECT_EQ(fvMesh.elements()[916].faceSigns()[1], -1);
  EXPECT_EQ(fvMesh.elements()[916].faceSigns()[2], 1);
  EXPECT_EQ(fvMesh.elements()[916].faceSigns()[3], 1);
  EXPECT_EQ(fvMesh.elements()[916].faceSigns()[4], 1);

  EXPECT_EQ(fvMesh.elements()[917].faceSigns()[0], -1);
  EXPECT_EQ(fvMesh.elements()[917].faceSigns()[1], -1);
  EXPECT_EQ(fvMesh.elements()[917].faceSigns()[2], -1);
  EXPECT_EQ(fvMesh.elements()[917].faceSigns()[3], 1);
  EXPECT_EQ(fvMesh.elements()[917].faceSigns()[4], 1);
}

TEST(ReadingOpenFoamMeshTest, constructingElementBoundaryWorks) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  EXPECT_EQ(fvMesh.nBElements(), 1990);
  EXPECT_EQ(fvMesh.nBFaces(), 1990);
}

TEST(ReadingOpenFoamMeshTest, setupNodeConnectivitiesPart1Works) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  EXPECT_EQ(fvMesh.nodes()[0].iFaces().size(), 7);
  EXPECT_EQ(fvMesh.nodes()[0].iFaces()[0], 171);
  EXPECT_EQ(fvMesh.nodes()[0].iFaces()[1], 327);
  EXPECT_EQ(fvMesh.nodes()[0].iFaces()[2], 1354);
  EXPECT_EQ(fvMesh.nodes()[0].iFaces()[3], 1385);
  EXPECT_EQ(fvMesh.nodes()[0].iFaces()[4], 1676);
  EXPECT_EQ(fvMesh.nodes()[0].iFaces()[5], 1890);
  EXPECT_EQ(fvMesh.nodes()[0].iFaces()[6], 1892);

  EXPECT_EQ(fvMesh.nodes()[1].iFaces().size(), 7);
  EXPECT_EQ(fvMesh.nodes()[1].iFaces()[0], 329);
  EXPECT_EQ(fvMesh.nodes()[1].iFaces()[1], 426);
  EXPECT_EQ(fvMesh.nodes()[1].iFaces()[2], 1385);
  EXPECT_EQ(fvMesh.nodes()[1].iFaces()[3], 1399);
  EXPECT_EQ(fvMesh.nodes()[1].iFaces()[4], 1892);
  EXPECT_EQ(fvMesh.nodes()[1].iFaces()[5], 2040);
  EXPECT_EQ(fvMesh.nodes()[1].iFaces()[6], 2044);

  EXPECT_EQ(fvMesh.nodes()[499].iFaces().size(), 10);
  EXPECT_EQ(fvMesh.nodes()[499].iFaces()[0], 1098);
  EXPECT_EQ(fvMesh.nodes()[499].iFaces()[1], 1099);
  EXPECT_EQ(fvMesh.nodes()[499].iFaces()[2], 1100);
  EXPECT_EQ(fvMesh.nodes()[499].iFaces()[3], 1101);
  EXPECT_EQ(fvMesh.nodes()[499].iFaces()[4], 1103);
  EXPECT_EQ(fvMesh.nodes()[499].iFaces()[5], 2946);
  EXPECT_EQ(fvMesh.nodes()[499].iFaces()[6], 2948);
  EXPECT_EQ(fvMesh.nodes()[499].iFaces()[7], 2950);
  EXPECT_EQ(fvMesh.nodes()[499].iFaces()[8], 2952);
  EXPECT_EQ(fvMesh.nodes()[499].iFaces()[9], 2954);

  EXPECT_EQ(fvMesh.nodes()[500].iFaces().size(), 12);
  EXPECT_EQ(fvMesh.nodes()[500].iFaces()[0], 1104);
  EXPECT_EQ(fvMesh.nodes()[500].iFaces()[1], 1105);
  EXPECT_EQ(fvMesh.nodes()[500].iFaces()[2], 1108);
  EXPECT_EQ(fvMesh.nodes()[500].iFaces()[3], 1109);
  EXPECT_EQ(fvMesh.nodes()[500].iFaces()[4], 1132);
  EXPECT_EQ(fvMesh.nodes()[500].iFaces()[5], 1248);
  EXPECT_EQ(fvMesh.nodes()[500].iFaces()[6], 2956);
  EXPECT_EQ(fvMesh.nodes()[500].iFaces()[7], 2960);
  EXPECT_EQ(fvMesh.nodes()[500].iFaces()[8], 2962);
  EXPECT_EQ(fvMesh.nodes()[500].iFaces()[9], 3000);
  EXPECT_EQ(fvMesh.nodes()[500].iFaces()[10], 3192);
  EXPECT_EQ(fvMesh.nodes()[500].iFaces()[11], 3194);

  // Last two nodes
  EXPECT_EQ(fvMesh.nodes()[1072].iFaces().size(), 12);
  EXPECT_EQ(fvMesh.nodes()[1072].iFaces()[0], 1290);
  EXPECT_EQ(fvMesh.nodes()[1072].iFaces()[1], 1291);
  EXPECT_EQ(fvMesh.nodes()[1072].iFaces()[2], 1292);
  EXPECT_EQ(fvMesh.nodes()[1072].iFaces()[3], 1293);
  EXPECT_EQ(fvMesh.nodes()[1072].iFaces()[4], 1294);
  EXPECT_EQ(fvMesh.nodes()[1072].iFaces()[5], 1298);
  EXPECT_EQ(fvMesh.nodes()[1072].iFaces()[6], 3273);
  EXPECT_EQ(fvMesh.nodes()[1072].iFaces()[7], 3275);
  EXPECT_EQ(fvMesh.nodes()[1072].iFaces()[8], 3277);
  EXPECT_EQ(fvMesh.nodes()[1072].iFaces()[9], 3279);
  EXPECT_EQ(fvMesh.nodes()[1072].iFaces()[10], 3283);
  EXPECT_EQ(fvMesh.nodes()[1072].iFaces()[11], 3287);

  EXPECT_EQ(fvMesh.nodes()[1073].iFaces().size(), 10);
  EXPECT_EQ(fvMesh.nodes()[1073].iFaces()[0], 1295);
  EXPECT_EQ(fvMesh.nodes()[1073].iFaces()[1], 1296);
  EXPECT_EQ(fvMesh.nodes()[1073].iFaces()[2], 1297);
  EXPECT_EQ(fvMesh.nodes()[1073].iFaces()[3], 1298);
  EXPECT_EQ(fvMesh.nodes()[1073].iFaces()[4], 1299);
  EXPECT_EQ(fvMesh.nodes()[1073].iFaces()[5], 3281);
  EXPECT_EQ(fvMesh.nodes()[1073].iFaces()[6], 3283);
  EXPECT_EQ(fvMesh.nodes()[1073].iFaces()[7], 3285);
  EXPECT_EQ(fvMesh.nodes()[1073].iFaces()[8], 3287);
  EXPECT_EQ(fvMesh.nodes()[1073].iFaces()[9], 3289);
}

TEST(ReadingOpenFoamMeshTest, setupNodeConnectivitiesPart2Works) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // *** Verify the node indices of some finite volume elements ***
  EXPECT_EQ(fvMesh.elements()[0].iNodes().size(), 6);
  EXPECT_EQ(fvMesh.elements()[0].iNodes()[0], 36);
  EXPECT_EQ(fvMesh.elements()[0].iNodes()[1], 573);
  EXPECT_EQ(fvMesh.elements()[0].iNodes()[2], 589);
  EXPECT_EQ(fvMesh.elements()[0].iNodes()[3], 52);
  EXPECT_EQ(fvMesh.elements()[0].iNodes()[4], 37);
  EXPECT_EQ(fvMesh.elements()[0].iNodes()[5], 574);

  EXPECT_EQ(fvMesh.elements()[1].iNodes().size(), 6);
  EXPECT_EQ(fvMesh.elements()[1].iNodes()[0], 41);
  EXPECT_EQ(fvMesh.elements()[1].iNodes()[1], 578);
  EXPECT_EQ(fvMesh.elements()[1].iNodes()[2], 634);
  EXPECT_EQ(fvMesh.elements()[1].iNodes()[3], 97);
  EXPECT_EQ(fvMesh.elements()[1].iNodes()[4], 42);
  EXPECT_EQ(fvMesh.elements()[1].iNodes()[5], 579);

  EXPECT_EQ(fvMesh.elements()[449].iNodes().size(), 6);
  EXPECT_EQ(fvMesh.elements()[449].iNodes()[0], 214);
  EXPECT_EQ(fvMesh.elements()[449].iNodes()[1], 751);
  EXPECT_EQ(fvMesh.elements()[449].iNodes()[2], 799);
  EXPECT_EQ(fvMesh.elements()[449].iNodes()[3], 262);
  EXPECT_EQ(fvMesh.elements()[449].iNodes()[4], 402);
  EXPECT_EQ(fvMesh.elements()[449].iNodes()[5], 939);

  EXPECT_EQ(fvMesh.elements()[450].iNodes().size(), 6);
  EXPECT_EQ(fvMesh.elements()[450].iNodes()[0], 304);
  EXPECT_EQ(fvMesh.elements()[450].iNodes()[1], 341);
  EXPECT_EQ(fvMesh.elements()[450].iNodes()[2], 878);
  EXPECT_EQ(fvMesh.elements()[450].iNodes()[3], 841);
  EXPECT_EQ(fvMesh.elements()[450].iNodes()[4], 404);
  EXPECT_EQ(fvMesh.elements()[450].iNodes()[5], 941);

  // Last two elements
  EXPECT_EQ(fvMesh.elements()[916].iNodes().size(), 6);
  EXPECT_EQ(fvMesh.elements()[916].iNodes()[0], 408);
  EXPECT_EQ(fvMesh.elements()[916].iNodes()[1], 535);
  EXPECT_EQ(fvMesh.elements()[916].iNodes()[2], 1072);
  EXPECT_EQ(fvMesh.elements()[916].iNodes()[3], 945);
  EXPECT_EQ(fvMesh.elements()[916].iNodes()[4], 536);
  EXPECT_EQ(fvMesh.elements()[916].iNodes()[5], 1073);

  EXPECT_EQ(fvMesh.elements()[917].iNodes().size(), 6);
  EXPECT_EQ(fvMesh.elements()[917].iNodes()[0], 475);
  EXPECT_EQ(fvMesh.elements()[917].iNodes()[1], 408);
  EXPECT_EQ(fvMesh.elements()[917].iNodes()[2], 945);
  EXPECT_EQ(fvMesh.elements()[917].iNodes()[3], 1012);
  EXPECT_EQ(fvMesh.elements()[917].iNodes()[4], 1073);
  EXPECT_EQ(fvMesh.elements()[917].iNodes()[5], 536);
}

TEST(ReadingOpenFoamMeshTest, setupNodeConnectivitiesPart3Works) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // *** Verify the element indices of some nodes ***
  EXPECT_EQ(fvMesh.nodes()[0].iElements().size(), 3);
  EXPECT_EQ(fvMesh.nodes()[0].iElements()[0], 111);
  EXPECT_EQ(fvMesh.nodes()[0].iElements()[1], 218);
  EXPECT_EQ(fvMesh.nodes()[0].iElements()[2], 219);

  EXPECT_EQ(fvMesh.nodes()[1].iElements().size(), 3);
  EXPECT_EQ(fvMesh.nodes()[1].iElements()[0], 219);
  EXPECT_EQ(fvMesh.nodes()[1].iElements()[1], 293);
  EXPECT_EQ(fvMesh.nodes()[1].iElements()[2], 295);

  EXPECT_EQ(fvMesh.nodes()[499].iElements().size(), 5);
  EXPECT_EQ(fvMesh.nodes()[499].iElements()[0], 746);
  EXPECT_EQ(fvMesh.nodes()[499].iElements()[1], 747);
  EXPECT_EQ(fvMesh.nodes()[499].iElements()[2], 748);
  EXPECT_EQ(fvMesh.nodes()[499].iElements()[3], 749);
  EXPECT_EQ(fvMesh.nodes()[499].iElements()[4], 750);

  EXPECT_EQ(fvMesh.nodes()[500].iElements().size(), 6);
  EXPECT_EQ(fvMesh.nodes()[500].iElements()[0], 751);
  EXPECT_EQ(fvMesh.nodes()[500].iElements()[1], 753);
  EXPECT_EQ(fvMesh.nodes()[500].iElements()[2], 754);
  EXPECT_EQ(fvMesh.nodes()[500].iElements()[3], 773);
  EXPECT_EQ(fvMesh.nodes()[500].iElements()[4], 869);
  EXPECT_EQ(fvMesh.nodes()[500].iElements()[5], 870);

  // Last two elements
  EXPECT_EQ(fvMesh.nodes()[1072].iElements().size(), 6);
  EXPECT_EQ(fvMesh.nodes()[1072].iElements()[0], 909);
  EXPECT_EQ(fvMesh.nodes()[1072].iElements()[1], 910);
  EXPECT_EQ(fvMesh.nodes()[1072].iElements()[2], 911);
  EXPECT_EQ(fvMesh.nodes()[1072].iElements()[3], 912);
  EXPECT_EQ(fvMesh.nodes()[1072].iElements()[4], 914);
  EXPECT_EQ(fvMesh.nodes()[1072].iElements()[5], 916);

  EXPECT_EQ(fvMesh.nodes()[1073].iElements().size(), 5);
  EXPECT_EQ(fvMesh.nodes()[1073].iElements()[0], 913);
  EXPECT_EQ(fvMesh.nodes()[1073].iElements()[1], 914);
  EXPECT_EQ(fvMesh.nodes()[1073].iElements()[2], 915);
  EXPECT_EQ(fvMesh.nodes()[1073].iElements()[3], 916);
  EXPECT_EQ(fvMesh.nodes()[1073].iElements()[4], 917);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
