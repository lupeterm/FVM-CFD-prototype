#include "processMesh.h"
#include <cstddef>
#include <vector>

void processMesh::processBasicFaceGeometry(Mesh &fvMesh) {
  std::size_t nFaces = fvMesh.nFaces();

  for (std::size_t iFace = 0; iFace < nFaces; ++iFace) {
    std::size_t *iNodes = fvMesh.faces()[iFace].iNodes();
    const std::size_t nNodes = fvMesh.faces()[iFace].nNodes();

    // *** Compute the geometric center of a face ***
    std::vector<double> center = {0.0, 0.0, 0.0};
    for (std::size_t iNode = 0; iNode < nNodes; ++iNode) {
      for (std::size_t iCoordinate = 0; iCoordinate < center.size();
           ++iCoordinate)
        center[iCoordinate] += fvMesh.nodes()[iNode].centroid()[iCoordinate];
    }

    for (std::size_t iCoordinate = 0; iCoordinate < center.size();
         ++iCoordinate) {
      center[iCoordinate] /= static_cast<double>(nNodes);
    }

    /*
    Using the center to compute the area and centroid of virtual
    triangles based on the center and the face nodes
    */
    // std::vector<double> centroid(3, 0.0);
    // std::vector<double> Sf(3, 0.0);
    // double area = 0.0;
    // std::vector<double> point1 = center;
    // if (nNodes > 3) {
    //   for (std::size_t iTriangle = 0; iTriangle < nNodes; ++iTriangle) {
    //     std::vector<double> point2 =
    //         fvMesh.nodes()[iNodes[iTriangle]].centroid();
    //   }
    // }
  }
}
