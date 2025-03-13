#ifndef NODE_HPP
#define NODE_HPP

#include <array>
#include <cstddef>
#include <vector>

class Node {
public:
  std::size_t &index() { return index_; }
  std::vector<std::size_t> &iFaces() { return iFaces_; }
  std::vector<std::size_t> &iElements() { return iElements_; }
  std::array<double, 3> &centroid() { return centroid_; }

  // Return flag which is used to sort boundary nodes from interior nodes
  int &Flag() { return Flag_; }

private:
  std::array<double, 3> centroid_ = {0.0, 0.0, 0.0};
  std::size_t index_ = 0;
  std::vector<std::size_t> iFaces_;
  std::vector<std::size_t> iElements_;
  int Flag_ = 0;
};
#endif