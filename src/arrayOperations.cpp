#include "arrayOperations.hpp"
#include <cmath>
#include <numeric>

double mag(const std::array<double, 3> &v) {
  double innerProduct = std::inner_product(v.begin(), v.end(), v.begin(), 0.0);
  return std::sqrt(innerProduct);
}

double dot_product(const std::array<double, 3> &a,
                   const std::array<double, 3> &b) {
  return std::inner_product(a.begin(), a.end(), b.begin(), 0.0);
}

std::array<double, 3> cross_product(const std::array<double, 3> &a,
                                    const std::array<double, 3> &b) {
  return {a[1] * b[2] - a[2] * b[1], a[2] * b[0] - a[0] * b[2],
          a[0] * b[1] - a[1] * b[0]};
}

// Calculate the difference between two vectors by operator overloading
std::array<double, 3> operator-(const std::array<double, 3> &a,
                                const std::array<double, 3> &b) {
  return {a[0] - b[0], a[1] - b[1], a[2] - b[2]};
}

// Calculate the product of a scalar and a vector by operator overloading
std::array<double, 3> operator*(double scalar, const std::array<double, 3> &a) {
  return {scalar * a[0], scalar * a[1], scalar * a[2]};
}
