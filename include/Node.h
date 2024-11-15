#ifndef NODE_H
#define NODE_H

class Node {
public:
  double &x() { return x_; }
  double &y() { return y_; }
  double &z() { return z_; }

private:
  double x_ = 0.0;
  double y_ = 0.0;
  double z_ = 0.0;
};
#endif