#include "ReadInitialBoundaryConditions.hpp"
#include "IO.hpp"
#include <fstream>
#include <iostream>

void ReadInitialBoundaryConditions::readOpenFoamInitialBoundaryConditions(
    Mesh &fvMesh, Field<std::array<double, 3>> &velocityVolField) {
  std::cout << "Reading initial and boundary conditions..." << std::endl;

  //   readPressureField(fvMesh);
  readInternalVelocityVolField(fvMesh, velocityVolField);
  //   readTemperatureField(fvMesh);
}

// void ReadInitialBoundaryConditions::readPressureField(Mesh &fvMesh) {
//   std::string pFileName = fvMesh.caseDir() + "/0/p";
//   std::ifstream pFile(pFileName);
//   IO::ifFileOpened(pFile, pFileName);
// }

void ReadInitialBoundaryConditions::readInternalVelocityVolField(
    Mesh &fvMesh, Field<std::array<double, 3>> &velocityVolField) {
  std::string UFileName = fvMesh.caseDir() + "/0/U";
  std::ifstream UFile(UFileName);
  IO::ifFileOpened(UFile, UFileName);

  // Discard the file header and the specific line #17 about the dimensions
  IO::discardLines(UFile, 18);

  std::string word;
  UFile >> word;
  if (word.compare("internalField") == 0) {
    UFile >> word;
    if (word.compare("uniform") == 0) {
      std::array<double, 3> U = {0.0, 0.0, 0.0};
      UFile >> U[0] >> U[1] >> U[2];
      velocityVolField.set(U);
    }
  }
}
// void ReadInitialBoundaryConditions::readTemperatureField(Mesh &fvMesh) {
//   std::string TFileName = fvMesh.caseDir() + "/0/T";
//   std::ifstream TFile(TFileName);
//   IO::ifFileOpened(TFile, TFileName);
// }