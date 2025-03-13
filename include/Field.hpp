#ifndef FIELD_HPP
#define FIELD_HPP

#include <vector>

class Field {

public:
  Field(std::size_t size)
      : nElements_(size),
        values_(size) { // Assumption: The default values of a Field are 0
  }
  std::vector<double> &values() { return values_; }
  const std::size_t nElements() { return nElements_; }

private:
  std::size_t nElements_;
  std::vector<double> values_;
};

#endif // FIELD_HPP