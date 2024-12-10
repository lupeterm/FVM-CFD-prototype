#ifndef NODE_H
#define NODE_H

#include <cstddef>

class Node {
public:
  double &x() { return x_; }
  double &y() { return y_; }
  double &z() { return z_; }
  std::size_t &index() { return index_; }
  std::vector<std::size_t> &iFaces() { return iFaces_; }
  std::vector<std::size_t> &iElements() { return iElements_; }

private:
  double x_ = 0.0;
  double y_ = 0.0;
  double z_ = 0.0;
  std::size_t index_ = 0;
  std::vector<std::size_t> iFaces_;
  std::vector<std::size_t> iElements_;
};
#endif