#include <gtest/gtest.h>
#include "add.h"

TEST(AdditionTest, HandlesPositiveInput) {
  EXPECT_EQ(add(1, 2), 3);
}

TEST(AdditionTest, HandlesNegativeInput) {
  EXPECT_EQ(add(-1, -1), -2);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
