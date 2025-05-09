#ifndef FIELD_HPP
#define FIELD_HPP

#include <array>
#include <string>
#include <vector>

template <typename ValueType> class Field {

public:
  Field() = default;
  Field(std::size_t nElements) : values_(nElements) {}

  std::vector<ValueType> &values() { return values_; }
  const std::size_t size() { return values_.size(); }

  // Set all the values of a field to a given value
  void set(const ValueType &value) { values_.assign(values_.size(), value); }

protected:
  std::vector<ValueType> values_;
};

template <typename ValueType> class boundaryField : public Field<ValueType> {
public:
  boundaryField() = default;
  boundaryField(std::size_t nFaces) : Field<ValueType>(nFaces) {}

  std::string &boundaryType() { return boundaryType_; }

private:
  std::string boundaryType_{""};
};

#endif // FIELD_HPP