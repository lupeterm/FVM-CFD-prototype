# Source directory
add_library(
    MyLibrary
    ReadMesh.cpp
    ProcessMesh.cpp
    utilities.cpp
    AssembleDiffusionTerm.cpp
)

target_include_directories(
    MyLibrary 
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)