#include "AssembleDiffusionTerm.hpp"
#include <cstddef>

void AssembleDiffusionTerm::elementBasedAssemble(Mesh &fvMesh) {
  for (std::size_t iElement = 0; iElement < fvMesh.nElements(); ++iElement) {
    // Get the element
    Element &element = fvMesh.elements()[iElement];
    const std::size_t nFaces = element.iFaces().size();

    // Go through the faces of the element
    for (std::size_t iFace = 0; iFace < nFaces; ++iFace) {
      // Get the face
      Face &face = fvMesh.faces()[element.iFaces()[iFace]];

      // Judege if the face is an interior face or a boundary face
      if (face.iNeighbor() != -1) {
        // The face is an interior face
        // Get the neighbor element
        // Element &neighborElement = fvMesh.elements()[face.iNeighbor()];

        // Get the geometric factors gDiff

        // Calculate the coefficients due to different faces of a given element
        // Store the coefficients in a full matrix
      } else {
        // The face is a boundary face
        // Get the patch index of the face
        // std::size_t patchIndex = face.patchIndex();

        // Calculate the geometric factors
        // Calculate the coefficients due to different faces of a given element
        // Store the coefficients in a full matrix
      }
    }
    // Calculate geometric factors
    // Calculate the coefficients due to different faces of a given element
    // Store the coefficients in a full matrix
  }
}
//   void AssembleDiffusionTerm::faceBasedAssemble() {}