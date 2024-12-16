#include "processMesh.h"
#include <cstddef>
#include <vector>

void processMesh::processBasicFaceGeometry(Mesh &fvMesh) {
  std::size_t nFaces = fvMesh.nFaces();

  for (std::size_t i = 0; i < nFaces; ++i) {
    std::size_t *iNodes = fvMesh.faces()[i].iNodes();
    const std::size_t nNodes = fvMesh.faces()[i].nNodes();

    // *** Compute a rough center of the face ***
    std::vector<double> center = {0.0, 0.0, 0.0};
    for (std::size_t j = 0; j < nNodes; ++j) {
      for (std::size_t k = 0; k < center.size(); ++k)
        center[k] += fvMesh.nodes()[j].centroid()[k];
    }

    for (std::size_t k = 0; k < center.size(); ++k) {
      center[k] /= static_cast<double>(nNodes);
    }

    /*
    Using the center to compute the area and centroid of virtual
    triangles based on the center and the face nodes
    */
    std::vector<double> centroid(3, 0.0);
    std::vector<double> Sf(3, 0.0);
    double area = 0.0;
  }
}
