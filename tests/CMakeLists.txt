# Google Test
enable_testing()

add_executable(
  test_readAndProcessOpenFoamMesh
  testReadOpenFoamMesh.cpp
  testProcessOpenFoamMesh.cpp
)

target_link_libraries(
  test_readAndProcessOpenFoamMesh
  MyLibrary
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_readAndProcessOpenFoamMesh)
