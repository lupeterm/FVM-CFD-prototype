#include <cmath>
#include <numeric>
#include <utility.h>

double mag(const std::array<double, 3> &v) {
  double innerProduct = std::inner_product(v.begin(), v.end(), v.begin(), 0.0);
  return std::sqrt(innerProduct);
}

double dot_product(const std::array<double, 3> &v1,
                   const std::array<double, 3> &v2) {
  return std::inner_product(v1.begin(), v1.end(), v2.begin(), 0.0);
}