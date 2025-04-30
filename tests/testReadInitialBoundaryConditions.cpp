#include "Field.hpp"
#include "Mesh.hpp"
#include "ReadInitialBoundaryConditions.hpp"
#include "ReadMesh.hpp"
#include "utilitiesForTesting.hpp"
#include <array>
#include <gtest/gtest.h>
#include <string>

// ****** Tests ******
TEST(ReadInitialConditionTest, ReadInternalVelocity) {

  // --- Arrange ---
  std::string caseDirectory("../../cases/testReadInitialBoundaryConditions");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  const std::array<double, 3> expected_internal_velocity_field = {2.0, 0.0,
                                                                  3.0};

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);
  Field<std::array<double, 3>> internalVelocityField(fvMesh.nElements());
  std::vector<boundaryField<std::array<double, 3>>> boundaryVelocityFields;
  ReadInitialBoundaryConditions initialBoundaryConditionsReader;
  initialBoundaryConditionsReader.readVelocityField(
      fvMesh, internalVelocityField, boundaryVelocityFields);

  // --- Assert ---
  EXPECT_EQ(internalVelocityField.size(), fvMesh.nElements());

  // The 1st two elements
  EXPECT_TRUE(VectorMatch(internalVelocityField.values()[0],
                          expected_internal_velocity_field, 3));

  EXPECT_TRUE(VectorMatch(internalVelocityField.values()[1],
                          expected_internal_velocity_field, 3));

  // The middle two faces
  EXPECT_TRUE(VectorMatch(internalVelocityField.values()[198],
                          expected_internal_velocity_field, 3));
  EXPECT_TRUE(VectorMatch(internalVelocityField.values()[199],
                          expected_internal_velocity_field, 3));

  // // The last two faces
  EXPECT_TRUE(VectorMatch(internalVelocityField.values()[398],
                          expected_internal_velocity_field, 3));
  EXPECT_TRUE(VectorMatch(internalVelocityField.values()[399],
                          expected_internal_velocity_field, 3));
}

TEST(ReadBoundaryConditionsTest, ReadBoundaryVelocity) {

  // --- Arrange ---
  std::string caseDirectory("../../cases/testReadInitialBoundaryConditions");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  const std::size_t expected_nBoundaries = 3;
  const std::array<std::string, expected_nBoundaries> expected_boundary_types =
      {"fixedValue", "noSlip", "empty"};

  const std::array<std::size_t, expected_nBoundaries> expected_boundary_nFaces =
      {20, 60, 800};

  // Only the 1st 2 boundaries need values since the 3rd boundary type is
  // empty
  const std::array<std::array<double, 3>, expected_nBoundaries - 1>
      expected_boundary_velocity_Fields = {{{1.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}};

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);
  Field<std::array<double, 3>> internalVelocityField(fvMesh.nElements());
  std::vector<boundaryField<std::array<double, 3>>> boundaryVelocityFields;
  ReadInitialBoundaryConditions initialBoundaryConditionsReader;
  initialBoundaryConditionsReader.readVelocityField(
      fvMesh, internalVelocityField, boundaryVelocityFields);

  // --- Assert ---
  EXPECT_EQ(boundaryVelocityFields.size(), expected_nBoundaries);

  // --- The 1st boundary ---
  EXPECT_EQ(boundaryVelocityFields[0].boundaryType(),
            expected_boundary_types[0]);
  EXPECT_EQ(boundaryVelocityFields[0].size(), expected_boundary_nFaces[0]);

  // The 1st two faces
  EXPECT_TRUE(VectorMatch(boundaryVelocityFields[0].values()[0],
                          expected_boundary_velocity_Fields[0], 3));
  EXPECT_TRUE(VectorMatch(boundaryVelocityFields[0].values()[1],
                          expected_boundary_velocity_Fields[0], 3));

  // The last two faces
  EXPECT_TRUE(VectorMatch(boundaryVelocityFields[0].values()[18],
                          expected_boundary_velocity_Fields[0], 3));
  EXPECT_TRUE(VectorMatch(boundaryVelocityFields[0].values()[19],
                          expected_boundary_velocity_Fields[0], 3));

  // --- The 2nd boundary ---
  EXPECT_EQ(boundaryVelocityFields[1].boundaryType(),
            expected_boundary_types[1]);
  EXPECT_EQ(boundaryVelocityFields[1].size(), expected_boundary_nFaces[1]);

  // The 1st two faces
  EXPECT_TRUE(VectorMatch(boundaryVelocityFields[1].values()[0],
                          expected_boundary_velocity_Fields[1], 3));
  EXPECT_TRUE(VectorMatch(boundaryVelocityFields[1].values()[1],
                          expected_boundary_velocity_Fields[1], 3));

  // The last two faces
  EXPECT_TRUE(VectorMatch(boundaryVelocityFields[1].values()[58],
                          expected_boundary_velocity_Fields[1], 3));
  EXPECT_TRUE(VectorMatch(boundaryVelocityFields[1].values()[59],
                          expected_boundary_velocity_Fields[1], 3));

  // --- The 3rd boundary ---
  EXPECT_EQ(boundaryVelocityFields[2].boundaryType(),
            expected_boundary_types[2]);
  EXPECT_EQ(boundaryVelocityFields[2].size(), expected_boundary_nFaces[2]);
}

TEST(ReadInitialConditionTest, ReadInternalTemperature) {

  // --- Arrange ---
  std::string caseDirectory("../../cases/testReadInitialBoundaryConditions");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  const double expected_internal_temperature_field = 239.0;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);
  Field<double> internalTemperatureField(fvMesh.nElements());
  std::vector<boundaryField<double>> boundaryTemperatureFields;
  ReadInitialBoundaryConditions initialBoundaryConditionsReader;
  initialBoundaryConditionsReader.readTemperatureField(
      fvMesh, internalTemperatureField, boundaryTemperatureFields);

  // --- Assert ---
  EXPECT_EQ(internalTemperatureField.size(), fvMesh.nElements());

  // The 1st two internal elements
  EXPECT_EQ(internalTemperatureField.values()[0],
            expected_internal_temperature_field);
  EXPECT_EQ(internalTemperatureField.values()[1],
            expected_internal_temperature_field);

  // The middle two internal elements
  EXPECT_EQ(internalTemperatureField.values()[198],
            expected_internal_temperature_field);
  EXPECT_EQ(internalTemperatureField.values()[199],
            expected_internal_temperature_field);

  // The last two internal elements
  EXPECT_EQ(internalTemperatureField.values()[398],
            expected_internal_temperature_field);
  EXPECT_EQ(internalTemperatureField.values()[399],
            expected_internal_temperature_field);
}

TEST(ReadBoundaryConditionsTest, ReadBoundaryTemperature) {

  // --- Arrange ---
  std::string caseDirectory("../../cases/testReadInitialBoundaryConditions");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  const std::size_t expected_nBoundaries = 3;
  const std::array<std::string, expected_nBoundaries> expected_boundary_types =
      {"fixedValue", "zeroGradient", "empty"};

  const std::array<std::size_t, expected_nBoundaries> expected_boundary_nFaces =
      {20, 60, 800};

  // Only the 1st boundary needs values since the 2nd boundary type is Neumann
  // BC, and the 3rd boundary type is empty
  const double expected_boundary_temperature_Field = 493.0;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);
  Field<double> internalTemperatureField(fvMesh.nElements());
  std::vector<boundaryField<double>> boundaryTemperatureFields;
  ReadInitialBoundaryConditions initialBoundaryConditionsReader;
  initialBoundaryConditionsReader.readTemperatureField(
      fvMesh, internalTemperatureField, boundaryTemperatureFields);

  // --- Assert ---
  EXPECT_EQ(boundaryTemperatureFields.size(), expected_nBoundaries);

  // --- The 1st boundary ---
  EXPECT_EQ(boundaryTemperatureFields[0].boundaryType(),
            expected_boundary_types[0]);
  EXPECT_EQ(boundaryTemperatureFields[0].size(), expected_boundary_nFaces[0]);

  // The 1st two faces
  EXPECT_EQ(boundaryTemperatureFields[0].values()[0],
            expected_boundary_temperature_Field);
  EXPECT_EQ(boundaryTemperatureFields[0].values()[1],
            expected_boundary_temperature_Field);

  // The last two faces
  EXPECT_EQ(boundaryTemperatureFields[0].values()[18],
            expected_boundary_temperature_Field);
  EXPECT_EQ(boundaryTemperatureFields[0].values()[19],
            expected_boundary_temperature_Field);

  // --- The 2nd boundary ---
  EXPECT_EQ(boundaryTemperatureFields[1].boundaryType(),
            expected_boundary_types[1]);
  EXPECT_EQ(boundaryTemperatureFields[1].size(), expected_boundary_nFaces[1]);

  // --- The 3rd boundary ---
  EXPECT_EQ(boundaryTemperatureFields[2].boundaryType(),
            expected_boundary_types[2]);
  EXPECT_EQ(boundaryTemperatureFields[2].size(), expected_boundary_nFaces[2]);
}

// *** A case with custom initial and boundary conditions ***
TEST(ReadCustomInitialConditionTest, ReadInternalTemperature) {

  // --- Arrange ---
  std::string caseDirectory(
      "../../cases/heat-conduction/test-setup-of-2D-heat-conduction");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  const double expected_internal_temperature_field = 273.0;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);
  Field<double> internalTemperatureField(fvMesh.nElements());
  std::vector<boundaryField<double>> boundaryTemperatureFields;
  ReadInitialBoundaryConditions initialBoundaryConditionsReader;
  initialBoundaryConditionsReader.readTemperatureField(
      fvMesh, internalTemperatureField, boundaryTemperatureFields);

  // --- Assert ---
  EXPECT_EQ(internalTemperatureField.size(), fvMesh.nElements());

  // The 1st two internal elements
  EXPECT_EQ(internalTemperatureField.values()[0],
            expected_internal_temperature_field);
  EXPECT_EQ(internalTemperatureField.values()[1],
            expected_internal_temperature_field);

  // The middle two internal elements
  EXPECT_EQ(internalTemperatureField.values()[198],
            expected_internal_temperature_field);
  EXPECT_EQ(internalTemperatureField.values()[199],
            expected_internal_temperature_field);

  // The last two internal elements
  EXPECT_EQ(internalTemperatureField.values()[398],
            expected_internal_temperature_field);
  EXPECT_EQ(internalTemperatureField.values()[399],
            expected_internal_temperature_field);
}

TEST(ReadCustomBoundaryConditionsTest, ReadBoundaryTemperature) {

  // --- Arrange ---
  std::string caseDirectory(
      "../../cases/heat-conduction/test-setup-of-2D-heat-conduction");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  const std::size_t expected_nBoundaries = 5;
  const std::array<std::string, expected_nBoundaries> expected_boundary_types =
      {"zeroGradient", "zeroGradient", "fixedValue", "fixedValue", "empty"};

  const std::array<std::size_t, expected_nBoundaries> expected_boundary_nFaces =
      {20, 20, 20, 20, 800};

  const std::array<double, 2> expected_boundary_temperature_Field = {373.0,
                                                                     273.0};

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);
  Field<double> internalTemperatureField(fvMesh.nElements());
  std::vector<boundaryField<double>> boundaryTemperatureFields;
  ReadInitialBoundaryConditions initialBoundaryConditionsReader;
  initialBoundaryConditionsReader.readTemperatureField(
      fvMesh, internalTemperatureField, boundaryTemperatureFields);

  // --- Assert ---
  EXPECT_EQ(boundaryTemperatureFields.size(), expected_nBoundaries);

  // --- The 1st boundary ---
  EXPECT_EQ(boundaryTemperatureFields[0].boundaryType(),
            expected_boundary_types[0]);
  EXPECT_EQ(boundaryTemperatureFields[0].size(), expected_boundary_nFaces[0]);

  // --- The 2nd boundary ---
  EXPECT_EQ(boundaryTemperatureFields[1].boundaryType(),
            expected_boundary_types[1]);
  EXPECT_EQ(boundaryTemperatureFields[1].size(), expected_boundary_nFaces[1]);

  // --- The 3rd boundary ---
  EXPECT_EQ(boundaryTemperatureFields[2].boundaryType(),
            expected_boundary_types[2]);
  EXPECT_EQ(boundaryTemperatureFields[2].size(), expected_boundary_nFaces[2]);

  // The 1st two faces
  EXPECT_EQ(boundaryTemperatureFields[2].values()[0],
            expected_boundary_temperature_Field[0]);
  EXPECT_EQ(boundaryTemperatureFields[2].values()[1],
            expected_boundary_temperature_Field[0]);

  // The last two faces
  EXPECT_EQ(boundaryTemperatureFields[2].values()[18],
            expected_boundary_temperature_Field[0]);
  EXPECT_EQ(boundaryTemperatureFields[2].values()[19],
            expected_boundary_temperature_Field[0]);

  // --- The 4th boundary ---
  EXPECT_EQ(boundaryTemperatureFields[3].boundaryType(),
            expected_boundary_types[3]);
  EXPECT_EQ(boundaryTemperatureFields[3].size(), expected_boundary_nFaces[3]);

  // The 1st two faces
  EXPECT_EQ(boundaryTemperatureFields[3].values()[0],
            expected_boundary_temperature_Field[1]);
  EXPECT_EQ(boundaryTemperatureFields[3].values()[1],
            expected_boundary_temperature_Field[1]);

  // The last two faces
  EXPECT_EQ(boundaryTemperatureFields[3].values()[18],
            expected_boundary_temperature_Field[1]);
  EXPECT_EQ(boundaryTemperatureFields[3].values()[19],
            expected_boundary_temperature_Field[1]);

  // --- The 5th boundary ---
  EXPECT_EQ(boundaryTemperatureFields[4].boundaryType(),
            expected_boundary_types[4]);
  EXPECT_EQ(boundaryTemperatureFields[4].size(), expected_boundary_nFaces[4]);
}