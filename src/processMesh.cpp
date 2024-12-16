#include "processMesh.h"
#include <cstddef>

void processMesh::processFaceGeometry(Mesh &fvMesh) {
  std::size_t nFaces = fvMesh.nFaces();

  for (std::size_t i = 0; i < nFaces; ++i) {
    std::size_t *iNodes = fvMesh.faces()[i].iNodes();
    const std::size_t nNodes = fvMesh.faces()[i].nNodes();

    // Compute a rough center of the face
    //     double center_x = 0;
    //     double center_y = 0;
    //     double center_z = 0;
    //     for (std::size_t j = 0; j < nNodes; ++j) {
    //       center_x += fvMesh.nodes()[j].x();
    //       center_y += fvMesh.nodes()[j].y();
    //       center_z += fvMesh.nodes()[j].z();
    //     }
    //     center_x /= static_cast<double>(nNodes);
    //     center_y /= static_cast<double>(nNodes);
    //     center_z /= static_cast<double>(nNodes);
    //   }
  }
}