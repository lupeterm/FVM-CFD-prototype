#ifndef FIELD_HPP
#define FIELD_HPP

#include <vector>

class Field {

public:
  Field(std::size_t size) : nCells_(size), values_(size) {}
  std::vector<double> &values() { return values_; }

private:
  std::size_t nCells_;
  std::vector<double> values_;
};

#endif // FIELD_HPP