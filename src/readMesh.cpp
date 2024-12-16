#include "readMesh.h"
#include <algorithm>
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
  constructElements(fvMesh);
  setupNodeConnectivities(fvMesh);
  MeshProcessor.processBasicFaceGeometry(fvMesh);
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

  fvMesh.allocateNodes();

  // Read x, y, z coordinates to mesh nodes
  for (std::size_t i = 0; i < fvMesh.nNodes(); ++i) {
    pointsFile.ignore(1); // Discard the left parenthesis

    pointsFile >> fvMesh.nodes()[i].centroid()[0] >>
        fvMesh.nodes()[i].centroid()[1] >> fvMesh.nodes()[i].centroid()[2];

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

  fvMesh.allocateFaces();

  for (std::size_t i = 0; i < fvMesh.nFaces(); ++i) {
    facesFile >> fvMesh.faces()[i].nNodes();
    facesFile.ignore(1); // Discard the left parenthesis

    fvMesh.faces()[i].allocateNodeList();

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

  fvMesh.allocateBoundaries();

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

void readMesh::constructElements(Mesh &fvMesh) {
  fvMesh.allocateElements();

  const std::size_t nElements = fvMesh.nElements();
  for (std::size_t i = 0; i < nElements; ++i) {
    fvMesh.elements()[i].index() = i;
  }

  const std::size_t nInteriorFaces = fvMesh.nInteriorFaces();
  for (std::size_t i = 0; i < nInteriorFaces; ++i) {
    std::size_t iOwner = fvMesh.faces()[i].iOwner();
    std::size_t iNeighbor = fvMesh.faces()[i].iNeighbor();

    fvMesh.elements()[iOwner].iFaces().push_back(fvMesh.faces()[i].index());
    fvMesh.elements()[iOwner].iNeighbors().push_back(iNeighbor);
    fvMesh.elements()[iOwner].faceSigns().push_back(1);

    fvMesh.elements()[iNeighbor].iFaces().push_back(fvMesh.faces()[i].index());
    fvMesh.elements()[iNeighbor].iNeighbors().push_back(iOwner);
    fvMesh.elements()[iNeighbor].faceSigns().push_back(-1);
  }

  // Go through boundary faces
  std::size_t nFaces = fvMesh.nFaces();
  for (std::size_t iBFace = nInteriorFaces; iBFace < nFaces; ++iBFace) {
    std::size_t iOwner = fvMesh.faces()[iBFace].iOwner();

    fvMesh.elements()[iOwner].iFaces().push_back(iBFace);
    fvMesh.elements()[iOwner].faceSigns().push_back(1);
  }

  for (std::size_t i = 0; i < nElements; ++i) {
    fvMesh.elements()[i].nNeighbors() =
        fvMesh.elements()[i].iNeighbors().size();
  }

  fvMesh.nBElements() = nFaces - nInteriorFaces;
  fvMesh.nBFaces() = nFaces - nInteriorFaces;
}

void readMesh::setupNodeConnectivities(Mesh &fvMesh) {
  const std::size_t nFaces = fvMesh.nFaces();
  for (std::size_t i = 0; i < nFaces; ++i) {

    std::size_t *iNodes = fvMesh.faces()[i].iNodes();
    const std::size_t nNodes = fvMesh.faces()[i].nNodes();
    for (std::size_t j = 0; j < nNodes; ++j) {
      fvMesh.nodes()[iNodes[j]].iFaces().push_back(fvMesh.faces()[i].index());
    }
  }

  const std::size_t nElements = fvMesh.nElements();
  for (std::size_t i = 0; i < nElements; ++i) {

    for (auto iFace : fvMesh.elements()[i].iFaces()) {

      std::size_t *iNodes = fvMesh.faces()[iFace].iNodes();
      const std::size_t nNodes = fvMesh.faces()[iFace].nNodes();
      for (std::size_t j = 0; j < nNodes; ++j) {
        if (std::count(fvMesh.elements()[i].iNodes().begin(),
                       fvMesh.elements()[i].iNodes().end(), iNodes[j]) == 0) {

          fvMesh.elements()[i].iNodes().push_back(iNodes[j]);
          fvMesh.nodes()[iNodes[j]].iElements().push_back(
              fvMesh.elements()[i].index());
        }
      }
    }
  }
}