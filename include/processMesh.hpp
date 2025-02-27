#ifndef PROCESS_MESH
#define PROCESS_MESH

#include "Mesh.hpp"

class processMesh {
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