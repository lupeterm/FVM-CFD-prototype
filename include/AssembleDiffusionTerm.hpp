#ifndef ASSERMBLE_DIFF_HPP
#define ASSERMBLE_DIFF_HPP

#include "Field.hpp"
#include "Matrix.hpp"
#include "Mesh.hpp"

class AssembleDiffusionTerm {
public:
  // Assemble the diffusion term on a Cartesian orthogonal mesh by looping over
  // the elements (cells)
  void elementBasedAssemble(Mesh &fvMesh,
                            const std::vector<double> diffusionCoef,
                            const std::vector<double> &source,
                            std::vector<boundaryField<double>> &boundaryFields,
                            Matrix<double> &coeffMatrix,
                            std::vector<double> &RHS);

  // Assemble the diffusion term on a Cartesian orthogonal mesh by looping over
  // the faces
  // void faceBasedAssemble();

private:
};
#endif // ASSERMBLE_DIFF_HPP