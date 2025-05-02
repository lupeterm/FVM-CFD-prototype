#ifndef IO_HPP
#define IO_HPP

#include "Mesh.hpp"
#include <fstream>
#include <string>
#include <vector>

class IO {
public:
  static void getDirectory(Mesh &fvMesh);

  static void ifFileOpened(const std::ifstream &file,
                           const std::string &fileName);
  static void discardLines(std::ifstream &file, std::size_t nLines = 1);
  template <typename ValueType>

  // Print out the elements of a vector
  static void printVector(const std::vector<ValueType> &vec);

  // Function to write the solution vector to a file in OpenFOAM format
  template <typename ValueType>
  static void writeResultToFile(const std::vector<ValueType> &solution,
                                const std::string &caseDirectory,
                                const std::string &timePoint,
                                const std::string &solutionFileName);

  // Function to create a .foam file for visualization of results in
  // ParaView
  static void createFoamFile(const std::string &caseDirectory);
};

#endif // IO_HPP