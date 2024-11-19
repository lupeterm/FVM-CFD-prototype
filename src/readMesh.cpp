#include "readMesh.h"
#include <fstream>
#include <iostream>
#include <limits>

void readMesh::readOpenFoamMesh(Mesh &fvMesh) {
  if (fvMesh.caseDir().empty()) {
    getDirectory(fvMesh);
  }
  readPointsFile(fvMesh);
  readFacesFile(fvMesh);
  readOwnersFile(fvMesh);
  readNeighborsFile(fvMesh);
  readBoundaryFile(fvMesh);
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

void readMesh::discardLines(std::ifstream &file, std::size_t nLines) {
  std::string line;
  for (int i = 0; i < nLines; ++i) {
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}

void readMesh::readPointsFile(Mesh &fvMesh) {
  std::string pointsFileName = fvMesh.caseDir() + "/constant/polyMesh/points";
  std::ifstream pointsFile(pointsFileName);
  ifFileOpened(pointsFile, pointsFileName);

  // Discard the file header
  discardLines(pointsFile, 18);

  // --- Start to read points data from the file ---
  pointsFile >> fvMesh.nNodes();

  // Discard the rest of the line and the next line
  discardLines(pointsFile, 2);

  fvMesh.constructNodes();

  // Read x, y, z coordinates to mesh nodes
  for (std::size_t i = 0; i < fvMesh.nNodes(); ++i) {
    pointsFile.ignore(1); // Discard the left parenthesis

    pointsFile >> fvMesh.nodes()[i].x() >> fvMesh.nodes()[i].y() >>
        fvMesh.nodes()[i].z();

    // Discard the rest of the line
    pointsFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    fvMesh.nodes()[i].index() = i;
  }

  pointsFile.close();
}

void readMesh::readFacesFile(Mesh &fvMesh) {
  std::string facesFileName = fvMesh.caseDir() + "/constant/polyMesh/faces";
  std::ifstream facesFile(facesFileName);
  ifFileOpened(facesFile, facesFileName);

  // Discard the file header
  discardLines(facesFile, 18);

  // --- Start to read faces data from the file ---
  facesFile >> fvMesh.nFaces();

  // Discard the rest of the line and the next line
  discardLines(facesFile, 2);

  fvMesh.constructFaces();

  for (std::size_t i = 0; i < fvMesh.nFaces(); ++i) {
    facesFile >> fvMesh.faces()[i].nNodes();
    facesFile.ignore(1); // Discard the left parenthesis

    fvMesh.faces()[i].constructNodeList();

    for (std::size_t j = 0; j < fvMesh.faces()[i].nNodes(); ++j) {
      facesFile >> fvMesh.faces()[i].iNodes()[j];
    }
    facesFile.ignore(1); // Discard the right parenthesis

    fvMesh.faces()[i].index() = i;
  }

  facesFile.close();
}

void readMesh::readOwnersFile(Mesh &fvMesh) {
  std::string ownersFileName = fvMesh.caseDir() + "/constant/polyMesh/owner";
  std::ifstream ownersFile(ownersFileName);
  ifFileOpened(ownersFile, ownersFileName);

  // Discard the file header
  discardLines(ownersFile, 18);

  ownersFile >> fvMesh.nOwners();

  // Discard the rest of the line and the next line
  discardLines(ownersFile, 2);

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

  // Discard the file header
  discardLines(neighborsFile, 18);

  std::size_t nNeighbors{0};
  neighborsFile >> nNeighbors;

  // Discard the rest of the line and the next line
  discardLines(neighborsFile, 2);

  for (std::size_t i = 0; i < nNeighbors; ++i) {
    neighborsFile >> fvMesh.faces()[i].iNeighbor();
  }

  fvMesh.nInteriorFaces() = nNeighbors;
  neighborsFile.close();
}

void readMesh::readBoundaryFile(Mesh &fvMesh) {
  std::string boundaryFileName =
      fvMesh.caseDir() + "/constant/polyMesh/boundary";

  std::ifstream boundaryFile(boundaryFileName);
  ifFileOpened(boundaryFile, boundaryFileName);

  // Discard the file header
  discardLines(boundaryFile, 17);

  boundaryFile >> fvMesh.nBoundaries();
  fvMesh.nPatches() = fvMesh.nBoundaries();

  // Discard the rest of the line and the next line
  discardLines(boundaryFile, 2);

  fvMesh.constructBoundaries();

  for (std::size_t i = 0; i < fvMesh.nBoundaries(); ++i) {

    boundaryFile >> fvMesh.boundaries()[i].userName();
    fvMesh.boundaries()[i].index() = i;

    discardLines(boundaryFile, 2);
    std::string token{""};
    boundaryFile >> token;
    while (token.compare("}") != 0) {

      if (token.compare("type") == 0) {
        boundaryFile >> fvMesh.boundaries()[i].type();
        fvMesh.boundaries()[i].type().pop_back();

      } else if (token.compare("nFaces") == 0) {
        boundaryFile >> fvMesh.boundaries()[i].nFaces();

      } else if (token.compare("startFace") == 0) {
        boundaryFile >> fvMesh.boundaries()[i].startFace();
      }
      discardLines(boundaryFile);
      boundaryFile >> token;
    }
  }
  boundaryFile.close();
}
