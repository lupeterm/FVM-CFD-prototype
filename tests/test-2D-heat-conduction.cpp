#include <gtest/gtest.h>

#include "Mesh.hpp"
#include "ReadMesh.hpp"
#include "utilitiesForTesting.hpp"
#include <array>
#include <string>

// ****** Tests ******
TEST(ReadingMeshFor2DHeatConduction, CellOrderingIsCorrect) {
  // --- Arrange ---
  std::string caseDirectory("../../cases/2D-heat-conduction");
  ReadMesh meshReader;
  Mesh fvMesh(caseDirectory);
}