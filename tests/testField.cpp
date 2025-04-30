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

  const double expected_element_scalar_field = 1.0;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);
  Field<double> elementScalarField(fvMesh.nElements());
  elementScalarField.set(1.0);

  // --- Assert ---
  // *** Verify the scalar field values of elements ***
  // The first two elements
  EXPECT_EQ(elementScalarField.values()[0], expected_element_scalar_field);
  EXPECT_EQ(elementScalarField.values()[1], expected_element_scalar_field);

  // The middle two faces
  EXPECT_EQ(elementScalarField.values()[198], expected_element_scalar_field);
  EXPECT_EQ(elementScalarField.values()[199], expected_element_scalar_field);

  // The last two faces
  EXPECT_EQ(elementScalarField.values()[398], expected_element_scalar_field);
  EXPECT_EQ(elementScalarField.values()[399], expected_element_scalar_field);
}

TEST(FieldTest, SetVectorVolField) {

  // --- Arrange ---
  std::string caseDirectory("../../cases/cavity");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  const std::array<double, 3> expected_element_vector_field = {1.0, 2.0, 3.0};

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);
  Field<std::array<double, 3>> elementVolField(fvMesh.nElements());
  elementVolField.set(expected_element_vector_field);

  // --- Assert ---
  // *** Verify the scalar field values of elements ***
  // The first two elements
  EXPECT_TRUE(VectorMatch(elementVolField.values()[0],
                          expected_element_vector_field, 3));
  EXPECT_TRUE(VectorMatch(elementVolField.values()[1],
                          expected_element_vector_field, 3));

  // // The middle two faces
  EXPECT_TRUE(VectorMatch(elementVolField.values()[198],
                          expected_element_vector_field, 3));
  EXPECT_TRUE(VectorMatch(elementVolField.values()[199],
                          expected_element_vector_field, 3));

  // // The last two faces
  EXPECT_TRUE(VectorMatch(elementVolField.values()[398],
                          expected_element_vector_field, 3));
  EXPECT_TRUE(VectorMatch(elementVolField.values()[399],
                          expected_element_vector_field, 3));
}

TEST(FieldTest, UseDefaultVectorVolField) {

  // --- Arrange ---
  std::string caseDirectory("../../cases/cavity");
  Mesh fvMesh(caseDirectory);
  ReadMesh meshReader;

  const std::array<double, 3> expected_element_vector_field = {0.0, 0.0, 0.0};

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);
  Field<std::array<double, 3>> elementVolField(fvMesh.nElements());

  // --- Assert ---
  // *** Verify the scalar field values of elements ***
  // The first two elements
  EXPECT_TRUE(VectorMatch(elementVolField.values()[0],
                          expected_element_vector_field, 3));
  EXPECT_TRUE(VectorMatch(elementVolField.values()[1],
                          expected_element_vector_field, 3));

  // // The middle two faces
  EXPECT_TRUE(VectorMatch(elementVolField.values()[198],
                          expected_element_vector_field, 3));
  EXPECT_TRUE(VectorMatch(elementVolField.values()[199],
                          expected_element_vector_field, 3));

  // // The last two faces
  EXPECT_TRUE(VectorMatch(elementVolField.values()[398],
                          expected_element_vector_field, 3));
  EXPECT_TRUE(VectorMatch(elementVolField.values()[399],
                          expected_element_vector_field, 3));
}