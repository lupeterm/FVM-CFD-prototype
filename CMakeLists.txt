# # Set the minimum required version of CMake
# cmake_minimum_required(VERSION 3.14)

# # Create a project named FVM-CFD and set the project version number
# project(FVM-CFD VERSION 1.0)

# # Set the required version of C++ standard
# set(CMAKE_CXX_STANDARD 14)
# set(CMAKE_CXX_STANDARD_REQUIRED ON)

# # Add subdirectories
# add_subdirectory(src)
# add_subdirectory(tests)
# add_subdirectory(lib)

# # Include directories
# include_directories(include)
# # # Declar a dependency on Google Test
# # # 03597a01ee50ed33e9dfd640b249b4be3799d395 is the Git commit hash of the Google Test version to use
# # # Updating the hash often to point to the latest version
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

# # add_subdirectory(tests)

# # enable_testing()

# # add_executable(
# #     hello_test
# #     hello_test.cc
# # )

# # target_link_libraries(
# #     hello_test
# #     GTest::gtest_main
# # )

# # include(GoogleTest)
# # gtest_discover_tests(hello_test)

cmake_minimum_required(VERSION 3.14)
project(MyProject)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add subdirectories
add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(lib)

# Include directories
# include_directories(include)
# include_directories(${CMAKE_SOURCE_DIR}/include)

