#ifndef IO_HPP
#define IO_HPP

#include "Mesh.hpp"
#include <fstream>
#include <string>

class IO {
public:
  static void getDirectory(Mesh &fvMesh);

  static void ifFileOpened(const std::ifstream &file,
                           const std::string &fileName);
  static void discardLines(std::ifstream &file, std::size_t nLines = 1);
};
#endif // IO_HPP