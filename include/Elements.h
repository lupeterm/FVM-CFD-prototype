#ifndef ELEMENT_H
#define ELEMENT_H

#include <cstddef>
#include <vector>

class Element {
public:
  std::size_t &index() { return index_; }
  int *faceSigns() { return faceSigns_; }
  // void allocate_iNodes() { iNodes_ = new std::size_t[maxNodes_]; }
  // void allocate_faceSigns() { faceSigns_ = new int[maxFaces_]; }
  std::vector<std::size_t> &iFaces() { return iFaces_; }
  std::vector<std::size_t> &iNeighbors() { return iNeighbors_; }
  std::size_t &nNeighbors() { return nNeighbors_; }

private:
  std::size_t index_ = 0;
  // std::size_t *iNodes_ = nullptr;
  std::vector<std::size_t> iFaces_;
  std::vector<std::size_t> iNeighbors_;
  double volume_ = 0;
  int *faceSigns_ = nullptr;
  // std::size_t maxFaces_ = 6;
  // std::size_t maxNodes_ = 8;
  std::size_t nNeighbors_ = 0;
};

#endif