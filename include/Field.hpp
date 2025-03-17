#ifndef FIELD_HPP
#define FIELD_HPP

#include <array>
#include <vector>

template <typename T> class Field {

public:
  Field(std::size_t nElement)
      : size_(nElement),
        values_(nElement) { // Assumption: The default values of a Field are 0
  }
  std::vector<T> &values() { return values_; }
  const std::size_t size() { return size_; }

  // Set all the values of a field to a given value
  void set(const T &value) {
    for (std::size_t iElement = 0; iElement < size_; ++iElement) {
      values_[iElement] = value;
    }
  }

private:
  std::size_t size_;
  std::vector<T> values_;
};

#endif // FIELD_HPP