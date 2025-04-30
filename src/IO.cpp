#include "IO.hpp"
#include <filesystem> // For checking and creating directories
#include <iomanip>
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

// Print out the contents of a vector
template <typename ValueType>
void IO::printVector(const std::vector<ValueType> &vec) {
  for (const auto &elem : vec) {
    std::cout << elem << std::endl;
  }
}

// Explicit template instantiation for commonly used types
template void IO::printVector(const std::vector<double> &vec);

// Function to write the solution vector to a file
template <typename ValueType>
void IO::writeSolutionToFile(const std::vector<ValueType> &solution,
                             const std::string &caseDirectory,
                             const std::string &timePoint,
                             const std::string &solutionFileName) {
  // Construct the file path
  std::string filePath =
      caseDirectory + "/" + timePoint + "/" + solutionFileName;

  // Ensure the directory path exists
  std::filesystem::path path(filePath);
  std::filesystem::path directory = path.parent_path();

  if (!std::filesystem::exists(directory)) {
    std::cout << "Directory does not exist. Creating directories: " << directory
              << std::endl;
    std::filesystem::create_directories(directory);
  }

  // Check if the file exists
  bool fileExists = std::filesystem::exists(filePath);

  // If the file exists, notify the user
  if (fileExists) {
    std::cout << "File already exists. Overwriting: " << filePath << std::endl;
  } else {
    std::cout << "File does not exist. Creating new file: " << filePath
              << std::endl;
  }

  // Open the file in write mode (creates the file if it doesn't exist)
  std::ofstream outFile(filePath, std::ios::out);
  if (!outFile.is_open()) {
    throw std::ios_base::failure("Failed to open or create file: " + filePath);
  }

  // Show a message indicating the file is being written
  std::cout << "Writing solution to file: " << filePath << std::endl;

  // Write the header (similar to the "T" file format)
  outFile
      << "FoamFile\n"
      << "{\n"
      << "    version     2.0;\n"
      << "    format      ascii;\n"
      << "    class       volScalarField;\n"
      << "    location    \"" + timePoint + "\";\n"
      << "    object      " + solutionFileName + ";\n"
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

  // Close the file
  outFile.close();
}

// Explicit template instantiation for commonly used types
template void IO::writeSolutionToFile(const std::vector<double> &solution,
                                      const std::string &caseDirectory,
                                      const std::string &timePoint,
                                      const std::string &solutionFileName);