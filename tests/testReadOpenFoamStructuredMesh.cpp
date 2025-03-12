#include <gtest/gtest.h>

#include "Mesh.hpp"
#include "readMesh.hpp"
#include "testUtility.hpp"
#include <array>
// #include <cstddef>
#include <string>

// ****** Tests ******
TEST(ReadingOpenFoamMeshTest, ReadingPointsWorksForStructuredMesh) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/Mycavity");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  const std::array<double, 3> expected_node0_centroid = {0.0, 0.0, 0.0};
  const std::array<double, 3> expected_node1_centroid = {0.00500000000000000,
                                                         0.0, 0.0};
  const std::array<double, 3> expected_node2_centroid = {0.0100000000000000,
                                                         0.0, 0.0};
  const std::array<double, 3> expected_node879_centroid = {0.09, 0.1, 0.01};
  const std::array<double, 3> expected_node880_centroid = {0.095, 0.1, 0.01};
  const std::array<double, 3> expected_node881_centroid = {0.1, 0.1, 0.01};

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the number of nodes
  EXPECT_EQ(fvMesh.nNodes(), 882);

  // Verify the first 3 nodes
  EXPECT_TRUE(
      VectorMatch(fvMesh.nodes()[0].centroid(), expected_node0_centroid, 3));
  EXPECT_TRUE(
      VectorMatch(fvMesh.nodes()[1].centroid(), expected_node1_centroid, 3));
  EXPECT_TRUE(
      VectorMatch(fvMesh.nodes()[2].centroid(), expected_node2_centroid, 3));

  // Verify the last 3 nodes
  EXPECT_TRUE(VectorMatch(fvMesh.nodes()[879].centroid(),
                          expected_node879_centroid, 3));
  EXPECT_TRUE(VectorMatch(fvMesh.nodes()[880].centroid(),
                          expected_node880_centroid, 3));
  EXPECT_TRUE(VectorMatch(fvMesh.nodes()[881].centroid(),
                          expected_node881_centroid, 3));
}

TEST(ReadingOpenFoamMeshTest, ReadingFacesWorksForStructuredMesh) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/Mycavity");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  const std::array<std::size_t, 4> expected_face0_iNodes = {1, 22, 463, 442};
  const std::array<std::size_t, 4> expected_face1_iNodes = {21, 462, 463, 22};
  const std::array<std::size_t, 4> expected_face2_iNodes = {2, 23, 464, 443};
  const std::array<std::size_t, 4> expected_face1637_iNodes = {817, 818, 839,
                                                               838};
  const std::array<std::size_t, 4> expected_face1638_iNodes = {838, 839, 860,
                                                               859};
  const std::array<std::size_t, 4> expected_face1639_iNodes = {859, 860, 881,
                                                               880};

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the number of faces
  EXPECT_EQ(fvMesh.nFaces(), 1640);

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
  EXPECT_EQ(fvMesh.faces()[1637].nNodes(), 4);
  EXPECT_TRUE(
      VectorMatch(fvMesh.faces()[1637].iNodes(), expected_face1637_iNodes, 4));

  // Verify the third from the last face
  EXPECT_EQ(fvMesh.faces()[1638].nNodes(), 4);
  EXPECT_TRUE(
      VectorMatch(fvMesh.faces()[1638].iNodes(), expected_face1638_iNodes, 4));

  // Verify the third from the last face
  EXPECT_EQ(fvMesh.faces()[1639].nNodes(), 4);
  EXPECT_TRUE(
      VectorMatch(fvMesh.faces()[1639].iNodes(), expected_face1639_iNodes, 4));
}

TEST(ReadingOpenFoamMeshTest, ReadingOwnersWorksForStructuredMesh) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/Mycavity");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  EXPECT_EQ(fvMesh.nOwners(), 1640);
  EXPECT_EQ(fvMesh.nElements(), 400);

  // Verify the first 10 entries in the owner file (interior faces)
  EXPECT_EQ(fvMesh.faces()[0].iOwner(), 0);
  EXPECT_EQ(fvMesh.faces()[1].iOwner(), 0);
  EXPECT_EQ(fvMesh.faces()[2].iOwner(), 1);
  EXPECT_EQ(fvMesh.faces()[3].iOwner(), 1);
  EXPECT_EQ(fvMesh.faces()[4].iOwner(), 2);
  EXPECT_EQ(fvMesh.faces()[5].iOwner(), 2);
  EXPECT_EQ(fvMesh.faces()[6].iOwner(), 3);
  EXPECT_EQ(fvMesh.faces()[7].iOwner(), 3);
  EXPECT_EQ(fvMesh.faces()[8].iOwner(), 4);
  EXPECT_EQ(fvMesh.faces()[9].iOwner(), 4);

  // Verify the last 5 entries in the owner file (boundary faces)
  EXPECT_EQ(fvMesh.faces()[1635].iOwner(), 319);
  EXPECT_EQ(fvMesh.faces()[1636].iOwner(), 339);
  EXPECT_EQ(fvMesh.faces()[1637].iOwner(), 359);
  EXPECT_EQ(fvMesh.faces()[1638].iOwner(), 379);
  EXPECT_EQ(fvMesh.faces()[1639].iOwner(), 399);
}

TEST(ReadingOpenFoamMeshTest, ReadingNeighborsWorksForStructuredMesh) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/Mycavity");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  EXPECT_EQ(fvMesh.nInteriorFaces(), 760);

  // Verify the first 10 entries in the neighbor file (interior faces)
  EXPECT_EQ(fvMesh.faces()[0].iNeighbor(), 1);
  EXPECT_EQ(fvMesh.faces()[1].iNeighbor(), 20);
  EXPECT_EQ(fvMesh.faces()[2].iNeighbor(), 2);
  EXPECT_EQ(fvMesh.faces()[3].iNeighbor(), 21);
  EXPECT_EQ(fvMesh.faces()[4].iNeighbor(), 3);
  EXPECT_EQ(fvMesh.faces()[5].iNeighbor(), 22);
  EXPECT_EQ(fvMesh.faces()[6].iNeighbor(), 4);
  EXPECT_EQ(fvMesh.faces()[7].iNeighbor(), 23);
  EXPECT_EQ(fvMesh.faces()[8].iNeighbor(), 5);
  EXPECT_EQ(fvMesh.faces()[9].iNeighbor(), 24);

  // Verify the last 5 entries in the neighbor file (interior faces)
  EXPECT_EQ(fvMesh.faces()[755].iNeighbor(), 395);
  EXPECT_EQ(fvMesh.faces()[756].iNeighbor(), 396);
  EXPECT_EQ(fvMesh.faces()[757].iNeighbor(), 397);
  EXPECT_EQ(fvMesh.faces()[758].iNeighbor(), 398);
  EXPECT_EQ(fvMesh.faces()[759].iNeighbor(), 399);

  // Verify the boundary faces have -1 as the neighbor index
  // The first 10 boundary faces
  EXPECT_EQ(fvMesh.faces()[760].iNeighbor(), -1);
  EXPECT_EQ(fvMesh.faces()[761].iNeighbor(), -1);
  EXPECT_EQ(fvMesh.faces()[762].iNeighbor(), -1);

  // The last 3 boundary faces
  EXPECT_EQ(fvMesh.faces()[1637].iNeighbor(), -1);
  EXPECT_EQ(fvMesh.faces()[1638].iNeighbor(), -1);
  EXPECT_EQ(fvMesh.faces()[1639].iNeighbor(), -1);
}

TEST(ReadingOpenFoamMeshTest, ReadingBoundariesWorksForStructuredMesh) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/Mycavity");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  EXPECT_EQ(fvMesh.nBoundaries(), 3);

  // Verify the 1st boundary
  EXPECT_EQ(fvMesh.boundaries()[0].userName(), "movingWall");
  EXPECT_EQ(fvMesh.boundaries()[0].index(), 0);
  EXPECT_EQ(fvMesh.boundaries()[0].type(), "wall");
  EXPECT_EQ(fvMesh.boundaries()[0].nFaces(), 20);
  EXPECT_EQ(fvMesh.boundaries()[0].startFace(), 760);

  // Verify the 2nd boundary
  EXPECT_EQ(fvMesh.boundaries()[1].userName(), "fixedWalls");
  EXPECT_EQ(fvMesh.boundaries()[1].index(), 1);
  EXPECT_EQ(fvMesh.boundaries()[1].type(), "wall");
  EXPECT_EQ(fvMesh.boundaries()[1].nFaces(), 60);
  EXPECT_EQ(fvMesh.boundaries()[1].startFace(), 780);

  // Verify the 3rd boundary
  EXPECT_EQ(fvMesh.boundaries()[2].userName(), "frontAndBack");
  EXPECT_EQ(fvMesh.boundaries()[2].index(), 2);
  EXPECT_EQ(fvMesh.boundaries()[2].type(), "empty");
  EXPECT_EQ(fvMesh.boundaries()[2].nFaces(), 800);
  EXPECT_EQ(fvMesh.boundaries()[2].startFace(), 840);
}

TEST(ConstructingElementsTest,
     ConstructingElementNeighborsWorksForStructuredMesh) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/Mycavity");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  const std::array<std::size_t, 2> expected_element0_iNeighbors = {1, 20};
  const std::array<std::size_t, 3> expected_element1_iNeighbors = {0, 2, 21};
  const std::array<std::size_t, 3> expected_element199_iNeighbors = {179, 198,
                                                                     219};
  const std::array<std::size_t, 3> expected_element200_iNeighbors = {180, 201,
                                                                     220};
  const std::array<std::size_t, 3> expected_element398_iNeighbors = {378, 397,
                                                                     399};
  const std::array<std::size_t, 2> expected_element399_iNeighbors = {379, 398};

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // *** Verify neighbors for the given finite volume elements ***
  EXPECT_EQ(fvMesh.elements()[0].nNeighbors(), 2);
  EXPECT_TRUE(VectorMatch(fvMesh.elements()[0].iNeighbors(),
                          expected_element0_iNeighbors, 2));

  EXPECT_EQ(fvMesh.elements()[1].nNeighbors(), 3);
  EXPECT_TRUE(VectorMatch(fvMesh.elements()[1].iNeighbors(),
                          expected_element1_iNeighbors, 3));

  EXPECT_EQ(fvMesh.elements()[199].nNeighbors(), 3);
  EXPECT_TRUE(VectorMatch(fvMesh.elements()[199].iNeighbors(),
                          expected_element199_iNeighbors, 3));

  EXPECT_EQ(fvMesh.elements()[200].nNeighbors(), 3);
  EXPECT_TRUE(VectorMatch(fvMesh.elements()[200].iNeighbors(),
                          expected_element200_iNeighbors, 2));
  // Last two elements
  EXPECT_EQ(fvMesh.elements()[398].nNeighbors(), 3);
  EXPECT_TRUE(VectorMatch(fvMesh.elements()[398].iNeighbors(),
                          expected_element398_iNeighbors, 3));

  EXPECT_EQ(fvMesh.elements()[399].nNeighbors(), 2);
  EXPECT_TRUE(VectorMatch(fvMesh.elements()[399].iNeighbors(),
                          expected_element399_iNeighbors, 2));
}

// TEST(ConstructingElementsTest,
// ConstructingElementFacesWorksForStructuredMesh) {
//   // --- Arrange ---
//   std::string caseDirectory("../../cases/Mycavity");
//   readMesh meshReader;
//   Mesh fvMesh(caseDirectory);
//   const std::array<std::size_t, 5> expected_element0_iFaces = {0, 1300, 1400,
//                                                                1454, 1455};
//   const std::array<std::size_t, 5> expected_element1_iFaces = {1, 1301, 1408,
//                                                                1456, 1457};
//   const std::array<std::size_t, 5> expected_element99_iFaces = {32, 154, 155,
//                                                                 1652, 1653};
//   const std::array<std::size_t, 5> expected_element100_iFaces = {154, 156,
//   1349,
//                                                                  1654, 1655};
//   const std::array<std::size_t, 5> expected_element916_iFaces = {
//       1294, 1298, 1299, 3286, 1637};
//   const std::array<std::size_t, 5> expected_element917_iFaces = {
//       1171, 1296, 1299, 1638, 1639};

//   // -- -Act-- -
//   meshReader.readOpenFoamMesh(fvMesh);

//   // --- Assert ---
//   // *** Verify face indices for the given finite volume elements ***
//   EXPECT_EQ(fvMesh.elements()[0].iFaces().size(), 5);
//   EXPECT_TRUE(
//       VectorMatch(fvMesh.elements()[0].iFaces(), expected_element0_iFaces,
//       5));

//   EXPECT_EQ(fvMesh.elements()[1].iFaces().size(), 5);
//   EXPECT_TRUE(
//       VectorMatch(fvMesh.elements()[1].iFaces(), expected_element1_iFaces,
//       5));

//   EXPECT_EQ(fvMesh.elements()[99].iFaces().size(), 5);
//   EXPECT_TRUE(VectorMatch(fvMesh.elements()[99].iFaces(),
//                           expected_element99_iFaces, 5));

//   EXPECT_EQ(fvMesh.elements()[100].iFaces().size(), 5);
//   EXPECT_TRUE(VectorMatch(fvMesh.elements()[100].iFaces(),
//                           expected_element100_iFaces, 5));

//   // Last two elements
//   EXPECT_EQ(fvMesh.elements()[916].iFaces().size(), 5);
//   EXPECT_TRUE(VectorMatch(fvMesh.elements()[916].iFaces(),
//                           expected_element916_iFaces, 5));

//   EXPECT_EQ(fvMesh.elements()[917].iFaces().size(), 5);
//   EXPECT_TRUE(VectorMatch(fvMesh.elements()[917].iFaces(),
//                           expected_element917_iFaces, 5));
// }

// TEST(ConstructingElementsTest,
//      ConstructingElementFaceSignsWorksForStructuredMesh) {
//   // --- Arrange ---
//   std::string caseDirectory("../../cases/Mycavity");
//   readMesh meshReader;
//   Mesh fvMesh(caseDirectory);
//   const std::array<int, 5> expected_element0_faceSigns = {1, 1, 1, 1, 1};
//   const std::array<int, 5> expected_element1_faceSigns = {1, 1, 1, 1, 1};
//   const std::array<int, 5> expected_element99_faceSigns = {-1, 1, 1, 1, 1};
//   const std::array<int, 5> expected_element101_faceSigns = {-1, 1, 1, 1, 1};
//   const std::array<int, 5> expected_element916_faceSigns = {-1, -1, 1, 1, 1};
//   const std::array<int, 5> expected_element917_faceSigns = {-1, -1, -1, 1,
//   1};

//   // -- -Act-- -
//   meshReader.readOpenFoamMesh(fvMesh);

//   // --- Assert ---
//   // *** Verify face signs for the given finite volume elements ***
//   EXPECT_TRUE(VectorMatch(fvMesh.elements()[0].faceSigns(),
//                           expected_element0_faceSigns, 5));
//   EXPECT_TRUE(VectorMatch(fvMesh.elements()[1].faceSigns(),
//                           expected_element1_faceSigns, 5));
//   EXPECT_TRUE(VectorMatch(fvMesh.elements()[99].faceSigns(),
//                           expected_element99_faceSigns, 5));
//   EXPECT_TRUE(VectorMatch(fvMesh.elements()[101].faceSigns(),
//                           expected_element101_faceSigns, 5));

//   // Last two elements
//   EXPECT_TRUE(VectorMatch(fvMesh.elements()[916].faceSigns(),
//                           expected_element916_faceSigns, 5));

//   EXPECT_TRUE(VectorMatch(fvMesh.elements()[917].faceSigns(),
//                           expected_element917_faceSigns, 5));
// }

// TEST(ConstructingElementsTest,
//      ConstructingElementBoundaryWorksForStructuredMesh) {
//   // --- Arrange ---
//   std::string caseDirectory("../../cases/Mycavity");
//   readMesh meshReader;
//   Mesh fvMesh(caseDirectory);

//   // -- -Act-- -
//   meshReader.readOpenFoamMesh(fvMesh);

//   // --- Assert ---
//   EXPECT_EQ(fvMesh.nBElements(), 1990);
//   EXPECT_EQ(fvMesh.nBFaces(), 1990);
// }

// TEST(SettingUpNodeConnectivitiesTest,
//      ConnectingFacesToNodeWorksForStructuredMesh) {
//   // --- Arrange ---
//   std::string caseDirectory("../../cases/Mycavity");
//   readMesh meshReader;
//   Mesh fvMesh(caseDirectory);
//   const std::array<std::size_t, 7> expected_node0_iFaces = {
//       171, 327, 1354, 1385, 1676, 1890, 1892};
//   const std::array<std::size_t, 7> expected_node1_iFaces = {
//       329, 426, 1385, 1399, 1892, 2040, 2044};
//   const std::array<std::size_t, 10> expected_node499_iFaces = {
//       1098, 1099, 1100, 1101, 1103, 2946, 2948, 2950, 2952, 2954};
//   const std::array<std::size_t, 12> expected_node500_iFaces = {
//       1104, 1105, 1108, 1109, 1132, 1248, 2956, 2960, 2962, 3000, 3192,
//       3194};
//   const std::array<std::size_t, 12> expected_node880_iFaces = {
//       1290, 1291, 1292, 1293, 1294, 1298, 3273, 3275, 3277, 3279, 3283,
//       1637};
//   const std::array<std::size_t, 10> expected_node881_iFaces = {
//       1295, 1296, 1297, 1298, 1299, 3281, 3283, 3285, 1637, 1639};

//   // -- -Act-- -
//   meshReader.readOpenFoamMesh(fvMesh);

//   // --- Assert ---
//   EXPECT_EQ(fvMesh.nodes()[0].iFaces().size(), 7);
//   EXPECT_TRUE(
//       VectorMatch(fvMesh.nodes()[0].iFaces(), expected_node0_iFaces, 7));

//   EXPECT_EQ(fvMesh.nodes()[1].iFaces().size(), 7);
//   EXPECT_TRUE(
//       VectorMatch(fvMesh.nodes()[1].iFaces(), expected_node1_iFaces, 7));

//   EXPECT_EQ(fvMesh.nodes()[499].iFaces().size(), 10);
//   EXPECT_TRUE(
//       VectorMatch(fvMesh.nodes()[499].iFaces(), expected_node499_iFaces,
//       10));

//   EXPECT_EQ(fvMesh.nodes()[500].iFaces().size(), 12);
//   EXPECT_TRUE(
//       VectorMatch(fvMesh.nodes()[500].iFaces(), expected_node500_iFaces,
//       12));

//   // Last two nodes
//   EXPECT_EQ(fvMesh.nodes()[880].iFaces().size(), 12);
//   EXPECT_TRUE(
//       VectorMatch(fvMesh.nodes()[880].iFaces(), expected_node880_iFaces,
//       12));

//   EXPECT_EQ(fvMesh.nodes()[881].iFaces().size(), 10);
//   EXPECT_TRUE(
//       VectorMatch(fvMesh.nodes()[881].iFaces(), expected_node881_iFaces,
//       10));
// }

// TEST(SettingUpNodeConnectivitiesTest,
//      ConnectingNodesToElementWorksForStructuredMesh) {
//   // --- Arrange ---
//   std::string caseDirectory("../../cases/Mycavity");
//   readMesh meshReader;
//   Mesh fvMesh(caseDirectory);
//   const std::array<std::size_t, 6> expected_element0_iNodes = {36, 573, 589,
//                                                                52, 37,  574};
//   const std::array<std::size_t, 6> expected_element1_iNodes = {41, 578, 634,
//                                                                97, 42,  579};
//   const std::array<std::size_t, 6> expected_element449_iNodes = {214, 751,
//   799,
//                                                                  262, 402,
//                                                                  939};
//   const std::array<std::size_t, 6> expected_element450_iNodes = {304, 341,
//   878,
//                                                                  841, 404,
//                                                                  941};
//   const std::array<std::size_t, 6> expected_element916_iNodes = {
//       408, 535, 880, 945, 536, 881};

//   const std::array<std::size_t, 6> expected_element917_iNodes = {
//       475, 408, 945, 1012, 881, 536};
//   // -- -Act-- -
//   meshReader.readOpenFoamMesh(fvMesh);

//   // --- Assert ---
//   // *** Verify the node indices of some finite volume elements ***
//   EXPECT_EQ(fvMesh.elements()[0].iNodes().size(), 6);
//   EXPECT_TRUE(
//       VectorMatch(fvMesh.elements()[0].iNodes(), expected_element0_iNodes,
//       6));

//   EXPECT_EQ(fvMesh.elements()[1].iNodes().size(), 6);
//   EXPECT_TRUE(
//       VectorMatch(fvMesh.elements()[1].iNodes(), expected_element1_iNodes,
//       6));

//   EXPECT_EQ(fvMesh.elements()[449].iNodes().size(), 6);
//   EXPECT_TRUE(VectorMatch(fvMesh.elements()[449].iNodes(),
//                           expected_element449_iNodes, 6));

//   EXPECT_EQ(fvMesh.elements()[450].iNodes().size(), 6);
//   EXPECT_TRUE(VectorMatch(fvMesh.elements()[450].iNodes(),
//                           expected_element450_iNodes, 6));

//   // Last two elements
//   EXPECT_EQ(fvMesh.elements()[916].iNodes().size(), 6);
//   EXPECT_TRUE(VectorMatch(fvMesh.elements()[916].iNodes(),
//                           expected_element916_iNodes, 6));

//   EXPECT_EQ(fvMesh.elements()[917].iNodes().size(), 6);
//   EXPECT_TRUE(VectorMatch(fvMesh.elements()[917].iNodes(),
//                           expected_element917_iNodes, 6));
// }

// TEST(SettingUpNodeConnectivitiesTest,
//      ConnectingElementsToNodetWorksForStructuredMesh) {
//   // --- Arrange ---
//   std::string caseDirectory("../../cases/Mycavity");
//   readMesh meshReader;
//   Mesh fvMesh(caseDirectory);
//   const std::array<std::size_t, 3> expected_node0_iElements = {111, 218,
//   219}; const std::array<std::size_t, 3> expected_node1_iElements = {219,
//   293, 295}; const std::array<std::size_t, 5> expected_node499_iElements =
//   {746, 747, 748,
//                                                                  749, 750};
//   const std::array<std::size_t, 6> expected_node500_iElements = {751, 753,
//   754,
//                                                                  773, 869,
//                                                                  870};
//   const std::array<std::size_t, 6> expected_node880_iElements = {
//       909, 910, 911, 912, 914, 916};
//   const std::array<std::size_t, 5> expected_node881_iElements = {913, 914,
//   915,
//                                                                   916, 917};
//   // -- -Act-- -
//   meshReader.readOpenFoamMesh(fvMesh);

//   // --- Assert ---
//   // *** Verify the element indices of some nodes ***
//   EXPECT_EQ(fvMesh.nodes()[0].iElements().size(), 3);
//   EXPECT_TRUE(
//       VectorMatch(fvMesh.nodes()[0].iElements(), expected_node0_iElements,
//       3));

//   EXPECT_EQ(fvMesh.nodes()[1].iElements().size(), 3);
//   EXPECT_TRUE(
//       VectorMatch(fvMesh.nodes()[1].iElements(), expected_node1_iElements,
//       3));

//   EXPECT_EQ(fvMesh.nodes()[499].iElements().size(), 5);
//   EXPECT_TRUE(VectorMatch(fvMesh.nodes()[499].iElements(),
//                           expected_node499_iElements, 5));

//   EXPECT_EQ(fvMesh.nodes()[500].iElements().size(), 6);
//   EXPECT_TRUE(VectorMatch(fvMesh.nodes()[500].iElements(),
//                           expected_node500_iElements, 6));

//   // Last two elements
//   EXPECT_EQ(fvMesh.nodes()[880].iElements().size(), 6);
//   EXPECT_TRUE(VectorMatch(fvMesh.nodes()[880].iElements(),
//                           expected_node880_iElements, 6));

//   EXPECT_EQ(fvMesh.nodes()[881].iElements().size(), 5);
//   EXPECT_TRUE(VectorMatch(fvMesh.nodes()[881].iElements(),
//                           expected_node881_iElements, 5));
// }

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
