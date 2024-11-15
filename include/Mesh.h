#ifndef MESH_H
#define MESH_H

#include "Face.h"
#include "Node.h"
#include <cstddef>
#include <string>

class Mesh {
private:
  std::string caseDir_ = "";
  std::size_t nNodes_ = 0;
  std::size_t nFaces_ = 0;
  Node *nodes_ = nullptr;
  Face *faces_ = nullptr;

public:
  Mesh(std::string caseDir) : caseDir_(caseDir) {}
  std::string &caseDir() { return caseDir_; }
  std::size_t &nNodes() { return nNodes_; }
  std::size_t &nFaces() { return nFaces_; }
  Node *nodes() { return nodes_; }
  void constructNodes() { nodes_ = new Node[nNodes_]; }
  Face *faces() { return faces_; }
};
#endif