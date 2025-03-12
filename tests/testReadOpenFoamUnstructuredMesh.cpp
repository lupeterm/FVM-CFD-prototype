// #include <gtest/gtest.h>

#include "Mesh.hpp"
#include "readMesh.hpp"
#include "testUtility.hpp"
// #include <array>
// #include <cstddef>
// #include <string>

// ****** Tests ******
TEST(ReadingOpenFoamMeshTest, ReadingPointsWorksForUnstructuredMesh) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  const std::array<double, 3> expected_node0_centroid = {32.0, 16.0,
                                                         0.9377383239};
  const std::array<double, 3> expected_node1_centroid = {
      33.9429245, 16.11834526, 0.9377383239};
  const std::array<double, 3> expected_node2_centroid = {
      35.84160614, 16.46798134, 0.9377383239};
  const std::array<double, 3> expected_node1071_centroid = {
      47.07066231, 11.31027148, -0.9377383239};
  const std::array<double, 3> expected_node1072_centroid = {
      54.24871481, 14.34322867, -0.9377383239};
  const std::array<double, 3> expected_node1073_centroid = {
      54.15826673, 15.64273318, -0.9377383239};

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the number of nodes
  EXPECT_EQ(fvMesh.nNodes(), 1074);

  // Verify the first 3 nodes
  EXPECT_TRUE(
      VectorMatch(fvMesh.nodes()[0].centroid(), expected_node0_centroid, 3));
  EXPECT_TRUE(
      VectorMatch(fvMesh.nodes()[1].centroid(), expected_node1_centroid, 3));
  EXPECT_TRUE(
      VectorMatch(fvMesh.nodes()[2].centroid(), expected_node2_centroid, 3));

  // Verify the last 3 nodes
  EXPECT_TRUE(VectorMatch(fvMesh.nodes()[1071].centroid(),
                          expected_node1071_centroid, 3));
  EXPECT_TRUE(VectorMatch(fvMesh.nodes()[1072].centroid(),
                          expected_node1072_centroid, 3));
  EXPECT_TRUE(VectorMatch(fvMesh.nodes()[1073].centroid(),
                          expected_node1073_centroid, 3));
}

TEST(ReadingOpenFoamMeshTest, ReadingFacesWorksForUnstructuredMesh) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  const std::array<std::size_t, 4> expected_face0_iNodes = {36, 573, 589, 52};
  const std::array<std::size_t, 4> expected_face1_iNodes = {41, 578, 634, 97};
  const std::array<std::size_t, 4> expected_face2_iNodes = {44, 81, 618, 581};
  const std::array<std::size_t, 3> expected_face3287_iNodes = {1072, 945, 1073};
  const std::array<std::size_t, 3> expected_face3288_iNodes = {536, 475, 408};
  const std::array<std::size_t, 3> expected_face3289_iNodes = {1073, 945, 1012};

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the number of faces
  EXPECT_EQ(fvMesh.nFaces(), 3290);

  // Verify the 1st face
  EXPECT_EQ(fvMesh.faces()[0].nNodes(), 4);
  EXPECT_TRUE(
      VectorMatch(fvMesh.faces()[0].iNodes(), expected_face0_iNodes, 4));

  // Verify the 2nd face
  EXPECT_EQ(fvMesh.faces()[1].nNodes(), 4);
  EXPECT_TRUE(
      VectorMatch(fvMesh.faces()[1].iNodes(), expected_face1_iNodes, 4));

  // Verify the 3rd face
  EXPECT_EQ(fvMesh.faces()[2].nNodes(), 4);
  EXPECT_TRUE(
      VectorMatch(fvMesh.faces()[2].iNodes(), expected_face2_iNodes, 4));

  // Verify the third from the last face
  EXPECT_EQ(fvMesh.faces()[3287].nNodes(), 3);
  EXPECT_TRUE(
      VectorMatch(fvMesh.faces()[3287].iNodes(), expected_face3287_iNodes, 3));

  // Verify the third from the last face
  EXPECT_EQ(fvMesh.faces()[3288].nNodes(), 3);
  EXPECT_TRUE(
      VectorMatch(fvMesh.faces()[3288].iNodes(), expected_face3288_iNodes, 3));

  // Verify the third from the last face
  EXPECT_EQ(fvMesh.faces()[3289].nNodes(), 3);
  EXPECT_TRUE(
      VectorMatch(fvMesh.faces()[3289].iNodes(), expected_face3289_iNodes, 3));
}

TEST(ReadingOpenFoamMeshTest, ReadingOwnersWorksForUnstructuredMesh) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  EXPECT_EQ(fvMesh.nOwners(), 3290);
  EXPECT_EQ(fvMesh.nElements(), 918);

  // Verify the first 10 entries in the owner file (interior faces)
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

  // Verify the last 10 entries in the owner file (boundary faces)
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

TEST(ReadingOpenFoamMeshTest, ReadingNeighborsWorksForUnstructuredMesh) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  EXPECT_EQ(fvMesh.nInteriorFaces(), 1300);

  // Verify the first 10 entries in the neighbor file (interior faces)
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

  // Verify the last 10 entries in the neighbor file (interior faces)
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

  // Verify the boundary faces have -1 as the neighbor index
  // The first 10 boundary faces
  EXPECT_EQ(fvMesh.faces()[1300].iNeighbor(), -1);
  EXPECT_EQ(fvMesh.faces()[1301].iNeighbor(), -1);
  EXPECT_EQ(fvMesh.faces()[1302].iNeighbor(), -1);

  // The last 3 boundary faces
  EXPECT_EQ(fvMesh.faces()[3287].iNeighbor(), -1);
  EXPECT_EQ(fvMesh.faces()[3288].iNeighbor(), -1);
  EXPECT_EQ(fvMesh.faces()[3289].iNeighbor(), -1);
}

TEST(ReadingOpenFoamMeshTest, ReadingBoundariesWorksForUnstructuredMesh) {
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

TEST(ConstructingElementsTest,
     ConstructingElementNeighborsWorksForUnstructuredMesh) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  const std::array<std::size_t, 3> expected_element99_iNeighbors = {19, 100,
                                                                    326};
  const std::array<std::size_t, 3> expected_element100_iNeighbors = {99, 213};
  const std::array<std::size_t, 3> expected_element916_iNeighbors = {912, 914,
                                                                     917};
  const std::array<std::size_t, 3> expected_element917_iNeighbors = {802, 913,
                                                                     916};

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // *** Verify neighbors for the given finite volume elements ***
  EXPECT_EQ(fvMesh.elements()[0].nNeighbors(), 1);
  EXPECT_EQ(fvMesh.elements()[0].iNeighbors()[0], 22);

  EXPECT_EQ(fvMesh.elements()[1].nNeighbors(), 1);
  EXPECT_EQ(fvMesh.elements()[1].iNeighbors()[0], 68);

  EXPECT_EQ(fvMesh.elements()[99].nNeighbors(), 3);
  EXPECT_TRUE(VectorMatch(fvMesh.elements()[99].iNeighbors(),
                          expected_element99_iNeighbors, 3));

  EXPECT_EQ(fvMesh.elements()[100].nNeighbors(), 2);
  EXPECT_TRUE(VectorMatch(fvMesh.elements()[100].iNeighbors(),
                          expected_element100_iNeighbors, 2));
  // Last two elements
  EXPECT_EQ(fvMesh.elements()[916].nNeighbors(), 3);
  EXPECT_TRUE(VectorMatch(fvMesh.elements()[916].iNeighbors(),
                          expected_element916_iNeighbors, 3));

  EXPECT_EQ(fvMesh.elements()[917].nNeighbors(), 3);
  EXPECT_TRUE(VectorMatch(fvMesh.elements()[917].iNeighbors(),
                          expected_element917_iNeighbors, 3));
}

TEST(ConstructingElementsTest,
     ConstructingElementFacesWorksForUnstructuredMesh) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  const std::array<std::size_t, 5> expected_element0_iFaces = {0, 1300, 1400,
                                                               1454, 1455};
  const std::array<std::size_t, 5> expected_element1_iFaces = {1, 1301, 1408,
                                                               1456, 1457};
  const std::array<std::size_t, 5> expected_element99_iFaces = {32, 154, 155,
                                                                1652, 1653};
  const std::array<std::size_t, 5> expected_element100_iFaces = {154, 156, 1349,
                                                                 1654, 1655};
  const std::array<std::size_t, 5> expected_element916_iFaces = {
      1294, 1298, 1299, 3286, 3287};
  const std::array<std::size_t, 5> expected_element917_iFaces = {
      1171, 1296, 1299, 3288, 3289};

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // *** Verify face indices for the given finite volume elements ***
  EXPECT_EQ(fvMesh.elements()[0].iFaces().size(), 5);
  EXPECT_TRUE(
      VectorMatch(fvMesh.elements()[0].iFaces(), expected_element0_iFaces, 5));

  EXPECT_EQ(fvMesh.elements()[1].iFaces().size(), 5);
  EXPECT_TRUE(
      VectorMatch(fvMesh.elements()[1].iFaces(), expected_element1_iFaces, 5));

  EXPECT_EQ(fvMesh.elements()[99].iFaces().size(), 5);
  EXPECT_TRUE(VectorMatch(fvMesh.elements()[99].iFaces(),
                          expected_element99_iFaces, 5));

  EXPECT_EQ(fvMesh.elements()[100].iFaces().size(), 5);
  EXPECT_TRUE(VectorMatch(fvMesh.elements()[100].iFaces(),
                          expected_element100_iFaces, 5));

  // Last two elements
  EXPECT_EQ(fvMesh.elements()[916].iFaces().size(), 5);
  EXPECT_TRUE(VectorMatch(fvMesh.elements()[916].iFaces(),
                          expected_element916_iFaces, 5));

  EXPECT_EQ(fvMesh.elements()[917].iFaces().size(), 5);
  EXPECT_TRUE(VectorMatch(fvMesh.elements()[917].iFaces(),
                          expected_element917_iFaces, 5));
}

TEST(ConstructingElementsTest,
     ConstructingElementFaceSignsWorksForUnstructuredMesh) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  const std::array<int, 5> expected_element0_faceSigns = {1, 1, 1, 1, 1};
  const std::array<int, 5> expected_element1_faceSigns = {1, 1, 1, 1, 1};
  const std::array<int, 5> expected_element99_faceSigns = {-1, 1, 1, 1, 1};
  const std::array<int, 5> expected_element101_faceSigns = {-1, 1, 1, 1, 1};
  const std::array<int, 5> expected_element916_faceSigns = {-1, -1, 1, 1, 1};
  const std::array<int, 5> expected_element917_faceSigns = {-1, -1, -1, 1, 1};

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // *** Verify face signs for the given finite volume elements ***
  EXPECT_TRUE(VectorMatch(fvMesh.elements()[0].faceSigns(),
                          expected_element0_faceSigns, 5));
  EXPECT_TRUE(VectorMatch(fvMesh.elements()[1].faceSigns(),
                          expected_element1_faceSigns, 5));
  EXPECT_TRUE(VectorMatch(fvMesh.elements()[99].faceSigns(),
                          expected_element99_faceSigns, 5));
  EXPECT_TRUE(VectorMatch(fvMesh.elements()[101].faceSigns(),
                          expected_element101_faceSigns, 5));

  // Last two elements
  EXPECT_TRUE(VectorMatch(fvMesh.elements()[916].faceSigns(),
                          expected_element916_faceSigns, 5));

  EXPECT_TRUE(VectorMatch(fvMesh.elements()[917].faceSigns(),
                          expected_element917_faceSigns, 5));
}

TEST(ConstructingElementsTest,
     ConstructingElementBoundaryWorksForUnstructuredMesh) {
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

TEST(SettingUpNodeConnectivitiesTest,
     ConnectingFacesToNodeWorksForUnstructuredMesh) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  const std::array<std::size_t, 7> expected_node0_iFaces = {
      171, 327, 1354, 1385, 1676, 1890, 1892};
  const std::array<std::size_t, 7> expected_node1_iFaces = {
      329, 426, 1385, 1399, 1892, 2040, 2044};
  const std::array<std::size_t, 10> expected_node499_iFaces = {
      1098, 1099, 1100, 1101, 1103, 2946, 2948, 2950, 2952, 2954};
  const std::array<std::size_t, 12> expected_node500_iFaces = {
      1104, 1105, 1108, 1109, 1132, 1248, 2956, 2960, 2962, 3000, 3192, 3194};
  const std::array<std::size_t, 12> expected_node1072_iFaces = {
      1290, 1291, 1292, 1293, 1294, 1298, 3273, 3275, 3277, 3279, 3283, 3287};
  const std::array<std::size_t, 10> expected_node1073_iFaces = {
      1295, 1296, 1297, 1298, 1299, 3281, 3283, 3285, 3287, 3289};

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  EXPECT_EQ(fvMesh.nodes()[0].iFaces().size(), 7);
  EXPECT_TRUE(
      VectorMatch(fvMesh.nodes()[0].iFaces(), expected_node0_iFaces, 7));

  EXPECT_EQ(fvMesh.nodes()[1].iFaces().size(), 7);
  EXPECT_TRUE(
      VectorMatch(fvMesh.nodes()[1].iFaces(), expected_node1_iFaces, 7));

  EXPECT_EQ(fvMesh.nodes()[499].iFaces().size(), 10);
  EXPECT_TRUE(
      VectorMatch(fvMesh.nodes()[499].iFaces(), expected_node499_iFaces, 10));

  EXPECT_EQ(fvMesh.nodes()[500].iFaces().size(), 12);
  EXPECT_TRUE(
      VectorMatch(fvMesh.nodes()[500].iFaces(), expected_node500_iFaces, 12));

  // Last two nodes
  EXPECT_EQ(fvMesh.nodes()[1072].iFaces().size(), 12);
  EXPECT_TRUE(
      VectorMatch(fvMesh.nodes()[1072].iFaces(), expected_node1072_iFaces, 12));

  EXPECT_EQ(fvMesh.nodes()[1073].iFaces().size(), 10);
  EXPECT_TRUE(
      VectorMatch(fvMesh.nodes()[1073].iFaces(), expected_node1073_iFaces, 10));
}

TEST(SettingUpNodeConnectivitiesTest,
     ConnectingNodesToElementWorksForUnstructuredMesh) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  const std::array<std::size_t, 6> expected_element0_iNodes = {36, 573, 589,
                                                               52, 37,  574};
  const std::array<std::size_t, 6> expected_element1_iNodes = {41, 578, 634,
                                                               97, 42,  579};
  const std::array<std::size_t, 6> expected_element449_iNodes = {214, 751, 799,
                                                                 262, 402, 939};
  const std::array<std::size_t, 6> expected_element450_iNodes = {304, 341, 878,
                                                                 841, 404, 941};
  const std::array<std::size_t, 6> expected_element916_iNodes = {
      408, 535, 1072, 945, 536, 1073};

  const std::array<std::size_t, 6> expected_element917_iNodes = {
      475, 408, 945, 1012, 1073, 536};
  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // *** Verify the node indices of some finite volume elements ***
  EXPECT_EQ(fvMesh.elements()[0].iNodes().size(), 6);
  EXPECT_TRUE(
      VectorMatch(fvMesh.elements()[0].iNodes(), expected_element0_iNodes, 6));

  EXPECT_EQ(fvMesh.elements()[1].iNodes().size(), 6);
  EXPECT_TRUE(
      VectorMatch(fvMesh.elements()[1].iNodes(), expected_element1_iNodes, 6));

  EXPECT_EQ(fvMesh.elements()[449].iNodes().size(), 6);
  EXPECT_TRUE(VectorMatch(fvMesh.elements()[449].iNodes(),
                          expected_element449_iNodes, 6));

  EXPECT_EQ(fvMesh.elements()[450].iNodes().size(), 6);
  EXPECT_TRUE(VectorMatch(fvMesh.elements()[450].iNodes(),
                          expected_element450_iNodes, 6));

  // Last two elements
  EXPECT_EQ(fvMesh.elements()[916].iNodes().size(), 6);
  EXPECT_TRUE(VectorMatch(fvMesh.elements()[916].iNodes(),
                          expected_element916_iNodes, 6));

  EXPECT_EQ(fvMesh.elements()[917].iNodes().size(), 6);
  EXPECT_TRUE(VectorMatch(fvMesh.elements()[917].iNodes(),
                          expected_element917_iNodes, 6));
}

TEST(SettingUpNodeConnectivitiesTest,
     ConnectingElementsToNodetWorksForUnstructuredMesh) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/elbow");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  const std::array<std::size_t, 3> expected_node0_iElements = {111, 218, 219};
  const std::array<std::size_t, 3> expected_node1_iElements = {219, 293, 295};
  const std::array<std::size_t, 5> expected_node499_iElements = {746, 747, 748,
                                                                 749, 750};
  const std::array<std::size_t, 6> expected_node500_iElements = {751, 753, 754,
                                                                 773, 869, 870};
  const std::array<std::size_t, 6> expected_node1072_iElements = {
      909, 910, 911, 912, 914, 916};
  const std::array<std::size_t, 5> expected_node1073_iElements = {913, 914, 915,
                                                                  916, 917};
  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // *** Verify the element indices of some nodes ***
  EXPECT_EQ(fvMesh.nodes()[0].iElements().size(), 3);
  EXPECT_TRUE(
      VectorMatch(fvMesh.nodes()[0].iElements(), expected_node0_iElements, 3));

  EXPECT_EQ(fvMesh.nodes()[1].iElements().size(), 3);
  EXPECT_TRUE(
      VectorMatch(fvMesh.nodes()[1].iElements(), expected_node1_iElements, 3));

  EXPECT_EQ(fvMesh.nodes()[499].iElements().size(), 5);
  EXPECT_TRUE(VectorMatch(fvMesh.nodes()[499].iElements(),
                          expected_node499_iElements, 5));

  EXPECT_EQ(fvMesh.nodes()[500].iElements().size(), 6);
  EXPECT_TRUE(VectorMatch(fvMesh.nodes()[500].iElements(),
                          expected_node500_iElements, 6));

  // Last two elements
  EXPECT_EQ(fvMesh.nodes()[1072].iElements().size(), 6);
  EXPECT_TRUE(VectorMatch(fvMesh.nodes()[1072].iElements(),
                          expected_node1072_iElements, 6));

  EXPECT_EQ(fvMesh.nodes()[1073].iElements().size(), 5);
  EXPECT_TRUE(VectorMatch(fvMesh.nodes()[1073].iElements(),
                          expected_node1073_iElements, 5));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
