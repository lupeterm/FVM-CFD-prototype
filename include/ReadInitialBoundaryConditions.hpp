#ifndef READ_INITIAL_BOUNDARY_CONDITIONS_HPP
#define READ_INITIAL_BOUNDARY_CONDITIONS_HPP

#include "Mesh.hpp"
class ReadInitialBoundaryConditions {
public:
  void readOpenFoamInitialBoundaryConditions(Mesh &fvMesh);
  void readPressureField(Mesh &fvMesh);
  void readVelocityField(Mesh &fvMesh);
  void readTemperatureField(Mesh &fvMesh);
};

#endif // READ_INITIAL_BOUNDARY_CONDITIONS_HPP