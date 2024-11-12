# Source directory
add_library(
    MyLibrary
    # main.cpp
    readOpenFoamMesh.cpp
)

target_include_directories(
    MyLibrary 
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)