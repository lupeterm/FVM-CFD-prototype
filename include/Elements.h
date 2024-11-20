#ifndef ELEMENT_H
#define ELEMENT_H

#include <cstddef>

class Element {
public:
  std::size_t &index() { return index_; }
  std::size_t *iNeighbors() { return iNeighbors_; }
  std::size_t *iFaces() { return iFaces_; }
  int *faceSigns() { return faceSigns_; }
  void allocate_iNeighbors() { iNeighbors_ = new std::size_t[maxFaces_]; }
  void allocate_iFaces() { iFaces_ = new std::size_t[maxFaces_]; }
  void allocate_iNodes() { iNodes_ = new std::size_t[maxNodes_]; }
  void allocate_faceSigns() { faceSigns_ = new int[maxFaces_]; }

private:
  std::size_t index_ = 0;
  std::size_t *iNeighbors_ = nullptr;
  std::size_t *iFaces_ = nullptr;
  std::size_t *iNodes_ = nullptr;
  double volume_ = 0;
  int *faceSigns_ = nullptr;
  std::size_t maxFaces_ = 6;
  std::size_t maxNodes_ = 8;
};

#endif