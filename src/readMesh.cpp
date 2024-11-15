#include "readMesh.h"
#include <fstream>
#include <iostream>

void readMesh::readOpenFoamMesh(Mesh &fvMesh) {
  if (fvMesh.caseDir().empty()) {
    getDirectory(fvMesh);
  }
  readPointsFile(fvMesh);
  readFacesFile(fvMesh);
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

void readMesh::readPointsFile(Mesh &fvMesh) {
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

void readMesh::readFacesFile(Mesh &fvMesh) {
  std::string facesFileName = fvMesh.caseDir() + "/constant/polyMesh/faces";
  std::ifstream facesFile(facesFileName);
  ifFileOpened(facesFile, facesFileName);
  consumeFileHeader(facesFile);

  // --- Start to read faces data from the file ---
  facesFile >> fvMesh.nFaces();

  std::string line;
  std::getline(facesFile, line); // Consume the rest of the line

  // Consume the left parenthesis for faces
  char dummy;
  facesFile >> dummy;

  fvMesh.constructFaces();

  for (std::size_t i = 0; i < fvMesh.nFaces(); ++i) {
    facesFile >> fvMesh.faces()[i].nNodes();
    facesFile >> dummy; // Consume the left parenthesis

    fvMesh.faces()[i].constructNodeList();

    for (std::size_t j = 0; j < fvMesh.faces()[i].nNodes(); ++j) {
      facesFile >> fvMesh.faces()[i].iNodes()[j];
    }
    facesFile >> dummy; // Consume the right parenthesis
  }

  facesFile.close();
}

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
