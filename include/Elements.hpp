#ifndef ELEMENT_HPP
#define ELEMENT_HPP

#include <array>
#include <cstddef>
#include <vector>

class Element {
public:
  std::size_t &index() { return index_; }
  std::vector<int> &faceSigns() { return faceSigns_; }
  std::vector<std::size_t> &iFaces() { return iFaces_; }

  // Neighbor element indices
  std::vector<std::size_t> &iNeighbors() { return iNeighbors_; }

  std::size_t &nNeighbors() { return nNeighbors_; }
  std::vector<std::size_t> &iNodes() { return iNodes_; }
  double &volume() { return volume_; }
  double &oldVolume() { return oldVolume_; }
  std::array<double, 3> &centroid() { return centroid_; }

private:
  std::size_t index_ = 0;
  std::vector<std::size_t> iFaces_;
  std::vector<std::size_t> iNeighbors_;
  std::vector<int> faceSigns_;
  std::size_t nNeighbors_ = 0;
  std::vector<std::size_t> iNodes_;
  double volume_ = 0.0;
  double oldVolume_ = 0.0;
  std::array<double, 3> centroid_ = {0.0, 0.0, 0.0};
};

#endif