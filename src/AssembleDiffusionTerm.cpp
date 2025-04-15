#include "AssembleDiffusionTerm.hpp"
#include "Field.hpp"
#include <cstddef>

void AssembleDiffusionTerm::elementBasedAssemble(
    Mesh &fvMesh, const std::vector<double> diffusionCoef,
    const std::vector<double> &Q,
    std::vector<boundaryField<double>> &boundaryFields,
    std::vector<std::vector<double>> &coeffMatrix, std::vector<double> &RHS) {

  const std::size_t nElements = fvMesh.nElements();

  // Declare a 2D array for coefficient matrix corresponding to the discrete
  // form of diffusion equation
  // std::vector<std::vector<double>> coeffMatrix(
  //     nElements, std::vector<double>(nElements, 0.0));

  for (std::size_t iElement = 0; iElement < nElements; ++iElement) {
    // Get the element
    Element &theElement = fvMesh.elements()[iElement];

    // Calculate the source term and it to the RHS
    RHS[iElement] = Q[iElement] * theElement.volume();

    const std::size_t nFaces = theElement.iFaces().size();

    for (std::size_t iFace = 0; iFace < nFaces; ++iFace) {
      // Get the face
      const std::size_t iFaceIndex = theElement.iFaces()[iFace];
      Face &theFace = fvMesh.faces()[iFaceIndex];

      double FluxCn = 0.0;
      double FluxFn = 0.0;
      double FluxVn = 0.0;

      // Check if the face is an interior face or a boundary face
      if (theFace.iNeighbor() != -1) { // If it is an interior face
        // Compute FluxCn, FluxFn and FluxVn
        FluxCn = diffusionCoef[iFaceIndex] * theFace.gDiff();
        FluxFn = -FluxCn;

        // Compute the coefficient matrix
        coeffMatrix[iElement][theElement.iNeighbors()[iFace]] = FluxFn;
        coeffMatrix[iElement][iElement] += FluxCn;

      } else { // If it is a boundary face
        // Get the boundary type
        const std::size_t iBoundary = fvMesh.faces()[iFaceIndex].patchIndex();
        const std::string &boundaryType =
            boundaryFields[iBoundary].boundaryType();

        double FluxCb = 0.0;
        double FluxVb = 0.0;

        if (boundaryType == "fixedValue") { // Dirichlet BC
          FluxCb = diffusionCoef[iFaceIndex] * theFace.gDiff();

          std::size_t relativeFaceIndex =
              iFaceIndex - fvMesh.boundaries()[iBoundary].startFace();
          FluxVb =
              -FluxCb * boundaryFields[iBoundary].values()[relativeFaceIndex];
        }

        else if (boundaryType == "zeroGradient") { // zero Neumann BC
          // Do nothing because FluxCb and FluxVb are already 0.0
        }

        coeffMatrix[iElement][iElement] += FluxCb;
        RHS[iElement] -= FluxVb;

        // else if () { // mixed BC
        // }
      }
    }
  }
}
//   void AssembleDiffusionTerm::faceBasedAssemble() {}