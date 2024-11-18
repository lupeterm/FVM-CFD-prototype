#ifndef NODE_H
#define NODE_H

#include <cstddef>

class Node {
public:
  double &x() { return x_; }
  double &y() { return y_; }
  double &z() { return z_; }
  std::size_t &index() { return index_; }

private:
  double x_ = 0.0;
  double y_ = 0.0;
  double z_ = 0.0;
  std::size_t index_ = 0;
  double *iFaces_ = nullptr;
  double *iElements_ = nullptr;
};
#endif