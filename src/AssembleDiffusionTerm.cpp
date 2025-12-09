#include "AssembleDiffusionTerm.hpp"

#include "Field.hpp"

#include <cstddef>

// The implementations of element-based assembly of the diffusion term
void AssembleDiffusionTerm::cellBasedAssemble(
    Mesh &fvMesh,
    const double diffusionCoef,
    Field<std::array<double, 3>> &internalVelocity,
    std::vector<boundaryField<std::array<double, 3>>> &boundaryFields,
    std::vector<gko::matrix_data<double, int>> &coeffMatrix,
    std::vector<std::array<double, 3>> &RHS)
{
  const std::size_t nCells = fvMesh.nCells();

  for (size_t dim = 0; dim < 3; dim++) {
    coeffMatrix[dim].size = {nCells, nCells};
  }

  for (std::size_t iElement = 0; iElement < nCells; ++iElement) {
    // Get the element
    Cell &theElement = fvMesh.cells()[iElement];

    // Calculate the source term and it to the RHS
    // RHS[iElement] = source[iElement] * theElement.volume();

    const std::size_t nFaces = theElement.iFaces().size();

    // Temporary storage of the diagonal entry of the coefficient matrix
    auto diag = internalVelocity.values()[iElement];

    for (std::size_t iFace = 0; iFace < nFaces; ++iFace) {

      // Get the face
      const std::size_t iFaceIndex = theElement.iFaces()[iFace];
      Face &theFace = fvMesh.faces()[iFaceIndex];
      // Check if the face is an interior face or a boundary face
      if (theFace.iNeighbor() != -1) { // If it is an interior face
        double FluxFn = 0.0;
        double FluxCn = 0.0;

        // double FluxVn = 0.0; unused

        // Compute FluxCn, FluxFn and FluxVn
        FluxCn = diffusionCoef * theFace.gDiff();
        FluxFn = -FluxCn;

        // Compute the coefficient matrix
        // if constexpr (std::is_same_v<MatrixType, Matrix<std::array<double, 3>>>) {
        //   for (size_t dim = 0; dim < 3; dim++) {
        //     coeffMatrix(iElement, theElement.iNeighbors()[iFace]) = FluxFn;
        //   }

        // } else if constexpr (std::is_same_v<
        //                          MatrixType,
        //                          gko::matrix_data<double, int>>) {

        for (size_t dim = 0; dim < 3; dim++) {
          coeffMatrix[dim].nonzeros.emplace_back(
              iElement,
              theElement.iNeighbors()[iFace],
              FluxFn);
        }
        for (size_t dim = 0; dim < 3; dim++) {
          diag[dim] += FluxCn;
        }
      } else { // If it is a boundary face
        // Get the boundary type

        const std::size_t iBoundary = fvMesh.faces()[iFaceIndex].patchIndex();
        const std::string &boundaryType =
            boundaryFields[iBoundary].boundaryType();

        double FluxCb = 0.0;
        std::array<double, 3> FluxVb{0.0, 0.0, 0.0};

        if (boundaryType == "fixedValue") { // Dirichlet BC

          FluxCb = diffusionCoef * theFace.gDiff();

          std::size_t relativeFaceIndex =
              iFaceIndex - fvMesh.boundaries()[iBoundary].startFace();
          // FluxVb = -FluxCb *
          // boundaryFields[iBoundary].values()[relativeFaceIndex];

          for (size_t dim = 0; dim < 3; dim++) {
            diag[dim] += FluxCb;
          }
          for (size_t dim = 0; dim < 3; dim++) {
            RHS[iElement][dim] -=
                -FluxCb *
                boundaryFields[iBoundary].values()[relativeFaceIndex][dim];
          }
        }

        else if (boundaryType == "zeroGradient") { // zero Neumann BC
                                                   // Do nothing because FluxCb
                                                   // and FluxVb are already 0.0
        }

        else if (boundaryType == "empty") { // empty BC for 1D or 2D problems
                                            // Do nothing because the face does
                                            // not contribute
        }

        // else if () { // mixed BC
        // }
      }
    }

    // Set the diagonal entry of the coefficient matrix
    // if constexpr (std::is_same_v<MatrixType, Matrix<std::array<double, 3>>>) {
    //   for (size_t dim = 0; dim < 3; dim++) {
    //     coeffMatrix(iElement, iElement) = diag[dim];
    //   }

    // } else if constexpr (std::is_same_v<
    //                          MatrixType,
    //                          gko::matrix_data<double, int>>) {

    for (size_t dim = 0; dim < 3; dim++) {
      coeffMatrix[dim].nonzeros.emplace_back(
          iElement,
          iElement,
          diag[dim]);
    }
    // }
  }
}

// Explicit instantiation of the template function cellBasedAssemble
// template void AssembleDiffusionTerm::cellBasedAssemble(
//     Mesh &fvMesh,
//     const double diffusionCoef,
//     Field<std::array<double, 3>> &internalVelocity,
//     std::vector<boundaryField<std::array<double, 3>>> &boundaryFields,
//     std::vector<Matrix<double>> &coeffMatrix,
//     std::vector<std::array<double, 3>> &RHS);

// template void AssembleDiffusionTerm::cellBasedAssemble(
//     Mesh &fvMesh,
//     const double diffusionCoef,
//     Field<std::array<double, 3>> &internalVelocity,
//     std::vector<boundaryField<std::array<double, 3>>> &boundaryFields,
//     std::vector<gko::matrix_data<double, int>> &coeffMatrix,
//     std::vector<std::array<double, 3>> &RHS);

// The implementations of face-based assembly of the diffusion term
template <typename MatrixType>
void AssembleDiffusionTerm::faceBasedAssemble(
    Mesh &fvMesh,
    const std::vector<double> diffusionCoef,
    const std::vector<double> &source,
    std::vector<boundaryField<double>> &boundaryFields,
    MatrixType &coeffMatrix,
    std::vector<double> &RHS)
{
  if constexpr (std::is_same_v<MatrixType, gko::matrix_data<double, int>>) {
    coeffMatrix.size = {fvMesh.nCells(), fvMesh.nCells()};
  }

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

      if constexpr (std::is_same_v<MatrixType, Matrix<double>>) {
        coeffMatrix(theFace.iOwner(), theFace.iNeighbor()) = FluxFn;
        coeffMatrix(theFace.iNeighbor(), theFace.iOwner()) = FluxFn;

        coeffMatrix(theFace.iOwner(), theFace.iOwner()) += FluxCn;
        coeffMatrix(theFace.iNeighbor(), theFace.iNeighbor()) += FluxCn;
      } else if constexpr (std::is_same_v<
                               MatrixType,
                               gko::matrix_data<double, int>>) {
        coeffMatrix.nonzeros.emplace_back(
            theFace.iOwner(),
            theFace.iNeighbor(),
            FluxFn);
        coeffMatrix.nonzeros.emplace_back(
            theFace.iNeighbor(),
            theFace.iOwner(),
            FluxFn);

        coeffMatrix.nonzeros.emplace_back(
            theFace.iOwner(),
            theFace.iOwner(),
            FluxCn);
        coeffMatrix.nonzeros.emplace_back(
            theFace.iNeighbor(),
            theFace.iNeighbor(),
            FluxCn);
      }

      else {
        static_assert(
            std::is_same_v<MatrixType, Matrix<double>> ||
                std::is_same_v<MatrixType, gko::matrix_data<double, int>>,
            "Unsupported MatrixType. Must be either Matrix<double> or "
            "gko::matrix_data<double, int>.");
      }
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

        if constexpr (std::is_same_v<MatrixType, Matrix<double>>) {
          coeffMatrix(theFace.iOwner(), theFace.iOwner()) += FluxCb;
        } else if constexpr (std::is_same_v<
                                 MatrixType,
                                 gko::matrix_data<double, int>>) {
          coeffMatrix.nonzeros.emplace_back(
              theFace.iOwner(),
              theFace.iOwner(),
              FluxCb);
        } else {
          static_assert(
              std::is_same_v<MatrixType, Matrix<double>> ||
                  std::is_same_v<MatrixType, gko::matrix_data<double, int>>,
              "Unsupported MatrixType. Must be either Matrix<double> or "
              "gko::matrix_data<double, int>.");
        }
        RHS[theFace.iOwner()] -= FluxVb;
      }

      else if (boundaryType == "zeroGradient") { // zero Neumann BC
                                                 // Do nothing because FluxCb
                                                 // and FluxVb are already 0.0
      }

      else if (boundaryType == "empty") { // empty BC for 1D or 2D problems
                                          // Do nothing because the face does
                                          // not contribute
      }

      // else if () { // mixed BC
      // }
    }
  }
  if constexpr (std::is_same_v<MatrixType, gko::matrix_data<double, int>>) {
    coeffMatrix.sum_duplicates();
  }
}

// Explicit instantiation of the template function faceBasedAssemble
template void AssembleDiffusionTerm::faceBasedAssemble(
    Mesh &fvMesh,
    const std::vector<double> diffusionCoef,
    const std::vector<double> &source,
    std::vector<boundaryField<double>> &boundaryFields,
    Matrix<double> &coeffMatrix,
    std::vector<double> &RHS);

template void AssembleDiffusionTerm::faceBasedAssemble(
    Mesh &fvMesh,
    const std::vector<double> diffusionCoef,
    const std::vector<double> &source,
    std::vector<boundaryField<double>> &boundaryFields,
    gko::matrix_data<double, int> &coeffMatrix,
    std::vector<double> &RHS);

// The implementations of batched face-based assembly of the diffusion term
template <typename MatrixType>
void AssembleDiffusionTerm::batchedFaceBasedAssemble(
    Mesh &fvMesh,
    const std::vector<double> diffusionCoef,
    const std::vector<double> &source,
    std::vector<boundaryField<double>> &boundaryFields,
    MatrixType &coeffMatrix,
    std::vector<double> &RHS)
{
  if constexpr (std::is_same_v<MatrixType, gko::matrix_data<double, int>>) {
    coeffMatrix.size = {fvMesh.nCells(), fvMesh.nCells()};
  }

  // *** Loop over all the interior faces of the given mesh ***
  const std::size_t nInteriorFaces = fvMesh.nInteriorFaces();
  for (std::size_t iFace = 0; iFace < nInteriorFaces; ++iFace) {
    // Get the face
    Face &theFace = fvMesh.faces()[iFace];

    double FluxCn = 0.0;
    double FluxFn = 0.0;
    // double FluxVn = 0.0; unused

    // Compute FluxCn, FluxFn and FluxVn for the owner cell and the neighbor
    // cell
    FluxCn = diffusionCoef[iFace] * theFace.gDiff();
    FluxFn = -FluxCn;

    if constexpr (std::is_same_v<MatrixType, Matrix<double>>) {
      coeffMatrix(theFace.iOwner(), theFace.iNeighbor()) = FluxFn;
      coeffMatrix(theFace.iNeighbor(), theFace.iOwner()) = FluxFn;

      coeffMatrix(theFace.iOwner(), theFace.iOwner()) += FluxCn;
      coeffMatrix(theFace.iNeighbor(), theFace.iNeighbor()) += FluxCn;
    } else if constexpr (std::is_same_v<
                             MatrixType,
                             gko::matrix_data<double, int>>) {
      coeffMatrix.nonzeros.emplace_back(
          theFace.iOwner(),
          theFace.iNeighbor(),
          FluxFn);
      coeffMatrix.nonzeros.emplace_back(
          theFace.iNeighbor(),
          theFace.iOwner(),
          FluxFn);

      coeffMatrix.nonzeros.emplace_back(
          theFace.iOwner(),
          theFace.iOwner(),
          FluxCn);
      coeffMatrix.nonzeros.emplace_back(
          theFace.iNeighbor(),
          theFace.iNeighbor(),
          FluxCn);
    }

    else {
      static_assert(
          std::is_same_v<MatrixType, Matrix<double>> ||
              std::is_same_v<MatrixType, gko::matrix_data<double, int>>,
          "Unsupported MatrixType. Must be either Matrix<double> or "
          "gko::matrix_data<double, int>.");
    }
  }

  // *** Loop over all the boundary faces of the given mesh patch by patch ***
  const std::size_t nBoundaries = fvMesh.nBoundaries();
  for (std::size_t iBoundary = 0; iBoundary < nBoundaries; ++iBoundary) {
    // Get the boundary
    Boundary &theBoundary = fvMesh.boundaries()[iBoundary];

    // Get the start and end face index of the boundary
    const std::size_t startFace = theBoundary.startFace();
    const std::size_t endFace = startFace + theBoundary.nFaces();

    // Get the boundary type
    const std::string &boundaryType = boundaryFields[iBoundary].boundaryType();

    if (boundaryType == "fixedValue") { // Dirichlet BC

      // Loop over all the faces of the boundary
      for (std::size_t iFace = startFace; iFace < endFace; ++iFace) {
        // Get the face
        Face &theFace = fvMesh.faces()[iFace];

        double FluxCb = 0.0;
        double FluxVb = 0.0;

        FluxCb = diffusionCoef[iFace] * theFace.gDiff();

        std::size_t relativeFaceIndex =
            iFace - fvMesh.boundaries()[iBoundary].startFace();
        FluxVb =
            -FluxCb * boundaryFields[iBoundary].values()[relativeFaceIndex];

        RHS[theFace.iOwner()] -= FluxVb;

        if constexpr (std::is_same_v<MatrixType, Matrix<double>>) {
          coeffMatrix(theFace.iOwner(), theFace.iOwner()) += FluxCb;
        } else if constexpr (std::is_same_v<
                                 MatrixType,
                                 gko::matrix_data<double, int>>) {
          coeffMatrix.nonzeros.emplace_back(
              theFace.iOwner(),
              theFace.iOwner(),
              FluxCb);
        } else {
          static_assert(
              std::is_same_v<MatrixType, Matrix<double>> ||
                  std::is_same_v<MatrixType, gko::matrix_data<double, int>>,
              "Unsupported MatrixType. Must be either Matrix<double> or "
              "gko::matrix_data<double, int>.");
        }
      }
    } else if (boundaryType == "zeroGradient") { // zero Neumann BC
                                                 // Do nothing because FluxCb
                                                 // and FluxVb are already 0.0
    }

    else if (boundaryType == "empty") { // empty BC for 1D or 2D problems
                                        // Do nothing because the face does not
                                        // contribute
    }
  }

  if constexpr (std::is_same_v<MatrixType, gko::matrix_data<double, int>>) {
    coeffMatrix.sum_duplicates();
  }
}

// Explicit instantiation of the template function batchedFaceBasedAssemble
template void AssembleDiffusionTerm::batchedFaceBasedAssemble(
    Mesh &fvMesh,
    const std::vector<double> diffusionCoef,
    const std::vector<double> &source,
    std::vector<boundaryField<double>> &boundaryFields,
    Matrix<double> &coeffMatrix,
    std::vector<double> &RHS);

template void AssembleDiffusionTerm::batchedFaceBasedAssemble(
    Mesh &fvMesh,
    const std::vector<double> diffusionCoef,
    const std::vector<double> &source,
    std::vector<boundaryField<double>> &boundaryFields,
    gko::matrix_data<double, int> &coeffMatrix,
    std::vector<double> &RHS);