#ifndef FACE_H
#define FACE_H

#include <cstddef>

class Face {
public:
  std::size_t &nNodes() { return nNodes_; }
  std::size_t *iNodes() { return iNodes_; }
  void allocateNodeList() { iNodes_ = new std::size_t[nNodes_]; }
  std::size_t &index() { return index_; }
  std::size_t &iOwner() { return iOwner_; }
  std::size_t &iNeighbor() { return iNeighbor_; }

private:
  std::size_t nNodes_ = 0;
  std::size_t *iNodes_ = nullptr;
  std::size_t index_ = 0;
  std::size_t iOwner_ = -1;
  std::size_t iNeighbor_ = -1;
  double deltaVol = 0.0;
};
#endif