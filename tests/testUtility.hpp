#ifndef TEST_UTILITY_HPP
#define TEST_UTILITY_HPP

// #include <array>
#include <cmath>
#include <cstddef>
#include <gtest/gtest.h>
// #include <string>

template <typename T1, typename T2>
inline ::testing::AssertionResult
VectorMatch(const T1 &actual, const T2 &expected, const std::size_t size) {
  for (std::size_t i = 0; i < size; ++i) {
    if (expected[i] != actual[i]) {
      return ::testing::AssertionFailure()
             << "actual[" << i << "] (" << actual[i] << ") != expected[" << i
             << "] (" << expected[i] << ")";
    }
  }
  return ::testing::AssertionSuccess();
}

inline bool AlmostEqualAbsAndRelative(const double &actualValue,
                                      const double &expectedValue,
                                      const double maxDiff,
                                      const double maxRelativeDiff) {

  // Check if the numbers are really close when comparing not very small numbers
  // or comparing against zero
  double absDiff = std::fabs(actualValue - expectedValue);
  if (absDiff <= maxDiff) {
    return true;
  }

  // Check if the numbers are really close when comparing very small non-zero
  // numbers
  auto expectedAbsValue = std::fabs(expectedValue);
  auto actualAbsValue = std::fabs(actualValue);

  if (absDiff <= expectedAbsValue * maxRelativeDiff) {
    return true;
  }
  return false;
}

template <typename T1, typename T2>
inline ::testing::AssertionResult
VectorAlmostEqual(const T1 &actual, const T2 &expected, const std::size_t size,
                  const double maxDiff, const double maxRelativeDiff) {
  for (std::size_t i = 0; i < size; ++i) {
    if (!AlmostEqualAbsAndRelative(actual[i], expected[i], maxDiff,
                                   maxRelativeDiff)) {
      return ::testing::AssertionFailure()
             << "actual[" << i << "] (" << actual[i] << ") != expected[" << i
             << "] (" << expected[i] << ")";
    }
  }
  return ::testing::AssertionSuccess();
}

inline ::testing::AssertionResult
ScalarAlmostEqual(const double &actual, const double &expected,
                  const double maxDiff, const double maxRelativeDiff) {

  if (!AlmostEqualAbsAndRelative(actual, expected, maxDiff, maxRelativeDiff)) {
    return ::testing::AssertionFailure()
           << "actual (" << actual << ") != expected (" << expected << ")";
  }
  return ::testing::AssertionSuccess();
}

#endif // TEST_UTILITY_HPP