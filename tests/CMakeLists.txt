# # Declar a dependency on Google Test
# # 03597a01ee50ed33e9dfd640b249b4be3799d395 is the Git commit hash of the Google Test version to use
# # Updating the hash often to point to the latest version
# # include(FetchContent)
# # FetchContent_Declare(
# #   googletest
# #   URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
# # )
# # FetchContent_MakeAvailable(googletest)

# # Configure the file storing some info
# #configure_file(Config.h.in Config.h)

# # Add an executable called FVM-CFD to the project
# # add_executable(FVM-CFD readOpenFoamMesh.cpp)
# # add_library(readOpenFoamMesh readOpenFoamMesh.cpp)

# # Use target_include_directories to include ${PROJECT_BINARY_DIR}
# #target_include_directories(FVM-CFD PUBLIC "${PROJECT_BINARY_DIR}")

# # Google Test
# enable_testing()

# add_executable(
#     test_add
#     test_add.cpp
# )

# target_link_libraries(
#     test_add
#     MyLibrary
#     GTest::gtest_main
# )

# include(GoogleTest)
# gtest_discover_tests(test_add)

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
