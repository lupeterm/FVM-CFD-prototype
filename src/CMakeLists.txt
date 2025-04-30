# Source directory
add_library(
    MyLibrary
    ReadMesh.cpp
    IO.cpp
    ProcessMesh.cpp
    arrayOperations.cpp
    ReadInitialBoundaryConditions.cpp
    Matrix.cpp
    AssembleDiffusionTerm.cpp
    LinearSolver.cpp
)

target_include_directories(
    MyLibrary 
    PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(
    MyLibrary
    PUBLIC
    ginkgo
)