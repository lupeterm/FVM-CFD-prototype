#include <gtest/gtest.h>

#include "Mesh.hpp"
#include "readMesh.hpp"
#include "testUtility.hpp"
#include <array>
#include <string>

// ****** Tests ******
TEST(ProcessingBasicFaceGeometryTest,
     ComputingFaceCentroidWorksForStructuredMesh) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/Mycavity");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  const std::array<double, 3> expected_face0_centroid = {
      0.00500000000000000, 0.00250000000000000, 0.00500000000000000};
  const std::array<double, 3> expected_face1_centroid = {
      0.00250000000000000, 0.00500000000000000, 0.00500000000000000};

  const std::array<double, 3> expected_face818_centroid = {
      0.100000000000000, 0.0925000000000000, 0.00500000000000000};
  const std::array<double, 3> expected_face819_centroid = {
      0.100000000000000, 0.0975000000000000, 0.00500000000000000};

  const std::array<double, 3> expected_face1638_centroid = {
      0.0975000000000000, 0.0925000000000000, 0.0100000000000000};
  const std::array<double, 3> expected_face1639_centroid = {
      0.0975000000000000, 0.0975000000000000, 0.0100000000000000};

  const double maxDiff = 1.0e-9;
  const double maxRelativeDiff = 1.0e-4;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // *** Verify the centroids of faces ***
  // The first two faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[0].centroid(),
                                expected_face0_centroid, 3, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1].centroid(),
                                expected_face1_centroid, 3, maxDiff,
                                maxRelativeDiff));

  // The middle two faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[818].centroid(),
                                expected_face818_centroid, 3, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[819].centroid(),
                                expected_face819_centroid, 3, maxDiff,
                                maxRelativeDiff));

  // The last two faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1638].centroid(),
                                expected_face1638_centroid, 3, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1639].centroid(),
                                expected_face1639_centroid, 3, maxDiff,
                                maxRelativeDiff));
}

TEST(ProcessingBasicFaceGeometryTest,
     ComputingFaceSurfaceVectorWorksForStructuredMesh) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/Mycavity");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  const std::array<double, 3> expected_face0_Sf = {5.00000000000000e-05, 0, 0};
  const std::array<double, 3> expected_face1_Sf = {0, 5.00000000000000e-05, 0};

  const std::array<double, 3> expected_face818_Sf = {5.00000000000000e-05, 0,
                                                     0};
  const std::array<double, 3> expected_face819_Sf = {5.00000000000000e-05, 0,
                                                     0};

  const std::array<double, 3> expected_face1638_Sf = {0, 0,
                                                      2.50000000000000e-05};
  const std::array<double, 3> expected_face1639_Sf = {0, 0,
                                                      2.50000000000000e-05};

  const double maxDiff = 1.0e-9;
  const double maxRelativeDiff = 1.0e-4;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the surface vectors of mesh faces
  // The first two faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[0].Sf(), expected_face0_Sf, 3,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1].Sf(), expected_face1_Sf, 3,
                                maxDiff, maxRelativeDiff));

  // The middle two faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[818].Sf(), expected_face818_Sf,
                                3, maxDiff, maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[819].Sf(), expected_face819_Sf,
                                3, maxDiff, maxRelativeDiff));

  // The last two faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1638].Sf(), expected_face1638_Sf,
                                3, maxDiff, maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1639].Sf(), expected_face1639_Sf,
                                3, maxDiff, maxRelativeDiff));
}

TEST(ProcessingBasicFaceGeometryTest, ComputingFaceAreaWorksForStructuredMesh) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/Mycavity");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  const double expected_face0_area = 5.00000000000000e-05;
  const double expected_face1_area = 5.00000000000000e-05;
  const double expected_face818_area = 5.00000000000000e-05;
  const double expected_face819_area = 5.00000000000000e-05;
  const double expected_face1638_area = 2.50000000000000e-05;
  const double expected_face1639_area = 2.50000000000000e-05;

  const double maxDiff = 1.0e-9;
  const double maxRelativeDiff = 1.0e-4;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the surface areas of mesh faces
  // The first two faces
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[0].area(), expected_face0_area,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[1].area(), expected_face1_area,
                                maxDiff, maxRelativeDiff));

  // The middle two faces
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[818].area(),
                                expected_face818_area, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[819].area(),
                                expected_face819_area, maxDiff,
                                maxRelativeDiff));

  // The last two faces
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[1638].area(),
                                expected_face1638_area, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[1639].area(),
                                expected_face1639_area, maxDiff,
                                maxRelativeDiff));
}

TEST(ComputingElementVolumeAndCentroidTest,
     ComputingElementVolumeWorksForStructuredMesh) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/Mycavity");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  const double expected_element0_volume = 2.50000000000000e-07;
  const double expected_element1_volume = 2.50000000000000e-07;

  const double expected_element198_volume = 2.50000000000000e-07;
  const double expected_element199_volume = 2.50000000000000e-07;

  const double expected_element398_volume = 2.50000000000000e-07;
  const double expected_element399_volume = 2.50000000000000e-07;

  const double maxDiff = 1.0e-9;
  const double maxRelativeDiff = 1.0e-4;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the volumes of the first two elements
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.elements()[0].volume(),
                                expected_element0_volume, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.elements()[1].volume(),
                                expected_element1_volume, maxDiff,
                                maxRelativeDiff));

  // Verify the volumes of the middle two elements
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.elements()[198].volume(),
                                expected_element198_volume, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.elements()[199].volume(),
                                expected_element199_volume, maxDiff,
                                maxRelativeDiff));

  // Verify the volumes of the last two elements
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.elements()[398].volume(),
                                expected_element398_volume, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.elements()[399].volume(),
                                expected_element399_volume, maxDiff,
                                maxRelativeDiff));
}

TEST(ComputingElementVolumeAndCentroidTest,
     ComputingElementCentroidWorksForStructuredMesh) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/Mycavity");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);
  const std::array<double, 3> expected_element0_centroid = {
      0.00250000000000000, 0.00250000000000000, 0.00500000000000000};
  const std::array<double, 3> expected_element1_centroid = {
      0.00750000000000000, 0.00250000000000000, 0.00500000000000000};

  const std::array<double, 3> expected_element198_centroid = {
      0.0925000000000000, 0.0475000000000000, 0.00500000000000000};
  const std::array<double, 3> expected_element199_centroid = {
      0.0975000000000000, 0.0475000000000000, 0.00500000000000000};

  const std::array<double, 3> expected_element398_centroid = {
      0.0925000000000000, 0.0975000000000000, 0.00500000000000000};
  const std::array<double, 3> expected_element399_centroid = {
      0.0975000000000000, 0.0975000000000000, 0.00500000000000000};

  const double maxDiff = 1.0e-9;
  const double maxRelativeDiff = 1.0e-4;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the centroids of the first two elements
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[0].centroid(),
                                expected_element0_centroid, 3, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[1].centroid(),
                                expected_element1_centroid, 3, maxDiff,
                                maxRelativeDiff));

  // Verify the centroids of the middle two elements
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[198].centroid(),
                                expected_element198_centroid, 3, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[199].centroid(),
                                expected_element199_centroid, 3, maxDiff,
                                maxRelativeDiff));

  // Verify the centroids of the last two elements
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[398].centroid(),
                                expected_element398_centroid, 3, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.elements()[399].centroid(),
                                expected_element399_centroid, 3, maxDiff,
                                maxRelativeDiff));
}

TEST(ProcessingSecondaryFaceGeometryTest,
     ComputingInteriorFaceGeometryWorksForStructuredMesh) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/Mycavity");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);

  // Expected data of face 0
  const std::array<double, 3> expected_face0_CN = {0.00500000000000000, 0,
                                                   8.67361737988404e-19};
  const std::array<double, 3> expected_face0_eCN = {1, 0, 1.73472347597681e-16};
  const double expected_face0_gDiff = 0.0100000000000000;
  const std::array<double, 3> expected_face0_T = {0, 0, -8.67361737988403e-21};
  const double expected_face0_gf = 0.500000000000000;

  // Expected data of face 1
  const std::array<double, 3> expected_face1_CN = {0, 0.00500000000000000, 0};
  const std::array<double, 3> expected_face1_eCN = {0, 1, 0};
  const double expected_face1_gDiff = 0.0100000000000000;
  const std::array<double, 3> expected_face1_T = {0, 0, -8.67361737988403e-21};
  const double expected_face1_gf = 0.500000000000000;

  // Expected data of face 758
  const std::array<double, 3> expected_face758_CN = {0.00499999999999999,
                                                     1.38777878078145e-17, 0};
  const std::array<double, 3> expected_face758_eCN = {1, 2.77555756156290e-15,
                                                      0};
  const double expected_face758_gDiff = 0.0100000000000000;
  const std::array<double, 3> expected_face758_T = {0, -1.38777878078145e-19,
                                                    0};
  const double expected_face758_gf = 0.500000000000000;

  // Expected data of face 759
  const std::array<double, 3> expected_face759_CN = {0.00499999999999999, 0, 0};
  const std::array<double, 3> expected_face759_eCN = {1, 0, 0};
  const double expected_face759_gDiff = 0.0100000000000000;
  const std::array<double, 3> expected_face759_T = {0, 0, 0};
  const double expected_face759_gf = 0.500000000000000;

  // Set tolerance
  const double maxDiff = 1.0e-9;
  const double maxRelativeDiff = 1.0e-4;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the geometric quantities of the first interior two faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[0].CN(), expected_face0_CN, 3,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[0].eCN(), expected_face0_eCN, 3,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[0].gDiff(), expected_face0_gDiff,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[0].T(), expected_face0_T, 3,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[0].gf(), expected_face0_gf,
                                maxDiff, maxRelativeDiff));

  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1].CN(), expected_face1_CN, 3,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1].eCN(), expected_face1_eCN, 3,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[1].gDiff(), expected_face1_gDiff,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1].T(), expected_face1_T, 3,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[1].gf(), expected_face1_gf,
                                maxDiff, maxRelativeDiff));

  // Verify the geometric quantities of the last two interior faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[758].CN(), expected_face758_CN,
                                3, maxDiff, maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[758].eCN(), expected_face758_eCN,
                                3, maxDiff, maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[758].gDiff(),
                                expected_face758_gDiff, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[758].T(), expected_face758_T, 3,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[758].gf(), expected_face758_gf,
                                maxDiff, maxRelativeDiff));

  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[759].CN(), expected_face759_CN,
                                3, maxDiff, maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[759].eCN(), expected_face759_eCN,
                                3, maxDiff, maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[759].gDiff(),
                                expected_face759_gDiff, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[759].T(), expected_face759_T, 3,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[759].gf(), expected_face759_gf,
                                maxDiff, maxRelativeDiff));
}

TEST(ProcessingSecondaryFaceGeometryTest,
     ComputingBoundaryFaceGeometryWorksForStructuredMesh) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/Mycavity");
  readMesh meshReader;
  Mesh fvMesh(caseDirectory);

  // Expected data of face 760
  const std::array<double, 3> expected_face760_CN = {0, 0.00250000000000000, 0};
  const std::array<double, 3> expected_face760_eCN = {0, 1, 0};
  const double expected_face760_gDiff = 0.0200000000000000;
  const std::array<double, 3> expected_face760_T = {0, 0, 0};
  const double expected_face760_gf = 1.00000000000000;
  const double expected_face760_walldist = 0.00250000000000000;

  // Expected data of face 761
  const std::array<double, 3> expected_face761_CN = {
      8.67361737988404e-19, 0.00250000000000002, 8.67361737988404e-19};
  const std::array<double, 3> expected_face761_eCN = {3.46944695195359e-16, 1,
                                                      3.46944695195359e-16};
  const double expected_face761_gDiff = 0.0200000000000000;
  const std::array<double, 3> expected_face761_T = {-1.73472347597680e-20, 0,
                                                    -1.73472347597680e-20};
  const double expected_face761_gf = 1.00000000000000;
  const double expected_face761_walldist = 0.00250000000000000;

  // Expected data of face 1638
  const std::array<double, 3> expected_face1638_CN = {0, -1.38777878078145e-17,
                                                      0.00500000000000000};
  const std::array<double, 3> expected_face1638_eCN = {0, -2.77555756156289e-15,
                                                       1};
  const double expected_face1638_gDiff = 0.00500000000000001;
  const std::array<double, 3> expected_face1638_T = {0, 6.93889390390724e-20,
                                                     0};
  const double expected_face1638_gf = 1.00000000000000;
  const double expected_face1638_walldist = 0.00500000000000000;

  // Expected data of face 1639
  const std::array<double, 3> expected_face1639_CN = {0, 0,
                                                      0.00500000000000000};
  const std::array<double, 3> expected_face1639_eCN = {0, 0, 1};
  const double expected_face1639_gDiff = 0.00500000000000001;
  const std::array<double, 3> expected_face1639_T = {0, 0, 0};
  const double expected_face1639_gf = 1.00000000000000;
  const double expected_face1639_walldist = 0.00500000000000000;

  // Set tolerance
  const double maxDiff = 1.0e-9;
  const double maxRelativeDiff = 1.0e-4;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);

  // --- Assert ---
  // Verify the geometric quantities of the first boundary two faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[760].CN(), expected_face760_CN,
                                3, maxDiff, maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[760].eCN(), expected_face760_eCN,
                                3, maxDiff, maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[760].gDiff(),
                                expected_face760_gDiff, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[760].T(), expected_face760_T, 3,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[760].gf(), expected_face760_gf,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[760].walldist(),
                                expected_face760_walldist, maxDiff,
                                maxRelativeDiff));

  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[761].CN(), expected_face761_CN,
                                3, maxDiff, maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[761].eCN(), expected_face761_eCN,
                                3, maxDiff, maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[761].gDiff(),
                                expected_face761_gDiff, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[761].T(), expected_face761_T, 3,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[761].gf(), expected_face761_gf,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[761].walldist(),
                                expected_face761_walldist, maxDiff,
                                maxRelativeDiff));

  // Verify the geometric quantities of the last boundary two faces
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1638].CN(), expected_face1638_CN,
                                3, maxDiff, maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1638].eCN(),
                                expected_face1638_eCN, 3, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[1638].gDiff(),
                                expected_face1638_gDiff, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1638].T(), expected_face1638_T,
                                3, maxDiff, maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[1638].gf(), expected_face1638_gf,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[1638].walldist(),
                                expected_face1638_walldist, maxDiff,
                                maxRelativeDiff));

  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1639].CN(), expected_face1639_CN,
                                3, maxDiff, maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1639].eCN(),
                                expected_face1639_eCN, 3, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[1639].gDiff(),
                                expected_face1639_gDiff, maxDiff,
                                maxRelativeDiff));
  EXPECT_TRUE(VectorAlmostEqual(fvMesh.faces()[1639].T(), expected_face1639_T,
                                3, maxDiff, maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[1639].gf(), expected_face1639_gf,
                                maxDiff, maxRelativeDiff));
  EXPECT_TRUE(ScalarAlmostEqual(fvMesh.faces()[1639].walldist(),
                                expected_face1639_walldist, maxDiff,
                                maxRelativeDiff));
}

// TEST(ProcessingSecondaryFaceGeometryTest,
//      ComputingElementInteriorFaceGeometryWorksForStructuredMesh) {
//   // --- Arrange ---
//   std::string caseDirectory("../../cases/Mycavity");
//   readMesh meshReader;
//   Mesh fvMesh(caseDirectory);

//   // --- Act ---
//   meshReader.readOpenFoamMesh(fvMesh);

//   // --- Assert ---
//   // Verify the geometric quantities of the first two elements
//   //  element 0: face 0 is the only local interior face
//   EXPECT_EQ(fvMesh.faces()[0].iOwnerNeighborCoef(), 1);

//   //  element 1: face 1 is the only local interior face
//   EXPECT_EQ(fvMesh.faces()[1].iOwnerNeighborCoef(), 1);

//   //  element 2: face 2 is only local interior face
//   EXPECT_EQ(fvMesh.faces()[2].iOwnerNeighborCoef(), 1);

//   // Verify the geometric quantities of the middle two elements
//   // element 458: face 672, 680, and 681 are local interior faces
//   EXPECT_EQ(fvMesh.faces()[672].iNeighborOwnerCoef(), 1);
//   EXPECT_EQ(fvMesh.faces()[680].iNeighborOwnerCoef(), 2);
//   EXPECT_EQ(fvMesh.faces()[681].iOwnerNeighborCoef(), 3);

//   // element 459: face 678, 681, and 682 are local interior faces
//   EXPECT_EQ(fvMesh.faces()[678].iNeighborOwnerCoef(), 1);
//   EXPECT_EQ(fvMesh.faces()[681].iNeighborOwnerCoef(), 2);
//   EXPECT_EQ(fvMesh.faces()[682].iOwnerNeighborCoef(), 3);

//   // element 460: face 338, 683, 684 are local interior faces
//   EXPECT_EQ(fvMesh.faces()[338].iNeighborOwnerCoef(), 1);
//   EXPECT_EQ(fvMesh.faces()[683].iOwnerNeighborCoef(), 2);
//   EXPECT_EQ(fvMesh.faces()[684].iOwnerNeighborCoef(), 3);

//   // Verify the geometric quantities of the last two elements
//   // element 915: face 978, 1295, 1297 are local interior faces
//   EXPECT_EQ(fvMesh.faces()[978].iNeighborOwnerCoef(), 1);
//   EXPECT_EQ(fvMesh.faces()[1295].iNeighborOwnerCoef(), 2);
//   EXPECT_EQ(fvMesh.faces()[1638].iNeighborOwnerCoef(), 3);

//   // element 916: face 1294, 1298, 1299 are local interior faces
//   EXPECT_EQ(fvMesh.faces()[1294].iNeighborOwnerCoef(), 1);
//   EXPECT_EQ(fvMesh.faces()[1639].iNeighborOwnerCoef(), 2);
//   EXPECT_EQ(fvMesh.faces()[1299].iOwnerNeighborCoef(), 3);

//   // element 917: face 1171, 1296, 1299 are local interior faces
//   EXPECT_EQ(fvMesh.faces()[1171].iNeighborOwnerCoef(), 1);
//   EXPECT_EQ(fvMesh.faces()[1296].iNeighborOwnerCoef(), 2);
//   EXPECT_EQ(fvMesh.faces()[1299].iNeighborOwnerCoef(), 3);
// }

// TEST(SortingBoundaryNodesFromInteriorNodesTest,
//      LabelingInteriorNodesWorksForStructuredMesh) {
//   // --- Arrange ---
//   std::string caseDirectory("../../cases/elbow");
//   readMesh meshReader;
//   Mesh fvMesh(caseDirectory);

//   // --- Act ---
//   meshReader.readOpenFoamMesh(fvMesh);

//   // --- Assert ---
//   // *** Verify the first two interior faces ***
//   // Node 36, 573, 589, 52 belong to face 0
//   EXPECT_EQ(fvMesh.faces()[0].patchIndex(), 0);
//   EXPECT_EQ(fvMesh.nodes()[36].Flag(), 0);
//   EXPECT_EQ(fvMesh.nodes()[573].Flag(), 0);
//   EXPECT_EQ(fvMesh.nodes()[589].Flag(), 0);
//   EXPECT_EQ(fvMesh.nodes()[52].Flag(), 0);

//   // Node 41, 578, 634, 97 belong to face 1
//   EXPECT_EQ(fvMesh.faces()[1].patchIndex(), 0);
//   EXPECT_EQ(fvMesh.nodes()[41].Flag(), 0);
//   EXPECT_EQ(fvMesh.nodes()[578].Flag(), 0);
//   EXPECT_EQ(fvMesh.nodes()[634].Flag(), 0);
//   EXPECT_EQ(fvMesh.nodes()[97].Flag(), 0);

//   // Node 44, 81, 618, 581 belong to face 2
//   EXPECT_EQ(fvMesh.faces()[2].patchIndex(), 0);
//   EXPECT_EQ(fvMesh.nodes()[44].Flag(), 0);
//   EXPECT_EQ(fvMesh.nodes()[81].Flag(), 0);
//   EXPECT_EQ(fvMesh.nodes()[618].Flag(), 0);
//   EXPECT_EQ(fvMesh.nodes()[581].Flag(), 0);

//   // *** Verify the last two interior faces ***
//   // Node 536, 476, 1013, 1073 belong to face 1297
//   EXPECT_EQ(fvMesh.faces()[1638].patchIndex(), 0);
//   EXPECT_EQ(fvMesh.nodes()[536].Flag(), 1);
//   EXPECT_EQ(fvMesh.nodes()[476].Flag(), 1);
//   EXPECT_EQ(fvMesh.nodes()[1013].Flag(), 1);
//   EXPECT_EQ(fvMesh.nodes()[1073].Flag(), 1);

//   // Node 536, 1073, 1072, 535 belong to face 1298
//   EXPECT_EQ(fvMesh.faces()[1639].patchIndex(), 0);
//   EXPECT_EQ(fvMesh.nodes()[1072].Flag(), 1);
//   EXPECT_EQ(fvMesh.nodes()[535].Flag(), 1);

//   // Node 408, 536, 1073, 945 belong to face 1299
//   EXPECT_EQ(fvMesh.faces()[1299].patchIndex(), 0);
//   EXPECT_EQ(fvMesh.nodes()[408].Flag(), 1);
//   EXPECT_EQ(fvMesh.nodes()[945].Flag(), 1);

//   // *** Verify the boundary faces of different username ***
//   // Face 1300 (username = wall-4)
//   // Node 37, 52, 589, 574 belong to face 1300
//   EXPECT_EQ(fvMesh.faces()[1300].patchIndex(), 0);
//   EXPECT_EQ(fvMesh.nodes()[37].Flag(), 0);
//   EXPECT_EQ(fvMesh.nodes()[589].Flag(), 0);
//   EXPECT_EQ(fvMesh.nodes()[574].Flag(), 0);

//   // Face 1400 (username = velocity-inlet-5)
//   // Node 36, 37, 574, 573 belong to face 1400
//   EXPECT_EQ(fvMesh.faces()[1400].patchIndex(), 1);
//   EXPECT_EQ(fvMesh.nodes()[36].Flag(), 0);
//   EXPECT_EQ(fvMesh.nodes()[573].Flag(), 0);

//   // Face 1420 (username = wall-8)
//   // Node 51, 121, 658, 588 belong to face 1420
//   EXPECT_EQ(fvMesh.nodes()[51].Flag(), 0);
//   EXPECT_EQ(fvMesh.nodes()[121].Flag(), 0);
//   EXPECT_EQ(fvMesh.nodes()[658].Flag(), 0);
//   EXPECT_EQ(fvMesh.nodes()[588].Flag(), 0);

//   // Face 1454 (username = frontAndBackPlanes)
//   // Node 36, 52, 37 belong to face 1454 and are already verified above

//   // Face 1455 (username = frontAndBackPlanes)
//   // Node 573, 574, 589 belong to face 1455 and are already verified above

//   // Face 3288 (username = frontAndBackPlanes)
//   // Node 536, 475, 408 belong to face 3288
//   EXPECT_EQ(fvMesh.nodes()[475].Flag(), 1);

//   // Face 3289 (username = frontAndBackPlanes)
//   // Node 1073, 945, 1012 belong to face 3289
//   EXPECT_EQ(fvMesh.nodes()[1012].Flag(), 1);
// }