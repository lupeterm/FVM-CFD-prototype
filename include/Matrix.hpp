#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <stdexcept>
#include <vector>

template <typename T> class Matrix {
private:
  std::size_t rows_;
  std::size_t cols_;
  std::vector<T> data_; // 1D vector to store the full matrix in row-major order

public:
  // Constructor
  Matrix(std::size_t rows, std::size_t cols);

  // Get number of rows
  std::size_t nRows() const;

  // Get number of columns
  std::size_t nCols() const;

  // Access element (read/write)
  T &operator()(std::size_t row, std::size_t col);

  // Access element (read-only)
  const T &operator()(std::size_t row, std::size_t col) const;

  // Set all elements to a value
  void fill(const T &value);
};

#endif // MATRIX_HPP