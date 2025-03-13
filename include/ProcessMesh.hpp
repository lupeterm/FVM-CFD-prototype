#ifndef PROCESS_MESH_HPP
#define PROCESS_MESH_HPP

#include "Mesh.hpp"

class ProcessMesh {
public:
  void processOpenFoamMesh(Mesh &fvMesh);

private:
  // Compute geometric center of each face
  void processBasicFaceGeometry(Mesh &fvMesh);

  // Compute volume and centroid of each element
  void computeElementVolumeAndCentroid(Mesh &fvMesh);

  // Process secondary face geometry
  void processSecondaryFaceGeometry(Mesh &fvMesh);

  // Create a flag to sort boundary nodes from interior nodes
  void sortBoundaryNodesFromInteriorNodes(Mesh &fvMesh);
};

#endif