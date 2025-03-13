#ifndef ASSERMBLE_DIFF_HPP
#define ASSERMBLE_DIFF_HPP

#include "Field.hpp"

class AssembleDiffusionTerm {
public:
  // Assemble the diffusion term on a structured mesh
  void cellBaesdAssemble(Field &scalarField);

  // Set the values of a scalar field to 1.0
  void setValues(Field &scalarField, const double value = 1.0);

private:
};
#endif // ASSERMBLE_DIFF_HPP