#ifndef FACE_H
#define FACE_H

#include <cstddef>

class Face {
public:
  std::size_t &nNodes() { return nNodes_; }
  std::size_t *iNodes() { return iNodes_; }
  void constructNodeList() { iNodes_ = new std::size_t[nNodes_]; }
  std::size_t &iOwner() { return iOwner_; }

private:
  std::size_t nNodes_ = 0;
  std::size_t *iNodes_ = nullptr;
  std::size_t iOwner_ = 0;
};
#endif