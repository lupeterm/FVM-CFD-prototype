#include "ReadMesh.hpp"
#include "IO.hpp"
#include <algorithm>
#include <fstream>
#include <limits>

using namespace std::string_literals;

void ReadMesh::readOpenFoamMesh(Mesh &fvMesh) {
  if (fvMesh.caseDir().empty()) {
    IO::getDirectory(fvMesh);
  }
  readPointsFile(fvMesh);
  readFacesFile(fvMesh);
  readOwnersFile(fvMesh);
  readNeighborsFile(fvMesh);
  readBoundaryFile(fvMesh);
  constructElements(fvMesh);
  setupNodeConnectivities(fvMesh);
  MeshProcessor.processOpenFoamMesh(fvMesh);
}

void ReadMesh::readPointsFile(Mesh &fvMesh) {
  std::string pointsFileName = fvMesh.caseDir() + "/constant/polyMesh/points"s;
  std::ifstream pointsFile(pointsFileName);
  IO::IO::ifFileOpened(pointsFile, pointsFileName);

  // Discard the file header
  IO::discardLines(pointsFile, 18);

  // --- Start to read points data from the file ---
  pointsFile >> fvMesh.nNodes();

  // Discard the rest of the line and the next line
  IO::discardLines(pointsFile, 2);

  fvMesh.nodes().resize(fvMesh.nNodes());

  // Read x, y, z coordinates to mesh nodes
  for (std::size_t iNode = 0; iNode < fvMesh.nNodes(); ++iNode) {
    pointsFile.ignore(1); // Discard the left parenthesis

    pointsFile >> fvMesh.nodes()[iNode].centroid()[0] >>
        fvMesh.nodes()[iNode].centroid()[1] >>
        fvMesh.nodes()[iNode].centroid()[2];

    // Discard the rest of the line
    pointsFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    fvMesh.nodes()[iNode].index() = iNode;
  }

  pointsFile.close();
}

void ReadMesh::readFacesFile(Mesh &fvMesh) {
  std::string facesFileName = fvMesh.caseDir() + "/constant/polyMesh/faces"s;
  std::ifstream facesFile(facesFileName);
  IO::ifFileOpened(facesFile, facesFileName);

  // Discard the file header
  IO::discardLines(facesFile, 18);

  // --- Start to read faces data from the file ---
  facesFile >> fvMesh.nFaces();

  // Discard the rest of the line and the next line
  IO::discardLines(facesFile, 2);

  fvMesh.faces().resize(fvMesh.nFaces());

  for (std::size_t iFace = 0; iFace < fvMesh.nFaces(); ++iFace) {
    facesFile >> fvMesh.faces()[iFace].nNodes();
    facesFile.ignore(1); // Discard the left parenthesis

    fvMesh.faces()[iFace].allocateNodeList();

    for (std::size_t iNode = 0; iNode < fvMesh.faces()[iFace].nNodes();
         ++iNode) {
      facesFile >> fvMesh.faces()[iFace].iNodes()[iNode];
    }
    facesFile.ignore(1); // Discard the right parenthesis

    fvMesh.faces()[iFace].index() = iFace;
  }

  facesFile.close();
}

void ReadMesh::readOwnersFile(Mesh &fvMesh) {
  std::string ownersFileName = fvMesh.caseDir() + "/constant/polyMesh/owner"s;
  std::ifstream ownersFile(ownersFileName);
  IO::ifFileOpened(ownersFile, ownersFileName);

  // Discard the file header
  IO::discardLines(ownersFile, 18);

  ownersFile >> fvMesh.nOwners();

  // Discard the rest of the line and the next line
  IO::discardLines(ownersFile, 2);

  std::size_t maxOwnerIdx{0};
  std::size_t ownerIdx{0};
  for (std::size_t iOwner = 0; iOwner < fvMesh.nOwners(); ++iOwner) {
    ownersFile >> ownerIdx;
    fvMesh.faces()[iOwner].iOwner() = ownerIdx;
    if (ownerIdx > maxOwnerIdx) {
      maxOwnerIdx = ownerIdx;
    }
  }
  fvMesh.nElements() = maxOwnerIdx + 1;

  ownersFile.close();
}

void ReadMesh::readNeighborsFile(Mesh &fvMesh) {
  std::string neighborsFileName =
      fvMesh.caseDir() + "/constant/polyMesh/neighbour"s;
  std::ifstream neighborsFile(neighborsFileName);
  IO::ifFileOpened(neighborsFile, neighborsFileName);

  // Discard the file header
  IO::discardLines(neighborsFile, 18);

  std::size_t nNeighbors{0};
  neighborsFile >> nNeighbors;

  // Discard the rest of the line and the next line
  if (nNeighbors <= 4) {
    neighborsFile.ignore(1); // Discard the left parenthesis
  } else {
    IO::discardLines(neighborsFile, 2);
  }

  for (std::size_t iNeighbor = 0; iNeighbor < nNeighbors; ++iNeighbor) {
    neighborsFile >> fvMesh.faces()[iNeighbor].iNeighbor();
  }

  fvMesh.nInteriorFaces() = nNeighbors;
  neighborsFile.close();
}

void ReadMesh::readBoundaryFile(Mesh &fvMesh) {
  std::string boundaryFileName =
      fvMesh.caseDir() + "/constant/polyMesh/boundary"s;

  std::ifstream boundaryFile(boundaryFileName);
  IO::ifFileOpened(boundaryFile, boundaryFileName);

  // Discard the file header
  IO::discardLines(boundaryFile, 17);

  boundaryFile >> fvMesh.nBoundaries();
  fvMesh.nPatches() = fvMesh.nBoundaries();

  // Discard the rest of the line and the next line
  IO::discardLines(boundaryFile, 2);

  fvMesh.boundaries().resize(fvMesh.nBoundaries());

  for (std::size_t iBoundary = 0; iBoundary < fvMesh.nBoundaries();
       ++iBoundary) {

    boundaryFile >> fvMesh.boundaries()[iBoundary].userName();
    fvMesh.boundaries()[iBoundary].index() = iBoundary;

    IO::discardLines(boundaryFile, 2);
    std::string token{""};
    boundaryFile >> token;

    while (token != "}"s) {

      if (token == "type"s) {
        boundaryFile >> fvMesh.boundaries()[iBoundary].type();
        fvMesh.boundaries()[iBoundary].type().pop_back();

      } else if (token == "nFaces"s) {
        boundaryFile >> fvMesh.boundaries()[iBoundary].nFaces();

      } else if (token == "startFace"s) {
        boundaryFile >> fvMesh.boundaries()[iBoundary].startFace();
      }
      IO::discardLines(boundaryFile);
      boundaryFile >> token;
    }
  }
  boundaryFile.close();
}

void ReadMesh::constructElements(Mesh &fvMesh) {
  fvMesh.elements().resize(fvMesh.nElements());

  for (std::size_t iElement = 0; iElement < fvMesh.nElements(); ++iElement) {
    fvMesh.elements()[iElement].index() = iElement;
  }

  for (std::size_t iInteriorFace = 0; iInteriorFace < fvMesh.nInteriorFaces();
       ++iInteriorFace) {
    std::size_t iOwner = fvMesh.faces()[iInteriorFace].iOwner();
    std::size_t iNeighbor = fvMesh.faces()[iInteriorFace].iNeighbor();

    fvMesh.elements()[iOwner].iFaces().push_back(
        fvMesh.faces()[iInteriorFace].index());
    fvMesh.elements()[iOwner].iNeighbors().push_back(iNeighbor);
    fvMesh.elements()[iOwner].faceSigns().push_back(1);

    fvMesh.elements()[iNeighbor].iFaces().push_back(
        fvMesh.faces()[iInteriorFace].index());
    fvMesh.elements()[iNeighbor].iNeighbors().push_back(iOwner);
    fvMesh.elements()[iNeighbor].faceSigns().push_back(-1);
  }

  // Go through boundary faces
  for (std::size_t iBFace = fvMesh.nInteriorFaces(); iBFace < fvMesh.nFaces();
       ++iBFace) {
    std::size_t iOwner = fvMesh.faces()[iBFace].iOwner();

    fvMesh.elements()[iOwner].iFaces().push_back(iBFace);
    fvMesh.elements()[iOwner].faceSigns().push_back(1);
  }

  for (std::size_t iElement = 0; iElement < fvMesh.nElements(); ++iElement) {
    fvMesh.elements()[iElement].nNeighbors() =
        fvMesh.elements()[iElement].iNeighbors().size();
  }

  fvMesh.nBElements() = fvMesh.nFaces() - fvMesh.nInteriorFaces();
  fvMesh.nBFaces() = fvMesh.nFaces() - fvMesh.nInteriorFaces();
}

void ReadMesh::setupNodeConnectivities(Mesh &fvMesh) {
  for (std::size_t iFace = 0; iFace < fvMesh.nFaces(); ++iFace) {

    std::vector<std::size_t> &iNodes = fvMesh.faces()[iFace].iNodes();
    const std::size_t nNodes = fvMesh.faces()[iFace].nNodes();
    for (std::size_t iNode = 0; iNode < nNodes; ++iNode) {
      fvMesh.nodes()[iNodes[iNode]].iFaces().push_back(
          fvMesh.faces()[iFace].index());
    }
  }

  for (std::size_t iElement = 0; iElement < fvMesh.nElements(); ++iElement) {

    for (auto iFace : fvMesh.elements()[iElement].iFaces()) {

      std::vector<std::size_t> &iNodes = fvMesh.faces()[iFace].iNodes();
      const std::size_t nNodes = fvMesh.faces()[iFace].nNodes();
      for (std::size_t iNode = 0; iNode < nNodes; ++iNode) {
        if (std::count(fvMesh.elements()[iElement].iNodes().begin(),
                       fvMesh.elements()[iElement].iNodes().end(),
                       iNodes[iNode]) == 0) {

          fvMesh.elements()[iElement].iNodes().push_back(iNodes[iNode]);
          fvMesh.nodes()[iNodes[iNode]].iElements().push_back(
              fvMesh.elements()[iElement].index());
        }
      }
    }
  }
}