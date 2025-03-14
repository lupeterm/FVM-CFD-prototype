#ifndef FIELD_HPP
#define FIELD_HPP

#include <vector>

class Field {

public:
  Field(std::size_t nElement)
      : size_(nElement),
        values_(nElement) { // Assumption: The default values of a Field are 0
  }
  std::vector<double> &values() { return values_; }
  const std::size_t size() { return size_; }

  // Set all the values of a scalar field to a given value (default is 1.0)
  void setValues(const double value = 1.0) {
    for (std::size_t iElement = 0; iElement < size(); ++iElement) {
      values()[iElement] = value;
    }
  }

private:
  std::size_t size_;
  std::vector<double> values_;
};

#endif // FIELD_HPP