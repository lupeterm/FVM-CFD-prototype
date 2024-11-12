#include <iostream>
#include <fstream>
#include "readOpenFoamMesh.h"

// Forward declaration
std::string getDirectory();
void readPoints(const std::string& pointsFile, std::vector<Node>& nodes);
void readFaces(const std::string& facesFile, std::vector<Face>& faces);
void cfdReadOpenFoamMesh(std::vector<Node>& nodes, std::vector<Face>& faces, std::string caseDirectory);

std::string getDirectory() {
    std::string caseDirectory;
    std::cout << "Enter the case directory: ";
    std::getline(std::cin, caseDirectory);
    return caseDirectory;
}

void readPoints
(
    const std::string& pointsFile,
    std::vector<Node>& nodes
)
{
    std::ifstream file(pointsFile);
    if(!file.is_open())
    {
        std::cerr << "Error opening file: " << pointsFile << std::endl;
        return;
    }
    
    // Consume the first 18 lines of the points file
    std::string line;
    for (int i = 0; i < 18; ++i)
    {
        std::getline(file, line);
    }

    int numberOfPoins(0);
    file >> numberOfPoins;
       
    std::getline(file, line); // Consume the rest of the line
    std::getline(file, line); // To consume the next line

    nodes.resize(numberOfPoins);
    for (int i = 0; i < numberOfPoins; ++i)
    {
        char dummy;
        file >> dummy; // To consume the left parenthesis
        double x(0.0), y(0.0), z(0.0);
        file >> x >> y >> z;
        file >> dummy; // To consume the right parenthesis
        
        nodes[i].centroid = {x, y, z};
        nodes[i].index = i;
        nodes[i].iFaces = {};
        nodes[i].iElements = {};
    }

    file.close();
}

void readFaces
(
    const std::string& facesFile,
    std::vector<Face>& faces
)
{
    std::ifstream file(facesFile);
    if (!file.is_open())
    {
        std::cerr << "Error opening file: " << facesFile << std::endl;
        return;
    }
    
    // Consume the first 18 lines
    std::string line;
    for (int i = 0; i < 18; ++i)
    {
        std::getline(file, line);
    }

    // Read the number of faces
    int numberOfFaces;
    file >> numberOfFaces;
    std::getline(file, line); // Consume the rest of the line

    // Consume the left parenthesis for faces
    char dummy;
    file >> dummy;

    faces.resize(numberOfFaces);

    // Read each face
    for (int i = 0; i < numberOfFaces; ++i)
    {
        int numberOfPoints{0};
        file >> numberOfPoints;
        file >> dummy; // Consume the left parenthesis

        faces[i].iNodes.resize(numberOfPoints);
        for (int j = 0; j < numberOfPoints; ++j)
        {
            file >> faces[i].iNodes[j];
        }
        file >> dummy; // Consume the right parenthesis
        faces[i].index = i;
        faces[i].iOwner = -1;
        faces[i].iNeighbor = -1;
    }

    file.close();
}

void cfdReadOpenFoamMesh
(
    std::vector<Node>& nodes,
    std::vector<Face>& faces,
    std::string caseDirectory
)
{
    if (caseDirectory.empty()) {
        caseDirectory = getDirectory();
    }
    
    std::string pointsFile = caseDirectory + "/constant/polyMesh/points";
    std::string facesFile = caseDirectory + "/constant/polyMesh/faces";
    std::string ownerFile = caseDirectory + "/constant/polyMesh/owner";
    std::string neighbourFile = caseDirectory + "/constant/polyMesh/neighbour";
    std::string boundaryFile = caseDirectory + "/constant/polyMesh/boundary";
    
    readPoints(pointsFile, nodes);
    readFaces(facesFile, faces);
}
