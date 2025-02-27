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
  std::array<double, 3> &centroid() { return centroid_; }
  std::array<double, 3> &Sf() { return Sf_; }
  double &area() { return area_; }
  std::array<double, 3> &CN() { return CN_; }
  std::array<double, 3> &eCN() { return eCN_; }
  double &gDiff() { return gDiff_; }
  std::array<double, 3> &T() { return T_; }
  double &gf() { return gf_; }
  double &walldist() { return walldist_; }
  std::size_t &iOwnerNeighborCoef() { return iOwnerNeighborCoef_; }
  std::size_t &iNeighborOwnerCoef() { return iNeighborOwnerCoef_; }
  std::size_t &patchIndex() { return patchIndex_; }

private:
  std::size_t nNodes_ = 0;
  std::size_t *iNodes_ = nullptr;
  std::size_t index_ = 0;
  std::size_t iOwner_ = -1;
  std::size_t iNeighbor_ = -1;
  double deltaVol = 0.0;
  std::array<double, 3> centroid_ = {0.0, 0.0, 0.0};
  std::array<double, 3> Sf_ = {0.0, 0.0, 0.0};
  double area_ = 0.0;

  // The distance vector from the owner element centroid to the surface centroid
  std::array<double, 3> CN_ = {0.0, 0.0, 0.0};

  std::array<double, 3> eCN_ = {0.0, 0.0, 0.0};
  double gDiff_ = 0.0;

  // The distance vector joining the centroids of the owner and neighbor
  // elements
  std::array<double, 3> T_ = {0.0, 0.0, 0.0};

  // The geometric factor
  double gf_ = 0.0;

  // The normal distance to the wall of the owner element centroid
  double walldist_ = 0.0;

  std::size_t iOwnerNeighborCoef_ = 0;
  std::size_t iNeighborOwnerCoef_ = 0;
  std::size_t patchIndex_ = 0;
};
#endif