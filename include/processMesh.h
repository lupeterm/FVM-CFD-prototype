#ifndef PROCESS_MESH
#define PROCESS_MESH

#include "Mesh.h"

class processMesh {
public:
  void processOpenFoamMesh(Mesh &fvMesh);

private:
  // Compute geometric center of each face
  void processBasicFaceGeometry(Mesh &fvMesh);

  // Compute volume and centroid of each element
  void computeElementVolumeAndCentroid(Mesh &fvMesh);
};

#endif