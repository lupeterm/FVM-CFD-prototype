#ifndef PROCESS_MESH
#define PROCESS_MESH

#include "Mesh.h"

class processMesh {
public:
  void processOpenFoamMesh(Mesh &fvMesh);

private:
  void processBasicFaceGeometry(Mesh &fvMesh);
};

#endif