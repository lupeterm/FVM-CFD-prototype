#include "ReadInitialBoundaryConditions.hpp"
#include "IO.hpp"
#include <fstream>
#include <iostream>

void ReadInitialBoundaryConditions::readOpenFoamInitialBoundaryConditions(
    Mesh &fvMesh, Field<std::array<double, 3>> &internalVelocityField,
    std::vector<Field<std::array<double, 3>>> boundaryVelocityFields) {

  std::cout << "Reading initial and boundary conditions..." << std::endl;

  //   readPressureField(fvMesh);
  readVelocityField(fvMesh, internalVelocityField, boundaryVelocityFields);
  //   readBoundaryVelocityField(fvMesh, boundaryVelocityField);
  //   readTemperatureField(fvMesh);
}

// void ReadInitialBoundaryConditions::readPressureField(Mesh &fvMesh) {
//   std::string pFileName = fvMesh.caseDir() + "/0/p";
//   std::ifstream pFile(pFileName);
//   IO::ifFileOpened(pFile, pFileName);
// }

void ReadInitialBoundaryConditions::readVelocityField(
    Mesh &fvMesh, Field<std::array<double, 3>> &internalVelocityField,
    std::vector<Field<std::array<double, 3>>> boundaryVelocityFields) {

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
      std::cout << U[0] << " " << U[1] << " " << U[2] << std::endl;
      internalVelocityField.set(U);
    }
  }

  // Read the boundary velocity field
  //   std::string boundaryFileName =
  //       fvMesh.caseDir() + "/constant/polyMesh/boundary";

  //   std::ifstream boundaryFile(boundaryFileName);
  //   IO::ifFileOpened(boundaryFile, boundaryFileName);

  //   // Discard the file header
  //   IO::discardLines(boundaryFile, 17);

  //   boundaryFile >> fvMesh.nBoundaries();
  //   fvMesh.nPatches() = fvMesh.nBoundaries();

  //===========================================================================
  //   const std::size_t nBoundaries = fvMesh.nBoundaries();
  //   boundaryVelocityFields.reserve(nBoundaries);

  //   // Discard the rest of the line and the next line
  //   IO::discardLines(UFile, 2);
  //   UFile >> word;
  //   if (word.compare("boundaryField") == 0) {

  //     //   fvMesh.allocateBoundaries();
  //     IO::discardLines(UFile, 2);

  //     for (std::size_t iBoundary = 0; iBoundary < fvMesh.nBoundaries();
  //          ++iBoundary) {

  //       UFile >> word;
  //       if (word.compare(fvMesh.boundaries()[iBoundary].userName()) == 0) {

  //         IO::discardLines(UFile, 2);
  //         std::string token{""};
  //         UFile >> token;
  //         while (token.compare("}") != 0) {

  //           if (token.compare("type") == 0) {
  //             //   boundaryFile >> fvMesh.boundaries()[iBoundary].type();
  //             //   fvMesh.boundaries()[iBoundary].type().pop_back();

  //             UFile >> boundaryVelocityFields[iBoundary].boundaryType();
  //             boundaryVelocityFields[iBoundary].boundaryType().pop_back();
  //             if (boundaryVelocityFields[iBoundary].boundaryType().compare(
  //                     "fixedValue") == 0) {
  //               IO::discardLines(UFile, 1);
  //               UFile >> word;
  //               if (word.compare("value") == 0) {
  //                 UFile >> word;
  //                 if (word.compare("uniform") == 0) {
  //                   UFile.ignore(1); // Discard the left parenthesis
  //                   std::array<double, 3> U = {0.0, 0.0, 0.0};
  //                   UFile >> U[0] >> U[1] >> U[2];
  //                   //   boundaryVelocityFields[iBoundary].set(U);
  //                 }

  //                 //   } else if (token.compare("nFaces") == 0) {
  //                 //     boundaryFile >>
  //                 fvMesh.boundaries()[iBoundary].nFaces();

  //                 //   } else if (token.compare("startFace") == 0) {
  //                 //     boundaryFile >>
  //                 //     fvMesh.boundaries()[iBoundary].startFace();
  //                 //   }
  //                 IO::discardLines(boundaryFile);
  //                 boundaryFile >> token;
  //               }
  //             }

  //             //   boundaryFile >> fvMesh.boundaries()[iBoundary].userName();
  //             //   fvMesh.boundaries()[iBoundary].index() = iBoundary;
  //           }
  //         }
  UFile.close();
}
// void ReadInitialBoundaryConditions::readTemperatureField(Mesh &fvMesh) {
//   std::string TFileName = fvMesh.caseDir() + "/0/T";
//   std::ifstream TFile(TFileName);
//   IO::ifFileOpened(TFile, TFileName);
// }