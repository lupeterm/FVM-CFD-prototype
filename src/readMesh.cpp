#include "readMesh.h"
#include <fstream>
#include <iostream>

void readMesh::readOpenFoamMesh(Mesh &fvMesh) {
  if (fvMesh.caseDir().empty()) {
    getDirectory(fvMesh);
  }
  readPointsFile(fvMesh);
  readFacesFile(fvMesh);
  readOwnersFile(fvMesh);
  readNeighborsFile(fvMesh);
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

void readMesh::readOwnersFile(Mesh &fvMesh) {
  std::string ownersFileName = fvMesh.caseDir() + "/constant/polyMesh/owner";
  std::ifstream ownersFile(ownersFileName);
  ifFileOpened(ownersFile, ownersFileName);
  consumeFileHeader(ownersFile);

  ownersFile >> fvMesh.nOwners();

  std::string line;
  std::getline(ownersFile, line); // Consume the rest of the line

  // Consume the left parenthesis for owners
  char dummy;
  ownersFile >> dummy;

  std::size_t maxOwnerIdx{0};
  std::size_t ownerIdx{0};
  for (std::size_t i = 0; i < fvMesh.nOwners(); ++i) {
    ownersFile >> ownerIdx;
    fvMesh.faces()[i].iOwner() = ownerIdx;
    if (ownerIdx > maxOwnerIdx) {
      maxOwnerIdx = ownerIdx;
    }
  }
  fvMesh.nElements() = maxOwnerIdx + 1;

  ownersFile.close();
}

void readMesh::readNeighborsFile(Mesh &fvMesh) {
  std::string neighborsFileName =
      fvMesh.caseDir() + "/constant/polyMesh/neighbour";
  std::ifstream neighborsFile(neighborsFileName);
  ifFileOpened(neighborsFile, neighborsFileName);
  consumeFileHeader(neighborsFile);

  neighborsFile >> fvMesh.nNeighbors();
}
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
