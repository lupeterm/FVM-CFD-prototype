#include "IO.hpp"
#include <filesystem> // For checking and creating directories
#include <iomanip>
#include <iostream>
#include <limits>
#include <regex> // For extracting boundaryField content

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

template <typename ValueType>
void IO::printVector(const std::vector<ValueType> &vec) {
  for (const auto &elem : vec) {
    std::cout << elem << std::endl;
  }
}

// Explicit template instantiation for commonly used types
template void IO::printVector(const std::vector<double> &vec);

template <typename ValueType>
void IO::writeSolutionToFile(const std::vector<ValueType> &solution,
                             const std::string &caseDirectory,
                             const std::string &timePoint,
                             const std::string &solutionFileName) {
  // Construct the file paths
  std::string sourceFilePath = caseDirectory + "/0/" + solutionFileName;
  std::string targetFilePath =
      caseDirectory + "/" + timePoint + "/" + solutionFileName;

  // Ensure the target directory exists
  std::filesystem::path targetPath(targetFilePath);
  std::filesystem::path targetDirectory = targetPath.parent_path();

  if (!std::filesystem::exists(targetDirectory)) {
    std::cout << "Target directory does not exist. Creating directories: "
              << targetDirectory << std::endl;
    std::filesystem::create_directories(targetDirectory);
  }

  // Check if the target file exists and notify the user about the file status
  if (std::filesystem::exists(targetFilePath)) {
    std::cout << "File already exists. Overwriting: " << targetFilePath
              << std::endl;
  } else {
    std::cout << "File does not exist. Creating new file: " << targetFilePath
              << std::endl;
  }

  // Open the target file in write mode (create if it doesn't exist)
  std::ofstream outFile(targetFilePath, std::ios::out);
  if (!outFile.is_open()) {
    throw std::ios_base::failure("Failed to open or create file: " +
                                 targetFilePath);
  }

  // Write the header (similar to the OpenFOAM "T" file format)
  outFile
      << "FoamFile\n"
      << "{\n"
      << "    version     2.0;\n"
      << "    format      ascii;\n"
      << "    class       volScalarField;\n"
      << "    location    \"" << timePoint << "\";\n"
      << "    object      " << solutionFileName << ";\n"
      << "}\n"
      << "// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //\n\n";

  // Write the dimensions (example: [0 0 0 1 0 0 0] for temperature)
  outFile << "dimensions      [0 0 0 1 0 0 0];\n\n";

  // Write the internal field
  outFile << "internalField   nonuniform List<scalar>\n";
  outFile << solution.size() << "\n(\n";
  for (const auto &value : solution) {
    outFile << "    " << std::fixed << std::setprecision(6) << value << "\n";
  }
  outFile << ");\n\n";

  // Read the boundaryField entry from the source file
  std::ifstream inFile(sourceFilePath);
  if (!inFile.is_open()) {
    throw std::ios_base::failure("Failed to open source file: " +
                                 sourceFilePath);
  }

  std::string line;
  bool boundaryFieldFound = false;

  while (std::getline(inFile, line)) {
    if (line.find("boundaryField") != std::string::npos) {
      boundaryFieldFound = true;
    }
    if (boundaryFieldFound) {
      outFile << line << "\n";
    }
  }

  if (!boundaryFieldFound) {
    throw std::runtime_error("boundaryField entry not found in source file: " +
                             sourceFilePath);
  }

  // Close the files
  inFile.close();
  outFile.close();

  std::cout << "Solution written to file: " << targetFilePath << std::endl;
}

// Explicit template instantiation for commonly used types
template void IO::writeSolutionToFile(const std::vector<double> &solution,
                                      const std::string &caseDirectory,
                                      const std::string &timePoint,
                                      const std::string &solutionFileName);

void IO::createFoamFile(const std::string &caseDirectory) {
  std::string foamFilePath = caseDirectory + "/test.foam";

  // Check if the file exists
  if (std::filesystem::exists(foamFilePath)) {
    std::cout << "test.foam File already exists: " << foamFilePath << std::endl;
  } else {
    // Create the file
    std::ofstream foamFile(foamFilePath);
    if (!foamFile.is_open()) {
      throw std::ios_base::failure("Failed to create test.foam file: " +
                                   foamFilePath);
    }
    foamFile.close();
    std::cout << "test.foam File created: " << foamFilePath << std::endl;
  }
}