# Set the minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Create a project named FVM-CFD and set the project version number
project(FVM-CFD VERSION 1.0)

# Set the required version of C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Configure the file storing some info
#configure_file(Config.h.in Config.h)

# Add an executable called FVM-CFD to the project
add_executable(FVM-CFD readOpenFoamMesh.cpp)

# Use target_include_directories to include ${PROJECT_BINARY_DIR}
#target_include_directories(FVM-CFD PUBLIC "${PROJECT_BINARY_DIR}")