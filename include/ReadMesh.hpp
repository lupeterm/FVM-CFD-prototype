#ifndef READ_MESH_HPP
#define READ_MESH_HPP

#include "Mesh.hpp"
#include "ProcessMesh.hpp"
#include <string>

class ReadMesh {
public:
  void readOpenFoamMesh(Mesh &fvMesh);

private:
  ProcessMesh MeshProcessor;
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