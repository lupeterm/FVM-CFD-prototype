#include "processMesh.h"
#include <cmath>
#include <cstddef>
#include <vector>

void processMesh::processBasicFaceGeometry(Mesh &fvMesh) {
  std::size_t nFaces = fvMesh.nFaces();

  for (std::size_t iFace = 0; iFace < nFaces; ++iFace) {
    std::size_t *iNodes = fvMesh.faces()[iFace].iNodes();
    const std::size_t nNodes = fvMesh.faces()[iFace].nNodes();

    /*
    // Compute the geometric center of a face
    */
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
    // Using the center to compute the area and centroid of virtual
    // triangles based on the center and the face nodes
    */
    std::vector<double> point1 = center;
    std::vector<double> point2(3, 0.0);
    std::vector<double> point3(3, 0.0);
    std::vector<double> centroid(3, 0.0);
    std::vector<double> Sf(3, 0.0);
    double area = 0.0;

    // TO DO: Should consider a special case when the polygon is a triangle
    for (std::size_t iTriangle = 0; iTriangle < nNodes; ++iTriangle) {
      point2 = fvMesh.nodes()[iNodes[iTriangle]].centroid();
      if (iTriangle < nNodes - 1) {
        point3 = fvMesh.nodes()[iNodes[iTriangle + 1]].centroid();
      } else {
        point3 = fvMesh.nodes()[iNodes[0]].centroid();
      }

      // Calculate the centroid of a given subtriangle
      std::vector<double> local_centroid(3, 0.0);
      for (std::size_t iCoordinate = 0; iCoordinate < 3; ++iCoordinate) {
        local_centroid[iCoordinate] =
            (point1[iCoordinate] + point2[iCoordinate] + point3[iCoordinate]) /
            3.0;
      }

      // Calculate the surface area vector of a given subtriangle by cross
      // product
      std::vector<double> local_Sf(3, 0.0);
      local_Sf[0] = 0.5 * ((point2[1] - point1[1]) * (point3[2] - point1[2]) -
                           (point2[2] - point1[2]) * (point3[1] - point1[1]));
      local_Sf[1] = 0.5 * ((point2[2] - point1[2]) * (point3[0] - point1[0]) -
                           (point2[0] - point1[0]) * (point3[2] - point1[2]));
      local_Sf[2] = 0.5 * ((point2[0] - point1[0]) * (point3[1] - point1[1]) -
                           (point2[1] - point1[1]) * (point3[0] - point1[0]));

      // Calculate the surface area of a given subtriangle
      double local_area =
          std::sqrt(local_Sf[0] * local_Sf[0] + local_Sf[1] * local_Sf[1] +
                    local_Sf[2] * local_Sf[2]);

      for (std::size_t iCoordinate = 0; iCoordinate < centroid.size();
           ++iCoordinate) {
        centroid[iCoordinate] += local_area * local_centroid[iCoordinate];
        Sf[iCoordinate] += local_Sf[iCoordinate];
      }

      area += local_area;
    }

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
