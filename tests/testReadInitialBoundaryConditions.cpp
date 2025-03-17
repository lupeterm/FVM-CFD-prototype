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

  const std::array<double, 3> expected_velocity_VolField = {2.0, 0.0, 3.0};

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);
  Field<std::array<double, 3>> internalVelocityField(fvMesh.nElements());
  std::vector<Field<std::array<double, 3>>> boundaryVelocityFields;
  ReadInitialBoundaryConditions initialBoundaryConditionsReader;
  initialBoundaryConditionsReader.readVelocityField(
      fvMesh, internalVelocityField, boundaryVelocityFields);

  // --- Assert ---
  // *** Verify the scalar field values of elements ***
  // The first two elements
  EXPECT_TRUE(VectorMatch(internalVelocityField.values()[0],
                          expected_velocity_VolField, 3));

  EXPECT_TRUE(VectorMatch(internalVelocityField.values()[1],
                          expected_velocity_VolField, 3));

  // The middle two faces
  EXPECT_TRUE(VectorMatch(internalVelocityField.values()[198],
                          expected_velocity_VolField, 3));
  EXPECT_TRUE(VectorMatch(internalVelocityField.values()[199],
                          expected_velocity_VolField, 3));

  // // The last two faces
  EXPECT_TRUE(VectorMatch(internalVelocityField.values()[398],
                          expected_velocity_VolField, 3));
  EXPECT_TRUE(VectorMatch(internalVelocityField.values()[399],
                          expected_velocity_VolField, 3));
}