#ifndef UTILITY
#define UTILITY

#include <array>

// Calculate the magnitude of a vector
double mag(const std::array<double, 3> &v);

// Calculate dot product of two vectors
double dot_product(const std::array<double, 3> &v1,
                   const std::array<double, 3> &v2);
#endif