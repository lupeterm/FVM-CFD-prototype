#ifndef ASSERMBLE_DIFF_HPP
#define ASSERMBLE_DIFF_HPP

#include "Field.hpp"
#include "Matrix.hpp"
#include "Mesh.hpp"
#include "ginkgo/ginkgo.hpp"

class AssembleDiffusionTerm {
public:
  // Assemble the diffusion term on a Cartesian orthogonal mesh by looping over
  // the elements (cells)
  template <typename MatrixType>
  void elementBasedAssemble(Mesh &fvMesh,
                            const std::vector<double> diffusionCoef,
                            const std::vector<double> &source,
                            std::vector<boundaryField<double>> &boundaryFields,
                            MatrixType &coeffMatrix, std::vector<double> &RHS);

  // Assemble the diffusion term on a Cartesian orthogonal mesh by looping over
  // the faces
  template <typename MatrixType>
  void faceBasedAssemble(Mesh &fvMesh, const std::vector<double> diffusionCoef,
                         const std::vector<double> &source,
                         std::vector<boundaryField<double>> &boundaryFields,
                         MatrixType &coeffMatrix, std::vector<double> &RHS);
};

// Prevent implicit instantiation of the template function for these types
extern template void AssembleDiffusionTerm::elementBasedAssemble(
    Mesh &fvMesh, const std::vector<double> diffusionCoef,
    const std::vector<double> &source,
    std::vector<boundaryField<double>> &boundaryFields,
    Matrix<double> &coeffMatrix, std::vector<double> &RHS);

extern template void AssembleDiffusionTerm::elementBasedAssemble(
    Mesh &fvMesh, const std::vector<double> diffusionCoef,
    const std::vector<double> &source,
    std::vector<boundaryField<double>> &boundaryFields,
    gko::matrix_data<double, int> &coeffMatrix, std::vector<double> &RHS);

extern template void AssembleDiffusionTerm::faceBasedAssemble(
    Mesh &fvMesh, const std::vector<double> diffusionCoef,
    const std::vector<double> &source,
    std::vector<boundaryField<double>> &boundaryFields,
    Matrix<double> &coeffMatrix, std::vector<double> &RHS);

extern template void AssembleDiffusionTerm::faceBasedAssemble(
    Mesh &fvMesh, const std::vector<double> diffusionCoef,
    const std::vector<double> &source,
    std::vector<boundaryField<double>> &boundaryFields,
    gko::matrix_data<double, int> &coeffMatrix, std::vector<double> &RHS);

#endif // ASSERMBLE_DIFF_HPP