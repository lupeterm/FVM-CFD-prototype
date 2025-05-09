#include <gtest/gtest.h>

#include "Mesh.hpp"
#include "ReadMesh.hpp"
#include "utilitiesForTesting.hpp"
#include <array>
#include <string>

// ****** Tests ******
TEST(ReadStructuredMeshTest, ReadPoints) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/cavity");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

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

TEST(ReadStructuredMeshTest, ReadFaces) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/cavity");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

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

  // Verify the 1st 3 faces
  EXPECT_EQ(fvMesh.faces()[0].nNodes(), 4);
  EXPECT_TRUE(
      VectorMatch(fvMesh.faces()[0].iNodes(), expected_face0_iNodes, 4));

  EXPECT_EQ(fvMesh.faces()[1].nNodes(), 4);
  EXPECT_TRUE(
      VectorMatch(fvMesh.faces()[1].iNodes(), expected_face1_iNodes, 4));

  EXPECT_EQ(fvMesh.faces()[2].nNodes(), 4);
  EXPECT_TRUE(
      VectorMatch(fvMesh.faces()[2].iNodes(), expected_face2_iNodes, 4));

  // Verify the last 3 faces
  EXPECT_EQ(fvMesh.faces()[1637].nNodes(), 4);
  EXPECT_TRUE(
      VectorMatch(fvMesh.faces()[1637].iNodes(), expected_face1637_iNodes, 4));

  EXPECT_EQ(fvMesh.faces()[1638].nNodes(), 4);
  EXPECT_TRUE(
      VectorMatch(fvMesh.faces()[1638].iNodes(), expected_face1638_iNodes, 4));

  EXPECT_EQ(fvMesh.faces()[1639].nNodes(), 4);
  EXPECT_TRUE(
      VectorMatch(fvMesh.faces()[1639].iNodes(), expected_face1639_iNodes, 4));
}

TEST(ReadStructuredMeshTest, ReadOwners) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/cavity");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  EXPECT_EQ(fvMesh.nOwners(), 1640);
  EXPECT_EQ(fvMesh.nCells(), 400);

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

TEST(ReadStructuredMeshTest, ReadNeighbors) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/cavity");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

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

  // Verify the last 3 boundary faces
  EXPECT_EQ(fvMesh.faces()[1637].iNeighbor(), -1);
  EXPECT_EQ(fvMesh.faces()[1638].iNeighbor(), -1);
  EXPECT_EQ(fvMesh.faces()[1639].iNeighbor(), -1);
}

TEST(ReadStructuredMeshTest, ReadBoundaries) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/cavity");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

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

TEST(StructuredElementTest, ConstructNeighbors) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/cavity");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  const std::array<std::size_t, 2> expected_cell0_iNeighbors = {1, 20};
  const std::array<std::size_t, 3> expected_cell1_iNeighbors = {0, 2, 21};
  const std::array<std::size_t, 3> expected_cell199_iNeighbors = {179, 198,
                                                                  219};
  const std::array<std::size_t, 3> expected_cell200_iNeighbors = {180, 201,
                                                                  220};
  const std::array<std::size_t, 3> expected_cell398_iNeighbors = {378, 397,
                                                                  399};
  const std::array<std::size_t, 2> expected_cell399_iNeighbors = {379, 398};

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // *** Verify neighbors for the given finite volume cells ***
  // Verify the 1st 2 cells
  EXPECT_EQ(fvMesh.cells()[0].nNeighbors(), 2);
  EXPECT_TRUE(VectorMatch(fvMesh.cells()[0].iNeighbors(),
                          expected_cell0_iNeighbors, 2));

  EXPECT_EQ(fvMesh.cells()[1].nNeighbors(), 3);
  EXPECT_TRUE(VectorMatch(fvMesh.cells()[1].iNeighbors(),
                          expected_cell1_iNeighbors, 3));

  // Verify two middle cells
  EXPECT_EQ(fvMesh.cells()[199].nNeighbors(), 3);
  EXPECT_TRUE(VectorMatch(fvMesh.cells()[199].iNeighbors(),
                          expected_cell199_iNeighbors, 3));

  EXPECT_EQ(fvMesh.cells()[200].nNeighbors(), 3);
  EXPECT_TRUE(VectorMatch(fvMesh.cells()[200].iNeighbors(),
                          expected_cell200_iNeighbors, 2));

  // Verify the two cells
  EXPECT_EQ(fvMesh.cells()[398].nNeighbors(), 3);
  EXPECT_TRUE(VectorMatch(fvMesh.cells()[398].iNeighbors(),
                          expected_cell398_iNeighbors, 3));

  EXPECT_EQ(fvMesh.cells()[399].nNeighbors(), 2);
  EXPECT_TRUE(VectorMatch(fvMesh.cells()[399].iNeighbors(),
                          expected_cell399_iNeighbors, 2));
}

TEST(StructuredElementTest, ConstructFaces) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/cavity");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  const std::size_t expected_cell_nFaces = 6;
  const std::array<std::size_t, 6> expected_cell0_iFaces = {0,   1,   780,
                                                            820, 840, 1240};
  const std::array<std::size_t, 6> expected_cell1_iFaces = {0,   2,   3,
                                                            821, 860, 1260};
  const std::array<std::size_t, 6> expected_cell99_iFaces = {155, 192,  194,
                                                             804, 1224, 1624};
  const std::array<std::size_t, 6> expected_cell100_iFaces = {157, 195, 196,
                                                              785, 845, 1245};
  const std::array<std::size_t, 6> expected_cell398_iFaces = {739, 758,  759,
                                                              778, 1219, 1619};
  const std::array<std::size_t, 6> expected_cell399_iFaces = {740, 759,  779,
                                                              819, 1239, 1639};

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // *** Verify face indices for the given finite volume cells ***
  // Verify the 1st 2 cells
  EXPECT_EQ(fvMesh.cells()[0].iFaces().size(), expected_cell_nFaces);
  EXPECT_TRUE(VectorMatch(fvMesh.cells()[0].iFaces(), expected_cell0_iFaces,
                          expected_cell_nFaces));

  EXPECT_EQ(fvMesh.cells()[1].iFaces().size(), expected_cell_nFaces);
  EXPECT_TRUE(VectorMatch(fvMesh.cells()[1].iFaces(), expected_cell1_iFaces,
                          expected_cell_nFaces));

  // Verify two middle cells
  EXPECT_EQ(fvMesh.cells()[99].iFaces().size(), expected_cell_nFaces);
  EXPECT_TRUE(VectorMatch(fvMesh.cells()[99].iFaces(), expected_cell99_iFaces,
                          expected_cell_nFaces));

  EXPECT_EQ(fvMesh.cells()[100].iFaces().size(), expected_cell_nFaces);
  EXPECT_TRUE(VectorMatch(fvMesh.cells()[100].iFaces(), expected_cell100_iFaces,
                          expected_cell_nFaces));

  // Verify the last two cells
  EXPECT_EQ(fvMesh.cells()[398].iFaces().size(), expected_cell_nFaces);
  EXPECT_TRUE(VectorMatch(fvMesh.cells()[398].iFaces(), expected_cell398_iFaces,
                          expected_cell_nFaces));

  EXPECT_EQ(fvMesh.cells()[399].iFaces().size(), expected_cell_nFaces);
  EXPECT_TRUE(VectorMatch(fvMesh.cells()[399].iFaces(), expected_cell399_iFaces,
                          expected_cell_nFaces));
}

TEST(StructuredElementTest, ConstructFaceSigns) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/cavity");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  const std::size_t expected_cell_nFaces = 6;
  const std::array<int, 6> expected_cell0_faceSigns = {1, 1, 1, 1, 1, 1};
  const std::array<int, 6> expected_cell1_faceSigns = {-1, 1, 1, 1, 1, 1};
  const std::array<int, 6> expected_cell99_faceSigns = {-1, -1, 1, 1, 1, 1};
  const std::array<int, 6> expected_cell100_faceSigns = {-1, 1, 1, 1, 1, 1};
  const std::array<int, 6> expected_cell398_faceSigns = {-1, -1, 1, 1, 1, 1};
  const std::array<int, 6> expected_cell399_faceSigns = {-1, -1, 1, 1, 1, 1};

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // *** Verify face signs for the given finite volume cells ***
  // Verify the 1st 2 cells
  EXPECT_TRUE(VectorMatch(fvMesh.cells()[0].faceSigns(),
                          expected_cell0_faceSigns, expected_cell_nFaces));
  EXPECT_TRUE(VectorMatch(fvMesh.cells()[1].faceSigns(),
                          expected_cell1_faceSigns, expected_cell_nFaces));

  // Verify two middle cells
  EXPECT_TRUE(VectorMatch(fvMesh.cells()[99].faceSigns(),
                          expected_cell99_faceSigns, expected_cell_nFaces));
  EXPECT_TRUE(VectorMatch(fvMesh.cells()[100].faceSigns(),
                          expected_cell100_faceSigns, expected_cell_nFaces));

  // Verify last two cells
  EXPECT_TRUE(VectorMatch(fvMesh.cells()[398].faceSigns(),
                          expected_cell398_faceSigns, expected_cell_nFaces));

  EXPECT_TRUE(VectorMatch(fvMesh.cells()[399].faceSigns(),
                          expected_cell399_faceSigns, expected_cell_nFaces));
}

TEST(StructuredElementTest, ConstructBoundary) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/cavity");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  EXPECT_EQ(fvMesh.nBCells(), 880);
  EXPECT_EQ(fvMesh.nBFaces(), 880);
}

TEST(StructuredNodeConnectivityTest, ConnectFacesToNode) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/cavity");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  const size_t expected_node0_nFaces = 3;
  const size_t expected_node1_nFaces = 5;
  const size_t expected_nodes438_nFaces = 5;
  const size_t expected_nodes439_nFaces = 5;
  const size_t expected_node880_nFaces = 5;
  const size_t expected_node881_nFaces = 3;

  const std::array<std::size_t, 3> expected_node0_iFaces = {780, 820, 840};
  const std::array<std::size_t, 5> expected_node1_iFaces = {0, 820, 821, 840,
                                                            860};
  const std::array<std::size_t, 5> expected_nodes438_iFaces = {758, 777, 778,
                                                               1199, 1219};
  const std::array<std::size_t, 5> expected_nodes439_iFaces = {759, 778, 779,
                                                               1219, 1239};
  const std::array<std::size_t, 5> expected_node880_iFaces = {759, 778, 779,
                                                              1619, 1639};
  const std::array<std::size_t, 3> expected_node881_iFaces = {779, 819, 1639};

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the 1st two nodes
  EXPECT_EQ(fvMesh.nodes()[0].iFaces().size(), expected_node0_nFaces);
  EXPECT_TRUE(VectorMatch(fvMesh.nodes()[0].iFaces(), expected_node0_iFaces,
                          expected_node0_nFaces));

  EXPECT_EQ(fvMesh.nodes()[1].iFaces().size(), expected_node1_nFaces);
  EXPECT_TRUE(VectorMatch(fvMesh.nodes()[1].iFaces(), expected_node1_iFaces,
                          expected_node1_nFaces));

  // Verify two middle nodes
  EXPECT_EQ(fvMesh.nodes()[438].iFaces().size(), expected_nodes438_nFaces);
  EXPECT_TRUE(VectorMatch(fvMesh.nodes()[438].iFaces(),
                          expected_nodes438_iFaces, expected_nodes438_nFaces));

  EXPECT_EQ(fvMesh.nodes()[439].iFaces().size(), expected_nodes439_nFaces);
  EXPECT_TRUE(VectorMatch(fvMesh.nodes()[439].iFaces(),
                          expected_nodes439_iFaces, expected_nodes439_nFaces));

  // Verify the last two nodes
  EXPECT_EQ(fvMesh.nodes()[880].iFaces().size(), expected_node880_nFaces);
  EXPECT_TRUE(VectorMatch(fvMesh.nodes()[880].iFaces(), expected_node880_iFaces,
                          expected_node880_nFaces));

  EXPECT_EQ(fvMesh.nodes()[881].iFaces().size(), expected_node881_nFaces);
  EXPECT_TRUE(VectorMatch(fvMesh.nodes()[881].iFaces(), expected_node881_iFaces,
                          expected_node881_nFaces));
}

TEST(StructuredNodeConnectivityTest, ConnectNodesToElement) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/cavity");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  const std::size_t expected_cell_nNodes = 8;
  const std::array<std::size_t, 8> expected_cell0_iNodes = {1,  22,  463, 442,
                                                            21, 462, 0,   441};
  const std::array<std::size_t, 8> expected_cell1_iNodes = {1, 22, 463, 442,
                                                            2, 23, 464, 443};
  const std::array<std::size_t, 8> expected_cell198_iNodes = {
      207, 648, 649, 208, 228, 669, 229, 670};
  const std::array<std::size_t, 8> expected_cell199_iNodes = {
      208, 649, 650, 209, 229, 670, 671, 230};
  const std::array<std::size_t, 8> expected_cell398_iNodes = {
      417, 858, 859, 418, 438, 879, 439, 880};
  const std::array<std::size_t, 8> expected_cell399_iNodes = {
      418, 859, 860, 419, 439, 880, 881, 440};

  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // *** Verify the node indices of some finite volume cells ***
  // Verify the 1st two cells
  EXPECT_EQ(fvMesh.cells()[0].iNodes().size(), expected_cell_nNodes);
  EXPECT_TRUE(VectorMatch(fvMesh.cells()[0].iNodes(), expected_cell0_iNodes,
                          expected_cell_nNodes));

  EXPECT_EQ(fvMesh.cells()[1].iNodes().size(), expected_cell_nNodes);
  EXPECT_TRUE(VectorMatch(fvMesh.cells()[1].iNodes(), expected_cell1_iNodes,
                          expected_cell_nNodes));

  // Verify two middle cells
  EXPECT_EQ(fvMesh.cells()[198].iNodes().size(), expected_cell_nNodes);
  EXPECT_TRUE(VectorMatch(fvMesh.cells()[198].iNodes(), expected_cell198_iNodes,
                          expected_cell_nNodes));

  EXPECT_EQ(fvMesh.cells()[199].iNodes().size(), expected_cell_nNodes);
  EXPECT_TRUE(VectorMatch(fvMesh.cells()[199].iNodes(), expected_cell199_iNodes,
                          expected_cell_nNodes));

  // Verify the last two cells
  EXPECT_EQ(fvMesh.cells()[398].iNodes().size(), expected_cell_nNodes);
  EXPECT_TRUE(VectorMatch(fvMesh.cells()[398].iNodes(), expected_cell398_iNodes,
                          expected_cell_nNodes));

  EXPECT_EQ(fvMesh.cells()[399].iNodes().size(), expected_cell_nNodes);
  EXPECT_TRUE(VectorMatch(fvMesh.cells()[399].iNodes(), expected_cell399_iNodes,
                          expected_cell_nNodes));
}

TEST(StructuredNodeConnectivityTest, ConnectElementsToNode) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/cavity");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  const size_t expected_node0_nCells = 1;
  const size_t expected_node1_nCells = 2;
  const size_t expected_node499_nCells = 4;
  const size_t expected_node500_nCells = 4;
  const size_t expected_node880_nCells = 2;
  const size_t expected_node881_nCells = 1;
  const std::array<std::size_t, 1> expected_node0_iCells = {0};
  const std::array<std::size_t, 2> expected_node1_iCells = {0, 1};
  const std::array<std::size_t, 4> expected_node499_iCells = {35, 36, 55, 56};
  const std::array<std::size_t, 4> expected_node500_iCells = {36, 37, 56, 57};
  const std::array<std::size_t, 2> expected_node880_iCells = {398, 399};
  const std::array<std::size_t, 1> expected_node881_iCells = {399};
  // -- -Act-- -
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // *** Verify the cell indices of some nodes ***
  // Verify the 1st two nodes
  EXPECT_EQ(fvMesh.nodes()[0].iCells().size(), expected_node0_nCells);
  EXPECT_TRUE(VectorMatch(fvMesh.nodes()[0].iCells(), expected_node0_iCells,
                          expected_node0_nCells));

  EXPECT_EQ(fvMesh.nodes()[1].iCells().size(), expected_node1_nCells);
  EXPECT_TRUE(VectorMatch(fvMesh.nodes()[1].iCells(), expected_node1_iCells,
                          expected_node1_nCells));

  // Verify two middle nodes
  EXPECT_EQ(fvMesh.nodes()[499].iCells().size(), expected_node499_nCells);
  EXPECT_TRUE(VectorMatch(fvMesh.nodes()[499].iCells(), expected_node499_iCells,
                          expected_node499_nCells));

  EXPECT_EQ(fvMesh.nodes()[500].iCells().size(), expected_node500_nCells);
  EXPECT_TRUE(VectorMatch(fvMesh.nodes()[500].iCells(), expected_node500_iCells,
                          expected_node500_nCells));

  // Verify the last two nodes
  EXPECT_EQ(fvMesh.nodes()[880].iCells().size(), expected_node880_nCells);
  EXPECT_TRUE(VectorMatch(fvMesh.nodes()[880].iCells(), expected_node880_iCells,
                          expected_node880_nCells));

  EXPECT_EQ(fvMesh.nodes()[881].iCells().size(), expected_node881_nCells);
  EXPECT_TRUE(VectorMatch(fvMesh.nodes()[881].iCells(), expected_node881_iCells,
                          expected_node881_nCells));
}