#ifndef MESH_H
#define MESH_H

#include "Boundary.hpp"
#include "Elements.hpp"
#include "Face.hpp"
#include "Node.hpp"
#include <cstddef>
#include <string>

class Mesh {
public:
  Mesh(std::string caseDir) : caseDir_(caseDir) {}
  std::string &caseDir() { return caseDir_; }
  std::size_t &nNodes() { return nNodes_; }
  std::size_t &nFaces() { return nFaces_; }
  std::size_t &nOwners() { return nOwners_; }
  std::size_t &nElements() { return nElements_; }
  std::size_t &nInteriorFaces() { return nInteriorFaces_; }
  std::size_t &nBoundaries() { return nBoundaries_; }
  std::size_t &nPatches() { return nPatches_; }
  Node *nodes() { return nodes_; }
  void allocateNodes() { nodes_ = new Node[nNodes_]; }
  Face *faces() { return faces_; }
  void allocateFaces() { faces_ = new Face[nFaces_]; }
  Boundary *boundaries() { return boundaries_; }
  void allocateBoundaries() { boundaries_ = new Boundary[nBoundaries_]; }
  Element *elements() { return elements_; }
  void allocateElements() { elements_ = new Element[nElements_]; }
  std::size_t &nBElements() { return nBElements_; }
  std::size_t &nBFaces() { return nBFaces_; }

private:
  std::string caseDir_ = "";
  std::size_t nNodes_ = 0;
  std::size_t nFaces_ = 0;
  std::size_t nOwners_ = 0;
  std::size_t nElements_ = 0;
  std::size_t nInteriorFaces_ = 0;
  std::size_t nBoundaries_ = 0;
  std::size_t nPatches_ = 0;
  Node *nodes_ = nullptr;
  Face *faces_ = nullptr;
  Boundary *boundaries_ = nullptr;
  Element *elements_ = nullptr;
  std::size_t nBElements_ = 0;
  std::size_t nBFaces_ = 0;
};
#endif