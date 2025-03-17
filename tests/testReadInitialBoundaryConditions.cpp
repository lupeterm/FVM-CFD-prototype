#include "Field.hpp"
#include "Mesh.hpp"
#include "ReadInitialBoundaryConditions.hpp"
#include "ReadMesh.hpp"
#include "utilitiesForTesting.hpp"
#include <array>
#include <gtest/gtest.h>
#include <string>

// ****** Tests ******
TEST(ReadInitialBoundaryConditionsTest, ReadingInternalVelocityVolFieldWorks) {

  // --- Arrange ---
  std::string caseDirectory("../../cases/testReadInitialBoundaryConditions");
  ReadMesh meshReader;
  Mesh fvMesh(caseDirectory);

  const std::array<double, 3> expected_velocity_VolField = {0.0, 1.0, 2.0};

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);
  Field<std::array<double, 3>> velocityVolField(fvMesh.nElements());
  ReadInitialBoundaryConditions initialBoundaryConditionsReader;
  initialBoundaryConditionsReader.readInternalVelocityVolField(
      fvMesh, velocityVolField);

  // --- Assert ---
  // *** Verify the scalar field values of elements ***
  // The first two elements
  VectorMatch(velocityVolField.values()[0], expected_velocity_VolField, 3);
  VectorMatch(velocityVolField.values()[1], expected_velocity_VolField, 3);

  // The middle two faces
  VectorMatch(velocityVolField.values()[198], expected_velocity_VolField, 3);
  VectorMatch(velocityVolField.values()[199], expected_velocity_VolField, 3);

  // // The last two faces
  VectorMatch(velocityVolField.values()[398], expected_velocity_VolField, 3);
  VectorMatch(velocityVolField.values()[399], expected_velocity_VolField, 3);
}