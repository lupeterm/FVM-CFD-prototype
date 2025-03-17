#include "ReadInitialBoundaryConditions.hpp"
#include "IO.hpp"
#include <fstream>
#include <iostream>

void ReadInitialBoundaryConditions::readOpenFoamInitialBoundaryConditions(
    Mesh &fvMesh) {
  std::cout << "Reading initial and boundary conditions..." << std::endl;

  readPressureField(fvMesh);
  readVelocityField(fvMesh);
  readTemperatureField(fvMesh);
}

void ReadInitialBoundaryConditions::readPressureField(Mesh &fvMesh) {
  std::string pFileName = fvMesh.caseDir() + "/0/p";
  std::ifstream pFile(pFileName);
  IO::ifFileOpened(pFile, pFileName);
}

void ReadInitialBoundaryConditions::readVelocityField(Mesh &fvMesh) {
  std::string UFileName = fvMesh.caseDir() + "/0/U";
  std::ifstream UFile(UFileName);
  IO::ifFileOpened(UFile, UFileName);
}

void ReadInitialBoundaryConditions::readTemperatureField(Mesh &fvMesh) {
  std::string TFileName = fvMesh.caseDir() + "/0/T";
  std::ifstream TFile(TFileName);
  IO::ifFileOpened(TFile, TFileName);
}