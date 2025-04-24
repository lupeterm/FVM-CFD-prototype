#include "Matrix.hpp"
#include <stdexcept>
#include <tuple>
#include <vector>

template <typename T>
Matrix<T>::Matrix(std::size_t rows, std::size_t cols)
    : rows_(rows), cols_(cols), cooData_() {
  if (rows_ == 0 || cols_ == 0) {
    throw std::invalid_argument("Matrix dimensions must be non-zero");
  }
}

template <typename T> std::size_t Matrix<T>::nRows() const { return rows_; }

template <typename T> std::size_t Matrix<T>::nCols() const { return cols_; }

template <typename T>
void Matrix<T>::build(std::size_t row, std::size_t col, const T &value) {
  if (row >= rows_ || col >= cols_) {
    throw std::out_of_range("Matrix indices out of range");
  }
  cooData_.emplace_back(row, col, value);
}

template <typename T>
T Matrix<T>::getValue(std::size_t row, std::size_t col) const {
  if (row >= rows_ || col >= cols_) {
    throw std::out_of_range("Matrix indices out of range");
  }

  for (const auto &[r, c, value] : cooData_) {
    if (r == row && c == col) {
      return value;
    }
  }
  return T(); // Return default value if not found
}

template <typename T>
void Matrix<T>::setValue(std::size_t row, std::size_t col, const T &value) {
  if (row >= rows_ || col >= cols_) {
    throw std::out_of_range("Matrix indices out of range");
  }

  // Check if the value already exists in the COO data
  for (auto &[r, c, existingValue] : cooData_) {
    if (r == row && c == col) {
      existingValue = value; // Update the value
      return;
    }
  }

  // If the value does not exist, add it to the COO data
  cooData_.emplace_back(row, col, value);
}

// Explicit template instantiation for commonly used types
template class Matrix<double>;
