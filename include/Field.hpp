#ifndef FIELD_HPP
#define FIELD_HPP

#include <array>
#include <string>
#include <vector>

template <typename T> class Field {

public:
  Field() = default;
  Field(std::size_t nElements) : values_(nElements) {}

  std::vector<T> &values() { return values_; }
  const std::size_t size() { return values_.size(); }

  // Set all the values of a field to a given value
  void set(const T &value) {
    for (std::size_t iElement = 0; iElement < values_.size(); ++iElement) {
      values_[iElement] = value;
    }
  }

  std::string &boundaryType() { return boundaryType_; }

private:
  std::vector<T> values_;
  std::string boundaryType_{""};
};

#endif // FIELD_HPP