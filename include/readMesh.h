#ifndef READ_MESH_H
#define READ_MESH_H

#include "Mesh.h"
#include <string>

class readMesh {
public:
  readMesh(std::string &caseDir);

  void readOpenFoamMesh(Mesh &fvMesh);

  // Private data members
private:
  /// @brief case directory
  std::string caseDir_;

  // Private member functions
private:
  void readPointsFle();
  void readFacesFile();
  void readOwnersFile();
  void readNeighborsFile();
  void consumeFileHeader();
};
#endif