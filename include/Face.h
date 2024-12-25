#ifndef FACE_H
#define FACE_H

#include <array>
#include <cstddef>
#include <vector>

class Face {
public:
  std::size_t &nNodes() { return nNodes_; }
  std::size_t *iNodes() { return iNodes_; }
  void allocateNodeList() { iNodes_ = new std::size_t[nNodes_]; }
  std::size_t &index() { return index_; }
  std::size_t &iOwner() { return iOwner_; }
  std::size_t &iNeighbor() { return iNeighbor_; }
  // std::vector<double> &centroid() { return centroid_; }
  std::array<double, 3> &centroid() { return centroid_; }
  // std::vector<double> &Sf() { return Sf_; }
  std::array<double, 3> &Sf() { return Sf_; }
  double &area() { return area_; }

private:
  std::size_t nNodes_ = 0;
  std::size_t *iNodes_ = nullptr;
  std::size_t index_ = 0;
  std::size_t iOwner_ = -1;
  std::size_t iNeighbor_ = -1;
  double deltaVol = 0.0;
  // std::vector<double> centroid_;
  // std::vector<double> Sf_;
  std::array<double, 3> centroid_ = {0.0, 0.0, 0.0};
  std::array<double, 3> Sf_ = {0.0, 0.0, 0.0};
  double area_ = 0.0;
};
#endif