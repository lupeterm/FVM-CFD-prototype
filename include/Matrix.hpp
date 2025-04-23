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
  // Constructor to initialize all private data members
  Matrix(std::size_t rows, std::size_t cols)
      : rows_(rows), cols_(cols), cooData_() {
    if (rows_ == 0 || cols_ == 0) {
      throw std::invalid_argument("Matrix dimensions must be non-zero");
    }
  }

  // Get number of rows
  std::size_t nRows() const { return rows_; }

  // Get number of columns
  std::size_t nCols() const { return cols_; }

  // Write COO format
  void build(std::size_t row, std::size_t col, const T &value) {
    if (row >= rows_ || col >= cols_) {
      throw std::out_of_range("Matrix indices out of range");
    }
    cooData_.emplace_back(row, col, value);
  }

  // Get value at a specific row and column in COO format
  T getValue(std::size_t row, std::size_t col) const {
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

  // Set value at a specific row and column in COO format
  void setValue(std::size_t row, std::size_t col, const T &value) {
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
};

#endif // MATRIX_HPP