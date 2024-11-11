#include <gtest/gtest.h>

#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include "mesh.h"
#include "readOpenFoamMesh.h"

#include "add.h"

TEST(AdditionTest, HandlesPositiveInput) {
  EXPECT_EQ(add(1, 2), 3);
}

TEST(AdditionTest, HandlesNegativeInput) {
  EXPECT_EQ(add(-1, -1), -2);
}

TEST(ReadingOpenFoamMeshTest, handleMeshPoints){

  std::string caseDirectory("../../cases/elbow");
  std::vector<Node> nodes;
  std::vector<Face> faces;
  cfdReadOpenFoamMesh(nodes, faces, caseDirectory);
  Mesh fvMesh{caseDirectory, nodes, faces};
    
  EXPECT_EQ(fvMesh.nodes()[0].centroid[0], 32);
  EXPECT_EQ(fvMesh.nodes()[0].centroid[1], 16);
  EXPECT_EQ(fvMesh.nodes()[0].centroid[2], 0.9377383239);

    // // ------------------ Test readFaces----------------------
    // for (int i = 0; i < 3; ++i)
    // { 
    //     int numberOfPoints = fvMesh.faces()[i].iNodes.size();

    //     std::cout << "(";

    //     for (int j = 0; j < numberOfPoints; ++j)
    //     {
    //         std::cout << fvMesh.faces()[i].iNodes[j];
            
    //         if (j < numberOfPoints-1)
    //         {
    //             std::cout << " ";
    //         }
    //         else
    //         {
    //             std::cout << ")" << std::endl;;
    //         }
    //     }
    // }

    // return 0;
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
