#ifndef NODE_H
#define NODE_H

class Node {
public:
  //   Node(double X, double Y, double Z) : x_(X), y_(Y), z_(Z){};
  double x() { return x_; }
  double y() { return y_; }
  double z() { return z_; }

private:
  double x_ = 0.0;
  double y_ = 0.0;
  double z_ = 0.0;
};
#endif