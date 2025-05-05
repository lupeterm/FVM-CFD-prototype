#include "AssembleDiffusionTerm.hpp"
#include "Field.hpp"
#include <cstddef>

// The implementations of element-based assembly of the diffusion term
template <typename MatrixType>
void AssembleDiffusionTerm::elementBasedAssemble(
    Mesh &fvMesh, const std::vector<double> diffusionCoef,
    const std::vector<double> &source,
    std::vector<boundaryField<double>> &boundaryFields, MatrixType &coeffMatrix,
    std::vector<double> &RHS) {

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

      // Check if the face is an interior face or a boundary face
      if (theFace.iNeighbor() != -1) { // If it is an interior face
        double FluxCn = 0.0;
        double FluxFn = 0.0;
        // double FluxVn = 0.0; unused

        // Compute FluxCn, FluxFn and FluxVn
        FluxCn = diffusionCoef[iFaceIndex] * theFace.gDiff();
        FluxFn = -FluxCn;

        // Compute the coefficient matrix
        if constexpr (std::is_same_v<MatrixType, Matrix<double>>) {
          coeffMatrix(iElement, theElement.iNeighbors()[iFace]) = FluxFn;
        } else if constexpr (std::is_same_v<MatrixType,
                                            gko::matrix_data<double, int>>) {
          coeffMatrix.size = {fvMesh.nElements(), fvMesh.nElements()};
          coeffMatrix.nonzeros.emplace_back(
              iElement, theElement.iNeighbors()[iFace], FluxFn);
        } else {
          static_assert(
              std::is_same_v<MatrixType, Matrix<double>> ||
                  std::is_same_v<MatrixType, gko::matrix_data<double, int>>,
              "Unsupported MatrixType. Must be either Matrix<double> or "
              " gko::matrix_data<double, int>.");
        }
        // coeffMatrix(iElement, theElement.iNeighbors()[iFace]) = FluxFn;
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

    // Set the diagonal entry of the coefficient matrix
    if constexpr (std::is_same_v<MatrixType, Matrix<double>>) {
      coeffMatrix(iElement, iElement) = diag;
    } else if constexpr (std::is_same_v<MatrixType,
                                        gko::matrix_data<double, int>>) {
      coeffMatrix.nonzeros.emplace_back(iElement, iElement, diag);
    }
  }
}

// Explicit instantiation of the template function
template void AssembleDiffusionTerm::elementBasedAssemble(
    Mesh &fvMesh, const std::vector<double> diffusionCoef,
    const std::vector<double> &source,
    std::vector<boundaryField<double>> &boundaryFields,
    Matrix<double> &coeffMatrix, std::vector<double> &RHS);

template void AssembleDiffusionTerm::elementBasedAssemble(
    Mesh &fvMesh, const std::vector<double> diffusionCoef,
    const std::vector<double> &source,
    std::vector<boundaryField<double>> &boundaryFields,
    gko::matrix_data<double, int> &coeffMatrix, std::vector<double> &RHS);

// The implementations of face-based assembly of the diffusion term
template <typename MatrixType>
void AssembleDiffusionTerm::faceBasedAssemble(
    Mesh &fvMesh, const std::vector<double> diffusionCoef,
    const std::vector<double> &source,
    std::vector<boundaryField<double>> &boundaryFields, MatrixType &coeffMatrix,
    std::vector<double> &RHS) {

  // Loop over all the faces of the given mesh
  const std::size_t nFaces = fvMesh.nFaces();
  for (std::size_t iFace = 0; iFace < nFaces; ++iFace) {
    // Get the face
    Face &theFace = fvMesh.faces()[iFace];

    // Check if the face is an interior face or a boundary face
    if (theFace.iNeighbor() != -1) { // If it is an interior face
      double FluxCn = 0.0;
      double FluxFn = 0.0;
      // double FluxVn = 0.0; unused

      // Compute FluxCn, FluxFn and FluxVn for the owner cell and the neighbor
      // cell
      FluxCn = diffusionCoef[iFace] * theFace.gDiff();
      FluxFn = -FluxCn;

      coeffMatrix(theFace.iOwner(), theFace.iNeighbor()) = FluxFn;
      coeffMatrix(theFace.iNeighbor(), theFace.iOwner()) = FluxFn;

      coeffMatrix(theFace.iOwner(), theFace.iOwner()) += FluxCn;
      coeffMatrix(theFace.iNeighbor(), theFace.iNeighbor()) += FluxCn;
    }

    else { // If it is a boundary face
      // Get the boundary type
      const std::size_t iBoundary = fvMesh.faces()[iFace].patchIndex();
      const std::string &boundaryType =
          boundaryFields[iBoundary].boundaryType();

      double FluxCb = 0.0;
      double FluxVb = 0.0;

      if (boundaryType == "fixedValue") { // Dirichlet BC
        FluxCb = diffusionCoef[iFace] * theFace.gDiff();

        std::size_t relativeFaceIndex =
            iFace - fvMesh.boundaries()[iBoundary].startFace();
        FluxVb =
            -FluxCb * boundaryFields[iBoundary].values()[relativeFaceIndex];
      }

      else if (boundaryType == "zeroGradient") { // zero Neumann BC
        // Do nothing because FluxCb and FluxVb are already 0.0
      }

      else if (boundaryType == "empty") { // empty BC for 1D or 2D problems
        // Do nothing because the face does not contribute
      }

      coeffMatrix(theFace.iOwner(), theFace.iOwner()) += FluxCb;
      RHS[theFace.iOwner()] -= FluxVb;

      // else if () { // mixed BC
      // }
    }
  }
}

// Explicit instantiation of the template function
template void AssembleDiffusionTerm::faceBasedAssemble(
    Mesh &fvMesh, const std::vector<double> diffusionCoef,
    const std::vector<double> &source,
    std::vector<boundaryField<double>> &boundaryFields,
    Matrix<double> &coeffMatrix, std::vector<double> &RHS);