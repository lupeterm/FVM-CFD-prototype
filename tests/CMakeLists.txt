# Google Test

add_executable(
  unitTests
  testReadOpenFoamUnstructuredMesh.cpp
  testProcessOpenFoamUnstructuredMesh.cpp
  testReadOpenFoamStructuredMesh.cpp
  testProcessOpenFoamStructuredMesh.cpp
  testField.cpp
  testReadInitialBoundaryConditions.cpp
  test-2D-heat-conduction.cpp
  testMatrix.cpp
)

# Link Ginkgo and Google Test to the target
target_link_libraries(
  unitTests
  MyLibrary
  GTest::gtest_main
  ginkgo
)

include(GoogleTest)
gtest_discover_tests(unitTests)

add_executable(
  testLinearSolver
  testLinearSolver.cpp
)

target_link_libraries(
  testLinearSolver
  MyLibrary
  GTest::gtest_main
  ginkgo
)

gtest_discover_tests(testLinearSolver)