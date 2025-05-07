#ifndef MESH_HPP
#define MESH_HPP

#include "Boundary.hpp"
#include "Elements.hpp"
#include "Face.hpp"
#include "Node.hpp"
#include <cstddef>
#include <string>

class Mesh {
public:
  Mesh() = default;
  Mesh(std::string caseDir) : caseDir_(caseDir) {}
  std::string &caseDir() { return caseDir_; }
  std::size_t &nNodes() { return nNodes_; }
  std::size_t &nFaces() { return nFaces_; }
  std::size_t &nOwners() { return nOwners_; }
  std::size_t &nElements() { return nElements_; }
  std::size_t &nInteriorFaces() { return nInteriorFaces_; }
  std::size_t &nBoundaries() { return nBoundaries_; }
  std::size_t &nPatches() { return nPatches_; }
  std::vector<Node> &nodes() { return nodes_; }
  std::vector<Face> &faces() { return faces_; }
  std::vector<Boundary> &boundaries() { return boundaries_; }
  std::vector<Element> &elements() { return elements_; }
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
  std::vector<Node> nodes_;
  std::vector<Face> faces_;
  std::vector<Boundary> boundaries_;
  std::vector<Element> elements_;
  std::size_t nBElements_ = 0;
  std::size_t nBFaces_ = 0;
};
#endif