#ifndef ASSERMBLE_DIFF_HPP
#define ASSERMBLE_DIFF_HPP

// #include "Field.hpp"
#include "Mesh.hpp"

class AssembleDiffusionTerm {
public:
  // Assemble the diffusion term on a Cartesian orthogonal mesh by looping over
  // the elements (cells)
  void AssembleDiffusionTerm::elementBasedAssemble(Mesh &fvMesh,
                                                   const double *diffusionCoef);

  // Assemble the diffusion term on a Cartesian orthogonal mesh by looping over
  // the faces
  // void faceBasedAssemble();

private:
};
#endif // ASSERMBLE_DIFF_HPP