#include "Field.hpp"
#include "Mesh.hpp"
#include "ReadInitialBoundaryConditions.hpp"
#include "ReadMesh.hpp"
#include "utilitiesForTesting.hpp"
#include <array>
#include <gtest/gtest.h>
#include <string>

// ****** Tests ******
TEST(ReadInitialBoundaryConditionsTest, ReadingInternalVelocityFieldWorks) {

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
  EXPECT_EQ(internalVelocityField.size(), fvMesh.nElements());

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

TEST(ReadInitialBoundaryConditionsTest, ReadingBoundaryVelocityFieldWorks) {

  // --- Arrange ---
  std::string caseDirectory("../../cases/testReadInitialBoundaryConditions");
  ReadMesh meshReader;
  Mesh fvMesh(caseDirectory);

  const std::size_t expected_nBoundaries = 3;
  const std::array<std::string, expected_nBoundaries> expected_boundary_types =
      {"fixedValue", "noSlip", "empty"};

  const std::array<std::size_t, expected_nBoundaries> expected_boundary_nFaces =
      {20, 60, 800};

  // Only the first 2 boundaries need values since the 3rd boundary type is
  // empty
  const std::array<std::array<double, 3>, expected_nBoundaries - 1>
      expected_boundary_velocity_Fields = {{{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}};

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);
  Field<std::array<double, 3>> internalVelocityField(fvMesh.nElements());
  std::vector<Field<std::array<double, 3>>> boundaryVelocityFields;
  ReadInitialBoundaryConditions initialBoundaryConditionsReader;
  initialBoundaryConditionsReader.readVelocityField(
      fvMesh, internalVelocityField, boundaryVelocityFields);

  // --- Assert ---
  EXPECT_EQ(boundaryVelocityFields.size(), expected_nBoundaries);

  // --- The first boundary ---
  EXPECT_EQ(boundaryVelocityFields[0].boundaryType(),
            expected_boundary_types[0]);
  EXPECT_EQ(boundaryVelocityFields[0].size(), expected_boundary_nFaces[0]);

  // The first two faces
  EXPECT_TRUE(VectorMatch(boundaryVelocityFields[0].values()[0],
                          expected_boundary_velocity_Fields[0], 3));
  EXPECT_TRUE(VectorMatch(boundaryVelocityFields[0].values()[1],
                          expected_boundary_velocity_Fields[0], 3));

  // The last two faces
  EXPECT_TRUE(VectorMatch(boundaryVelocityFields[0].values()[18],
                          expected_boundary_velocity_Fields[0], 3));
  EXPECT_TRUE(VectorMatch(boundaryVelocityFields[0].values()[19],
                          expected_boundary_velocity_Fields[0], 3));

  // --- The second boundary ---
  EXPECT_EQ(boundaryVelocityFields[1].boundaryType(),
            expected_boundary_types[1]);
  EXPECT_EQ(boundaryVelocityFields[1].size(), expected_boundary_nFaces[1]);

  // The first two faces
  EXPECT_TRUE(VectorMatch(boundaryVelocityFields[1].values()[0],
                          expected_boundary_velocity_Fields[1], 3));
  EXPECT_TRUE(VectorMatch(boundaryVelocityFields[1].values()[1],
                          expected_boundary_velocity_Fields[1], 3));

  // The last two faces
  EXPECT_TRUE(VectorMatch(boundaryVelocityFields[1].values()[58],
                          expected_boundary_velocity_Fields[1], 3));
  EXPECT_TRUE(VectorMatch(boundaryVelocityFields[1].values()[59],
                          expected_boundary_velocity_Fields[1], 3));
}