# Source directory
add_library(
    MyLibrary
    readMesh.cpp
    processMesh.cpp
)

target_include_directories(
    MyLibrary 
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)