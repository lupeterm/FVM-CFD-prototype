#ifndef MESH_H
#define MESH_H

#include "Node.h"
#include <cstddef>
#include <string>
// #include <vector>

class Mesh {
private:
  std::string caseDir_ = "";
  std::size_t nNodes_ = 0;
  Node *nodes_ = nullptr;
  // std::string caseDirectory_;
  // // int numberofNodes;
  // std::vector<Node> &nodes_;
  // std::vector<Face> &faces_;
  // // int numberOfElement_;

public:
  Mesh(std::string caseDir) : caseDir_(caseDir) {}
  std::string &caseDir() { return caseDir_; }
  std::size_t &nNodes() { return nNodes_; }
  Node *nodes() { return nodes_; }
  void constructNodes() { nodes_ = new Node[nNodes_]; }
  // Mesh(std::string caseDir, std::vector<Node> &points, std::vector<Face>
  // &faces)
  //     : caseDirectory_(caseDir), nodes_(points), faces_(faces) {}

  // std::vector<Node> &nodes() { return nodes_; }
  // std::vector<Face> &faces() { return faces_; }
  // // int numberOfElement() { return numberOfElement_; }
};
#endif