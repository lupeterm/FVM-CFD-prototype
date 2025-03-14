// #include "AssembleDiffusionTerm.hpp"
#include "Field.hpp"
#include "Mesh.hpp"
#include "ReadMesh.hpp"
#include "testUtility.hpp"
#include <array>
#include <gtest/gtest.h>
#include <string>

// ****** Tests ******
TEST(FieldTest, SettingScalarFieldWorksForMesh) {

  // --- Arrange ---
  std::string caseDirectory("../../cases/Mycavity");
  ReadMesh meshReader;
  Mesh fvMesh(caseDirectory);

  const double expected_element0_scalar_field = 1.0;
  const double expected_element1_scalar_field = 1.0;
  const double expected_element198_scalar_field = 1.0;
  const double expected_element199_scalar_field = 1.0;
  const double expected_element398_scalar_field = 1.0;
  const double expected_element399_scalar_field = 1.0;

  const double maxDiff = 1.0e-9;
  const double maxRelativeDiff = 1.0e-4;

  // --- Act ---
  meshReader.readOpenFoamMesh(fvMesh);
  Field elementScalarField(fvMesh.nElements());
  elementScalarField.setValues();

  // --- Assert ---
  // *** Verify the scalar field values of elements ***
  // The first two elements
  EXPECT_EQ(elementScalarField.values()[0], expected_element0_scalar_field);
  EXPECT_EQ(elementScalarField.values()[1], expected_element1_scalar_field);

  // The middle two faces
  EXPECT_EQ(elementScalarField.values()[198], expected_element198_scalar_field);
  EXPECT_EQ(elementScalarField.values()[199], expected_element199_scalar_field);

  // The last two faces
  EXPECT_EQ(elementScalarField.values()[398], expected_element398_scalar_field);
  EXPECT_EQ(elementScalarField.values()[399], expected_element399_scalar_field);
}
