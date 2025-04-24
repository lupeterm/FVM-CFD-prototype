#include "AssembleDiffusionTerm.hpp"
#include "Field.hpp"
#include <cstddef>

#include "ginkgo/ginkgo.hpp"
#include <iostream>

void AssembleDiffusionTerm::elementBasedAssemble(
    Mesh &fvMesh, const std::vector<double> diffusionCoef,
    const std::vector<double> &source,
    std::vector<boundaryField<double>> &boundaryFields,
    Matrix<double> &coeffMatrix, std::vector<double> &RHS) {

  const std::size_t nElements = fvMesh.nElements();

  for (std::size_t iElement = 0; iElement < nElements; ++iElement) {
    // Get the element
    Element &theElement = fvMesh.elements()[iElement];

    // Calculate the source term and it to the RHS
    RHS[iElement] = source[iElement] * theElement.volume();

    const std::size_t nFaces = theElement.iFaces().size();

    // Temporary storage of the diagonal entry of the coefficient matrix
    double diag = 0.0;

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
        coeffMatrix.build(iElement, theElement.iNeighbors()[iFace], FluxFn);
        diag += FluxCn;

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

        else if (boundaryType == "empty") { // empty BC for 1D or 2D problems
          // Do nothing because the face does not contribute
        }

        diag += FluxCb;
        RHS[iElement] -= FluxVb;

        // else if () { // mixed BC
        // }
      }
    }
    // Update the diagonal entry of the coefficient matrix in COO format
    coeffMatrix.build(iElement, iElement, diag);
  }
}
//   void AssembleDiffusionTerm::faceBasedAssemble() {}