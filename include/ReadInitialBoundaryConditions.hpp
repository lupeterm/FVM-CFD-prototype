#ifndef READ_INITIAL_BOUNDARY_CONDITIONS_HPP
#define READ_INITIAL_BOUNDARY_CONDITIONS_HPP

#include "Field.hpp"
#include "Mesh.hpp"

class ReadInitialBoundaryConditions {
public:
  void readOpenFoamInitialBoundaryConditions(
      Mesh &fvMesh, Field<std::array<double, 3>> &internalVelocityField,
      std::vector<Field<std::array<double, 3>>> &boundaryVelocityFields);
  //   void readPressureField(Mesh &fvMesh);
  void readVelocityField(
      Mesh &fvMesh, Field<std::array<double, 3>> &internalVelocityField,
      std::vector<Field<std::array<double, 3>>> &boundaryVelocityFields);

  //   void readTemperatureField(Mesh &fvMesh);
};

#endif // READ_INITIAL_BOUNDARY_CONDITIONS_HPP