#include <vector>
#include <string>
#include <iostream>
#include <iomanip>
#include "mesh.h"
#include "readOpenFoamMesh.h"

int main(int argc, char* argv[]) {

    std::string caseDirectory(argv[1]);
    std::vector<Node> nodes;
    std::vector<Face> faces;
    cfdReadOpenFoamMesh(nodes, faces, caseDirectory);
    Mesh fvMesh{caseDirectory, nodes, faces};
    
    // ------------------ Test readPoints----------------------
    int precision = 10;
    for (int i = 0; i < 3; ++i)
    { 
        std::cout << std::fixed << std::setprecision(precision) << 
                    "(" << fvMesh.nodes()[i].centroid[0] << " " 
                        << fvMesh.nodes()[i].centroid[1] << " " 
                        << fvMesh.nodes()[i].centroid[2] << ")" << std::endl;
    }

    // ------------------ Test readFaces----------------------
    for (int i = 0; i < 3; ++i)
    { 
        int numberOfPoints = fvMesh.faces()[i].iNodes.size();

        std::cout << "(";

        for (int j = 0; j < numberOfPoints; ++j)
        {
            std::cout << fvMesh.faces()[i].iNodes[j];
            
            if (j < numberOfPoints-1)
            {
                std::cout << " ";
            }
            else
            {
                std::cout << ")" << std::endl;;
            }
        }
    }

    return 0;
}
