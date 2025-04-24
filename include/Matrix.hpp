#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>
#include <stdexcept>
#include <tuple> // For COO format
#include <vector>

template <typename T> class Matrix {
private:
  std::size_t rows_;
  std::size_t cols_;
  std::vector<std::tuple<std::size_t, std::size_t, T>> cooData_;

public:
  // Constructor
  Matrix(std::size_t rows, std::size_t cols);

  // Get number of rows
  std::size_t nRows() const;

  // Get number of columns
  std::size_t nCols() const;

  // Write COO format
  void build(std::size_t row, std::size_t col, const T &value);

  // Get value at a specific row and column in COO format
  T getValue(std::size_t row, std::size_t col) const;

  // Set value at a specific row and column in COO format
  void setValue(std::size_t row, std::size_t col, const T &value);
};

#endif // MATRIX_HPP