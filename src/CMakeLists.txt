# Source directory
add_library(
    MyLibrary
    ReadMesh.cpp
    IO.cpp
    ProcessMesh.cpp
    arrayOperations.cpp
    ReadInitialBoundaryConditions.cpp
    AssembleDiffusionTerm.cpp
)

target_include_directories(
    MyLibrary 
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)