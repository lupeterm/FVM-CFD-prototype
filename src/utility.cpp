#include <cmath>
#include <numeric>
#include <utility.h>

double mag(const std::array<double, 3> &v) {
  double innerProduct = std::inner_product(v.begin(), v.end(), v.begin(), 0.0);
  return std::sqrt(innerProduct);
}