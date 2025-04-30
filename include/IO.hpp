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
  static void printVector(const std::vector<ValueType> &vec);

  // New function to write the solution vector to a file
  // template <typename ValueType>
  // static void writeSolutionToFile(const std::vector<ValueType> &solution,
  //                                 const std::string &filePath);
  template <typename ValueType>
  static void writeSolutionToFile(const std::vector<ValueType> &solution,
                                  const std::string &caseDirectory,
                                  const std::string &timePoint,
                                  const std::string &solutionFileName);
};

#endif // IO_HPP