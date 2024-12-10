#ifndef ELEMENT_H
#define ELEMENT_H

#include <cstddef>
#include <vector>

class Element {
public:
  std::size_t &index() { return index_; }
  std::vector<int> &faceSigns() { return faceSigns_; }
  std::vector<std::size_t> &iFaces() { return iFaces_; }
  std::vector<std::size_t> &iNeighbors() { return iNeighbors_; }
  std::size_t &nNeighbors() { return nNeighbors_; }
  std::vector<std::size_t> &iNodes() { return iNodes_; }

private:
  std::size_t index_ = 0;
  std::vector<std::size_t> iFaces_;
  std::vector<std::size_t> iNeighbors_;
  double volume_ = 0;
  std::vector<int> faceSigns_;
  std::size_t nNeighbors_ = 0;
  std::vector<std::size_t> iNodes_;
};

#endif