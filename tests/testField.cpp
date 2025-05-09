#include "Field.hpp"
#include "Mesh.hpp"
#include "ReadMesh.hpp"
#include "utilitiesForTesting.hpp"
#include <array>
#include <gtest/gtest.h>
#include <string>

// ****** Tests ******
TEST(FieldTest, SetScalarVolField) {

  // --- Arrange ---
  std::string caseDirectory("../../cases/cavity");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  const double expected_cell_scalar_field = 1.0;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);
  Field<double> cellScalarField(fvMesh.nCells());
  cellScalarField.set(1.0);

  // --- Assert ---
  // *** Verify the scalar field values of cells ***
  // The first two cells
  EXPECT_EQ(cellScalarField.values()[0], expected_cell_scalar_field);
  EXPECT_EQ(cellScalarField.values()[1], expected_cell_scalar_field);

  // The middle two faces
  EXPECT_EQ(cellScalarField.values()[198], expected_cell_scalar_field);
  EXPECT_EQ(cellScalarField.values()[199], expected_cell_scalar_field);

  // The last two faces
  EXPECT_EQ(cellScalarField.values()[398], expected_cell_scalar_field);
  EXPECT_EQ(cellScalarField.values()[399], expected_cell_scalar_field);
}

TEST(FieldTest, SetVectorVolField) {

  // --- Arrange ---
  std::string caseDirectory("../../cases/cavity");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  const std::array<double, 3> expected_cell_vector_field = {1.0, 2.0, 3.0};

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);
  Field<std::array<double, 3>> cellVolField(fvMesh.nCells());
  cellVolField.set(expected_cell_vector_field);

  // --- Assert ---
  // *** Verify the scalar field values of cells ***
  // The first two cells
  EXPECT_TRUE(
      VectorMatch(cellVolField.values()[0], expected_cell_vector_field, 3));
  EXPECT_TRUE(
      VectorMatch(cellVolField.values()[1], expected_cell_vector_field, 3));

  // // The middle two faces
  EXPECT_TRUE(
      VectorMatch(cellVolField.values()[198], expected_cell_vector_field, 3));
  EXPECT_TRUE(
      VectorMatch(cellVolField.values()[199], expected_cell_vector_field, 3));

  // // The last two faces
  EXPECT_TRUE(
      VectorMatch(cellVolField.values()[398], expected_cell_vector_field, 3));
  EXPECT_TRUE(
      VectorMatch(cellVolField.values()[399], expected_cell_vector_field, 3));
}

TEST(FieldTest, UseDefaultVectorVolField) {

  // --- Arrange ---
  std::string caseDirectory("../../cases/cavity");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  const std::array<double, 3> expected_cell_vector_field = {0.0, 0.0, 0.0};

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);
  Field<std::array<double, 3>> cellVolField(fvMesh.nCells());

  // --- Assert ---
  // *** Verify the scalar field values of cells ***
  // The first two cells
  EXPECT_TRUE(
      VectorMatch(cellVolField.values()[0], expected_cell_vector_field, 3));
  EXPECT_TRUE(
      VectorMatch(cellVolField.values()[1], expected_cell_vector_field, 3));

  // // The middle two faces
  EXPECT_TRUE(
      VectorMatch(cellVolField.values()[198], expected_cell_vector_field, 3));
  EXPECT_TRUE(
      VectorMatch(cellVolField.values()[199], expected_cell_vector_field, 3));

  // // The last two faces
  EXPECT_TRUE(
      VectorMatch(cellVolField.values()[398], expected_cell_vector_field, 3));
  EXPECT_TRUE(
      VectorMatch(cellVolField.values()[399], expected_cell_vector_field, 3));
}