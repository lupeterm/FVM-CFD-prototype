#include "AssembleDiffusionTerm.hpp"
#include <cstddef>

void AssembleDiffusionTerm::elementBasedAssemble(Mesh &fvMesh) {
  for (std::size_t iElement = 0; iElement < fvMesh.nElements(); ++iElement) {
    // Get the element
    // Go through the faces of the element
    // Calculate geometric factors
    // Calculate the coefficients due to different faces of a given element
    // Store the coefficients in a full matrix
  }
}
//   void AssembleDiffusionTerm::faceBasedAssemble() {}