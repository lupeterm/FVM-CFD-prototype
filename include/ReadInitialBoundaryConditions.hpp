#ifndef READ_INITIAL_BOUNDARY_CONDITIONS_HPP
#define READ_INITIAL_BOUNDARY_CONDITIONS_HPP

#include "Field.hpp"
#include "Mesh.hpp"

class ReadInitialBoundaryConditions {
public:
  void readOpenFoamInitialBoundaryConditions(
      Mesh &fvMesh, Field<std::array<double, 3>> &internalVelocityField,
      std::vector<boundaryField<std::array<double, 3>>> &boundaryVelocityFields,
      Field<double> &internalTemperatureField,
      std::vector<boundaryField<double>> &boundaryTemperatureFields);

  void readVelocityField(Mesh &fvMesh,
                         Field<std::array<double, 3>> &internalVelocityField,
                         std::vector<boundaryField<std::array<double, 3>>>
                             &boundaryVelocityFields);

  void readTemperatureField(
      Mesh &fvMesh, Field<double> &internalTemperatureField,
      std::vector<boundaryField<double>> &boundaryTemperatureFields);

  // TO DO:
  // void readPressureField(Mesh &fvMesh);
};

#endif // READ_INITIAL_BOUNDARY_CONDITIONS_HPP