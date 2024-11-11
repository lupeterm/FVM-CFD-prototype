#ifndef READ_OPENFOAM_MESH_H
#define READ_OPENFOAM_MESH_H

#include <vector>
#include <string>
#include "mesh.h"

void cfdReadOpenFoamMesh
(
    std::vector<Node>& nodes,
    std::vector<Face>& faces,
    std::string caseDirectory = ""
);

#endif