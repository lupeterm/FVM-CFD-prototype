#ifndef ELEMENT_H
#define ELEMENT_H

#include <cstddef>

class Element {
public:
  std::size_t &index() { return index_; }

private:
  std::size_t index_ = 0;
  std::size_t *iNeighbors_ = nullptr;
  std::size_t *iFaces_ = nullptr;
  std::size_t *iNodes_ = nullptr;
  double volume_ = 0;
  int *faceSign = nullptr;
};

#endif