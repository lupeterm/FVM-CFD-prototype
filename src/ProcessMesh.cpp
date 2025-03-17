#include "ProcessMesh.hpp"
#include "utilities.hpp"
#include <array>
#include <cmath>
#include <cstddef>
#include <vector>

// *** Debug code ***
// #include <iostream>
// template <typename T> void printOutArray(T &customVector) {
//   for (std::size_t iCoordinate = 0; iCoordinate < customVector.size();
//        ++iCoordinate) {
//     std::cout << customVector[iCoordinate] << "\n";
//   }
//   std::cout << std::endl;
// }
// *******************

void ProcessMesh::processOpenFoamMesh(Mesh &fvMesh) {
  processBasicFaceGeometry(fvMesh);
  computeElementVolumeAndCentroid(fvMesh);
  processSecondaryFaceGeometry(fvMesh);
  sortBoundaryNodesFromInteriorNodes(fvMesh);
}

void ProcessMesh::processBasicFaceGeometry(Mesh &fvMesh) {
  for (std::size_t iFace = 0; iFace < fvMesh.nFaces(); ++iFace) {

    std::array<double, 3> centroid = {0.0, 0.0, 0.0};
    std::array<double, 3> Sf = {0.0, 0.0, 0.0};
    double area = 0.0;

    // Consider a special case where the polygon is a triangle
    if (fvMesh.faces()[iFace].nNodes() == 3) {

      std::array<double, 3> &triangleNode1 =
          fvMesh.nodes()[fvMesh.faces()[iFace].iNodes()[0]].centroid();
      std::array<double, 3> &triangleNode2 =
          fvMesh.nodes()[fvMesh.faces()[iFace].iNodes()[1]].centroid();
      std::array<double, 3> &triangleNode3 =
          fvMesh.nodes()[fvMesh.faces()[iFace].iNodes()[2]].centroid();

      for (std::size_t iCoordinate = 0; iCoordinate < 3; ++iCoordinate) {
        centroid[iCoordinate] =
            (triangleNode1[iCoordinate] + triangleNode2[iCoordinate] +
             triangleNode3[iCoordinate]) /
            3.0;
      }

      // Calculate the surface area vector of a given triangle by cross
      // product
      Sf = 0.5 * cross_product(triangleNode2 - triangleNode1,
                               triangleNode3 - triangleNode1);
      area = mag(Sf);

    } else { // General case where the polygon is not a triangle
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

        local_Sf = 0.5 * cross_product(triangleNode2 - triangleNode1,
                                       triangleNode3 - triangleNode1);

        // Calculate the surface area of a given subtriangle
        double local_area = mag(local_Sf);

        for (std::size_t iCoordinate = 0; iCoordinate < centroid.size();
             ++iCoordinate) {
          centroid[iCoordinate] += local_area * local_centroid[iCoordinate];
          Sf[iCoordinate] += local_Sf[iCoordinate];
        }
      }
      area = mag(Sf);

      // Compute centroid of the polygon
      for (std::size_t iCoordinate = 0; iCoordinate < centroid.size();
           ++iCoordinate) {
        centroid[iCoordinate] /= area;
      }
    }
    fvMesh.faces()[iFace].centroid() = centroid;
    fvMesh.faces()[iFace].Sf() = Sf;
    fvMesh.faces()[iFace].area() = area;
  }
}

void ProcessMesh::computeElementVolumeAndCentroid(Mesh &fvMesh) {
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

    // Compute volume and centroid of each element
    std::array<double, 3> elementCentroid = {0.0, 0.0, 0.0};
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

      // Calculate volume-weighted center of sub-element pyramid (centroid)
      std::array<double, 3> localCentroid = {0.0, 0.0, 0.0};
      for (std::size_t iCoordinate = 0; iCoordinate < 3; ++iCoordinate) {
        localCentroid[iCoordinate] = 0.75 * localFace.centroid()[iCoordinate] +
                                     0.25 * elementCenter[iCoordinate];
      }

      for (std::size_t iCoordinate = 0; iCoordinate < 3; ++iCoordinate) {
        localVolumeCentroidSum[iCoordinate] +=
            localCentroid[iCoordinate] * localVolume;
      }
    }
    for (std::size_t iCoordinate = 0; iCoordinate < 3; ++iCoordinate) {
      fvMesh.elements()[iElement].centroid()[iCoordinate] =
          localVolumeCentroidSum[iCoordinate] / localVolumeSum;
    }
    fvMesh.elements()[iElement].volume() = localVolumeSum;
    fvMesh.elements()[iElement].oldVolume() = localVolumeSum;
  }
}

void ProcessMesh::processSecondaryFaceGeometry(Mesh &fvMesh) {
  // Loop over interiror faces
  for (std::size_t iFace = 0; iFace < fvMesh.nInteriorFaces(); ++iFace) {
    Face &theFace = fvMesh.faces()[iFace];

    // Compute unit surface normal vector
    std::array<double, 3> nf = {0.0, 0.0, 0.0};
    for (std::size_t iCoordinate = 0; iCoordinate < 3; ++iCoordinate) {
      nf[iCoordinate] = theFace.Sf()[iCoordinate] / theFace.area();
    }

    Element &ownerElement = fvMesh.elements()[theFace.iOwner()];
    Element &neighborElement = fvMesh.elements()[theFace.iNeighbor()];

    std::array<double, 3> CN = {0.0, 0.0, 0.0};
    for (std::size_t iCoordinate = 0; iCoordinate < 3; ++iCoordinate) {
      CN[iCoordinate] = neighborElement.centroid()[iCoordinate] -
                        ownerElement.centroid()[iCoordinate];
    }
    fvMesh.faces()[iFace].CN() = CN;

    std::array<double, 3> eCN = {0.0, 0.0, 0.0};
    const double magCN = mag(CN);
    for (std::size_t iCoordinate = 0; iCoordinate < 3; ++iCoordinate) {
      eCN[iCoordinate] = CN[iCoordinate] / magCN;
    }
    fvMesh.faces()[iFace].eCN() = eCN;

    std::array<double, 3> E = {0.0, 0.0, 0.0};
    for (std::size_t iCoordinate = 0; iCoordinate < 3; ++iCoordinate) {
      E[iCoordinate] = theFace.area() * eCN[iCoordinate];
    }

    fvMesh.faces()[iFace].gDiff() = mag(E) / magCN;

    for (std::size_t iCoordinate = 0; iCoordinate < 3; ++iCoordinate) {
      fvMesh.faces()[iFace].T()[iCoordinate] =
          theFace.Sf()[iCoordinate] - E[iCoordinate];
    }

    // Compute face weighting factor
    std::array<double, 3> Cf = {0.0, 0.0, 0.0};
    for (std::size_t iCoordinate = 0; iCoordinate < 3; ++iCoordinate) {
      Cf[iCoordinate] = theFace.centroid()[iCoordinate] -
                        ownerElement.centroid()[iCoordinate];
    }

    std::array<double, 3> fF = {0.0, 0.0, 0.0};
    for (std::size_t iCoordinate = 0; iCoordinate < 3; ++iCoordinate) {
      fF[iCoordinate] = neighborElement.centroid()[iCoordinate] -
                        theFace.centroid()[iCoordinate];
    }
    fvMesh.faces()[iFace].gf() =
        dot_product(Cf, nf) / (dot_product(Cf, nf) + dot_product(fF, nf));

    // fvMesh.faces()[iFace].walldist() = 0.0; Default value = 0.0
  }

  // Loop over boundary faces
  for (std::size_t iBFace = fvMesh.nInteriorFaces(); iBFace < fvMesh.nFaces();
       ++iBFace) {
    Face &theBFace = fvMesh.faces()[iBFace];

    // Compute unit surface normal vector
    std::array<double, 3> nf = {0.0, 0.0, 0.0};
    for (std::size_t iCoordinate = 0; iCoordinate < 3; ++iCoordinate) {
      nf[iCoordinate] = theBFace.Sf()[iCoordinate] / theBFace.area();
    }

    Element &ownerElement = fvMesh.elements()[theBFace.iOwner()];

    std::array<double, 3> CN = {0.0, 0.0, 0.0};
    for (std::size_t iCoordinate = 0; iCoordinate < 3; ++iCoordinate) {
      CN[iCoordinate] = theBFace.centroid()[iCoordinate] -
                        ownerElement.centroid()[iCoordinate];
    }
    fvMesh.faces()[iBFace].CN() = CN;

    fvMesh.faces()[iBFace].gDiff() =
        theBFace.area() * theBFace.area() / dot_product(CN, theBFace.Sf());

    std::array<double, 3> eCN = {0.0, 0.0, 0.0};
    const double magCN = mag(CN);
    for (std::size_t iCoordinate = 0; iCoordinate < 3; ++iCoordinate) {
      eCN[iCoordinate] = CN[iCoordinate] / magCN;
    }
    fvMesh.faces()[iBFace].eCN() = eCN;

    std::array<double, 3> E = {0.0, 0.0, 0.0};
    for (std::size_t iCoordinate = 0; iCoordinate < 3; ++iCoordinate) {
      E[iCoordinate] = theBFace.area() * eCN[iCoordinate];
    }

    for (std::size_t iCoordinate = 0; iCoordinate < 3; ++iCoordinate) {
      fvMesh.faces()[iBFace].T()[iCoordinate] =
          theBFace.Sf()[iCoordinate] - E[iCoordinate];
    }

    fvMesh.faces()[iBFace].gf() = 1.0;
    fvMesh.faces()[iBFace].walldist() =
        dot_product(CN, theBFace.Sf()) / mag(theBFace.Sf());
  }

  // Loop over elements
  for (std::size_t iElement = 0; iElement < fvMesh.nElements(); ++iElement) {
    std::vector<std::size_t> &iFaces = fvMesh.elements()[iElement].iFaces();
    std::vector<std::size_t> &iNeighbors =
        fvMesh.elements()[iElement].iNeighbors();

    std::size_t kf = 1;

    // Loop over local interior faces of an element
    for (std::size_t i = 0; i < iNeighbors.size(); ++i) {
      const std::size_t iFace = iFaces[i];
      if (fvMesh.faces()[iFace].iOwner() == iElement) {
        fvMesh.faces()[iFace].iOwnerNeighborCoef() = kf;

      } else if (fvMesh.faces()[iFace].iNeighbor() == iElement) {
        fvMesh.faces()[iFace].iNeighborOwnerCoef() = kf;
      }
      kf++;
    }
  }
}

void ProcessMesh::sortBoundaryNodesFromInteriorNodes(Mesh &fvMesh) {
  for (std::size_t iFace = 0; iFace < fvMesh.nInteriorFaces(); ++iFace) {
    fvMesh.faces()[iFace].patchIndex() = 0;

    std::size_t *iNodes = fvMesh.faces()[iFace].iNodes();
    std::size_t nNodes = fvMesh.faces()[iFace].nNodes();
    for (std::size_t iNode = 0; iNode < nNodes; ++iNode) {
      fvMesh.nodes()[iNodes[iNode]].Flag() = 1;
    }
  }

  for (std::size_t iBoundary = 0; iBoundary < fvMesh.nBoundaries();
       ++iBoundary) {
    const std::size_t &startFace = fvMesh.boundaries()[iBoundary].startFace();
    const std::size_t &nBFaces = fvMesh.boundaries()[iBoundary].nFaces();

    bool s1 = (fvMesh.boundaries()[iBoundary].userName() == "frontAndBack");
    bool s2 =
        (fvMesh.boundaries()[iBoundary].userName() == "frontAndBackPlanes");
    if (s1 || s2) {
      for (std::size_t iFace = startFace; iFace < startFace + nBFaces - 1;
           ++iFace) {
        std::size_t *iNodes = fvMesh.faces()[iFace].iNodes();
        const std::size_t &nNodes = fvMesh.faces()[iFace].nNodes();

        for (std::size_t iNode = 0; iNode < nNodes; ++iNode) {
          fvMesh.nodes()[iNodes[iNode]].Flag() = 1;
        }
      }
    }
  }

  for (std::size_t iBoundary = 0; iBoundary < fvMesh.nBoundaries();
       ++iBoundary) {
    const std::size_t &startFace = fvMesh.boundaries()[iBoundary].startFace();
    const std::size_t &nBFaces = fvMesh.boundaries()[iBoundary].nFaces();

    bool s1 = (fvMesh.boundaries()[iBoundary].userName() == "frontAndBack");
    bool s2 =
        (fvMesh.boundaries()[iBoundary].userName() == "frontAndBackPlanes");
    if (!s1 && !s2) {
      for (std::size_t iFace = startFace; iFace < startFace + nBFaces - 1;
           ++iFace) {
        fvMesh.faces()[iFace].patchIndex() = iBoundary;

        std::size_t *iNodes = fvMesh.faces()[iFace].iNodes();
        const std::size_t &nNodes = fvMesh.faces()[iFace].nNodes();

        for (std::size_t iNode = 0; iNode < nNodes; ++iNode) {
          fvMesh.nodes()[iNodes[iNode]].Flag() = 0;
        }
      }
    }
  }
}