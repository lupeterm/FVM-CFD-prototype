#ifndef NODE_H
#define NODE_H

#include <cstddef>

class Node {
public:
  std::size_t &index() { return index_; }
  std::vector<std::size_t> &iFaces() { return iFaces_; }
  std::vector<std::size_t> &iElements() { return iElements_; }
  std::vector<double> &centroid() { return centroid_; }

private:
  std::vector<double> centroid_ = {0.0, 0.0, 0.0};
  std::size_t index_ = 0;
  std::vector<std::size_t> iFaces_;
  std::vector<std::size_t> iElements_;
};
#endif