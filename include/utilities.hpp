#ifndef UTILITIES_HPP
#define UTILITIES_HPP

#include <array>

// Calculate the magnitude of a vector
double mag(const std::array<double, 3> &v);

// Calculate dot product of two vectors
double dot_product(const std::array<double, 3> &a,
                   const std::array<double, 3> &b);

// Calculate cross product of two vectors
std::array<double, 3> cross_product(const std::array<double, 3> &a,
                                    const std::array<double, 3> &b);

// Calculate the difference between two vectors by operator overloading
std::array<double, 3> operator-(const std::array<double, 3> &a,
                                const std::array<double, 3> &b);

// Calculate the product of a scalar and a vector by operator overloading
std::array<double, 3> operator*(double scalar, const std::array<double, 3> &a);
#endif