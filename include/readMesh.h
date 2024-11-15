#ifndef READ_MESH_H
#define READ_MESH_H

#include "mesh.h"
#include <string>
#include <vector>

class readMesh {
public:
  readMesh();

  void readOpenFoamMesh(Mesh &fvMesh);

  // Private data members
private:
  std::string caseDir;

  // Private member functions
private:
  void readPointsFle();
  void readFacesFile();
  void readOwnersFile();
  void readNeighborsFile();
  void consumeFileHeader();
};
// void cfdReadOpenFoamMesh(std::vector<Node> &nodes, std::vector<Face> &faces,
//                          std::string caseDirectory = "");

#endif