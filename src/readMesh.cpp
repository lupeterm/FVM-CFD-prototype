#include "readMesh.h"
#include <fstream>
#include <iostream>

// // Forward declaration
// std::string getDirectory();
// void readPoints(const std::string &pointsFile, std::vector<Node> &nodes);
// void readFaces(const std::string &facesFile, std::vector<Face> &faces);
// void readOwners(const std::string &ownerFile, std::vector<Face> &faces);
// void cfdReadOpenFoamMesh(std::vector<Node> &nodes, std::vector<Face> &faces,
//                          std::string caseDirectory);

// readMesh::readMesh(std::string &caseDir) : caseDir_(caseDir) {}

void readMesh::readOpenFoamMesh(Mesh &fvMesh) {
  if (fvMesh.caseDir().empty()) {
    getDirectory(fvMesh);
  }
  readPointsFle(fvMesh);
}

void readMesh::getDirectory(Mesh &fvMesh) {
  std::cout << "Enter the case directory: ";
  std::getline(std::cin, fvMesh.caseDir());
}

void readMesh::ifFileOpened(const std::ifstream &file,
                            const std::string &fileName) {
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << fileName << std::endl;
  }
}

void readMesh::consumeFileHeader(std::ifstream &file) {
  std::string line;
  for (int i = 0; i < 18; ++i) {
    std::getline(file, line);
  }
}

void readMesh::readPointsFle(Mesh &fvMesh) {
  std::string pointsFileName = fvMesh.caseDir() + "/constant/polyMesh/points";
  std::ifstream pointsFile(pointsFileName);
  ifFileOpened(pointsFile, pointsFileName);
  consumeFileHeader(pointsFile);

  // --- Start to read points data from the file ---
  pointsFile >> fvMesh.nNodes();

  std::string line;
  std::getline(pointsFile, line); // Consume the rest of the line
  std::getline(pointsFile, line); // To consume the next line

  fvMesh.constructNodes();

  // Read x, y, z coordinates to mesh nodes
  for (std::size_t i = 0; i < fvMesh.nNodes(); ++i) {
    char dummy;
    pointsFile >> dummy; // To consume the left parenthesis

    pointsFile >> fvMesh.nodes()[i].x() >> fvMesh.nodes()[i].y() >>
        fvMesh.nodes()[i].z();

    pointsFile >> dummy; // To consume the right parenthesis
  }

  pointsFile.close();
}

// void readFaces(const std::string &facesFile, std::vector<Face> &faces) {
//   std::ifstream file(facesFile);
//   if (!file.is_open()) {
//     std::cerr << "Error opening file: " << facesFile << std::endl;
//     return;
//   }

//   // Consume the first 18 lines
//   std::string line;
//   for (int i = 0; i < 18; ++i) {
//     std::getline(file, line);
//   }

//   // Read the number of faces
//   int numberOfFaces;
//   file >> numberOfFaces;
//   std::getline(file, line); // Consume the rest of the line

//   // Consume the left parenthesis for faces
//   char dummy;
//   file >> dummy;

//   faces.resize(numberOfFaces);

//   // Read each face
//   for (int i = 0; i < numberOfFaces; ++i) {
//     int numberOfPoints{0};
//     file >> numberOfPoints;
//     file >> dummy; // Consume the left parenthesis

//     faces[i].iNodes.resize(numberOfPoints);
//     for (int j = 0; j < numberOfPoints; ++j) {
//       file >> faces[i].iNodes[j];
//     }
//     file >> dummy; // Consume the right parenthesis
//     faces[i].index = i;
//     faces[i].iOwner = -1;
//     faces[i].iNeighbor = -1;
//   }

//   file.close();
// }

// void readOwners(const std::string &ownerFile, std::vector<Face> &faces) {
//   std::ifstream file(ownerFile);
//   if (!file.is_open()) {
//     std::cerr << "Error opening file: " << ownerFile << std::endl;
//     return;
//   }

//   // Consume the first 18 lines
//   std::string line;
//   for (int i = 0; i < 18; ++i) {
//     std::getline(file, line);
//   }

//   // Read the number of faces
//   int numberOfOwners;
//   file >> numberOfOwners;
//   std::getline(file, line); // Consume the rest of the line

//   // Consume the left parenthesis for owners
//   char dummy;
//   file >> dummy;

//   int numberOfElements{0};

//   // -- Test ---
//   std::cout << "Number of owners:" << numberOfOwners << std::endl;

//   int OwnerIndex{0};
//   int maxOwnerIndex{0};
//   for (int i = 0; i < numberOfOwners; ++i) {

//     file >> OwnerIndex;
//     faces[i].iOwner = OwnerIndex;

//     if (OwnerIndex > maxOwnerIndex) {
//       maxOwnerIndex = OwnerIndex;
//     }
//     // >> faces[i].iOwner;
//   }

//   // number of elements = the largest owner index + 1
//   numberOfElements = maxOwnerIndex + 1;

//   // -- Test ---
//   std::cout << "Number of elements:" << numberOfElements << std::endl;

//   file.close();

//   // return maxOwnerIndex;
// }

// void cfdReadOpenFoamMesh(std::vector<Node> &nodes, std::vector<Face> &faces,
//                          std::string caseDirectory) {
//   if (caseDirectory.empty()) {
//     caseDirectory = getDirectory();
//   }

//   std::string pointsFile = caseDirectory + "/constant/polyMesh/points";
//   std::string facesFile = caseDirectory + "/constant/polyMesh/faces";
//   std::string ownerFile = caseDirectory + "/constant/polyMesh/owner";
//   std::string neighbourFile = caseDirectory + "/constant/polyMesh/neighbour";
//   std::string boundaryFile = caseDirectory + "/constant/polyMesh/boundary";

//   // readPoints(pointsFile, nodes);
//   // readFaces(facesFile, faces);
//   // readOwners(ownerFile, faces);

//   // return numberOfElement;
// }
