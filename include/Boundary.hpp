#ifndef BOUNDARY_HPP
#define BOUNDARY_HPP
#include <string>

class Boundary {
public:
  std::string &userName() { return userName_; }
  std::size_t &index() { return index_; }
  std::string &type() { return type_; }
  std::size_t &nFaces() { return nFaces_; }
  std::size_t &startFace() { return startFace_; }

private:
  std::string userName_ = "";
  std::size_t index_ = 0;
  std::string type_ = "";
  std::size_t nFaces_ = 0;
  std::size_t startFace_ = 0;
};
#endif