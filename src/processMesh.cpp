#include "processMesh.h"
#include <cmath>
#include <cstddef>
#include <vector>

#include <iostream>

void printOutVector(std::vector<double> &customVector) {
  for (std::size_t iCoordinate = 0; iCoordinate < customVector.size();
       ++iCoordinate) {
    std::cout << customVector[iCoordinate] << "\n";
  }
  std::cout << std::endl;
}

void processMesh::processBasicFaceGeometry(Mesh &fvMesh) {
  for (std::size_t iFace = 0; iFace < fvMesh.nFaces(); ++iFace) {
    /*
    // Compute the geometric center of a face
    */
    std::vector<double> center = {0.0, 0.0, 0.0};
    for (std::size_t iNode = 0; iNode < fvMesh.faces()[iFace].nNodes();
         ++iNode) {
      for (std::size_t iCoordinate = 0; iCoordinate < center.size();
           ++iCoordinate)
        center[iCoordinate] +=
            fvMesh.nodes()[fvMesh.faces()[iFace].iNodes()[iNode]]
                .centroid()[iCoordinate];
    }

    for (std::size_t iCoordinate = 0; iCoordinate < center.size();
         ++iCoordinate) {
      center[iCoordinate] /=
          static_cast<double>(fvMesh.faces()[iFace].nNodes());
    }

    /*
    // Using the center to compute the area and centroid of virtual
    // triangles based on the center and the face nodes
    */
    std::vector<double> triangleNode1 = center;
    std::vector<double> triangleNode2(3, 0.0);
    std::vector<double> triangleNode3(3, 0.0);
    std::vector<double> centroid(3, 0.0);
    std::vector<double> Sf(3, 0.0);
    double area = 0.0;

    // TO DO: Should consider a special case when the polygon is a triangle
    for (std::size_t iNode = 0; iNode < fvMesh.faces()[iFace].nNodes();
         ++iNode) {
      triangleNode2 =
          fvMesh.nodes()[fvMesh.faces()[iFace].iNodes()[iNode]].centroid();
      if (iNode < fvMesh.faces()[iFace].nNodes() - 1) {
        triangleNode3 =
            fvMesh.nodes()[fvMesh.faces()[iFace].iNodes()[iNode + 1]]
                .centroid();
      } else {
        triangleNode3 =
            fvMesh.nodes()[fvMesh.faces()[iFace].iNodes()[0]].centroid();
      }

      // Calculate the centroid of a given subtriangle
      std::vector<double> local_centroid(3, 0.0);
      for (std::size_t iCoordinate = 0; iCoordinate < local_centroid.size();
           ++iCoordinate) {
        local_centroid[iCoordinate] =
            (triangleNode1[iCoordinate] + triangleNode2[iCoordinate] +
             triangleNode3[iCoordinate]) /
            3.0;
      }

      // Calculate the surface area vector of a given subtriangle by cross
      // product
      std::vector<double> local_Sf(3, 0.0);
      local_Sf[0] = 0.5 * ((triangleNode2[1] - triangleNode1[1]) *
                               (triangleNode3[2] - triangleNode1[2]) -
                           (triangleNode2[2] - triangleNode1[2]) *
                               (triangleNode3[1] - triangleNode1[1]));
      local_Sf[1] = 0.5 * ((triangleNode2[2] - triangleNode1[2]) *
                               (triangleNode3[0] - triangleNode1[0]) -
                           (triangleNode2[0] - triangleNode1[0]) *
                               (triangleNode3[2] - triangleNode1[2]));
      local_Sf[2] = 0.5 * ((triangleNode2[0] - triangleNode1[0]) *
                               (triangleNode3[1] - triangleNode1[1]) -
                           (triangleNode2[1] - triangleNode1[1]) *
                               (triangleNode3[0] - triangleNode1[0]));

      // Calculate the surface area of a given subtriangle
      double local_area =
          std::sqrt(local_Sf[0] * local_Sf[0] + local_Sf[1] * local_Sf[1] +
                    local_Sf[2] * local_Sf[2]);

      for (std::size_t iCoordinate = 0; iCoordinate < centroid.size();
           ++iCoordinate) {
        centroid[iCoordinate] += local_area * local_centroid[iCoordinate];
        Sf[iCoordinate] += local_Sf[iCoordinate];
      }
    }
    area = std::sqrt(Sf[0] * Sf[0] + Sf[1] * Sf[1] + Sf[2] * Sf[2]);

    // Compute centroid of the polygon
    for (std::size_t iCoordinate = 0; iCoordinate < centroid.size();
         ++iCoordinate) {
      centroid[iCoordinate] /= area;
    }

    fvMesh.faces()[iFace].centroid() = centroid;
    fvMesh.faces()[iFace].Sf() = Sf;
    fvMesh.faces()[iFace].area() = area;
  }
}
