# Google Test
enable_testing()

add_executable(
  test_readOpenFoamMesh
  testReadOpenFoamMesh.cpp
)

target_link_libraries(
  test_readOpenFoamMesh
  MyLibrary
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_readOpenFoamMesh)
