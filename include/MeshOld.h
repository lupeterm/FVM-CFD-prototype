#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>

struct Node {
  std::vector<double> centroid;
  int index;
  std::vector<int> iFaces;
  std::vector<int> iElements;
};

struct Face {
  std::vector<int> iNodes;
  int index;
  int iOwner;
  int iNeighbor;
};

class Mesh {
private:
  std::string caseDirectory_;
  // int numberofNodes;
  std::vector<Node> &nodes_;
  std::vector<Face> &faces_;
  // int numberOfElement_;

public:
  Mesh(std::string caseDir, std::vector<Node> &points, std::vector<Face> &faces)
      : caseDirectory_(caseDir), nodes_(points), faces_(faces) {}

  std::vector<Node> &nodes() { return nodes_; }
  std::vector<Face> &faces() { return faces_; }
  // int numberOfElement() { return numberOfElement_; }
};

#endif