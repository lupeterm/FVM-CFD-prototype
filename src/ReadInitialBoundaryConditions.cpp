#include "ReadInitialBoundaryConditions.hpp"
#include "IO.hpp"
#include <fstream>
#include <iostream>

void ReadInitialBoundaryConditions::readOpenFoamInitialBoundaryConditions(
    Mesh &fvMesh, Field<std::array<double, 3>> &internalVelocityField,
    std::vector<Field<std::array<double, 3>>> &boundaryVelocityFields,
    Field<double> &internalTemperatureField,
    std::vector<Field<double>> &boundaryTemperatureFields) {

  std::cout << "Reading initial and boundary conditions..." << std::endl;

  readVelocityField(fvMesh, internalVelocityField, boundaryVelocityFields);
  readTemperatureField(fvMesh, internalTemperatureField,
                       boundaryTemperatureFields);

  //   readPressureField(fvMesh);
}

void ReadInitialBoundaryConditions::readVelocityField(
    Mesh &fvMesh, Field<std::array<double, 3>> &internalVelocityField,
    std::vector<Field<std::array<double, 3>>> &boundaryVelocityFields) {

  std::string UFileName = fvMesh.caseDir() + "/0/U";
  std::ifstream UFile(UFileName);
  IO::ifFileOpened(UFile, UFileName);

  // Discard the file header and the specific line #17 about the dimensions
  IO::discardLines(UFile, 18);

  // Read the internal velocity field
  std::string word;
  UFile >> word;

  if (word.compare("internalField") == 0) {
    UFile >> word;
    if (word.compare("uniform") == 0) {
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
  if (word.compare("boundaryField") == 0) {

    IO::discardLines(UFile, 2);
    for (std::size_t iBoundary = 0; iBoundary < fvMesh.nBoundaries();
         ++iBoundary) {

      UFile >> word;
      if (word.compare(fvMesh.boundaries()[iBoundary].userName()) == 0) {

        boundaryVelocityFields[iBoundary].values().resize(
            fvMesh.boundaries()[iBoundary].nFaces());

        IO::discardLines(UFile, 2);
        std::string token{""};
        UFile >> token;

        while (token.compare("}") != 0) {
          if (token.compare("type") == 0) {
            UFile >> boundaryVelocityFields[iBoundary].boundaryType();
            boundaryVelocityFields[iBoundary].boundaryType().pop_back();

            if (boundaryVelocityFields[iBoundary].boundaryType().compare(
                    "noSlip") == 0) {
              boundaryVelocityFields[iBoundary].set({0.0, 0.0, 0.0});
            }

          } else if (token.compare("value") == 0) {
            UFile >> token;
            if (token.compare("uniform") == 0) {
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
    std::vector<Field<double>> &boundaryTemperatureFields) {

  std::string TFileName = fvMesh.caseDir() + "/0/T";
  std::ifstream TFile(TFileName);
  IO::ifFileOpened(TFile, TFileName);

  // Discard the file header and the specific line #17 about the dimensions
  IO::discardLines(TFile, 18);

  // Read the internal temperature field
  std::string word;
  TFile >> word;

  if (word.compare("internalField") == 0) {
    TFile >> word;
    if (word.compare("uniform") == 0) {
      // TFile.ignore(2); // Discard the space and the left parenthesis
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
  if (word.compare("boundaryField") == 0) {

    IO::discardLines(TFile, 2);
    for (std::size_t iBoundary = 0; iBoundary < fvMesh.nBoundaries();
         ++iBoundary) {

      TFile >> word;
      if (word.compare(fvMesh.boundaries()[iBoundary].userName()) == 0) {

        boundaryTemperatureFields[iBoundary].values().resize(
            fvMesh.boundaries()[iBoundary].nFaces());

        IO::discardLines(TFile, 2);
        std::string token{""};
        TFile >> token;

        while (token.compare("}") != 0) {
          if (token.compare("type") == 0) {
            TFile >> boundaryTemperatureFields[iBoundary].boundaryType();
            boundaryTemperatureFields[iBoundary].boundaryType().pop_back();

          } else if (token.compare("value") == 0) {
            TFile >> token;
            if (token.compare("uniform") == 0) {
              // TFile.ignore(2); // Discard the space and the left parenthesis
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

// void ReadInitialBoundaryConditions::readPressureField(Mesh &fvMesh) {
//   std::string pFileName = fvMesh.caseDir() + "/0/p";
//   std::ifstream pFile(pFileName);
//   IO::ifFileOpened(pFile, pFileName);
// }