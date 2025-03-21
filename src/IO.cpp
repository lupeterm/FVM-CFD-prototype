#include "IO.hpp"
#include <iostream>
#include <limits>

void IO::getDirectory(Mesh &fvMesh) {
  std::cout << "Enter the case directory: ";
  std::getline(std::cin, fvMesh.caseDir());
}

void IO::ifFileOpened(const std::ifstream &file, const std::string &fileName) {
  if (!file.is_open()) {
    std::cerr << "Error opening file: " << fileName << std::endl;
  }
}

void IO::discardLines(std::ifstream &file, const std::size_t nLines) {
  std::string line;
  for (int iLine = 0; iLine < nLines; ++iLine) {
    file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  }
}