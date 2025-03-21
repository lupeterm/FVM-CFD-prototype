#include "ReadInitialBoundaryConditions.hpp"
#include "IO.hpp"
#include <fstream>
#include <iostream>

using namespace std::string_literals;

void ReadInitialBoundaryConditions::readOpenFoamInitialBoundaryConditions(
    Mesh &fvMesh, Field<std::array<double, 3>> &internalVelocityField,
    std::vector<boundaryField<std::array<double, 3>>> &boundaryVelocityFields,
    Field<double> &internalTemperatureField,
    std::vector<boundaryField<double>> &boundaryTemperatureFields) {

  std::cout << "Reading initial and boundary conditions..." << std::endl;

  readVelocityField(fvMesh, internalVelocityField, boundaryVelocityFields);
  readTemperatureField(fvMesh, internalTemperatureField,
                       boundaryTemperatureFields);

  // TO DO:
  // readPressureField(fvMesh);
}

void ReadInitialBoundaryConditions::readVelocityField(
    Mesh &fvMesh, Field<std::array<double, 3>> &internalVelocityField,
    std::vector<boundaryField<std::array<double, 3>>> &boundaryVelocityFields) {

  std::string UFileName = fvMesh.caseDir() + "/0/U"s;
  std::ifstream UFile(UFileName);
  IO::ifFileOpened(UFile, UFileName);

  // Discard the file header and the specific line #17 about the dimensions
  IO::discardLines(UFile, 18);

  // Read the internal velocity field
  std::string word;
  UFile >> word;

  if (word == "internalField"s) {
    UFile >> word;

    if (word == "uniform"s) {
      UFile.ignore(2); // Discard the space and the left parenthesis
      std::array<double, 3> U = {0.0, 0.0, 0.0};
      UFile >> U[0] >> U[1] >> U[2];
      internalVelocityField.set(U);
    }
  }

  // Read the boundary velocity field
  const std::size_t nBoundaries = fvMesh.nBoundaries();
  boundaryVelocityFields.resize(nBoundaries);

  // Discard the rest of the line and the next line
  IO::discardLines(UFile, 2);
  UFile >> word;

  if (word == "boundaryField"s) {

    IO::discardLines(UFile, 2);
    for (std::size_t iBoundary = 0; iBoundary < fvMesh.nBoundaries();
         ++iBoundary) {

      UFile >> word;

      if (word == fvMesh.boundaries()[iBoundary].userName()) {
        boundaryVelocityFields[iBoundary].values().resize(
            fvMesh.boundaries()[iBoundary].nFaces());

        IO::discardLines(UFile, 2);
        std::string token{""};
        UFile >> token;

        while (token != "}"s) {
          if (token == "type"s) {
            UFile >> boundaryVelocityFields[iBoundary].boundaryType();
            boundaryVelocityFields[iBoundary].boundaryType().pop_back();

            if (boundaryVelocityFields[iBoundary].boundaryType() == "noSlip"s) {
              boundaryVelocityFields[iBoundary].set({0.0, 0.0, 0.0});
            }

          } else if (token == "value"s) {
            UFile >> token;
            if (token == "uniform"s) {
              UFile.ignore(2); // Discard the space and the left parenthesis
              std::array<double, 3> U = {0.0, 0.0, 0.0};
              UFile >> U[0] >> U[1] >> U[2];
              boundaryVelocityFields[iBoundary].set(U);
            }
          }
          IO::discardLines(UFile);
          UFile >> token;
        }
      }
    }
  }
  UFile.close();
}

void ReadInitialBoundaryConditions::readTemperatureField(
    Mesh &fvMesh, Field<double> &internalTemperatureField,
    std::vector<boundaryField<double>> &boundaryTemperatureFields) {

  std::string TFileName = fvMesh.caseDir() + "/0/T"s;
  std::ifstream TFile(TFileName);
  IO::ifFileOpened(TFile, TFileName);

  // Discard the file header and the specific line #17 about the dimensions
  IO::discardLines(TFile, 18);

  // Read the internal temperature field
  std::string word;
  TFile >> word;

  if (word == "internalField"s) {
    TFile >> word;
    if (word == "uniform"s) {
      double temperature = 0.0;
      TFile >> temperature;
      internalTemperatureField.set(temperature);
    }
  }

  // Read the boundary temperature field
  const std::size_t nBoundaries = fvMesh.nBoundaries();
  boundaryTemperatureFields.resize(nBoundaries);

  // Discard the rest of the line and the next line
  IO::discardLines(TFile, 2);
  TFile >> word;

  if (word == "boundaryField"s) {
    IO::discardLines(TFile, 2);
    for (std::size_t iBoundary = 0; iBoundary < fvMesh.nBoundaries();
         ++iBoundary) {
      TFile >> word;

      if (word == fvMesh.boundaries()[iBoundary].userName()) {
        boundaryTemperatureFields[iBoundary].values().resize(
            fvMesh.boundaries()[iBoundary].nFaces());

        IO::discardLines(TFile, 2);
        std::string token{""};
        TFile >> token;

        while (token != "}"s) {
          if (token == "type"s) {
            TFile >> boundaryTemperatureFields[iBoundary].boundaryType();
            boundaryTemperatureFields[iBoundary].boundaryType().pop_back();
          } else if (token == "value"s) {
            TFile >> token;
            if (token == "uniform"s) {
              double temperature = 0.0;
              TFile >> temperature;
              boundaryTemperatureFields[iBoundary].set(temperature);
            }
          }
          IO::discardLines(TFile);
          TFile >> token;
        }
      }
    }
  }
  TFile.close();
}

// TO DO:
// void ReadInitialBoundaryConditions::readPressureField(Mesh &fvMesh) {
//   std::string pFileName = fvMesh.caseDir() + "/0/p";
//   std::ifstream pFile(pFileName);
//   IO::ifFileOpened(pFile, pFileName);
// }