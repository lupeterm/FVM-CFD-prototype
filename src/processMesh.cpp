#include "processMesh.h"
#include <array>
#include <cmath>
#include <cstddef>
#include <vector>

#include <iostream>

// *** Debug code ***
template <typename T> void printOutArray(T &customVector) {
  for (std::size_t iCoordinate = 0; iCoordinate < customVector.size();
       ++iCoordinate) {
    std::cout << customVector[iCoordinate] << "\n";
  }
  std::cout << std::endl;
}
// *******************

void processMesh::processOpenFoamMesh(Mesh &fvMesh) {
  processBasicFaceGeometry(fvMesh);
  computeElementVolumeAndCentroid(fvMesh);
}

void processMesh::processBasicFaceGeometry(Mesh &fvMesh) {
  for (std::size_t iFace = 0; iFace < fvMesh.nFaces(); ++iFace) {
    // std::vector<double> center = {0.0, 0.0, 0.0};
    std::array<double, 3> center = {0.0, 0.0, 0.0};
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
    std::array<double, 3> triangleNode1 = center;
    std::array<double, 3> triangleNode2 = {0.0, 0.0, 0.0};
    std::array<double, 3> triangleNode3 = {0.0, 0.0, 0.0};
    std::array<double, 3> centroid = {0.0, 0.0, 0.0};
    std::array<double, 3> Sf = {0.0, 0.0, 0.0};
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
      std::array<double, 3> local_centroid = {0.0, 0.0, 0.0};
      for (std::size_t iCoordinate = 0; iCoordinate < local_centroid.size();
           ++iCoordinate) {
        local_centroid[iCoordinate] =
            (triangleNode1[iCoordinate] + triangleNode2[iCoordinate] +
             triangleNode3[iCoordinate]) /
            3.0;
      }

      // Calculate the surface area vector of a given subtriangle by cross
      // product
      std::array<double, 3> local_Sf = {0.0, 0.0, 0.0};
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

void processMesh::computeElementVolumeAndCentroid(Mesh &fvMesh) {
  for (std::size_t iElement = 0; iElement < fvMesh.nElements(); ++iElement) {
    const std::vector<std::size_t> &iFaces =
        fvMesh.elements()[iElement].iFaces();

    // Compute the geometric center of the element
    std::array<double, 3> elementCenter = {0.0, 0.0, 0.0};
    for (auto iFace : iFaces) {
      for (auto iCoordinate = 0; iCoordinate < 3; ++iCoordinate) {
        elementCenter[iCoordinate] +=
            fvMesh.faces()[iFace].centroid()[iCoordinate];
      }
    }

    for (auto iCoordinate = 0; iCoordinate < 3; ++iCoordinate) {
      elementCenter[iCoordinate] /= iFaces.size();
    }

    // *************** Debug code ***************
    // if (iElement == 0) {
    //   std::cout << "Element 0 geometric center:"
    //             << "\n";
    //   printOutArray(center);
    // } else if (iElement == 1) {
    //   std::cout << "Element 1 geometric center:"
    //             << "\n";
    //   printOutArray(center);
    // } else if (iElement == 2) {
    //   std::cout << "Element 2 geometric center:"
    //             << "\n";
    //   printOutArray(center);
    // } else if (iElement == 915) {
    //   std::cout << "Element 915 geometric center:"
    //             << "\n";
    //   printOutArray(center);
    // } else if (iElement == 916) {
    //   std::cout << "Element 916 geometric center:"
    //             << "\n";
    //   printOutArray(center);
    // } else if (iElement == 917) {
    //   std::cout << "Element 917 geometric center:"
    //             << "\n";
    //   printOutArray(center);
    // }
    // **************************************************

    // Compute volume and centroid of each element
    std::array<double, 3> elementCentroid = {0.0, 0.0, 0.0};
    // std::array<double, 3> Sf = {0.0, 0.0, 0.0};

    std::array<double, 3> localVolumeCentroidSum = {0.0, 0.0, 0.0};
    double localVolumeSum = 0.0;

    for (std::size_t iFace = 0; iFace < iFaces.size(); ++iFace) {
      Face &localFace = fvMesh.faces()[iFaces[iFace]];
      const int localFaceSign = fvMesh.elements()[iElement].faceSigns()[iFace];
      std::array<double, 3> Sf = {0.0, 0.0, 0.0};

      for (std::size_t iCoordinate = 0; iCoordinate < 3; ++iCoordinate) {
        Sf[iCoordinate] = localFace.Sf()[iCoordinate] * localFaceSign;
      }

      // Calculate the distance vector from geometric center to the face
      // centroid
      std::array<double, 3> d_Gf = {0.0, 0.0, 0.0};
      for (std::size_t iCoordinate = 0; iCoordinate < 3; ++iCoordinate) {
        d_Gf[iCoordinate] =
            localFace.centroid()[iCoordinate] - elementCenter[iCoordinate];
      }

      // Calculate the volume of each sub-element pyramid
      double localVolume =
          (Sf[0] * d_Gf[0] + Sf[1] * d_Gf[1] + Sf[2] * d_Gf[2]) / 3.0;

      localVolumeSum += localVolume;
    }
    fvMesh.elements()[iElement].volume() = localVolumeSum;
  }
}