#ifndef ASSERMBLE_DIFF_HPP
#define ASSERMBLE_DIFF_HPP

#include "Field.hpp"
#include "Mesh.hpp"

class AssembleDiffusionTerm {
public:
  // Assemble the diffusion term on a Cartesian orthogonal mesh by looping over
  // the elements (cells)
  void elementBasedAssemble(Mesh &fvMesh,
                            const std::vector<double> diffusionCoef,
                            const std::vector<double> &Q,
                            std::vector<boundaryField<double>> &boundaryFields,
                            std::vector<std::vector<double>> &coeffMatrix,
                            std::vector<double> &RHS);

  // Assemble the diffusion term on a Cartesian orthogonal mesh by looping over
  // the faces
  // void faceBasedAssemble();

private:
};
#endif // ASSERMBLE_DIFF_HPP