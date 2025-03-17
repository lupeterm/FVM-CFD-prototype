# Google Test
enable_testing()

add_executable(
  unitTests
  testReadOpenFoamUnstructuredMesh.cpp
  testProcessOpenFoamUnstructuredMesh.cpp
  testReadOpenFoamStructuredMesh.cpp
  testProcessOpenFoamStructuredMesh.cpp
  testField.cpp
  # testIO.cpp  // Don't include this file for automatic testing
)

target_link_libraries(
  unitTests
  MyLibrary
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(unitTests)
