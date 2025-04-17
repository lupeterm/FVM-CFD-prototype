#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <stdexcept>
#include <vector>

template <typename T> class Matrix {
private:
  std::vector<std::vector<T>> data_;
  std::size_t rows_;
  std::size_t cols_;

public:
  // Constructor
  Matrix(std::size_t rows, std::size_t cols, const T &initialValue = T())
      : rows_(rows), cols_(cols),
        data_(rows, std::vector<T>(cols, initialValue)) {}

  // Access element (read/write)
  T &operator()(std::size_t row, std::size_t col) {
    if (row >= rows_ || col >= cols_) {
      throw std::out_of_range("Matrix indices out of range");
    }
    return data_[row][col];
  }

  // Access element (read-only)
  const T &operator()(std::size_t row, std::size_t col) const {
    if (row >= rows_ || col >= cols_) {
      throw std::out_of_range("Matrix indices out of range");
    }
    return data_[row][col];
  }

  // Get number of rows
  std::size_t nRows() const { return rows_; }

  // Get number of columns
  std::size_t nCols() const { return cols_; }

  // Set all elements to a value
  void fill(const T &value) {
    for (std::size_t i = 0; i < rows_; ++i) {
      std::fill(data_[i].begin(), data_[i].end(), value);
    }
  }
};

#endif // MATRIX_HPP