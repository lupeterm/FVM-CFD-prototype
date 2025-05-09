#include "PostProcessing.hpp"
#include <stdexcept>

double PostProcessing::averageL2Norm(const std::vector<double> &vec1,
                                     const std::vector<double> &vec2) {
  if (vec1.size() != vec2.size()) {
    throw std::invalid_argument("Vectors must be of the same size.");
  }

  double sum = 0.0;
  for (size_t i = 0; i < vec1.size(); ++i) {
    double diff = vec1[i] - vec2[i];
    sum += diff * diff;
  }

  return std::sqrt(sum / vec1.size());
}
