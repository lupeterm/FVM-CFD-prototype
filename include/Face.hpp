#ifndef FACE_HPP
#define FACE_HPP

#include <array>
#include <cstddef>
#include <vector>

class Face {
public:
  std::size_t &nNodes() { return nNodes_; }
  std::size_t *iNodes() { return iNodes_; }
  void allocateNodeList() { iNodes_ = new std::size_t[nNodes_]; }
  std::size_t &index() { return index_; }
  int &iOwner() { return iOwner_; }
  int &iNeighbor() { return iNeighbor_; }
  std::array<double, 3> &centroid() { return centroid_; }
  std::array<double, 3> &Sf() { return Sf_; }
  double &area() { return area_; }
  double &magCN() { return magCN_; }
  std::array<double, 3> &CN() { return CN_; }
  std::array<double, 3> &eCN() { return eCN_; }
  double &gDiff() { return gDiff_; }
  std::array<double, 3> &T() { return T_; }
  double &gf() { return gf_; }
  double &walldist() { return walldist_; }
  std::size_t &iOwnerNeighborCoef() { return iOwnerNeighborCoef_; }
  std::size_t &iNeighborOwnerCoef() { return iNeighborOwnerCoef_; }
  int &patchIndex() { return patchIndex_; }
  ~Face() { delete[] iNodes_; }

private:
  std::size_t nNodes_ = 0;
  std::size_t *iNodes_ = nullptr;
  std::size_t index_ = 0;
  int iOwner_ = -1;
  int iNeighbor_ = -1;
  double deltaVol = 0.0;
  std::array<double, 3> centroid_ = {0.0, 0.0, 0.0};
  std::array<double, 3> Sf_ = {0.0, 0.0, 0.0};
  double area_ = 0.0;

  // The distance between the owner element centroid and the neighbor element
  // centroid for interior faces
  // The distance between the owner element centroid and the wall for boundary
  // faces
  double magCN_ = 0.0;

  // The distance vector from the owner element centroid to the neighbor element
  // centroid
  std::array<double, 3> CN_ = {0.0, 0.0, 0.0};

  // The unit vector from the owner element centroid to the neighbor element
  std::array<double, 3> eCN_ = {0.0, 0.0, 0.0};

  double gDiff_ = 0.0;

  std::array<double, 3> T_ = {0.0, 0.0, 0.0};

  // The geometric factor
  double gf_ = 0.0;

  // The normal distance to the wall of the owner element centroid
  double walldist_ = 0.0;

  std::size_t iOwnerNeighborCoef_ = 0;
  std::size_t iNeighborOwnerCoef_ = 0;
  int patchIndex_ = -1;
};
#endif