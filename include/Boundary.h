#ifndef BOUNDARY_H
#define BOUNDARY_H
#include <string>

class Boundary {
public:
  std::string &userName() { return userName_; }

private:
  std::string userName_ = "";
};
#endif