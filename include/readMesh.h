#ifndef READ_MESH_H
#define READ_MESH_H

#include "mesh.h"
#include <string>
#include <vector>

void cfdReadOpenFoamMesh(std::vector<Node> &nodes, std::vector<Face> &faces,
                         std::string caseDirectory = "");

#endif