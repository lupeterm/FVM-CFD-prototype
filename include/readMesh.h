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
  // private:
public:
  void getDirectory();
  void ifFileOpened(const std::ifstream &file, const std::string &fileName);
  void consumeFileHeader(std::ifstream &file);
  void readPointsFle();
  void readFacesFile();
  void readOwnersFile();
  void readNeighborsFile();
};
#endif