# Google Test
enable_testing()

add_executable(
  test_add
  test_add.cpp
)

target_link_libraries(
  test_add
  MyLibrary
  GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_add)
