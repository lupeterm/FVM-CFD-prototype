#ifndef POST_PROCESSING_HPP
#define POST_PROCESSING_HPP

#include <cmath>
#include <vector>

class PostProcessing {
public:
  // Calculate the L2 norm of the difference between two vectors
  static double averageL2Norm(const std::vector<double> &vec1,
                              const std::vector<double> &vec2);
};

#endif // POST_PROCESSING_HPP