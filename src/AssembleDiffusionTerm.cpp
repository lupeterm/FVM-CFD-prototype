#include "AssembleDiffusionTerm.hpp"
#include "Field.hpp"
#include <cstddef>

void AssembleDiffusionTerm::cellBaesdAssemble(Field &scalarField) {
  for (int iElement = 0; iElement < scalarField.nElements(); ++iElement) {
    // scalarField.values()[iElement] = 1.0;
  }
}

void AssembleDiffusionTerm::setValues(Field &scalarField, const double value) {
  for (std::size_t iElement = 0; iElement < scalarField.nElements();
       ++iElement) {
    scalarField.values()[iElement] = value;
  }
}