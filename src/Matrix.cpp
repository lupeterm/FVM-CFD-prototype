#include "Matrix.hpp"
#include <stdexcept>
#include <vector>

// Constructor to initialize all private data members
template <typename T>
Matrix<T>::Matrix(std::size_t rows, std::size_t cols)
    : rows_(rows), cols_(cols), data_(rows * cols, T()) {
  if (rows_ == 0 || cols_ == 0) {
    throw std::invalid_argument("Matrix dimensions must be non-zero");
  }
}

// Get number of rows
template <typename T> std::size_t Matrix<T>::nRows() const { return rows_; }

// Get number of columns
template <typename T> std::size_t Matrix<T>::nCols() const { return cols_; }

// Access element (read/write)
template <typename T>
T &Matrix<T>::operator()(std::size_t row, std::size_t col) {
  if (row >= rows_ || col >= cols_) {
    throw std::out_of_range("Matrix indices out of range");
  }
  return data_[row * cols_ + col];
}

// Access element (read-only)
template <typename T>
const T &Matrix<T>::operator()(std::size_t row, std::size_t col) const {
  if (row >= rows_ || col >= cols_) {
    throw std::out_of_range("Matrix indices out of range");
  }
  return data_[row * cols_ + col];
}

// Set all elements to a value
template <typename T> void Matrix<T>::fill(const T &value) {
  std::fill(data_.begin(), data_.end(), value);
}

// Explicit template instantiation for commonly used types
template class Matrix<double>;
