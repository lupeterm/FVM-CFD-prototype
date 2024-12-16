#ifndef READ_MESH_H
#define READ_MESH_H

#include "Mesh.h"
// #include "processMesh.h"
#include <string>

class readMesh {
public:
  void readOpenFoamMesh(Mesh &fvMesh);

private:
  void getDirectory(Mesh &fvMesh);
  void ifFileOpened(const std::ifstream &file, const std::string &fileName);
  void discardLines(std::ifstream &file, std::size_t nLines = 1);
  void readPointsFile(Mesh &fvMesh);
  void readFacesFile(Mesh &fvMesh);
  void readOwnersFile(Mesh &fvMesh);
  void readNeighborsFile(Mesh &fvMesh);
  void readBoundaryFile(Mesh &fvMesh);
  void constructElements(Mesh &fvMesh);
  void setupNodeConnectivities(Mesh &fvMesh);
};
#endif